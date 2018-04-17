#ifndef DE_ALPHASONIC_AUTO_MESH_HPP
#define DE_ALPHASONIC_AUTO_MESH_HPP

#include <common/AutoMeshBuffer.hpp>

/*
inline void
enumerateMesh( irr::scene::SMesh & p )
{
    std::cout << "VertexCount = " << p.Vertices.size() << "\n";
    for ( uint32_t i = 0; i < p.Vertices.size(); ++i )
    {
        std::cout << "Vertex[" << i << "]" << toString( p.Vertices[ i ] ) << "\n";
    }

    std::cout << "IndexCount = " << p.Indices.size() << "\n";

    for ( uint32_t i = 0; i < p.Indices.size(); ++i )
    {
        std::cout << "Index[" << i << "]" << p.Indices[ i ] << "\n";
    }

    std::cout << "Material = " << p.Vertices.size() << "\n";
    std::cout << "BoundingBox = " << p.Vertices.size() << "\n";
}
*/

class AutoMesh : public irr::scene::IMesh
{
public:
    //! constructor
    AutoMesh()
    {
        #ifdef _DEBUG
        setDebugName("AutoMesh");
        #endif
        DefaultMaterial.Wireframe = false;
        DefaultMaterial.Lighting = false;
        DefaultMaterial.MaterialType = irr::video::EMT_SOLID;
    }

    //! destructor
    virtual ~AutoMesh()
    {
        for ( irr::u32 i = 0; i < MeshBuffers.size(); ++i )
        {
            AutoMeshBuffer* p = MeshBuffers[ i ];
            if ( p )
            {
                p->drop();
            }
        }
    }

    //! clean mesh
    virtual void clear()
    {
        for ( irr::u32 i = 0; i < MeshBuffers.size(); ++i )
        {
            AutoMeshBuffer* p = MeshBuffers[ i ];
            if ( p )
            {
                p->drop();
            }
        }
        MeshBuffers.clear();
        BoundingBox.reset ( 0.f, 0.f, 0.f );
    }

    virtual irr::u32 getMaterialCount() const
    {
        return getMeshBufferCount();
    }

    virtual irr::video::SMaterial & getMaterial( irr::u32 i )
    {
        if ( i >= getMaterialCount() )
        {
            std::cout << __FUNCTION__ << "(" << i << ") :: [Error] Invalid material index.\n";
            return DefaultMaterial;
        }

        AutoMeshBuffer* p = MeshBuffers[ i ];
        if ( !p )
        {
            std::cout << __FUNCTION__ << "(" << i << ") :: [Error] Invalid pointer to AutoMeshBuffer\n";
            return DefaultMaterial;
        }

        return p->MeshBuffer.Material;
    }

    //! returns amount of mesh buffers.
    virtual irr::u32 getMeshBufferCount() const override
    {
        return static_cast< irr::u32 >( MeshBuffers.size() );
    }

    //! returns pointer to a mesh buffer
    virtual irr::scene::IMeshBuffer* getMeshBuffer( irr::u32 i ) const override
    {
        AutoMeshBuffer* p = MeshBuffers[ i ];
        if ( !p )
        {
            std::cout << __FUNCTION__ << "(" << i << ") :: [Error] Invalid pointer to AutoMeshBuffer\n";
            return nullptr;
        }
        return &(p->MeshBuffer);
    }

    //! returns a meshbuffer which fits a material
    /** reverse search */
    virtual irr::scene::IMeshBuffer* getMeshBuffer( irr::video::SMaterial const & material ) const override
    {
        for ( irr::s32 i = (irr::s32)MeshBuffers.size() - 1; i >= 0; --i )
        {
            AutoMeshBuffer* p = MeshBuffers[ i ];
            if ( p && p->MeshBuffer.getMaterial() == material )
            {
                return &(p->MeshBuffer);
            }
        }

        return nullptr;
    }

    //! returns an axis aligned bounding box
    virtual irr::core::aabbox3d<irr::f32> const & getBoundingBox() const override
    {
        return BoundingBox;
    }

    //! set user axis aligned bounding box
    virtual void setBoundingBox( irr::core::aabbox3df const & box ) override
    {
        BoundingBox = box;
    }

    //! recalculates the bounding box
    virtual void recalculateBoundingBox() // override
    {
        if (MeshBuffers.size())
        {
            BoundingBox = MeshBuffers[ 0 ]->getBoundingBox();
            for ( irr::u32 i = 1; i < MeshBuffers.size(); ++i )
            {
                BoundingBox.addInternalBox( MeshBuffers[i]->getBoundingBox() );
            }
        }
        else
            BoundingBox.reset(0.0f, 0.0f, 0.0f);
    }

    //! adds a MeshBuffer
    /** The bounding box is not updated automatically. */
    virtual void addMeshBuffer( irr::scene::IMeshBuffer* buf ) // override
    {
        std::cout << "[Warn] " << __FUNCTION__ << "() :: Should not be called\n";
    }

    //! adds a MeshBuffer
    /** The bounding box is not updated automatically. */
    virtual void addAutoMeshBuffer( AutoMeshBuffer* buf, bool dropAfter = false ) // override
    {
        if ( !buf )
        {
            std::cout << "[Warn] " << __FUNCTION__ << " :: Cannot add nullptr\n";
            return;
        }

        buf->grab();

        if ( MeshBuffers.size() == 0 )
        {
            BoundingBox.reset( buf->getBoundingBox() );
        }
        else
        {
            BoundingBox.addInternalBox( buf->getBoundingBox() );
        }

        MeshBuffers.emplace_back( buf );

        if ( dropAfter )
        {
            buf->drop(); // remove old owner from ref count
        }
    }

    //! sets a flag of all contained materials to a new value
    virtual void setMaterialFlag( irr::video::E_MATERIAL_FLAG flag, bool newvalue) override
    {
        for ( irr::u32 i=0; i<MeshBuffers.size(); ++i )
        {
            getMeshBuffer( i )->getMaterial().setFlag( flag, newvalue );
        }
    }

    //! set the hardware mapping hint, for driver
    virtual void setHardwareMappingHint( irr::scene::E_HARDWARE_MAPPING newMappingHint, irr::scene::E_BUFFER_TYPE buffer = irr::scene::EBT_VERTEX_AND_INDEX ) override
    {
        for ( irr::u32 i=0; i<MeshBuffers.size(); ++i )
        {
            getMeshBuffer( i )->setHardwareMappingHint( newMappingHint, buffer);
        }
    }

    //! flags the meshbuffer as changed, reloads hardware buffers
    virtual void setDirty( irr::scene::E_BUFFER_TYPE buffer = irr::scene::EBT_VERTEX_AND_INDEX ) override
    {
        for (irr::u32 i=0; i<MeshBuffers.size(); ++i)
        {
            getMeshBuffer( i )->setDirty(buffer);
        }
    }

    //! The meshbuffers of this mesh
    std::vector< AutoMeshBuffer* > MeshBuffers;

    //! The bounding box of this mesh
    irr::core::aabbox3df BoundingBox;

    irr::video::SMaterial DefaultMaterial;

};

#endif // AUTOMESH_HPP
