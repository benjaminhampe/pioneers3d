#include "createCircle.hpp"

irr::scene::SMeshBuffer* 
createMeshBuffer_Circle( float r, int segments, float x, float y, float z )
{
    if (segments < 3) return nullptr;

    irr::scene::SMeshBuffer* p = new irr::scene::SMeshBuffer();

    const irr::video::SColor white = 0xFFFFFFFF;
    const float phi = (2.0f * irr::core::PI) / (float)segments;

    p->Vertices.push_back( irr::video::S3DVertex( x,y,z, 0,1,0, white, 0.5f, 0.5f ) );

    for ( int i = 0; i < segments; ++i )
    {
        const float w = phi * i;
        const float s = sinf( w );
        const float c = cosf( w );
        p->Vertices.push_back( irr::video::S3DVertex( x + (r*s), y, z + (r*c), 0,1,0, white, 0.5f+(0.5f*s), 0.5f-(0.5f*c) ) );
    }

    p->recalculateBoundingBox();

    /// Connect triangles

    for ( int i = 1; i <= segments; ++i )
    {
        p->Indices.push_back(0);    // M

        if (i==segments)
        {
            p->Indices.push_back(i);    // Ai
            p->Indices.push_back(1);    // Ai+1
        }
        else
        {
            p->Indices.push_back(i);    // Ai
            p->Indices.push_back(i+1);  // Ai+1
        }
    }

    p->Material.Lighting = false;
    p->Material.FogEnable = false;
    p->Material.Wireframe = false;
    p->Material.MaterialType = irr::video::EMT_SOLID;

    return p;
}