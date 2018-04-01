// Copyright (C) 2002-2018 Benjamin Hampe

#ifndef DE_ALPHASONIC_COMMON_CREATE_BOX_MESHBUFFER_HPP
#define DE_ALPHASONIC_COMMON_CREATE_BOX_MESHBUFFER_HPP

#include <common/AutoMeshBuffer.hpp>

/// @brief Create a box with one repeating texture over all 6 planes
inline AutoMeshBuffer *
createBox( glm::vec3 const & pos, glm::vec3 const & size, uint32_t color )
{
    AutoMeshBuffer * p = new AutoMeshBuffer( irr::scene::EPT_TRIANGLES );

    // material
//    if (color.getAlpha()<255)
//        buffer->Material.MaterialType = irr::video::EMT_TRANSPARENT_VERTEX_ALPHA;
//    else
//        buffer->Material.MaterialType = irr::video::EMT_SOLID;

    float const dx = 0.5f*size.x;
    float const dy = 0.5f*size.y;
    float const dz = 0.5f*size.z;

    glm::vec3 const A = pos + glm::vec3(-dx,-dy,-dz);
    glm::vec3 const B = pos + glm::vec3(-dx, dy,-dz);
    glm::vec3 const C = pos + glm::vec3( dx, dy,-dz);
    glm::vec3 const D = pos + glm::vec3( dx,-dy,-dz);
    glm::vec3 const E = pos + glm::vec3(-dx,-dy, dz);
    glm::vec3 const F = pos + glm::vec3(-dx, dy, dz);
    glm::vec3 const G = pos + glm::vec3( dx, dy, dz);
    glm::vec3 const H = pos + glm::vec3( dx,-dy, dz);

    addQuad( *p, E, F, B, A, color ); // n(-1, 0, 0);    // Neg X = EFBA
    addQuad( *p, E, A, D, H, color ); // n( 0,-1, 0);    // Neg Y = EADH
    addQuad( *p, A, B, C, D, color ); // n( 0, 0, -1);   // Neg Z = ABCD
    addQuad( *p, D, C, G, H, color ); // n( 1, 0, 0);    // Pos X = DCGH
    addQuad( *p, B, F, G, C, color ); // n( 0, 1, 0);    // Pos Y = BFGC
    addQuad( *p, H, G, F, E, color ); // n( 0, 0, 1);    // Pos Z = HGFE

    return p;
}

/// @brief Create a box with one repeating texture over all 6 planes
AutoMeshBuffer *
createRotatedBox( glm::vec3 const & pos, glm::vec3 const & size, glm::vec3 const & rot, uint32_t color );

/// @brief Create a box mesh with 6 mesh-buffers and 6 textures
irr::scene::SMesh*
createBoxMesh( 	irr::core::vector3df const& size, // 3d-size
                irr::video::SColor const & color, // vertexcolor
                uint32_t matCount = 6 ); // material count == meshbuffer count


#if 0
//! Create a Box MeshBuffer with one color.
IMeshBuffer*
createBoxMeshBuffer(
    irr::core::vector3df const& size,
    const video::SColor& color,
    bool closeNegX,
    bool closeNegY,
    bool closeNegZ,
    bool closePosX,
    bool closePosY,
    bool closePosZ,
    float thickness,
    video::E_VERTEX_TYPE vType,
    E_PRIMITIVE_TYPE pType,
    u16 lineStipple,
    s32 lineFactor) const
{
    IMeshBuffer* buffer = 0;

    switch (vType)
    {
        case video::EVT_STANDARD: buffer = new SMeshBuffer(); break;
        case video::EVT_2TCOORDS: buffer = new SMeshBufferLightMap(); break;
        case video::EVT_TANGENTS: buffer = new SMeshBufferTangents(); break;
        default: break;
    }

    if (!buffer)
        return 0;



    return buffer;
}


//! Create a Box MeshBuffer with six colors.
IMeshBuffer*
createBoxMeshBuffer(
    irr::core::vector3df const& size,
    const video::SColor& colorNegX,
    const video::SColor& colorNegY,
    const video::SColor& colorNegZ,
    const video::SColor& colorPosX,
    const video::SColor& colorPosY,
    const video::SColor& colorPosZ,
    bool closeNegX,
    bool closeNegY,
    bool closeNegZ,
    bool closePosX,
    bool closePosY,
    bool closePosZ,
    float thickness,
    video::E_VERTEX_TYPE vType,
    E_PRIMITIVE_TYPE pType,
    u16 lineStipple,
    s32 lineFactor) const
{
    IMeshBuffer* buffer = 0;

    switch (vType)
    {
        case video::EVT_STANDARD: buffer = new SMeshBuffer(); break;
        case video::EVT_2TCOORDS: buffer = new SMeshBufferLightMap(); break;
        case video::EVT_TANGENTS: buffer = new SMeshBufferTangents(); break;
        default: break;
    }

    if (!buffer)
        return 0;



    return buffer;
}
#endif

#endif // DE_ALPHASONIC_COMMON_CREATE_BOX_MESHBUFFER_HPP

