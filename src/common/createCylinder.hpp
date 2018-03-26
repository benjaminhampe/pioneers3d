// Copyright (C) 2002-2018 Benjamin Hampe

#ifndef DE_ALPHASONIC_COMMON_CREATE_CYLINDER_HPP
#define DE_ALPHASONIC_COMMON_CREATE_CYLINDER_HPP

#include <common/Types.hpp>
#include <common/sinCosTable.hpp>

inline
irr::scene::SMeshBuffer*
createCylinderHullMeshBuffer(
    float radius,
    float height,
    irr::video::SColor const & color,
    uint32_t tessCircle = 33,
    uint32_t tessHull = 1)
{
    //! hull
    irr::scene::SMeshBuffer* buffer = new irr::scene::SMeshBuffer();
    assert( buffer );

    // common vars and constants
    float const y0 = 0.5f*height;				// top
    float const y1 = -0.5f*height;			// bottom
    float const sx = 1.f / (float)tessCircle;   // value step for circle
    float const sy = 1.f / (float)tessHull;		// value step for hull

    // bbox
    buffer->BoundingBox.reset( irr::core::aabbox3df(-radius,y1,-radius, radius,y0,radius) );

    // material
    if (color.getAlpha()<255)
        buffer->Material.MaterialType = irr::video::EMT_TRANSPARENT_VERTEX_ALPHA;
    else
        buffer->Material.MaterialType = irr::video::EMT_SOLID;

    // memory
    buffer->Vertices.reallocate( (tessCircle+1)*(tessHull+1) );
    buffer->Vertices.set_used( 0 );

    SinCosTablef sincosTable( tessCircle );

    // vertices
    for (uint32_t y=0; y<=tessHull; y++)
    {
        for (uint32_t x=0; x<=tessCircle; x++)
        {
            float const s = sincosTable[x].s;
            float const c = sincosTable[x].c;

            buffer->Vertices.push_back(
                irr::video::S3DVertex(
                    irr::core::vector3df( radius*s, y1 + height*sy*y, radius*c),
                    irr::core::vector3df( s,0,c ),
                    color,
                    irr::core::vector2df( 1.0f-sx*x, 1.0f-sy*y )));
        }
    }

    // indices
    const uint32_t pitch = tessCircle + 1; // vertices per row to skip

    buffer->Indices.reallocate( 6*tessCircle*tessHull );
    buffer->Indices.set_used( 0 );

    for (uint32_t y=0; y<tessHull; y++)
    {
        for (uint32_t x=0; x<tessCircle; x++)
        {
            const uint32_t ix=x+1;
            const uint32_t iy=y+1;
            const uint32_t iA = x + y*pitch;
            const uint32_t iB = x + iy*pitch;
            const uint32_t iC = ix + iy*pitch;
            const uint32_t iD = ix + y*pitch;
            buffer->Indices.push_back(iA);
            buffer->Indices.push_back(iC);
            buffer->Indices.push_back(iB);
            buffer->Indices.push_back(iA);
            buffer->Indices.push_back(iD);
            buffer->Indices.push_back(iC);
        }
    }

    return buffer;
}


#endif // DE_ALPHASONIC_COMMON_CREATE_CYLINDER_HPP

