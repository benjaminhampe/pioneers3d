// Copyright (C) 2002-2018 Benjamin Hampe

#ifndef DE_ALPHASONIC_COMMON_CREATE_TRIANGLE_HPP
#define DE_ALPHASONIC_COMMON_CREATE_TRIANGLE_HPP

#include <common/Types.hpp>

/// @brief Add a triangle as EPT_TRIANGLES to a meshbuffer with one color.
inline void
    addTriangle(
        irr::scene::SMeshBuffer* buffer,
        irr::core::vector3df const & A,
        irr::core::vector3df const & B,
        irr::core::vector3df const & C,
        irr::video::SColor const & color )
{
    assert( buffer );

    // vertex-count before pushing new vertices:
    irr::u32 const vertexCount0 = buffer->Vertices.size();

    // vertices:
    irr::core::vector3df n = (B-A).crossProduct(C-A);
    n.normalize();
    buffer->Vertices.push_back( irr::video::S3DVertex( A, n, color, irr::core::vector2df(0,1) ) );
    buffer->Vertices.push_back( irr::video::S3DVertex( B, n, color, irr::core::vector2df(0.5f,0) ) );
    buffer->Vertices.push_back( irr::video::S3DVertex( C, n, color, irr::core::vector2df(1,1) ) );

    // indices
    buffer->Indices.push_back( vertexCount0 );
    buffer->Indices.push_back( vertexCount0 + 1 );
    buffer->Indices.push_back( vertexCount0 + 2 );

    // bounding-box:
    buffer->BoundingBox.addInternalPoint( A );
    buffer->BoundingBox.addInternalPoint( B );
    buffer->BoundingBox.addInternalPoint( C );
}

/// @brief Add a triangle as EPT_TRIANGLES to a meshbuffer with three colors.
inline void
    addTriangle(
        irr::scene::SMeshBuffer* buffer,
        irr::core::vector3df const & A,
        irr::core::vector3df const & B,
        irr::core::vector3df const & C,
        irr::video::SColor const & colorA,
        irr::video::SColor const & colorB,
        irr::video::SColor const & colorC )
{
    assert( buffer );

    // vertex-count before pushing new vertices:
    irr::u32 const vertexCount0 = buffer->Vertices.size();

    // vertices:
    irr::core::vector3df n = (B-A).crossProduct(C-A);
    n.normalize();
    buffer->Vertices.push_back( irr::video::S3DVertex( A, n, colorA, irr::core::vector2df(0,1) ) );
    buffer->Vertices.push_back( irr::video::S3DVertex( B, n, colorB, irr::core::vector2df(0.5f,0) ) );
    buffer->Vertices.push_back( irr::video::S3DVertex( C, n, colorC, irr::core::vector2df(1,1) ) );

    // indices
    buffer->Indices.push_back( vertexCount0 );
    buffer->Indices.push_back( vertexCount0 + 1 );
    buffer->Indices.push_back( vertexCount0 + 2 );

    // bounding-box:
    buffer->BoundingBox.addInternalPoint( A );
    buffer->BoundingBox.addInternalPoint( B );
    buffer->BoundingBox.addInternalPoint( C );
}

#endif // DE_ALPHASONIC_COMMON_CREATE_TRIANGLE_HPP

