#include <pioneers3d/scene/createHexagonMeshBufferXZ.hpp>

#include <irrlicht.h>

namespace pioneers3d {

irr::core::vector3df
getBoardPositionFromIndex( float w, float h, int i, int j )
{
    float const x = (0.50f * w) * (abs(j) % 2) + w * i;
    float const y = 0.0f; // sqrtf( (float)(i*i + j*j) );
    float const z = (0.75f * h) * j;
    return irr::core::vector3df( x, y, z );
}

/// Hexagon

irr::scene::SMeshBuffer*
createHexagonMeshBufferXZ( float w, float h, float x, float y, float z )
{
    irr::scene::SMeshBuffer* meshBuffer = createMeshBuffer();

    irr::video::SColor const white = 0xFFFFFFFF;

    // Vertices:
    meshBuffer->Vertices.reallocate(6);
    meshBuffer->Vertices.set_used(0);
    meshBuffer->Vertices.push_back( irr::video::S3DVertex( -.50f*w + x, y, 0.25f*h + z, 0,1,0, white, 0.00f,0.75f ) ); // A
    meshBuffer->Vertices.push_back( irr::video::S3DVertex( 0.00f*w + x, y, 0.50f*h + z, 0,1,0, white, 0.50f,1.00f ) ); // B
    meshBuffer->Vertices.push_back( irr::video::S3DVertex( 0.50f*w + x, y, 0.25f*h + z, 0,1,0, white, 1.00f,0.75f ) ); // C
    meshBuffer->Vertices.push_back( irr::video::S3DVertex( 0.50f*w + x, y, -.25f*h + z, 0,1,0, white, 1.00f,0.25f ) ); // D
    meshBuffer->Vertices.push_back( irr::video::S3DVertex( 0.00f*w + x, y, -.50f*h + z, 0,1,0, white, 0.50f,0.00f ) ); // E
    meshBuffer->Vertices.push_back( irr::video::S3DVertex( -.50f*w + x, y, -.25f*h + z, 0,1,0, white, 0.00f,0.25f ) ); // F
    // BBox:
    meshBuffer->recalculateBoundingBox();
    // Indices:
    meshBuffer->Indices.reallocate( 12 );
    meshBuffer->Indices.set_used( 0 );
    // ABC
    meshBuffer->Indices.push_back( 0 );
    meshBuffer->Indices.push_back( 1 );
    meshBuffer->Indices.push_back( 2 );
    // ACD
    meshBuffer->Indices.push_back( 0 );
    meshBuffer->Indices.push_back( 2 );
    meshBuffer->Indices.push_back( 3 );
    // ADF
    meshBuffer->Indices.push_back( 0 );
    meshBuffer->Indices.push_back( 3 );
    meshBuffer->Indices.push_back( 5 );
    // FDE
    meshBuffer->Indices.push_back( 5 );
    meshBuffer->Indices.push_back( 3 );
    meshBuffer->Indices.push_back( 4 );
    return meshBuffer;
}

} // end namespace pioneers3d
