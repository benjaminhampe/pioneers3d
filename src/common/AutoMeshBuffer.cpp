#include "AutoMeshBuffer.hpp"

// static
uint32_t
AutoMeshBuffer::getPrimitiveCount( irr::scene::E_PRIMITIVE_TYPE primitiveType, uint32_t indexCount )
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

#if 0
AutoMeshBuffer::AutoMeshBuffer()
    : PrimitiveType( irr::scene::EPT_POINTS )
    , VertexType( irr::video::EVT_STANDARD )
    , IndexType( irr::video::EIT_16BIT )
    , MeshBuffer()
{
    MeshBuffer.Material.MaterialType = irr::video::EMT_SOLID;
    MeshBuffer.Material.Lighting = false;
    MeshBuffer.Material.FogEnable = false;
//    MeshBuffer.Material.GouraudShading = false;
//    MeshBuffer.Material.BlendOperation = irr::video::EBO_NONE;
//    MeshBuffer.Material.NormalizeNormals = true;
}
#endif
// explicit
AutoMeshBuffer::AutoMeshBuffer(
                    irr::scene::E_PRIMITIVE_TYPE primType,
                    irr::video::E_VERTEX_TYPE vertexType,
                    irr::video::E_INDEX_TYPE indexType )
    : PrimitiveType( primType )
    , VertexType( vertexType )
    , IndexType( indexType )
{
    MeshBuffer.Material.MaterialType = irr::video::EMT_SOLID;
    MeshBuffer.Material.Lighting = false;
    MeshBuffer.Material.FogEnable = false;
//    MeshBuffer.Material.GouraudShading = false;
//    MeshBuffer.Material.BlendOperation = irr::video::EBO_NONE;
//    MeshBuffer.Material.NormalizeNormals = true;
}

AutoMeshBuffer::~AutoMeshBuffer()
{}

uint32_t
AutoMeshBuffer::getPrimitiveCount() const
{
    return getPrimitiveCount( PrimitiveType, MeshBuffer.getIndexCount() );
}

void
AutoMeshBuffer::render( irr::video::IVideoDriver* driver )
{
    driver->setMaterial( MeshBuffer.Material );

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
