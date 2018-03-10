#include "createHexagonMeshBuffer.hpp"

irr::core::vector3df 
getBoardPositionFromIndex( float w, float h, int i, int j )
{
    const float x = (0.50f * w) * (abs(j) % 2) + w * i;
    const float y = 0.0f; // sqrtf( (float)(i*i + j*j) );
    const float z = (0.75f * h) * j;
    return irr::core::vector3df(x, y, z );
}

/// Hexagon

irr::scene::SMeshBuffer* 
createHexagonMeshBuffer( float w, float h, float x, float y, float z )
{
    irr::scene::SMeshBuffer* p = new irr::scene::SMeshBuffer();
    irr::video::SColor white(255,255,255,255);
    p->Vertices.reallocate(6);
    p->Vertices.set_used(0);
    p->Vertices.push_back( irr::video::S3DVertex( -.50f*w + x, y, 0.25f*h + z, 0,1,0, white, 0.00f,0.75f ) ); // A
    p->Vertices.push_back( irr::video::S3DVertex( 0.00f*w + x, y, 0.50f*h + z, 0,1,0, white, 0.50f,1.00f ) ); // B
    p->Vertices.push_back( irr::video::S3DVertex( 0.50f*w + x, y, 0.25f*h + z, 0,1,0, white, 1.00f,0.75f ) ); // C
    p->Vertices.push_back( irr::video::S3DVertex( 0.50f*w + x, y, -.25f*h + z, 0,1,0, white, 1.00f,0.25f ) ); // D
    p->Vertices.push_back( irr::video::S3DVertex( 0.00f*w + x, y, -.50f*h + z, 0,1,0, white, 0.50f,0.00f ) ); // E
    p->Vertices.push_back( irr::video::S3DVertex( -.50f*w + x, y, -.25f*h + z, 0,1,0, white, 0.00f,0.25f ) ); // F
    p->recalculateBoundingBox();

    p->Indices.reallocate(12);
    p->Indices.set_used(0);
    p->Indices.push_back(0); p->Indices.push_back(1); p->Indices.push_back(2); // ABC
    p->Indices.push_back(0); p->Indices.push_back(2); p->Indices.push_back(3); // ACD
    p->Indices.push_back(0); p->Indices.push_back(3); p->Indices.push_back(5); // ADF
    p->Indices.push_back(5); p->Indices.push_back(3); p->Indices.push_back(4); // FDE

    p->Material.MaterialType = irr::video::EMT_SOLID;
    p->Material.FrontfaceCulling = false;
    p->Material.Lighting = false;
    p->Material.FogEnable = false;

    return p;
}