#include "createCircleMeshBufferXZ.hpp"

#include <irrlicht.h>
#include <assert.h>

namespace pioneers3d {

irr::scene::SMeshBuffer*
createCircleMeshBufferXZ( float r, int segments, float center_x, float center_y, float center_z )
{
    assert( r > 0.0f );

    assert( segments >= 3 );

    irr::scene::SMeshBuffer * meshBuffer = createMeshBuffer();

    assert( meshBuffer );

    irr::video::SColor const white = 0xFFFFFFFF;

    float const phi = float( 2.0 * M_PI ) / float(segments);

    assert( phi > 0.001f ); // If not, then fails because of too many vertices for one circle

    // push 3d center point of circle as first vertex
    meshBuffer->Vertices.push_back( irr::video::S3DVertex( center_x, center_y, center_z, 0,1,0, white, 0.5f, 0.5f ) );

    for ( int i = 0; i < segments; ++i )
    {
        float const w = phi * i;
        float const s = sinf( w );
        float const c = cosf( w );
        float const x = center_x + (r * s);
        float const y = center_y;
        float const z = center_z + (r * c);
        float const u = 0.5f + ( 0.5f * s );
        float const v = 0.5f - ( 0.5f * c );
        meshBuffer->Vertices.push_back( irr::video::S3DVertex( x, y, z, 0, 1, 0, white, u, v ) );
    }

    meshBuffer->recalculateBoundingBox();

    // IndexList: Connect vertex-list as triangles ( center-point always reused and two neighbours )
    // so at this point an indexed based mesh is already better than a trianglelist for a circle.
    for ( int i = 1; i <= segments; ++i )
    {
        meshBuffer->Indices.push_back( 0 );    	// center point M

        if ( i == segments )
        {
            meshBuffer->Indices.push_back(i);   // Ai
            meshBuffer->Indices.push_back(1);   // Ai+1
        }
        else
        {
            meshBuffer->Indices.push_back(i);   // Ai
            meshBuffer->Indices.push_back(i+1); // Ai+1
        }
    }

    return meshBuffer;
}

} // end namespace pioneers3d
