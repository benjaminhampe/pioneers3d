#include "createCircle.hpp"

#include <irrlicht.h>
#include <assert.h>

AutoMeshBuffer*
createCircleXY( float r, int segments, float center_x, float center_y, float center_z )
{
    assert( r > 0.0f );

    assert( segments >= 3 );

    AutoMeshBuffer* p = new AutoMeshBuffer();

    assert( p );

    p->PrimitiveType = irr::scene::EPT_TRIANGLES;

    float const phi = float( 2.0 * M_PI ) / float(segments);

    assert( phi > 0.001f ); // If not, then fails because of too many vertices for one circle

    auto addVertex = [ p ] ( float32_t x, float32_t y, float32_t z, float32_t u, float32_t v )
    {
        p->MeshBuffer.Vertices.push_back( irr::video::S3DVertex( x, y, z, 0, 1, 0, 0xFFFFFFEE, u, v ) );
    };

    // push 3d center point of circle as first vertex
    addVertex( center_x, center_y, center_z, 0.5f, 0.5f );

    for ( int i = 0; i < segments; ++i )
    {
        float const w = phi * i;
        float const s = sinf( w );
        float const c = cosf( w );
        float const x = center_x + (r * s);
        float const y = center_y + (r * c);
        float const z = center_z;
        float const u = 0.5f + ( 0.5f * s );
        float const v = 0.5f - ( 0.5f * c );
        addVertex( x, y, z, u, v );
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

    for ( int i = 1; i <= segments; ++i )
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
createCircleXZ( glm::vec3 pos, float r, int segments )
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

    for ( int i = 0; i < segments; ++i )
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

    for ( int i = 1; i <= segments; ++i )
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
