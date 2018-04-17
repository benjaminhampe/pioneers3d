#include "createRect.hpp"

void addRect( AutoMeshBuffer* p, glm::vec3 pos, glm::vec2 size, uint32_t color)
{
    // bbox
    float32_t dx = 0.5f*size.x;
    float32_t dy = 0.5f*size.y;

    uint32_t const n = p->MeshBuffer.Vertices.size();
    p->MeshBuffer.Vertices.push_back( irr::video::S3DVertex( pos.x - dx, pos.y - dy, pos.z, 0, 0, -1, color, 0.0f, 1.0f ) ); // A=0
    p->MeshBuffer.Vertices.push_back( irr::video::S3DVertex( pos.x - dx, pos.y + dy, pos.z, 0, 0, -1, color, 0.0f, 0.0f ) ); // B=1
    p->MeshBuffer.Vertices.push_back( irr::video::S3DVertex( pos.x + dx, pos.y + dy, pos.z, 0, 0, -1, color, 1.0f, 0.0f ) ); // C=2
    p->MeshBuffer.Vertices.push_back( irr::video::S3DVertex( pos.x + dx, pos.y - dy, pos.z, 0, 0, -1, color, 1.0f, 1.0f ) ); // D=3
    p->MeshBuffer.Indices.push_back( n + 0 );
    p->MeshBuffer.Indices.push_back( n + 1 );
    p->MeshBuffer.Indices.push_back( n + 2 );
    p->MeshBuffer.Indices.push_back( n + 0 );
    p->MeshBuffer.Indices.push_back( n + 2 );
    p->MeshBuffer.Indices.push_back( n + 3 );
}

AutoMeshBuffer* createRect( glm::vec3 pos, glm::vec2 size, uint32_t color )
{
    AutoMeshBuffer* p = new AutoMeshBuffer( irr::scene::EPT_TRIANGLES );

    // bbox
    float32_t dx = 0.5f*size.x;
    float32_t dy = 0.5f*size.y;
    p->MeshBuffer.BoundingBox = irr::core::aabbox3df( pos.x-dx, pos.y-dy, pos.z, pos.x+dx, pos.y+dy, pos.z);

    // material
    p->setDefaultMaterialType( color );

    // vertices
    p->MeshBuffer.Vertices.reallocate( 4 );
    p->MeshBuffer.Vertices.set_used( 0 );

    auto addVertex = [ p, &pos, color ] ( float32_t x, float32_t y, float32_t z, float32_t u, float32_t v )
    {
        p->MeshBuffer.Vertices.push_back( irr::video::S3DVertex( pos.x + x, pos.y + y, pos.z + z, 0, 0, -1, color, u, v ) );
    };

    addVertex( -dx, -dy, 0.0f, 0.0f, 1.0f ); // A=0
    addVertex( -dx,  dy, 0.0f, 0.0f, 0.0f ); // B=1
    addVertex(  dx,  dy, 0.0f, 1.0f, 0.0f ); // C=2
    addVertex(  dx, -dy, 0.0f, 1.0f, 1.0f ); // D=3

    // indices
    p->MeshBuffer.Indices.reallocate( 6 );
    p->MeshBuffer.Indices.set_used( 0 );

    auto addTriangle = [ p ] ( uint16_t a, uint16_t b, uint16_t c )
    {
        p->MeshBuffer.Indices.push_back( a );
        p->MeshBuffer.Indices.push_back( b );
        p->MeshBuffer.Indices.push_back( c );
    };

    addTriangle( 0, 1, 2 ); 	// ABC = 012
    addTriangle( 0, 2, 3 ); 	// ACD = 023

    return p;
}
