// Copyright (C) 2002-2018 Benjamin Hampe

#ifndef DE_ALPHASONIC_COMMON_CREATE_RECT_HPP
#define DE_ALPHASONIC_COMMON_CREATE_RECT_HPP

#include <common/Types.hpp>

/// @brief Add a rect to a meshbuffer.
inline void addRect(
        irr::scene::SMeshBuffer* buffer,
        float32_t width,
        float32_t height,
        irr::video::SColor const & color )
{

}

/// @brief Add a rect to a meshbuffer.
inline void addRect(
        irr::scene::SMeshBuffer* buffer,
        float32_t width,
        float32_t height,
        irr::video::SColor const & bottomLeftColor = 0xffffffff,
        irr::video::SColor const & topLeftColor = 0xffffffff,
        irr::video::SColor const & topRightColor = 0xffffffff,
        irr::video::SColor const & bottomRightColor = 0xffffffff )
{
    // vertices:
    irr::core::vector3df const n( 0,0,-1 );
    float const w = 0.5f * width;
    float const h = 0.5f * height;
    irr::core::vector3df const A( -w,-h,0 );
    irr::core::vector3df const B( -w, h,0 );
    irr::core::vector3df const C(  w, h,0 );
    irr::core::vector3df const D(  w,-h,0 );
    irr::core::vector2df const uvA( 0,1 );
    irr::core::vector2df const uvB( 0,0 );
    irr::core::vector2df const uvC( 1,0 );
    irr::core::vector2df const uvD( 1,1 );
    buffer->Vertices.push_back( irr::video::S3DVertex( A,n,bottomLeftColor,uvA ) );
    buffer->Vertices.push_back( irr::video::S3DVertex( B,n,topLeftColor,uvB ) );
    buffer->Vertices.push_back( irr::video::S3DVertex( C,n,topRightColor,uvC ) );
    buffer->Vertices.push_back( irr::video::S3DVertex( D,n,bottomRightColor,uvD ) );
    buffer->BoundingBox.addInternalPoint( A );
    buffer->BoundingBox.addInternalPoint( B );
    buffer->BoundingBox.addInternalPoint( C );
    buffer->BoundingBox.addInternalPoint( D );


    buffer->Indices.push_back( 0 );
    buffer->Indices.push_back( 1 );
    buffer->Indices.push_back( 2 );
    buffer->Indices.push_back( 0 );
    buffer->Indices.push_back( 2 );
    buffer->Indices.push_back( 3 );
}

#endif // DE_ALPHASONIC_COMMON_CREATE_RECT_HPP

