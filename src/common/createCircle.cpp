#include "createCircle.hpp"

#include <irrlicht.h>
#include <assert.h>

AutoMeshBuffer*
createCircle( glm::vec3 const & pos, float r, uint32_t segments, uint32_t color )
{
    assert( r > 0.0f );

    assert( segments >= 3 );

    float const phi = float( 2.0 * M_PI ) / float(segments);

    AutoMeshBuffer* p = new AutoMeshBuffer( irr::scene::EPT_TRIANGLES );

    // push center of circle as first vertex
    p->MeshBuffer.Vertices.push_back( irr::video::S3DVertex( pos.x, pos.y, pos.z, 0, 0, -1, color, 0.5f, 0.5f ) );

    for ( uint32_t i = 0; i < segments; ++i )
    {
        float const w = phi * i;
        float const s = sinf( w );
        float const c = cosf( w );
        float const x = pos.x + (r * s);
        float const y = pos.y + (r * c);
        float const z = pos.z;
        float const u = 0.5f + ( 0.5f * s );
        float const v = 0.5f - ( 0.5f * c );
        p->MeshBuffer.Vertices.push_back( irr::video::S3DVertex( x, y, z, 0, 0, -1, color, u, v ) );
    }

    p->MeshBuffer.recalculateBoundingBox();

    // IndexList: Connect vertex-list as triangles ( center-point always reused and two neighbours )
    // so at this point an indexed based mesh is already better than a trianglelist for a circle.

    auto addTriangle = [ p ] ( uint16_t a, uint16_t b, uint16_t c )
    {
        p->MeshBuffer.Indices.push_back( a );
        p->MeshBuffer.Indices.push_back( b );
        p->MeshBuffer.Indices.push_back( c );
    };

    for ( uint32_t i = 1; i <= segments; ++i )
    {
        if ( i == segments )
        {
            addTriangle( 0,i,1 ); // center point M, Ai, Ai+1
        }
        else
        {
            addTriangle( 0,i,i+1 ); // center point M, Ai, Ai+1
        }
    }

    return p;
}

AutoMeshBuffer*
createCircleXZ( glm::vec3 const & pos, float r, uint32_t segments )
{
    assert( r > 0.0f );

    assert( segments >= 3 );

    AutoMeshBuffer* p = new AutoMeshBuffer();
    assert( p );

    p->PrimitiveType = irr::scene::EPT_TRIANGLES;

    float const phi = float( 2.0 * M_PI ) / float(segments);
    assert( phi > 0.001f ); // If not, then fails because of too many vertices for one circle

    auto addVertex = [ p, &pos ] ( float32_t x, float32_t y, float32_t z, float32_t u, float32_t v )
    {
        p->MeshBuffer.Vertices.push_back( irr::video::S3DVertex( pos.x + x, pos.y + y, pos.z + z, 0, 1, 0, 0xFFFFFFEE, u, v ) );
    };

    // push 3d center point of circle as first vertex
    addVertex( 0.0f, 0.0f, 0.0f, 0.5f, 0.5f );

    for ( uint32_t i = 0; i < segments; ++i )
    {
        float const w = phi * i;
        float const s = sinf( w );
        float const c = cosf( w );
        float const u = 0.5f + ( 0.5f * s );
        float const v = 0.5f - ( 0.5f * c );
        addVertex( (r * s), 0.0f, (r * c), u, v );
    }

    p->MeshBuffer.recalculateBoundingBox();

    // IndexList: Connect vertex-list as triangles ( center-point always reused and two neighbours )
    // so at this point an indexed based mesh is already better than a trianglelist for a circle.

    auto addTriangle = [ p ] ( uint16_t a, uint16_t b, uint16_t c )
    {
        p->MeshBuffer.Indices.push_back( a );
        p->MeshBuffer.Indices.push_back( b );
        p->MeshBuffer.Indices.push_back( c );
    };

    for ( uint32_t i = 1; i <= segments; ++i )
    {
        if ( i == segments )
        {
            addTriangle( 0,i,1 ); // center point M, Ai, Ai+1
        }
        else
        {
            addTriangle( 0,i,i+1 ); // center point M, Ai, Ai+1
        }
    }

    return p;
}
