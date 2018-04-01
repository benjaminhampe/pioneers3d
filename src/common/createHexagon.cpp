#include "createHexagon.hpp"

glm::vec3
getHexagonPoint( float w, float h, int i )
{
    switch ( i )
    {
        case 0: return glm::vec3( 0.00f*w, 0.0f, -.50f*h ); // A
        case 1: return glm::vec3( -.50f*w, 0.0f, -.25f*h ); // B
        case 2: return glm::vec3( -.50f*w, 0.0f, 0.25f*h ); // C
        case 3: return glm::vec3( 0.00f*w, 0.0f, 0.50f*h ); // D
        case 4: return glm::vec3( 0.50f*w, 0.0f, 0.25f*h ); // E
        case 5: return glm::vec3( 0.50f*w, 0.0f, -.25f*h ); // F
        default: return glm::vec3( 0,0,0 ); // M
    }
}

AutoMeshBuffer*
createHexagon( float w, float h )
{
    // MeshBuffer
    AutoMeshBuffer* p = new AutoMeshBuffer( irr::scene::EPT_TRIANGLES );

    // Vertices:
    auto addVertex = [ p ] ( float32_t x, float32_t y, float32_t z, float32_t u, float32_t v, bool flipV )
    {
        p->MeshBuffer.Vertices.push_back( irr::video::S3DVertex( x, y, z, 0, 1, 0, 0xFFFFFFEE, u, (flipV) ? 1.0f - v : v ) );
    };

    p->MeshBuffer.Vertices.reallocate(6);
    p->MeshBuffer.Vertices.set_used(0);
    addVertex( 0.00f*w, 0.0f, -.50f*h, 0.50f, 0.00f, true ); // A = 0
    addVertex( -.50f*w, 0.0f, -.25f*h, 0.00f, 0.25f, true ); // B = 1
    addVertex( -.50f*w, 0.0f, 0.25f*h, 0.00f, 0.75f, true ); // C = 2
    addVertex( 0.00f*w, 0.0f, 0.50f*h, 0.50f, 1.00f, true ); // D = 3
    addVertex( 0.50f*w, 0.0f, 0.25f*h, 1.00f, 0.75f, true ); // E = 4
    addVertex( 0.50f*w, 0.0f, -.25f*h, 1.00f, 0.25f, true ); // F = 5

    // Indices ( triangles: ABF, BCE, BEF, CDE ):
    auto addTriangle = [ p ] ( uint16_t a, uint16_t b, uint16_t c )
    {
        p->MeshBuffer.Indices.push_back( a );
        p->MeshBuffer.Indices.push_back( b );
        p->MeshBuffer.Indices.push_back( c );
    };

    p->MeshBuffer.Indices.reallocate( 12 );
    p->MeshBuffer.Indices.set_used( 0 );
    addTriangle( 0,1,5 ); // ABF
    addTriangle( 1,2,4 ); // BCE
    addTriangle( 1,4,5 ); // BEF
    addTriangle( 2,3,4 ); // CDE

    // Return MeshBuffer
    return p;
}

AutoMeshBuffer*
createHafenXZ( float w, float h, int i )
{
    // MeshBuffer
    AutoMeshBuffer* p = new AutoMeshBuffer( irr::scene::EPT_TRIANGLES );

    // Vertices:
    auto addVertex = [ p ] ( float32_t x, float32_t y, float32_t z, float32_t u, float32_t v, bool flipV )
    {
        p->MeshBuffer.Vertices.push_back( irr::video::S3DVertex( x, y, z, 0, 1, 0, 0xFFFFFFEE, u, (flipV) ? 1.0f - v : v ) );
    };

    p->MeshBuffer.Vertices.reallocate(6);
    p->MeshBuffer.Vertices.set_used(0);
    addVertex( 0.00f*w, 0.0f, -.50f*h, 0.50f, 0.00f, true ); // A = 0
    addVertex( -.50f*w, 0.0f, -.25f*h, 0.00f, 0.25f, true ); // B = 1
    addVertex( -.50f*w, 0.0f, 0.25f*h, 0.00f, 0.75f, true ); // C = 2
    addVertex( 0.00f*w, 0.0f, 0.50f*h, 0.50f, 1.00f, true ); // D = 3
    addVertex( 0.50f*w, 0.0f, 0.25f*h, 1.00f, 0.75f, true ); // E = 4
    addVertex( 0.50f*w, 0.0f, -.25f*h, 1.00f, 0.25f, true ); // F = 5

    // Indices ( triangles: ABF, BCE, BEF, CDE ):
    auto addTriangle = [ p ] ( uint16_t a, uint16_t b, uint16_t c )
    {
        p->MeshBuffer.Indices.push_back( a );
        p->MeshBuffer.Indices.push_back( b );
        p->MeshBuffer.Indices.push_back( c );
    };

    p->MeshBuffer.Indices.reallocate( 12 );
    p->MeshBuffer.Indices.set_used( 0 );
    addTriangle( 0,1,5 ); // ABF
    addTriangle( 1,2,4 ); // BCE
    addTriangle( 1,4,5 ); // BEF
    addTriangle( 2,3,4 ); // CDE

    // Return MeshBuffer
    return p;
}
