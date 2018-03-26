// Copyright (C) 2002-2018 Benjamin Hampe

#ifndef DE_ALPHASONIC_COMMON_CREATE_BOX_MESHBUFFER_HPP
#define DE_ALPHASONIC_COMMON_CREATE_BOX_MESHBUFFER_HPP

#include <irrlicht.h>
#include <glm/glm.hpp>

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

