#ifndef DE_ALPHASONIC_AUTO_MESH_BUFFER_HPP
#define DE_ALPHASONIC_AUTO_MESH_BUFFER_HPP

#include <common/Types.hpp>

class AutoMeshBuffer : public irr::IReferenceCounted
{
public:
    static uint32_t
    getPrimitiveCount( irr::scene::E_PRIMITIVE_TYPE primitiveType, uint32_t indexCount )
    {
        switch( primitiveType )
        {
            case irr::scene::EPT_POINTS: return indexCount;
            case irr::scene::EPT_LINES: return indexCount / 2;
            case irr::scene::EPT_LINE_LOOP: return indexCount - 1;
            case irr::scene::EPT_TRIANGLES: return indexCount / 3;
            case irr::scene::EPT_POLYGON: return indexCount;
            case irr::scene::EPT_QUADS: return indexCount / 4;
            default: return 0;
        }
        return 0;
    }

    AutoMeshBuffer()
        : PrimitiveType( irr::scene::EPT_POINTS )
        , VertexType( irr::video::EVT_STANDARD )
        , IndexType( irr::video::EIT_16BIT )
        , MeshBuffer()
    {}

    AutoMeshBuffer( irr::scene::SMeshBuffer && mb,
                    irr::scene::E_PRIMITIVE_TYPE primType = irr::scene::EPT_POINTS,
                    irr::video::E_VERTEX_TYPE vertexType = irr::video::EVT_STANDARD,
                    irr::video::E_INDEX_TYPE indexType = irr::video::EIT_16BIT )
        : PrimitiveType( primType )
        , VertexType( vertexType )
        , IndexType( indexType )
        , MeshBuffer( std::move( mb ) )
    {}

    ~AutoMeshBuffer()
    {}

    uint32_t
    getPrimitiveCount() const
    {
        return getPrimitiveCount( PrimitiveType, MeshBuffer.getIndexCount() );
    }

    void
    render( irr::video::IVideoDriver* driver )
    {
        assert( driver );
        driver->drawVertexPrimitiveList(
            MeshBuffer.getVertices(),
            MeshBuffer.getVertexCount(),
            MeshBuffer.getIndices(),
            getPrimitiveCount(),
            VertexType,
            PrimitiveType,
            IndexType
        );
    }

public:
    irr::scene::E_PRIMITIVE_TYPE PrimitiveType;
    irr::video::E_VERTEX_TYPE VertexType;
    irr::video::E_INDEX_TYPE IndexType;
    irr::scene::SMeshBuffer MeshBuffer;

};

#endif // DE_ALPHASONIC_AUTO_MESH_BUFFER_HPP
