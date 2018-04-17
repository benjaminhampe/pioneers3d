#ifndef AUTOTRIANGLESELECTOR_HPP
#define AUTOTRIANGLESELECTOR_HPP

#include <common/Types.hpp>

//! Interface to return triangles with specific properties.
class AutoTriangleSelector : public virtual irr::scene::ITriangleSelector
{
    irr::scene::ISceneNode* m_SceneNode;
    std::vector< irr::core::triangle3df > m_Triangles;
    irr::core::aabbox3df m_BoundingBox;
public:
    void clear() { m_Triangles.clear(); m_SceneNode = nullptr; }

    //! Get amount of all available triangles in this selector
    void setSceneNode( irr::scene::ISceneNode* node ) { m_SceneNode = node; }

    void addTriangle( irr::core::triangle3df const & triangle ) { m_Triangles.emplace_back( std::move( triangle ) ); }

    void addMeshBuffer( irr::scene::IMeshBuffer* p, irr::scene::E_PRIMITIVE_TYPE primType = irr::scene::EPT_TRIANGLES )
    {
        if ( primType != irr::scene::EPT_TRIANGLES )
        {
            std::cout << "[Warn] " << __FUNCTION__ << " :: Adding incompatible MeshBuffer of primType(" << primType << ")\n";
        }

        uint32_t triCount = p->getIndexCount() / 3;
        for ( uint32_t i = 0; i < triCount; ++i )
        {
            irr::video::S3DVertex* vertices = (irr::video::S3DVertex*)p->getVertices();
            irr::core::vector3df const & A = vertices[ 3*i + 0 ].Pos;
            irr::core::vector3df const & B = vertices[ 3*i + 1 ].Pos;
            irr::core::vector3df const & C = vertices[ 3*i + 2 ].Pos;
            m_Triangles.emplace_back( irr::core::triangle3df( A, B, C ) );
        }
    }
    //! Get amount of all available triangles in this selector
    virtual irr::s32 getTriangleCount() const { return m_Triangles.size(); }

    //! Get scene node associated with a given triangle.
    virtual irr::scene::ISceneNode* getSceneNodeForTriangle( irr::u32 /*triangleIndex*/ ) const { return m_SceneNode; }

    //! Get number of TriangleSelectors that are part of this one
    virtual irr::u32 getSelectorCount() const { return 1; }

    //! Get TriangleSelector based on index based on getSelectorCount
    virtual ITriangleSelector* getSelector( irr::u32 index ) { return nullptr; }

    //! Get TriangleSelector based on index based on getSelectorCount
    virtual const ITriangleSelector* getSelector( irr::u32 index ) const { return nullptr; }

    //! Gets the triangles for one associated node.
    virtual void getTriangles( irr::core::triangle3df* triangles, irr::s32 arraySize,
        irr::s32& outTriangleCount, const irr::core::matrix4* transform=0 ) const override
    {
        irr::u32 cnt = m_Triangles.size();
        if (cnt > (irr::u32)arraySize)
            cnt = (irr::u32)arraySize;

        irr::core::matrix4  mat;
        if (transform)      mat = *transform;
        if (m_SceneNode)    mat *= m_SceneNode->getAbsoluteTransformation();

        for ( irr::u32 i = 0; i < cnt; ++i )
        {
            mat.transformVect( triangles[i].pointA, m_Triangles[i].pointA );
            mat.transformVect( triangles[i].pointB, m_Triangles[i].pointB );
            mat.transformVect( triangles[i].pointC, m_Triangles[i].pointC );
        }

        outTriangleCount = cnt;
    }


//! Gets all triangles which lie within a specific bounding box.
    virtual void getTriangles( irr::core::triangle3df* triangles,
                    irr::s32 arraySize, irr::s32 & outTriangleCount,
                    irr::core::aabbox3d<irr::f32> const & box,
                    irr::core::matrix4 const * transform) const override
    {
        irr::core::matrix4 mat( irr::core::matrix4::EM4CONST_NOTHING );
        irr::core::aabbox3df tBox(box);

        if (m_SceneNode)
        {
            m_SceneNode->getAbsoluteTransformation().getInverse(mat);
            mat.transformBoxEx( tBox );
        }
        if ( transform )    mat = *transform;
        else                mat.makeIdentity();
        if (m_SceneNode)    mat *= m_SceneNode->getAbsoluteTransformation();

        outTriangleCount = 0;

        if ( !tBox.intersectsWithBox( m_BoundingBox ) ) return;

        irr::s32 triangleCount = 0;
        irr::u32 const cnt = m_Triangles.size();
        for ( irr::u32 i = 0; i < cnt; ++i )
        {
            // This isn't an accurate test, but it's fast, and the
            // API contract doesn't guarantee complete accuracy.
            if ( m_Triangles[i].isTotalOutsideBox(tBox) )
               continue;

            triangles[ triangleCount ] = m_Triangles[ i ];
            mat.transformVect( triangles[ triangleCount ].pointA );
            mat.transformVect( triangles[ triangleCount ].pointB );
            mat.transformVect( triangles[ triangleCount ].pointC );

            ++triangleCount;

            if (triangleCount == arraySize)
                break;
        }

        outTriangleCount = triangleCount;
    }


    //! Gets all triangles which have or may have contact with a 3d line.
    virtual void getTriangles( irr::core::triangle3df* triangles,
                    irr::s32 arraySize,
                    irr::s32 & outTriangleCount,
                    irr::core::line3d<irr::f32> const & line,
                    irr::core::matrix4 const * transform) const override
    {
        irr::core::aabbox3d<irr::f32> box( line.start );
        box.addInternalPoint( line.end );

        // TODO: Could be optimized for line a little bit more.
        getTriangles( triangles, arraySize, outTriangleCount, box, transform );
    }
};

#endif // AUTOTRIANGLESELECTOR_HPP
