// Copyright (C) 2002-2013 Benjamin Hampe <BenjaminHampe@gmx.de>
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CGeometryCreatorEx.h"

#include <../source/Irrlicht/os.h>

#include "sinCosTable.h"

namespace irr
{

namespace scene
{

void CGeometryCreatorEx::addToBuffer(const video::S3DVertex& v, SMeshBuffer* Buffer) const
{
	const s32 tnidx = Buffer->Vertices.linear_reverse_search(v);
	const bool alreadyIn = (tnidx != -1);
	u16 nidx = (u16)tnidx;
	if (!alreadyIn)
	{
		nidx = (u16)Buffer->Vertices.size();
		Buffer->Indices.push_back(nidx);
		Buffer->Vertices.push_back(v);
	}
	else
		Buffer->Indices.push_back(nidx);
}

//! Create a Triangle MeshBuffer with one color.
IMeshBuffer* CGeometryCreatorEx::createTriangleMeshBuffer(
	const core::vector3df& A,
	const core::vector3df& B,
	const core::vector3df& C,
	const video::SColor& color,
	f32 thickness,
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


//! Create a Triangle MeshBuffer with 3 colors.
IMeshBuffer* CGeometryCreatorEx::createTriangleMeshBuffer(
	const core::vector3df& A,
	const core::vector3df& B,
	const core::vector3df& C,
	const video::SColor& colorA,
	const video::SColor& colorB,
	const video::SColor& colorC,
	f32 thickness,
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


//! Create a Rectangular MeshBuffer with one color.
IMeshBuffer* CGeometryCreatorEx::createRectMeshBuffer(
	f32 width,
	f32 height,
	const video::SColor& color,
	f32 thickness,
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


//! Create a Rectangular MeshBuffer with four colors.
IMeshBuffer* CGeometryCreatorEx::createRectMeshBuffer(
	f32 width,
	f32 height,
	const video::SColor& bottomLeftColor,
	const video::SColor& topLeftColor,
	const video::SColor& topRightColor,
	const video::SColor& bottomRightColor,
	f32 thickness,
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


//! Create a RoundRect MeshBuffer with one color.
IMeshBuffer* CGeometryCreatorEx::createRoundRectMeshBuffer(
	f32 width,
	f32 height,
	f32 rx,
	f32 ry,
	const video::SColor& color,
	u32 segments,
	bool bFullyTextured,
	f32 thickness,
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



//! Create a hexagon MeshBuffer with one color.
IMeshBuffer* CGeometryCreatorEx::createHexagonMeshBuffer(
	const core::vector3df& size,
	const video::SColor& color,
	bool closeHull,
	bool closeBottom,
	f32 thickness,
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


//! Create a circle MeshBuffer with one color.
IMeshBuffer* CGeometryCreatorEx::createCircleMeshBuffer(
	f32 radius,
	const video::SColor& color,
	u32 segments,
	u32 tesselation,
	f32 thickness,
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


//! Create a circle MeshBuffer with two colors.
IMeshBuffer* CGeometryCreatorEx::createCircleMeshBuffer(
	f32 radius,
	const video::SColor& outerColor,
	const video::SColor& innerColor,
	u32 segments,
	u32 tesselation,
	f32 thickness,
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


//! Create a ellipse MeshBuffer with one color.
IMeshBuffer* CGeometryCreatorEx::createEllipseMeshBuffer(
	f32 radiusX,
	f32 radiusY,
	const video::SColor& color,
	u32 segments,
	u32 tesselation,
	f32 thickness,
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


//! Create a ellipse MeshBuffer with two colors.
IMeshBuffer* CGeometryCreatorEx::createEllipseMeshBuffer(
	f32 radiusX,
	f32 radiusY,
	const video::SColor& outerColor,
	const video::SColor& innerColor,
	u32 segments,
	u32 tesselation,
	f32 thickness,
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


//! Create a ring MeshBuffer with one color.
IMeshBuffer* CGeometryCreatorEx::createRingMeshBuffer(
	f32 outerRadius,
	f32 innerRadius,
	const video::SColor& color,
	bool bRepeatTexture,
	u32 segments,
	u32 tesselation,
	f32 thickness,
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


//! Create a ring MeshBuffer with two colors.
IMeshBuffer* CGeometryCreatorEx::createRingMeshBuffer(
	f32 outerRadius,
	f32 innerRadius,
	const video::SColor& outerColor,
	const video::SColor& innerColor,
	bool bRepeatTexture,
	u32 segments,
	u32 tesselation,
	f32 thickness,
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


//! Create a Arc MeshBuffer with one color.
IMeshBuffer* CGeometryCreatorEx::createArcMeshBuffer(
	f32 outerRadius,
	f32 innerRadius,
	f32 angleStart,
	f32 angleEnd,
	const video::SColor& color,
	bool bRepeatTexture,
	u32 segments,
	u32 tesselation,
	f32 thickness,
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


//! Create a Arc MeshBuffer with two colors.
IMeshBuffer* CGeometryCreatorEx::createArcMeshBuffer(
	f32 outerRadius,
	f32 innerRadius,
	f32 angleStart,
	f32 angleEnd,
	const video::SColor& outerColor,
	const video::SColor& innerColor,
	bool bRepeatTexture,
	u32 segments,
	u32 tesselation,
	f32 thickness,
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


//! Create a cylinder MeshBuffer with one material.
IMeshBuffer* CGeometryCreatorEx::createCylinderMeshBuffer(
	f32 radius,
	f32 height,
	const video::SColor& color,
	u32 tessCircle,
	u32 tessHull,
	bool closeTop,
	bool closeBottom,
	f32 thickness,
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


//! Create a UpperSphereHalf MeshBuffer (skydome) with one color.
IMeshBuffer* CGeometryCreatorEx::createUpperSphereHalfMeshBuffer(
	f32 radius,
	const video::SColor& color,
	u32 tessCircle,
	u32 tessRows,
	f32 thickness,
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


//! Create a LowerSphereHalf MeshBuffer with one color.
IMeshBuffer* CGeometryCreatorEx::createLowerSphereHalfMeshBuffer(
	f32 radius,
	const video::SColor& color,
	u32 tessCircle,
	u32 tessRows,
	f32 thickness,
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

//! Create a Capsule MeshBuffer with one color.
IMeshBuffer* CGeometryCreatorEx::createCapsuleMeshBuffer(
	f32 radius,
	f32 height,
	const video::SColor& color,
	u32 tessCircle,
	u32 tessRows,
	u32 tessHull,
	f32 thickness,
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


//! Create a Tube MeshBuffer with one color.
IMeshBuffer* CGeometryCreatorEx::createTubeMeshBuffer(
	f32 outerRadius,
	f32 innerRadius,
	f32 height,
	const video::SColor& color,
	u32 tessCircle,
	u32 tessHull,
	bool closeTop,
	bool closeBottom,
	bool bRepeatTexture,
	f32 thickness,
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


//! Create a Box MeshBuffer with one color.
IMeshBuffer* CGeometryCreatorEx::createBoxMeshBuffer(
	const core::vector3df& size,
	const video::SColor& color,
	bool closeNegX,
	bool closeNegY,
	bool closeNegZ,
	bool closePosX,
	bool closePosY,
	bool closePosZ,
	f32 thickness,
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
IMeshBuffer* CGeometryCreatorEx::createBoxMeshBuffer(
	const core::vector3df& size,
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
	f32 thickness,
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

//! Create a Torus MeshBuffer with one color.
IMeshBuffer* CGeometryCreatorEx::createTorusMeshBuffer(
			f32 outerRadius,
			f32 innerRadius,
			const video::SColor& color,
			u32 tessOuterRadius,
			u32 tessInnerRadius,
			f32 thickness,
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

//! Create a OuterTorusHalf MeshBuffer with one color.
IMeshBuffer* CGeometryCreatorEx::createOuterTorusHalfMeshBuffer(
			f32 outerRadius,
			f32 innerRadius,
			const video::SColor& color,
			u32 tessOuterRadius,
			u32 tessInnerRadius,
			f32 thickness,
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












IMesh* CGeometryCreatorEx::createTriangleMesh(
		const core::vector3df& A,
		const core::vector3df& B,
		const core::vector3df& C,
		const video::SColor& colorA,
		const video::SColor& colorB,
		const video::SColor& colorC) const
{
	// triangle mesh
	SMesh* mesh = new SMesh();
	if (!mesh)
		return 0;

	// triangle meshbuffer
	SMeshBuffer* buffer = new SMeshBuffer();
	if (!buffer)
		return mesh;

	// material
	if (colorA.getAlpha()<255 || colorB.getAlpha()<255 || colorC.getAlpha()<255)
		buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
	else
		buffer->Material.MaterialType = video::EMT_SOLID;

	// set buffer sizes
	buffer->Vertices.reallocate( 3 );
	buffer->Vertices.set_used( 0 );
	buffer->Indices.reallocate( 3 );
	buffer->Indices.set_used( 0 );

	// normale
	core::vector3df n = (B-A).crossProduct(C-A);
	n.normalize();

	// add data to meshbuffer
	buffer->Vertices.push_back( video::S3DVertex(A,n,colorA,core::vector2df(0,1)) );
	buffer->Vertices.push_back( video::S3DVertex(B,n,colorB,core::vector2df(0.5f,0)) );
	buffer->Vertices.push_back( video::S3DVertex(C,n,colorC,core::vector2df(1,1)) );
	buffer->Indices.push_back( 0 );
	buffer->Indices.push_back( 1 );
	buffer->Indices.push_back( 2 );
	buffer->recalculateBoundingBox();

	// add meshbuffer to mesh
	mesh->addMeshBuffer( buffer );
	buffer->drop();

	// return mesh
	mesh->recalculateBoundingBox();
	mesh->setHardwareMappingHint(EHM_STATIC);
	return mesh;
}

IMesh* CGeometryCreatorEx::createRectMesh(
		f32 width,
		f32 height,
		const video::SColor& bottomLeftColor,
		const video::SColor& topLeftColor,
		const video::SColor& topRightColor,
		const video::SColor& bottomRightColor) const
{
	// triangle mesh
	SMesh* mesh = new SMesh();
	if (!mesh)
		return 0;

	// triangle meshbuffer
	SMeshBuffer* buffer = new SMeshBuffer();
	if (!buffer)
		return mesh;

	// material
	if (bottomLeftColor.getAlpha()<255 || topLeftColor.getAlpha()<255 ||
		topRightColor.getAlpha()<255 || bottomRightColor.getAlpha()<255)
		buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
	else
		buffer->Material.MaterialType = video::EMT_SOLID;

	// set buffer sizes
	buffer->Vertices.reallocate( 4 );
	buffer->Vertices.set_used( 0 );
	buffer->Indices.reallocate( 6 );
	buffer->Indices.set_used( 0 );

	// normale
	const core::vector3df n( 0,0,-1 );
	const f32 w = 0.5f*width;
	const f32 h = 0.5f*height;

	// add data to meshbuffer
	buffer->Vertices.push_back( video::S3DVertex( -w,-h,0,n.X,n.Y,n.Z,bottomLeftColor,0,1 ) );
	buffer->Vertices.push_back( video::S3DVertex( -w, h,0,n.X,n.Y,n.Z,topLeftColor,0,0 ) );
	buffer->Vertices.push_back( video::S3DVertex(  w, h,0,n.X,n.Y,n.Z,topRightColor,1,0 ) );
	buffer->Vertices.push_back( video::S3DVertex(  w,-h,0,n.X,n.Y,n.Z,bottomRightColor,1,1 ) );
	buffer->recalculateBoundingBox();

	buffer->Indices.push_back( 0 );
	buffer->Indices.push_back( 1 );
	buffer->Indices.push_back( 2 );
	buffer->Indices.push_back( 0 );
	buffer->Indices.push_back( 2 );
	buffer->Indices.push_back( 3 );

	// add meshbuffer to mesh
	mesh->addMeshBuffer( buffer );
	buffer->drop();

	// return mesh
	mesh->recalculateBoundingBox();
	mesh->setHardwareMappingHint(EHM_STATIC);
	return mesh;
}

IMesh* CGeometryCreatorEx::createRoundRectMesh(
		f32 width,
		f32 height,
		f32 rx,
		f32 ry,
		u32 tesselation,
		bool bFullyTextured,
		const video::SColor& outlineColor,
		const video::SColor& centerColor) const
{
	SMesh* mesh = new SMesh();
	if (!mesh)
		return 0;

	// tables
	core::CSinTablef sinTable( tesselation, 0.f, .5f*core::PI);
	core::CCosTablef cosTable( tesselation, 0.f, .5f*core::PI);

	SMeshBuffer* buffer = new SMeshBuffer();
	if (buffer)
	{
		// bbox
		buffer->setBoundingBox(
			core::aabbox3df(-0.5f*width, -0.5f*height, 0.0f, 0.5f*width, 0.5f*height, 0.0f) );

		// material
		if (outlineColor.getAlpha()<255 || centerColor.getAlpha()<255)
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		else
			buffer->Material.MaterialType = video::EMT_SOLID;

		const f32 fw = 1.0f/(f32)width;
		const f32 fh = 1.0f/(f32)height;
		const f32 frw = (f32)rx*fw;
		const f32 frh = (f32)ry*fh;
		const f32 fwrw = (f32)(width-rx)*fw;
		const f32 fhrh = (f32)(height-ry)*fh;
		const f32 x = -0.5f*width;
		const f32 y = -0.5f*height;

		// vertices = 12 + 4*tesselation
		buffer->Vertices.reallocate(12 + 4*tesselation);
		buffer->Vertices.set_used(0);

		// indices += 30 + 4*3*(tesselation+1)
		buffer->Indices.reallocate(30 + 4*3*(tesselation+1));
		buffer->Indices.set_used(0);

		const core::vector3df A(x+rx,y+ry,0);
		const core::vector3df B(x+rx,y+height-ry,0);
		const core::vector3df C(x+width-rx,y+height-ry,0);
		const core::vector3df D(x+width-rx,y+ry,0);
		const core::vector3df E(x+rx,y,0);
		const core::vector3df F(x+width-rx,y,0);
		const core::vector3df G(x+rx,y+height,0);
		const core::vector3df H(x+width-rx,y+height,0);
		const core::vector3df I(x+0,y+ry,0);
		const core::vector3df J(x+0,y+height-ry,0);
		const core::vector3df K(x+width,y+height-ry,0);
		const core::vector3df L(x+width,y+ry,0);
		const core::vector3df n(0,0,-1);

		// vertices += 12
		buffer->Vertices.push_back( video::S3DVertex( A,n,centerColor,core::vector2df(frw,fhrh)) ); // A=0
		buffer->Vertices.push_back( video::S3DVertex( B,n,centerColor,core::vector2df(frw,frh)) ); 	// B=1
		buffer->Vertices.push_back( video::S3DVertex( C,n,centerColor,core::vector2df(fwrw,frh)) );	// C=2
		buffer->Vertices.push_back( video::S3DVertex( D,n,centerColor,core::vector2df(fwrw,fhrh)) );// D=3
		buffer->Vertices.push_back( video::S3DVertex( E,n,outlineColor,core::vector2df(frw,1)) ); 	// E=4
		buffer->Vertices.push_back( video::S3DVertex( F,n,outlineColor,core::vector2df(fwrw,1)) ); 	// F=5
		buffer->Vertices.push_back( video::S3DVertex( G,n,outlineColor,core::vector2df(frw,0)) ); 	// G=6
		buffer->Vertices.push_back( video::S3DVertex( H,n,outlineColor,core::vector2df(fwrw,0)) ); 	// H=7
		buffer->Vertices.push_back( video::S3DVertex( I,n,outlineColor,core::vector2df(0,fhrh)) ); 	// I=8
		buffer->Vertices.push_back( video::S3DVertex( J,n,outlineColor,core::vector2df(0,frh)) ); 	// J=9
		buffer->Vertices.push_back( video::S3DVertex( K,n,outlineColor,core::vector2df(1,frh)) ); 	// K=A
		buffer->Vertices.push_back( video::S3DVertex( L,n,outlineColor,core::vector2df(1,fhrh)) ); 	// L=B

		// indices += 30
		buffer->Indices.push_back(0);	buffer->Indices.push_back(1);	buffer->Indices.push_back(2); // ABC = 012
		buffer->Indices.push_back(0);	buffer->Indices.push_back(2);	buffer->Indices.push_back(3); // ACD = 023
		buffer->Indices.push_back(1);	buffer->Indices.push_back(6);	buffer->Indices.push_back(7); // BGH = 167
		buffer->Indices.push_back(1);	buffer->Indices.push_back(7);	buffer->Indices.push_back(2); // BHC = 172
		buffer->Indices.push_back(4);	buffer->Indices.push_back(0);	buffer->Indices.push_back(3); // EAD = 403
		buffer->Indices.push_back(4);	buffer->Indices.push_back(3);	buffer->Indices.push_back(5); // EDF = 435
		buffer->Indices.push_back(8);	buffer->Indices.push_back(9);	buffer->Indices.push_back(1); // IJB = 891
		buffer->Indices.push_back(8);	buffer->Indices.push_back(1);	buffer->Indices.push_back(0); // IBA = 810
		buffer->Indices.push_back(3);	buffer->Indices.push_back(2);	buffer->Indices.push_back(10);// DCK = 32A
		buffer->Indices.push_back(3);	buffer->Indices.push_back(10);	buffer->Indices.push_back(11);// DKL = 3AB

		const u32 INDEX_A = 0;
		const u32 INDEX_B = 1;
		const u32 INDEX_C = 2;
		const u32 INDEX_D = 3;
		const u32 INDEX_E = 4;
		const u32 INDEX_F = 5;
		const u32 INDEX_G = 6;
		const u32 INDEX_H = 7;
		const u32 INDEX_I = 8;
		const u32 INDEX_J = 9;
		const u32 INDEX_K = 10;
		const u32 INDEX_L = 11;

		//! topLeft BJG quarter circle
		// vertices += tesselation
		u32 k=buffer->Vertices.size();
		for (u32 i=0; i<tesselation; i++)
		{
			f32 x = buffer->Vertices[INDEX_B].Pos.X - rx*cosTable[i];
			f32 y = buffer->Vertices[INDEX_B].Pos.Y + ry*sinTable[i];
			f32 z = buffer->Vertices[INDEX_B].Pos.Z;
			f32 u = (f32)rx*(1.0f-cosTable[i])/(f32)width;
			f32 v = (f32)ry*(1.0f-sinTable[i])/(f32)height;
			buffer->Vertices.push_back(video::S3DVertex( x, y,	z, 0, 0, -1, outlineColor, u, v ));
		}
		// indices += 3*(tesselation+1)
		for (u32 i=0; i<tesselation+1; i++)
		{
			s32 a,b,c;
			if (i==0) 					{ a = INDEX_B; b = INDEX_J; c = k; }
			else if (i==tesselation) 	{ a = INDEX_B; b = k+i-1; c = INDEX_G; }
			else 						{ a = INDEX_B; b = k+i-1; c = k+i; }
			buffer->Indices.push_back(a);
			buffer->Indices.push_back(b);
			buffer->Indices.push_back(c);
		}

		//! topRight CHK quarter circle
		// vertices += tesselation
		k=buffer->Vertices.size();
		for (u32 i=0; i<tesselation; i++)
		{
			f32 x = buffer->Vertices[INDEX_C].Pos.X + rx*cosTable[i];
			f32 y = buffer->Vertices[INDEX_C].Pos.Y + ry*sinTable[i];
			f32 z = buffer->Vertices[INDEX_C].Pos.Z;
			f32 u = 1.0f-(f32)rx*(1.0f-cosTable[i])/(f32)width;
			f32 v = (f32)ry*(1.0f-sinTable[i])/(f32)height;
			buffer->Vertices.push_back(video::S3DVertex( x, y,	z, 0, 0, -1, outlineColor, u, v ));
		}
		// indices += 3*(tesselation+1)
		for (u32 i=0; i<tesselation+1; i++)
		{
			s32 a,b,c;
			if (i==0) 					{ a=INDEX_C; b=k; c=INDEX_K; }
			else if (i==tesselation) 	{ a=INDEX_C; b=INDEX_H; c=k+i-1; }
			else 						{ a=INDEX_C; b=k+i; c=k+i-1; }
			buffer->Indices.push_back(a);
			buffer->Indices.push_back(b);
			buffer->Indices.push_back(c);
		}

		//! bottomRight DLF quarter circle
		// vertices += tesselation
		k=buffer->Vertices.size();
		for (u32 i=0; i<tesselation; i++)
		{
			f32 x = buffer->Vertices[INDEX_D].Pos.X + rx*cosTable[i];
			f32 y = buffer->Vertices[INDEX_D].Pos.Y - ry*sinTable[i];
			f32 z = buffer->Vertices[INDEX_D].Pos.Z;
			f32 u = 1.0f-(f32)rx*(1.0f-cosTable[i])/(f32)width;
			f32 v = 1.0f-(f32)ry*(1.0f-sinTable[i])/(f32)height;
			buffer->Vertices.push_back(video::S3DVertex( x, y,	z, 0, 0, -1, outlineColor, u, v ));
		}
		// indices += 3*(tesselation+1)
		for (u32 i=0; i<tesselation+1; i++)
		{
			s32 a,b,c;
			if (i==0) 					{ a=INDEX_D; b=INDEX_L; c=k; }
			else if (i==tesselation) 	{ a=INDEX_D; b=k+i-1; c=INDEX_F; }
			else 						{ a=INDEX_D; b=k+i-1; c=k+i; }
			buffer->Indices.push_back(a);
			buffer->Indices.push_back(b);
			buffer->Indices.push_back(c);
		}

		//! bottomLeft AEI quarter circle
		// vertices += tesselation
		k=buffer->Vertices.size();
		for (u32 i=0; i<tesselation; i++)
		{
			f32 x = buffer->Vertices[INDEX_A].Pos.X - rx*cosTable[i];
			f32 y = buffer->Vertices[INDEX_A].Pos.Y - ry*sinTable[i];
			f32 z = buffer->Vertices[INDEX_A].Pos.Z;
			f32 u = (f32)rx*(1.0f-cosTable[i])/(f32)width;
			f32 v = 1.0f-(f32)ry*(1.0f-sinTable[i])/(f32)height;
			buffer->Vertices.push_back(video::S3DVertex( x, y,	z, 0, 0, -1, outlineColor, u, v ));
		}
		// indices += 3*(tesselation+1)
		for (u32 i=0; i<tesselation+1; i++)
		{
			s32 a,b,c;
			if (i==0) 					{ a=INDEX_A; b=k; c=INDEX_I; }
			else if (i==tesselation) 	{ a=INDEX_A; b=INDEX_E; c=k+i-1; }
			else 						{ a=INDEX_A; b=k+i; c=k+i-1; }
			buffer->Indices.push_back(a);
			buffer->Indices.push_back(b);
			buffer->Indices.push_back(c);
		}

		// add to mesh
		mesh->addMeshBuffer( buffer );
		mesh->setBoundingBox( buffer->getBoundingBox() );
		buffer->drop();
	}

	// return mesh
	mesh->setHardwareMappingHint(EHM_STATIC);
	return mesh;
}

//
//IMesh* CGeometryCreatorEx::createRoundRectMesh(
//		f32 width,
//		f32 height,
//		f32 rx,
//		f32 ry,
//		u32 tesselation,
//		bool bFullyTextured,
//		const video::SColor& outlineColor,
//		const video::SColor& centerColor) const
//{
//	SMesh* mesh = new SMesh();
//	if (!mesh)
//		return 0;
//
//	SMeshBuffer* buffer = new SMeshBuffer();
//	if (!buffer)
//		return mesh;
//
//	// tables
//	core::CSinTablef sinTable(tesselation);
//	core::CCosTablef cosTable(tesselation);
//
//	// material
//	if (outlineColor.getAlpha()<255 || centerColor.getAlpha()<255)
//		buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
//	else
//		buffer->Material.MaterialType = video::EMT_SOLID;
//
//	const f32& w = width;
//	const f32& h = height;
//	const f32 fw = 1.0f/(f32)w;
//	const f32 fh = 1.0f/(f32)h;
//	const f32 frw = (f32)rx*fw;
//	const f32 frh = (f32)ry*fh;
//	const f32 fwrw = (f32)(w-rx)*fw;
//	const f32 fhrh = (f32)(h-ry)*fh;
//	const f32 x = -0.5f*width;
//	const f32 y = -0.5f*height;
//	// vertices
//	buffer->Vertices.clear();
//	// buffer->Vertices.reallocate(3*(2*5+(tesselation*4)));
//	// buffer->Vertices.set_used(0)
//	buffer->Vertices.push_back( video::S3DVertex( x+rx, y+ry, 0,0,0, -1, centerColor, frw, fhrh)); 	// A=0
//	buffer->Vertices.push_back( video::S3DVertex( x+rx, y+h-ry, 0,0,0, -1, centerColor, frw, frh )); 	// B=1
//	buffer->Vertices.push_back( video::S3DVertex( x+w-rx, y+h-ry, 0,0,0, -1, centerColor, fwrw, frh ));	// C=2
//	buffer->Vertices.push_back( video::S3DVertex( x+w-rx, y+ry, 0,0,0, -1, centerColor, fwrw, fhrh )); 	// D=3
//	buffer->Vertices.push_back( video::S3DVertex( x+rx,	y+0, 0,0,0, -1, outlineColor, frw, 1 )); 		// E=4
//	buffer->Vertices.push_back( video::S3DVertex( x+w-rx, y+0, 0,0,0, -1, outlineColor, fwrw, 1 )); 	// F=5
//	buffer->Vertices.push_back( video::S3DVertex( x+rx,	 y+h, 0,0,0, -1, outlineColor, frw, 0 )); 		// G=6
//	buffer->Vertices.push_back( video::S3DVertex( x+w-rx, y+h, 0,0,0, -1, outlineColor, fwrw, 0 )); 	// H=7
//	buffer->Vertices.push_back( video::S3DVertex( x+0,	y+ry, 0,0,0, -1, outlineColor, 0,	fhrh )); 	// I=8
//	buffer->Vertices.push_back( video::S3DVertex( x+0, 	y+h-ry, 0,0,0, -1, outlineColor, 0,	frh )); 	// J=9
//	buffer->Vertices.push_back( video::S3DVertex( x+w,	y+h-ry, 0,0,0, -1, outlineColor, 1,	frh )); 	// K=A
//	buffer->Vertices.push_back( video::S3DVertex( x+w,	y+ry, 0,0,0, -1, outlineColor, 1,	fhrh )); 	// L=B
//
//	// indices
//	// buffer->Indices.reallocate(3*(2*5+(tesselation*4)));
//	buffer->Indices.push_back(0);	buffer->Indices.push_back(1);	buffer->Indices.push_back(2); // ABC = 012
//	buffer->Indices.push_back(0);	buffer->Indices.push_back(2);	buffer->Indices.push_back(3); // ACD = 023
//	buffer->Indices.push_back(1);	buffer->Indices.push_back(6);	buffer->Indices.push_back(7); // BGH = 167
//	buffer->Indices.push_back(1);	buffer->Indices.push_back(7);	buffer->Indices.push_back(2); // BHC = 172
//	buffer->Indices.push_back(4);	buffer->Indices.push_back(0);	buffer->Indices.push_back(3); // EAD = 403
//	buffer->Indices.push_back(4);	buffer->Indices.push_back(3);	buffer->Indices.push_back(5); // EDF = 435
//	buffer->Indices.push_back(8);	buffer->Indices.push_back(9);	buffer->Indices.push_back(1); // IJB = 891
//	buffer->Indices.push_back(8);	buffer->Indices.push_back(1);	buffer->Indices.push_back(0); // IBA = 810
//	buffer->Indices.push_back(3);	buffer->Indices.push_back(2);	buffer->Indices.push_back(10);// DCK = 32A
//	buffer->Indices.push_back(3);	buffer->Indices.push_back(10);	buffer->Indices.push_back(11);// DKL = 3AB
//
//	f32 phi = 0.5f*core::PI / (f32)tesselation;
//	f32* sinTable = new f32[tesselation-1];
//	f32* cosTable = new f32[tesselation-1];
//	for (u32 i=1; i<tesselation; ++i)
//	{
//		sinTable[i-1] = sinf(phi*(f32)i);
//		cosTable[i-1] = cosf(phi*(f32)i);
//	}
//
//	//! topLeft quarter circle
//	//! topLeft BJG
//	//!	buffer->Indices.push_back(1);	// B
//	//!	buffer->Indices.push_back(9);	// J
//	//!	buffer->Indices.push_back(6);	// G
//	u32 k=buffer->Vertices.size();
//
//	for (u32 i=1; i<tesselation; ++i)
//	{
//		f32 x = buffer->Vertices[1].Pos.X - rx*cosTable[i-1];
//		f32 y = buffer->Vertices[1].Pos.Y + ry*sinTable[i-1];
//		f32 z = buffer->Vertices[1].Pos.Z;
//		f32 u = (f32)rx*(1.0f-cosTable[i-1])/(f32)w;
//		f32 v = (f32)ry*(1.0f-sinTable[i-1])/(f32)h;
//		buffer->Vertices.push_back(video::S3DVertex( x, y,	z, 0, 0, -1, outlineColor, u, v ));
//	}
//	for (u32 i=0; i<tesselation; ++i)
//	{
//		s32 iA,iB,iC;
//		if (i==0) {
//			iA = 1;
//			iB = 9;
//			iC = k;
//		} else if (i==tesselation-1) {
//			iA = 1;
//			iB = k+i-1;
//			iC = 6;
//		} else {
//			iA = 1;
//			iB = k+i-1;
//			iC = k+i;
//		}
//		buffer->Indices.push_back(iA);	// B
//		buffer->Indices.push_back(iB);	// J
//		buffer->Indices.push_back(iC);	// G
//	}
//
//	//! topRight quarter circle
//	//! topRight CHK
//	//!	buffer->Indices.push_back(2);	// C
//	//!	buffer->Indices.push_back(7);	// H
//	//!	buffer->Indices.push_back(10);	// K
//	k=buffer->Vertices.size();
//	for (u32 i=1; i<tesselation; ++i)
//	{
//		f32 x = buffer->Vertices[2].Pos.X + rx*cosTable[i-1];
//		f32 y = buffer->Vertices[2].Pos.Y + ry*sinTable[i-1];
//		f32 z = buffer->Vertices[2].Pos.Z;
//		f32 u = 1.0f-(f32)rx*(1.0f-cosTable[i-1])/(f32)w;
//		f32 v = (f32)ry*(1.0f-sinTable[i-1])/(f32)h;
//		buffer->Vertices.push_back(video::S3DVertex( x, y,	z, 0, 0, -1, outlineColor, u, v ));
//	}
//	for (u32 i=0; i<tesselation; ++i)
//	{
//		s32 iA,iB,iC;
//		if (i==0) {
//			iA = 2;
//			iB = k;
//			iC = 10;
//		} else if (i==tesselation-1) {
//			iA = 2;
//			iB = 7;
//			iC = k+i-1;
//		} else {
//			iA = 2;
//			iB = k+i;
//			iC = k+i-1;
//		}
//		buffer->Indices.push_back(iA);	// B
//		buffer->Indices.push_back(iB);	// J
//		buffer->Indices.push_back(iC);	// G
//	}
//
//	//! bottomRight quarter circle
//	//! bottomRight DLF
//	//!	buffer->Indices.push_back(3);	// D
//	//!	buffer->Indices.push_back(11);	// L
//	//!	buffer->Indices.push_back(5);	// F
//	k=buffer->Vertices.size();
//	for (u32 i=1; i<tesselation; ++i)
//	{
//		f32 x = buffer->Vertices[3].Pos.X + rx*cosTable[i-1];
//		f32 y = buffer->Vertices[3].Pos.Y - ry*sinTable[i-1];
//		f32 z = buffer->Vertices[3].Pos.Z;
//		f32 u = 1.0f-(f32)rx*(1.0f-cosTable[i-1])/(f32)w;
//		f32 v = 1.0f-(f32)ry*(1.0f-sinTable[i-1])/(f32)h;
//		buffer->Vertices.push_back(video::S3DVertex( x, y,	z, 0, 0, -1, outlineColor, u, v ));
//	}
//	for (u32 i=0; i<tesselation; ++i)
//	{
//		s32 iA,iB,iC;
//		if (i==0) {
//			iA = 3;		// D
//			iB = 11;	// L
//			iC = k;		// P_i+1
//		} else if (i==tesselation-1) {
//			iA = 3;		// D
//			iB = k+i-1;	// P_seg-1
//			iC = 5;		// F
//		} else {
//			iA = 3;		// D
//			iB = k+i-1;	// P_seg-1
//			iC = k+i;	// P_i+1
//		}
//		buffer->Indices.push_back(iA);	// D
//		buffer->Indices.push_back(iB);	// L
//		buffer->Indices.push_back(iC);	// F
//	}
//
//
//	//! bottomLeft quarter circle
//	//! bottomLeft AEI
//	//	buffer->Indices.push_back(0);	// A
//	//	buffer->Indices.push_back(4);	// E
//	//	buffer->Indices.push_back(8);	// I
//	k=buffer->Vertices.size();
//	for (u32 i=1; i<tesselation; ++i)
//	{
//		f32 x = buffer->Vertices[0].Pos.X - rx*cosTable[i-1];
//		f32 y = buffer->Vertices[0].Pos.Y - ry*sinTable[i-1];
//		f32 z = buffer->Vertices[0].Pos.Z;
//		f32 u = (f32)rx*(1.0f-cosTable[i-1])/(f32)w;
//		f32 v = 1.0f-(f32)ry*(1.0f-sinTable[i-1])/(f32)h;
//		buffer->Vertices.push_back(video::S3DVertex( x, y,	z, 0, 0, -1, outlineColor, u, v ));
//	}
//	for (u32 i=0; i<tesselation; ++i)
//	{
//		s32 iA,iB,iC;
//		if (i==0) {
//			iA = 0;
//			iB = k;
//			iC = 8;
//		} else if (i==tesselation-1) {
//			iA = 0;
//			iB = 4;
//			iC = k+i-1;
//		} else {
//			iA = 0;
//			iB = k+i;
//			iC = k+i-1;
//		}
//		buffer->Indices.push_back(iA);	// A
//		buffer->Indices.push_back(iB);	// E
//		buffer->Indices.push_back(iC);	// I
//	}
//
//	delete [] sinTable;
//	delete [] cosTable;
//
//	// bbox
//	buffer->recalculateBoundingBox();
//
//	// add to mesh
//	mesh->addMeshBuffer(buffer);
//	mesh->BoundingBox.addInternalBox(buffer->BoundingBox);
//	buffer->drop();
//
//	// return mesh
//	mesh->setHardwareMappingHint(EHM_STATIC);
//	return mesh;
//}

IMesh* CGeometryCreatorEx::createHexagonMesh(
		const core::vector3df& size,
		bool closeHull,
		bool closeBottom,
		const video::SColor& color) const
{
	// mesh
	SMesh* mesh = new SMesh();
	if (!mesh)
		return 0;

	// meshbuffer
	SMeshBuffer* buffer = new SMeshBuffer();
	if (buffer)
	{
		// bbox
		buffer->setBoundingBox( core::aabbox3df( -.5f*size.X,-.5f*size.Y,-.5f*size.Z, .5f*size.X,.5f*size.Y,.5f*size.Z ) );

		// material
		if (color.getAlpha()<255)
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		else
			buffer->Material.MaterialType = video::EMT_SOLID;

		// vertices
		buffer->Vertices.reallocate(6);
		buffer->Vertices.set_used(0);
		buffer->Vertices.push_back( video::S3DVertex( -0.5f*size.X, -0.25f*size.Y, 0, 0,0,-1, color, 0,   0.75f) );
		buffer->Vertices.push_back( video::S3DVertex( -0.5f*size.X,  0.25f*size.Y, 0, 0,0,-1, color, 0,   0.25f) );
		buffer->Vertices.push_back( video::S3DVertex(  0,            0.5f *size.Y, 0, 0,0,-1, color, 0.5f,0    ) );
		buffer->Vertices.push_back( video::S3DVertex(  0.5f*size.X,  0.25f*size.Y, 0, 0,0,-1, color, 1.0f,0.25f) );
		buffer->Vertices.push_back( video::S3DVertex(  0.5f*size.X, -0.25f*size.Y, 0, 0,0,-1, color, 1.0f,0.75f) );
		buffer->Vertices.push_back( video::S3DVertex(  0,           -0.5f *size.Y, 0, 0,0,-1, color, 0.5f,1    ) );

		// indices
		buffer->Indices.reallocate(12);
		buffer->Indices.set_used(0);
		buffer->Indices.push_back( 0 );
		buffer->Indices.push_back( 1 );
		buffer->Indices.push_back( 3 ); // ABD
		buffer->Indices.push_back( 0 );
		buffer->Indices.push_back( 3 );
		buffer->Indices.push_back( 4 ); // ADE
		buffer->Indices.push_back( 1 );
		buffer->Indices.push_back( 2 );
		buffer->Indices.push_back( 3 ); // BCD
		buffer->Indices.push_back( 0 );
		buffer->Indices.push_back( 4 );
		buffer->Indices.push_back( 5 ); // AEF

		// add to mesh
		mesh->addMeshBuffer(buffer);
		mesh->BoundingBox = buffer->getBoundingBox();
		buffer->drop();
	}

	mesh->setHardwareMappingHint(EHM_STATIC);
	return mesh;
}

IMesh* CGeometryCreatorEx::createCircleMesh(
		f32 radius,
		u32 tesselation,
		bool filled,
		const video::SColor& outerColor,
		const video::SColor& innerColor) const
{
	SMesh* mesh = new SMesh();
	if (!mesh)
		return 0;

	SMeshBuffer* buffer = new SMeshBuffer();
	if (buffer)
	{
		// bbox
		buffer->setBoundingBox( core::aabbox3df( -radius,-radius,0, radius,radius,0 ) );

		// memory
		if (filled)	// draw as EPT_TRIANGLES
		{
			buffer->Vertices.reallocate( tesselation+1 );
			buffer->Vertices.set_used( 0 );
			buffer->Indices.reallocate( 3*tesselation );
			buffer->Indices.set_used( 0 );
			//buffer->PrimitiveType = EPT_TRIANGLES;
		}
		else	// draw as EPT_LINE_LOOP
		{
			buffer->Vertices.reallocate( tesselation );
			buffer->Vertices.set_used( 0 );
			buffer->Indices.reallocate( tesselation );
			buffer->Indices.set_used( 0 );
			//buffer->PrimitiveType = EPT_LINE_LOOP;
		}

		// tables
		core::CSinTablef sinTable(tesselation);
		core::CCosTablef cosTable(tesselation);

		// material
		buffer->Material.MaterialType = video::EMT_SOLID;

		if (outerColor.getAlpha()<255)
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;

		if (filled)
		{
			// material
			if (innerColor.getAlpha()<255)
				buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;

			// center vertex
			buffer->Vertices.push_back( video::S3DVertex(0,0,0,0,0,-1,innerColor,0.5f,0.5f) );
		}

		// fill vertices and indices for (tesselation-1) x segments ( either a triangle or only one vertex )
		for (u32 i=0; i<tesselation; ++i)
		{
			const f32 x = -radius * sinTable[i];
			const f32 y = radius * cosTable[i];
			const f32 u = 0.5f-0.5f*sinTable[i];
			const f32 v = 0.5f-0.5f*cosTable[i];
			buffer->Vertices.push_back( video::S3DVertex(x,y,0,0,0,-1,outerColor,u,v) );

			if (filled)
			{
				buffer->Indices.push_back(0);
				u32 j=i+2;
				if (j>=tesselation+1)
					j=1;
				buffer->Indices.push_back(j);
				buffer->Indices.push_back(i+1);
			}
			else
			{
				buffer->Indices.push_back(i);
			}
		}

		// add to mesh
		mesh->addMeshBuffer(buffer);
		core::aabbox3df bbox = mesh->getBoundingBox();
		bbox.addInternalBox( buffer->getBoundingBox() );
		mesh->setBoundingBox( bbox );
		buffer->drop();
	}

	mesh->setHardwareMappingHint(EHM_STATIC);
	return mesh;
}

IMesh* CGeometryCreatorEx::createEllipseMesh(
		f32 radiusX,
		f32 radiusY,
		u32 tesselation,
		const video::SColor& outerColor,
		const video::SColor& innerColor) const
{
	SMesh* mesh = new SMesh();
	if (!mesh)
		return 0;

	SMeshBuffer* buffer = new SMeshBuffer();
	if (buffer)
	{
		// bbox
		buffer->setBoundingBox( core::aabbox3df( -radiusX,-radiusY,0, radiusX,radiusY,0 ) );

		buffer->Vertices.reallocate( tesselation+1 );
		buffer->Vertices.set_used( 0 );
		buffer->Indices.reallocate( 3*tesselation );
		buffer->Indices.set_used( 0 );

		// material
		if (outerColor.getAlpha()<255 || innerColor.getAlpha()<255)
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		else
			buffer->Material.MaterialType = video::EMT_SOLID;

		// center vertex
		buffer->Vertices.push_back( video::S3DVertex(0,0,0,0,0,-1,innerColor,0.5f,0.5f) );

		// tables
		core::CSinTablef sinTable(tesselation);
		core::CCosTablef cosTable(tesselation);

		// fill buffer
		for (u32 i=0; i<tesselation; ++i)
		{
			const f32 x = -radiusX * sinTable[i];
			const f32 y = radiusY * cosTable[i];
			const f32 u = 0.5f-0.5f*sinTable[i];
			const f32 v = 0.5f-0.5f*cosTable[i];
			buffer->Vertices.push_back( video::S3DVertex(x,y,0,0,0,-1,outerColor,u,v) );

			buffer->Indices.push_back(0);
			u32 j=i+2;
			if (j>=tesselation+1)
				j=1;
			buffer->Indices.push_back(j);
			buffer->Indices.push_back(i+1);
		}

		// add to mesh
		mesh->addMeshBuffer(buffer);
		core::aabbox3df bbox = mesh->getBoundingBox();
		bbox.addInternalBox( buffer->getBoundingBox() );
		mesh->setBoundingBox( bbox );
		buffer->drop();
	}

	mesh->setHardwareMappingHint(EHM_STATIC);
	return mesh;
}

IMesh* CGeometryCreatorEx::createRingMesh(
		f32 outerRadius,
		f32 innerRadius,
		u32 tesselation,
		bool bRepeatTexture,
		const video::SColor& outerColor,
		const video::SColor& innerColor) const
{
	SMesh* mesh = new SMesh();
	if (!mesh)
		return 0;

	SMeshBuffer* buffer = new SMeshBuffer();
	if (buffer)
	{
		// bbox
		buffer->setBoundingBox( core::aabbox3df( -outerRadius,-outerRadius,0, outerRadius,outerRadius,0) );

		buffer->Vertices.reallocate( 2*tesselation+2 );
		buffer->Vertices.set_used( 0 );
		buffer->Indices.reallocate( 6*tesselation );
		buffer->Indices.set_used( 0 );

		// material
		if (outerColor.getAlpha()<255 || innerColor.getAlpha()<255)
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		else
			buffer->Material.MaterialType = video::EMT_SOLID;

		// tables
		core::CSinTablef sinTable(tesselation);
		core::CCosTablef cosTable(tesselation);

		// ring vertices
		f32 oi = innerRadius / outerRadius;

		for (u32 i=0; i<tesselation+1; i++)
		{
			const f32& s = -sinTable[i];
			const f32& c = cosTable[i];

			buffer->Vertices.push_back(	video::S3DVertex(
				outerRadius*s,outerRadius*c,0, 0,0,-1, outerColor, .5f+.5f*s, .5f+.5f*c));

			buffer->Vertices.push_back(	video::S3DVertex(
				innerRadius*s,innerRadius*c,0, 0,0,-1, innerColor, .5f+.5f*oi*s, .5f+.5f*oi*c));
		}

		// ring indices
		for (u32 i=0; i<tesselation; i++)
		{
			buffer->Indices.push_back(2*i);			// A
			buffer->Indices.push_back(2*i+1);		// B
			buffer->Indices.push_back(2*(i+1)+1);	// C
			buffer->Indices.push_back(2*i);			// A
			buffer->Indices.push_back(2*(i+1)+1);	// C
			buffer->Indices.push_back(2*(i+1));		// D
		}

		// add to mesh
		mesh->addMeshBuffer(buffer);
		core::aabbox3df bbox = mesh->getBoundingBox();
		bbox.addInternalBox( buffer->getBoundingBox() );
		mesh->setBoundingBox( bbox );
		buffer->drop();

	}
	mesh->setHardwareMappingHint(EHM_STATIC);
	return mesh;
}

IMesh* CGeometryCreatorEx::createArcMesh(
		f32 outerRadius,
		f32 innerRadius,
		f32 angleStart,
		f32 angleEnd,
		u32 tesselation,
		bool bRepeatTexture,
		const video::SColor& outerColor,
		const video::SColor& innerColor) const
{
	SMesh* mesh = new SMesh();
	if (!mesh)
		return 0;

	SMeshBuffer* buffer = new SMeshBuffer();
	if (buffer)
	{
		// bbox
		buffer->setBoundingBox( core::aabbox3df( -outerRadius,-outerRadius,0, outerRadius,outerRadius,0 ) );

		// material
		if ((outerColor.getAlpha()<255) || (innerColor.getAlpha()<255))
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		else
			buffer->Material.MaterialType = video::EMT_SOLID;

		buffer->Vertices.clear();
	//	buffer->Vertices.reallocate();
	//	buffer->Vertices.set_used(0);
		buffer->Indices.clear();
	//	buffer->Indices.reallocate();
	//	buffer->Indices.set_used(0);

		// constants
		const f32 phi = 2.0f*core::PI * (angleEnd-angleStart) / (360.0f * (f32)tesselation);
		const f32 phiStart = 2.0f*core::PI * (angleStart-90.0f) / 360.0f;
		const f32 z = 0.0f;

		// locals
		f32 x0,y0,x1,y1,x2,y2,x3,y3,sinPhi,cosPhi;

		// tables
		f32* sinTable = new f32[tesselation+1];
		f32* cosTable = new f32[tesselation+1];
		for (u32 i=0; i<tesselation+1; ++i)
		{
			const f32 angle = (f32)i*phi + phiStart;
			sinTable[i] = sinf(angle);
			cosTable[i] = cosf(angle);
		}

		// build meshBuffer
		for (u32 i=0; i<tesselation; ++i)
		{
			x0 = -innerRadius * sinTable[i+1];
			y0 =  innerRadius * cosTable[i+1];
			x1 = -outerRadius * sinTable[i+1];
			y1 =  outerRadius * cosTable[i+1];
			x2 = -outerRadius * sinTable[i];
			y2 =  outerRadius * cosTable[i];
			x3 = -innerRadius * sinTable[i];
			y3 =  innerRadius * cosTable[i];

			buffer->Vertices.push_back(video::S3DVertex(x0,y0,z,0,0,-1,innerColor,0,1)); // A
			buffer->Vertices.push_back(video::S3DVertex(x1,y1,z,0,0,-1,outerColor,0,0)); // B
			buffer->Vertices.push_back(video::S3DVertex(x2,y2,z,0,0,-1,outerColor,1,0)); // C
			buffer->Vertices.push_back(video::S3DVertex(x3,y3,z,0,0,-1,innerColor,1,1)); // D
			buffer->Indices.push_back(4*i+0); // A
			buffer->Indices.push_back(4*i+1); // B
			buffer->Indices.push_back(4*i+2); // C
			buffer->Indices.push_back(4*i+0); // A
			buffer->Indices.push_back(4*i+2); // C
			buffer->Indices.push_back(4*i+3); // D
		}

		delete [] sinTable;
		delete [] cosTable;

		// add to mesh
		mesh->addMeshBuffer(buffer);
		core::aabbox3df bbox = mesh->getBoundingBox();
		bbox.addInternalBox( buffer->getBoundingBox() );
		mesh->setBoundingBox( bbox );
		buffer->drop();
	}

	mesh->setHardwareMappingHint(EHM_STATIC);
	return mesh;
}

// berechnet alle Punkte für eine Zylindermantelflaeche
// Die Flaeche besteht aus tessCircle * tessHull Segmenten
// Jedes Segment besteht aus 2 Dreiecken ABC und ACD
// Die Punkte ABCD werden wie folgt berechnet.

IMesh* CGeometryCreatorEx::createCylinderMesh(
		f32 radius,
		f32 height,
		u32 tessCircle,
		u32 tessHull,
		bool closeTop,
		bool closeBottom,
		bool bOneMaterial,
		const video::SColor& color,
		const video::SColor& topColor,
		const video::SColor& bottomColor) const
{
	SMesh* mesh = new SMesh();
	if (!mesh)
		return 0;

	// common vars and constants
	const f32 y0 = 0.5f*height;				// top
	const f32 y1 = -0.5f*height;			// bottom
	const f32 sx = 1.f / (f32)tessCircle;	// angle step for circle
	const f32 sy = 1.f / (f32)tessHull;		// value step for hull
	core::CSinTablef sinTable(tessCircle);	// sin-table
	core::CCosTablef cosTable(tessCircle);	// cos-table

	// bbox
	mesh->BoundingBox.reset( core::aabbox3df(-radius,y1,-radius, radius,y0,radius) );

	//! hull
	SMeshBuffer* buffer = new SMeshBuffer();
	if (buffer)
	{
		// bbox
		buffer->BoundingBox.reset( core::aabbox3df(-radius,y1,-radius,radius,y0,radius) );

		// material
		if (color.getAlpha()<255)
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		else
			buffer->Material.MaterialType = video::EMT_SOLID;

		// memory
		buffer->Vertices.reallocate( (tessCircle+1)*(tessHull+1) );
		buffer->Indices.reallocate( 6*tessCircle*tessHull );
		buffer->Vertices.set_used( 0 );
		buffer->Indices.set_used( 0 );

		// vertices
		for (u32 y=0; y<=tessHull; y++)
		{
			for (u32 x=0; x<=tessCircle; x++)
			{
				const f32& s = sinTable[x];
				const f32& c = cosTable[x];

				buffer->Vertices.push_back(
					video::S3DVertex( radius*s, y1 + height*sy*y, radius*c, s,0,c, color, 1.0f-sx*x, 1.0f-sy*y ) );
			}
		}

		// indices
		const u32 pitch = tessCircle + 1; // vertices per row to skip

		for (u32 y=0; y<tessHull; y++)
		{
			for (u32 x=0; x<tessCircle; x++)
			{
				const u32 ix=x+1;
				const u32 iy=y+1;
				const u32 iA = x + y*pitch;
				const u32 iB = x + iy*pitch;
				const u32 iC = ix + iy*pitch;
				const u32 iD = ix + y*pitch;
				buffer->Indices.push_back(iA);
				buffer->Indices.push_back(iC);
				buffer->Indices.push_back(iB);
				buffer->Indices.push_back(iA);
				buffer->Indices.push_back(iD);
				buffer->Indices.push_back(iC);
			}
		}

		// add to mesh
		mesh->addMeshBuffer(buffer);
//		core::aabbox3df bbox = mesh->getBoundingBox();
//		bbox.addInternalBox( buffer->getBoundingBox() );
//		mesh->setBoundingBox( bbox );
		buffer->drop();
		buffer = 0;
	}

	//! top circle - cannot share vertices with hull, due to texturing and lighting
	if (closeTop)
	{
		buffer = new SMeshBuffer();
		if (buffer)
		{
			// bbox
			buffer->BoundingBox.reset( core::aabbox3df(-radius,y0,-radius,radius,y0,radius) );

			// material
			if (topColor.getAlpha()<255)
				buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
			else
				buffer->Material.MaterialType = video::EMT_SOLID;

			// memory
			buffer->Vertices.reallocate( tessCircle+1 );
			buffer->Vertices.set_used( 0 );
			buffer->Indices.reallocate( 3*tessCircle );
			buffer->Indices.set_used( 0 );

			// center vertex
			buffer->Vertices.push_back( video::S3DVertex(0,y0,0, 0,1,0,topColor,0.5f,0.5f) );

			// vertices + indices
			for (u32 i=0; i<tessCircle; i++)
			{
				const f32 x = radius * sinTable[i];
				const f32 z = radius * cosTable[i];
				const f32 u = 0.5f+0.5f*sinTable[i];
				const f32 v = 0.5f-0.5f*cosTable[i];
				buffer->Vertices.push_back( video::S3DVertex(x,y0,z,0,1,0,topColor,u,v) );

				buffer->Indices.push_back(0);	// push always center vertex
				u32 j=i+2;
				if (j>=tessCircle+1)
					j=1;
				buffer->Indices.push_back(i+1);
				buffer->Indices.push_back(j);
			}

			// add to mesh
			mesh->addMeshBuffer(buffer);
	//		core::aabbox3df bbox = mesh->getBoundingBox();
	//		bbox.addInternalBox( buffer->getBoundingBox() );
	//		mesh->setBoundingBox( bbox );
			buffer->drop();
			buffer = 0;
		}
	}

	//! bottom circle - cannot share vertices with hull, due to texturing and lighting
	if (closeBottom)
	{
		buffer = new SMeshBuffer();
		if (buffer)
		{
			// bbox
			buffer->BoundingBox.reset( core::aabbox3df(-radius,y1,-radius,radius,y1,radius) );

			// material
			if (topColor.getAlpha()<255)
				buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
			else
				buffer->Material.MaterialType = video::EMT_SOLID;

			// memory
			buffer->Vertices.reallocate( tessCircle+1 );
			buffer->Vertices.set_used( 0 );
			buffer->Indices.reallocate( 3*tessCircle );
			buffer->Indices.set_used( 0 );

			// center vertex
			buffer->Vertices.push_back( video::S3DVertex(0,y1,0, 0,-1,0,bottomColor,0.5f,0.5f) );

			// vertices + indices
			for (u32 i=0; i<tessCircle; i++)
			{
				const f32 x = radius * sinTable[i];
				const f32 z = radius * cosTable[i];
				const f32 u = 0.5f+0.5f*sinTable[i];
				const f32 v = 0.5f+0.5f*cosTable[i];
				buffer->Vertices.push_back( video::S3DVertex(x,y1,z,0,-1,0,bottomColor,u,v) );

				buffer->Indices.push_back(0);	// push always center vertex
				u32 j=i+2;
				if (j>=tessCircle+1)
					j=1;
				buffer->Indices.push_back(j);
				buffer->Indices.push_back(i+1);
			}

			// add to mesh
			mesh->addMeshBuffer(buffer);
	//		core::aabbox3df bbox = mesh->getBoundingBox();
	//		bbox.addInternalBox( buffer->getBoundingBox() );
	//		mesh->setBoundingBox( bbox );
			buffer->drop();
			buffer = 0;
		}
	}
	// return mesh
	mesh->setHardwareMappingHint(EHM_STATIC);
	return mesh;
}


IMesh* CGeometryCreatorEx::createEllipsoidMesh(
		f32 radiusX,
		f32 radiusY,
		f32 radiusZ,
		u32 tessX,
		u32 tessY,
		u32 tessZ,
		const video::SColor& color) const
{
	// this function is a working, but temporary solution,
	// so the real algorithm is not implemented yet!
	// it creates a sphere and scales the coords of each vertex to the desired size
	//
	// wikipedia: ellipsoid parameter-form
	//
	// ( a*sin(theta)*cos(phi) 	) 	0<= theta <= pi
	// ( b*sin(theta)*sin(phi) 	) 	0<= phi <= 2*pi
	// ( c*cos(theta) 			)	0<= a,b,c
	//
//
//	// determine the smallest values of the 3 given radiuses
//	f32 radius = core::min_<f32>( radiusX, radiusY, radiusZ );
//
//	// create sphere mesh with the smallest radius
	IMesh* mesh = 0;
//	IMesh* mesh = createSphereMesh( radius, tessX, tessY );
//
//	// abort
//	if (!mesh)
//		return 0;
//
//	// get number of meshbuffer within mesh
//	u32 bufferCount = mesh->getMeshBufferCount();
//
//	// calculate scale factors for each dimension
//	const f32 scaleX = radiusX/radius;
//	const f32 scaleY = radiusY/radius;
//	const f32 scaleZ = radiusZ/radius;
//
//	// loop all internal meshbuffers and scale each vertex
//	for (u32 i=0; i<bufferCount; i++)
//	{
//		scene::IMeshBuffer* buffer = mesh->getMeshBuffer(i);
//		if (buffer)
//		{
//			const u32 vCount = buffer->getVertexCount();
//
//			const video::E_VERTEX_TYPE vType = buffer->getVertexType();
//			switch (vType)
//			{
//				case video::EVT_STANDARD:
//					{	scene::SMeshBuffer* p = (scene::SMeshBuffer*)buffer;
//						for (u32 v=0; v<vCount; v++)
//						{	p->Vertices[v].Pos.X *= scaleX;
//							p->Vertices[v].Pos.Y *= scaleY;
//							p->Vertices[v].Pos.Z *= scaleZ;
//							p->Vertices[v].Color = color;
//							p->Material.MaterialType = (color.getAlpha()<255)?(video::EMT_SOLID):(video::EMT_TRANSPARENT_VERTEX_ALPHA);
//						}
//					}
//					break;
//
//				case video::EVT_2TCOORDS:
//					{	scene::SMeshBufferLightMap* p = (scene::SMeshBufferLightMap*)buffer;
//						for (u32 v=0; v<vCount; v++)
//						{	p->Vertices[v].Pos.X *= scaleX;
//							p->Vertices[v].Pos.Y *= scaleY;
//							p->Vertices[v].Pos.Z *= scaleZ;
//							p->Vertices[v].Color = color;
//						}
//					}
//					break;
//
//				case video::EVT_TANGENTS:
//					{	scene::SMeshBufferTangents* p = (scene::SMeshBufferTangents*)buffer;
//						for (u32 v=0; v<vCount; v++)
//						{	p->Vertices[v].Pos.X *= scaleX;
//							p->Vertices[v].Pos.Y *= scaleY;
//							p->Vertices[v].Pos.Z *= scaleZ;
//							p->Vertices[v].Color = color;
//						}
//					}
//					break;
//
//				default:
//					break;
//			}
//		}
//	}
//
//	mesh->setHardwareMappingHint(EHM_STATIC);
	return mesh;
}

IMesh* CGeometryCreatorEx::createUpperSphereHalfMesh(
		f32 radius,
		u32 tessCircle,
		u32 tessRows,
		const video::SColor& color,
		bool closeBottom) const
{
	SMesh* mesh = new SMesh();
	if (!mesh)
		return 0;

	const f32 sxz = 1.f / (f32)tessCircle;
	const f32 sy = 1.f / (f32)tessRows;

	// tables
	core::CSinTablef sinTableA(tessCircle);
	core::CCosTablef cosTableA(tessCircle);
	core::CSinTablef sinTableB(tessRows, 0.0f, 0.5f*core::PI);
	core::CCosTablef cosTableB(tessRows, 0.0f, 0.5f*core::PI);

	//! upper sphere half
	SMeshBuffer* buffer = new SMeshBuffer();
	if (buffer)
	{
		// bbox
		buffer->BoundingBox = core::aabbox3df( -radius, 0, -radius, radius, radius, radius);

		// material
		if (color.getAlpha()<255)
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		else
			buffer->Material.MaterialType = video::EMT_SOLID;

		buffer->Vertices.clear();
		buffer->Indices.clear();
		// buffer->Vertices.reallocate( (tessCircle+1)*(tessHull+1) );
		// buffer->Indices.reallocate( 6*tessCircle*tessHull );
		// buffer->Vertices.set_used( 0 );
		// buffer->Indices.set_used( 0 );

		for (u32 j=0; j<tessRows; ++j)
		{
			for (u32 i=0; i<tessCircle; ++i)
			{
				const f32 sinA = sinTableA[i];
				const f32 cosA = cosTableA[i];
				const f32 sinB = sinTableB[j];
				const f32 cosB = cosTableB[j];
				const f32 x = -sinA * cosB;				// equals the normal at point radius*(x,y,z)
				const f32 y =  sinB;					// equals the normal at point radius*(x,y,z)
				const f32 z =  cosA * cosB;				// equals the normal at point radius*(x,y,z)
				const f32 u = 0.5f-0.5f*cosB * sinA; // not finished
				const f32 v = 0.5f-0.5f*cosB * cosA; // not finished
				buffer->Vertices.push_back(
					video::S3DVertex( radius*x,radius*y,radius*z, x,y,z, color, u,v ) );
			}
		}

		// push top center vertex
		buffer->Vertices.push_back(video::S3DVertex(0,radius,0, 0,1,0, color, 0.5f,0.5f) );

		// push indices
		for (u32 j=0; j<tessRows; j++)
		{
			for (u32 i=0; i<tessCircle; i++)
			{
				// top row contains just triangles, no quads
				if (j==tessRows-1)
				{
					s32 i0; // A
					s32 i1; // B
					s32 i2 = buffer->Vertices.size()-1; // C - top center

					// border
					if (i==tessCircle-1)
					{
						i0 = (j)*tessCircle + (i);	// A
						i1 = (j)*tessCircle + (0);	// B
					}
					// normal
					else
					{
						i0 = (j)*tessCircle + (i);	// A
						i1 = (j)*tessCircle + (i+1);	// B
					}
					buffer->Indices.push_back((u16)i0); // A
					buffer->Indices.push_back((u16)i2); // C
					buffer->Indices.push_back((u16)i1); // B
				}

				// bottom to top-1 rows consist of quad segments (each of 2 triangles)
				else
				{
					s32 i0;	// A
					s32 i1;	// B
					s32 i2;	// C
					s32 i3;	// D

					// border
					if (i==tessCircle-1)
					{
						i0 = (j)*tessCircle + (i);	// A
						i1 = (j+1)*tessCircle + (i);	// B
						i2 = (j+1)*tessCircle + (0);	// C
						i3 = (j)*tessCircle + (0);	// D
					}
					// normal
					else
					{
						i0 = (j)*tessCircle + (i);	// A
						i1 = (j+1)*tessCircle + (i);	// B
						i2 = (j+1)*tessCircle + (i+1);// C
						i3 = (j)*tessCircle + (i+1);	// D
					}
					buffer->Indices.push_back((u16)i0); // A
					buffer->Indices.push_back((u16)i1); // B
					buffer->Indices.push_back((u16)i2); // C
					buffer->Indices.push_back((u16)i0); // A
					buffer->Indices.push_back((u16)i2); // C
					buffer->Indices.push_back((u16)i3); // D
				}
			}
		}

		// add to mesh
		mesh->addMeshBuffer(buffer);
		core::aabbox3df bbox = mesh->getBoundingBox();
		bbox.addInternalBox( buffer->getBoundingBox() );
		mesh->setBoundingBox( bbox );
		buffer->drop();
		buffer = 0;
	}

	//! bottom circle - cannot share vertices with hull, due to texturing and lighting
	if (closeBottom)
	{
		buffer = new SMeshBuffer();
		if (buffer)
		{
			// bbox
			buffer->BoundingBox.reset( core::aabbox3df(-radius,0,-radius, radius,0,radius) );

			// material
			if (color.getAlpha()<255)
				buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
			else
				buffer->Material.MaterialType = video::EMT_SOLID;

			// memory
			buffer->Vertices.reallocate( tessCircle+1 );
			buffer->Vertices.set_used( 0 );
			buffer->Indices.reallocate( 3*tessCircle );
			buffer->Indices.set_used( 0 );

			// center vertex
			buffer->Vertices.push_back( video::S3DVertex(0,0,0, 0,-1,0,color,0.5f,0.5f) );

			// vertices + indices
			for (u32 i=0; i<tessCircle; i++)
			{
				const f32 x = radius * sinTableA[i];
				const f32 z = radius * cosTableA[i];
				const f32 u = 0.5f+0.5f*sinTableA[i];
				const f32 v = 0.5f+0.5f*cosTableA[i];
				buffer->Vertices.push_back( video::S3DVertex(x,0,z,0,-1,0,color,u,v) );

				buffer->Indices.push_back(0);	// push always center vertex
				u32 j=i+2;
				if (j>=tessCircle+1)
					j=1;
				buffer->Indices.push_back(j);
				buffer->Indices.push_back(i+1);
			}

			mesh->addMeshBuffer(buffer);
			core::aabbox3df bbox = mesh->getBoundingBox();
			bbox.addInternalBox( buffer->getBoundingBox() );
			mesh->setBoundingBox( bbox );
			buffer->drop();
			buffer = 0;
		}
	}

	// exit
	mesh->setHardwareMappingHint(EHM_STATIC);
	return mesh;
}

//!----------------------------------------------------------------------------
//! lower-HalfSphere
//!----------------------------------------------------------------------------

IMesh* CGeometryCreatorEx::createLowerSphereHalfMesh(
		f32 radius,
		u32 tessCircle,
		u32 tessRows,
		const video::SColor& color,
		bool closeTop) const
{
	SMesh* mesh = new SMesh();
	if (!mesh)
		return 0;

	// tables
	core::CSinTablef sinTableA(tessCircle);
	core::CCosTablef cosTableA(tessCircle);
	core::CSinTablef sinTableB(tessRows, 0.0f, 0.5f*core::PI);
	core::CCosTablef cosTableB(tessRows, 0.0f, 0.5f*core::PI);

	const f32 sxz = 1.f / (f32)tessCircle;
	const f32 sy = 1.f / (f32)tessRows;

	//!----------------------------------------------------------------------------
	//! lower-HalfSphere
	//!----------------------------------------------------------------------------

	SMeshBuffer* buffer = new SMeshBuffer();
	if (buffer)
	{
		// bbox
		buffer->BoundingBox = core::aabbox3df( -radius, -radius, -radius, radius, 0, radius);

		// material
		if (color.getAlpha()<255)
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		else
			buffer->Material.MaterialType = video::EMT_SOLID;

		buffer->Vertices.clear();
		buffer->Indices.clear();
		// buffer->Vertices.reallocate( (tessCircle+1)*(tessHull+1) );
		// buffer->Indices.reallocate( 6*tessCircle*tessHull );
		// buffer->Vertices.set_used( 0 );
		// buffer->Indices.set_used( 0 );

		for (u32 j=0; j<tessRows; ++j)
		{
			for (u32 i=0; i<tessCircle; ++i)
			{
				const f32 sinA = sinTableA[i];
				const f32 cosA = cosTableA[i];
				const f32 sinB = sinTableB[j];
				const f32 cosB = cosTableB[j];
				const f32 x = -sinA * cosB;				// equals the normal at point radius*(x,y,z)
				const f32 y = -sinB;					// equals the normal at point radius*(x,y,z)
				const f32 z =  cosA * cosB;				// equals the normal at point radius*(x,y,z)
				const f32 u = 0.5f-0.5f*cosB * sinA; // not finished
				const f32 v = 0.5f+0.5f*cosB * cosA; // not finished
				buffer->Vertices.push_back(
					video::S3DVertex( radius*x,radius*y,radius*z, x,y,z, color, u,v ) );
			}
		}

		// lower-sphere-half bottom center vertex
		buffer->Vertices.push_back( video::S3DVertex(0.f,-radius,0.f, 0.f,-1.f,0.f, color, .5f,.5f) );

		// lower-sphere-half Indices
		for (u32 j=0; j<tessRows; j++)
		{
			for (u32 i=0; i<tessCircle; i++)
			{
				// Top just triangles
				if (j==tessRows-1)
				{
					s32 i0; // A
					s32 i1; // B
					s32 i2 = buffer->Vertices.size()-1; // C - top center

					// border
					if (i==tessCircle-1)
					{
						i0 = (j)*tessCircle + (i);	// A
						i1 = (j)*tessCircle + (0);	// B
					}
					// normal
					else
					{
						i0 = (j)*tessCircle + (i);	// A
						i1 = (j)*tessCircle + (i+1);	// B
					}
					buffer->Indices.push_back((u16)i1); // A
					buffer->Indices.push_back((u16)i2); // C
					buffer->Indices.push_back((u16)i0); // B
				}
				// Bottom to Top-1 consist each of 2 triangles
				else
				{
					s32 i0;	// A
					s32 i1;	// B
					s32 i2;	// C
					s32 i3;	// D

					// border
					if (i==tessCircle-1)
					{
						i0 = (j)*tessCircle + (i);	// A
						i1 = (j+1)*tessCircle + (i);	// B
						i2 = (j+1)*tessCircle + (0);	// C
						i3 = (j)*tessCircle + (0);	// D
					}
					// normal
					else
					{
						i0 = (j)*tessCircle + (i);	// A
						i1 = (j+1)*tessCircle + (i);	// B
						i2 = (j+1)*tessCircle + (i+1);// C
						i3 = (j)*tessCircle + (i+1);	// D
					}
					buffer->Indices.push_back((u16)i2); // A
					buffer->Indices.push_back((u16)i1); // B
					buffer->Indices.push_back((u16)i0); // C
					buffer->Indices.push_back((u16)i3); // A
					buffer->Indices.push_back((u16)i2); // C
					buffer->Indices.push_back((u16)i0); // D
				}
			}
		}

		// add to mesh
		mesh->addMeshBuffer(buffer);
		core::aabbox3df bbox = mesh->getBoundingBox();
		bbox.addInternalBox( buffer->getBoundingBox() );
		mesh->setBoundingBox( bbox );
		buffer->drop();
	}

	//!----------------------------------------------------------------------------
	//! top circle
	//!----------------------------------------------------------------------------

	if (closeTop)
	{
		buffer = new SMeshBuffer();
		if (buffer)
		{
			// bbox
			buffer->setBoundingBox( core::aabbox3df( -radius,0,-radius, radius,0,radius ) );

			// memory
			buffer->Vertices.reallocate( tessCircle+1 );
			buffer->Vertices.set_used( 0 );
			buffer->Indices.reallocate( 3*tessCircle );
			buffer->Indices.set_used( 0 );

			// material
			if (color.getAlpha()<255)
				buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
			else
				buffer->Material.MaterialType = video::EMT_SOLID;

			// center vertex
			buffer->Vertices.push_back( video::S3DVertex(0,0,0,0,1,0,color,0.5f,0.5f) );

			// fill buffer
			for (u32 i=0; i<tessCircle; ++i)
			{
				const f32 x = -radius * sinTableA[i];
				const f32 z =  radius * cosTableA[i];
				const f32 u = 0.5f-0.5f*sinTableA[i];
				const f32 v = 0.5f-0.5f*cosTableA[i];
				buffer->Vertices.push_back( video::S3DVertex( x,0,z, 0,1,0, color, u,v ) );

				buffer->Indices.push_back(0);
				u32 j=i+2;
				if (j>=tessCircle+1)
					j=1;
				buffer->Indices.push_back(j);
				buffer->Indices.push_back(i+1);
			}

			// add to mesh
			mesh->addMeshBuffer(buffer);
			core::aabbox3df bbox = mesh->getBoundingBox();
			bbox.addInternalBox( buffer->getBoundingBox() );
			mesh->setBoundingBox( bbox );
			buffer->drop();
		}
	}

	mesh->setHardwareMappingHint(EHM_STATIC);
	return mesh;
}



IMesh* CGeometryCreatorEx::createCapsuleMesh(
		f32 radius,
		f32 height,
		u32 tessCircle,
		u32 tessRows,
		u32 tessHull,
		bool bOneMaterial,
		const video::SColor& color,
		const video::SColor& topColor,
		const video::SColor& bottomColor) const
{
	SMesh* mesh = new SMesh();
	if (!mesh)
		return 0;

	core::CSinTablef sinTable(tessCircle);
	core::CCosTablef cosTable(tessCircle);
//	const f32 sx = 1.f / (f32)tessCircle;
//	const f32 sy = 1.f / (f32)tessHull;
//	const f32 sxz = 1.f / (f32)tessCircle;
//	const f32 sy = 1.f / (f32)tessRows;
//	const f32 wa = 2.0f*core::PI / (f32)tessCircle; // azimutale angle between r_xz and +z axis [0°..360°]
//	const f32 wb = 0.5f*core::PI / (f32)tessRows;  // polar angle between r_xz and +y axis [0°..90°] ( begin at ground )
	const f32 y0 = -0.5f * height;
	const f32 y1 =  0.5f * height;
	const f32 sxz = 1.f / (f32)tessCircle;
	const f32 sy = 1.f / (f32)tessRows;
	const f32 sy0 = 1.f / (f32)tessHull;
	const f32 wa = 2.0f*core::PI / (f32)tessCircle; // azimutale angle between r_xz and +z axis [0°..360°]
	const f32 wb = 0.5f*core::PI / (f32)tessRows;  // polar angle between r_xz and +y axis [0°..90°] ( begin at top )


	//!----------------------------------------------------------------------------
	//! #1 cylinder hull meshbuffer
	//!----------------------------------------------------------------------------

	SMeshBuffer* buffer = new SMeshBuffer();
	if (buffer)
	{
			// bbox
		mesh->BoundingBox.reset( core::aabbox3df(-radius,y1,-radius, radius,y0,radius) );

		// material
		if (color.getAlpha()<255)
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		else
			buffer->Material.MaterialType = video::EMT_SOLID;

		buffer->Vertices.reallocate( (tessCircle+1)*(tessHull+1) );
		buffer->Indices.reallocate( 6*tessCircle*tessHull );
		buffer->Vertices.set_used( 0 );
		buffer->Indices.set_used( 0 );

		// hull - vertices
		for (u32 y=0; y<=tessHull; y++)
		{
			for (u32 x=0; x<=tessCircle; x++)
			{
				const f32& s = sinTable[x];
				const f32& c = cosTable[x];
				const f32 u = core::clamp( 1.0f-sxz*x, core::ROUNDING_ERROR_f32, 1.0f-core::ROUNDING_ERROR_f32 );
				const f32 v = core::clamp( 1.0f-sy0*y, core::ROUNDING_ERROR_f32, 1.0f-core::ROUNDING_ERROR_f32 );
				buffer->Vertices.push_back(
					video::S3DVertex( radius*s, y0 + height*sy0*y, radius*c, s,0,c, color, u,v  ) );
			}
		}

		const u32 pitch = tessCircle + 1; // vertices per row to skip

		// hull - indices
		for (u32 y=0; y<tessHull; y++)
		{
			for (u32 x=0; x<tessCircle; x++)
			{
				u32 ix=x+1;
				u32 iy=y+1;
				u32 iA = x + y*pitch;
				u32 iB = x + iy*pitch;
				u32 iC = ix + iy*pitch;
				u32 iD = ix + y*pitch;
				buffer->Indices.push_back(iA);
				buffer->Indices.push_back(iC);
				buffer->Indices.push_back(iB);
				buffer->Indices.push_back(iA);
				buffer->Indices.push_back(iD);
				buffer->Indices.push_back(iC);
			}
		}

		// add to mesh
		mesh->addMeshBuffer(buffer);
		core::aabbox3df bbox = mesh->getBoundingBox(); bbox.addInternalBox( buffer->getBoundingBox() );
		mesh->setBoundingBox( bbox );
		buffer->drop();
		buffer = 0;
	}

	//!----------------------------------------------------------------------------
	//! #2 upper-sphere-half
	//!----------------------------------------------------------------------------

	buffer = new SMeshBuffer();
	if (buffer)
	{
		// bbox
		buffer->BoundingBox = core::aabbox3df( -radius, y1, -radius, radius, y1+radius, radius);

		// material
		if (color.getAlpha()<255)
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		else
			buffer->Material.MaterialType = video::EMT_SOLID;

		buffer->Vertices.clear();
		buffer->Indices.clear();
		// buffer->Vertices.reallocate( (tessCircle+1)*(tessHull+1) );
		// buffer->Indices.reallocate( 6*tessCircle*tessHull );
		// buffer->Vertices.set_used( 0 );
		// buffer->Indices.set_used( 0 );

		for (u32 j=0; j<tessRows; ++j)
		{
			for (u32 i=0; i<tessCircle; ++i)
			{
				const f32 sinA = sinf( wa * (f32)i);
				const f32 cosA = cosf( wa * (f32)i);
				const f32 sinB = sinf( wb * (f32)j);
				const f32 cosB = cosf( wb * (f32)j);
				const f32 x = -sinA * cosB;				// equals the normal at point radius*(x,y,z)
				const f32 y =  sinB;					// equals the normal at point radius*(x,y,z)
				const f32 z =  cosA * cosB;				// equals the normal at point radius*(x,y,z)
				const f32 u = core::clamp( 0.5f-0.5f*cosB * sinA, core::ROUNDING_ERROR_f32, 1.0f-core::ROUNDING_ERROR_f32 );
				const f32 v = core::clamp( 0.5f-0.5f*cosB * cosA, core::ROUNDING_ERROR_f32, 1.0f-core::ROUNDING_ERROR_f32 );
				buffer->Vertices.push_back(
					video::S3DVertex( radius*x,y1+radius*y,radius*z, x,y,z, color, u,v ) );
			}
		}

		// push top center vertex
		buffer->Vertices.push_back(video::S3DVertex(0,y1+radius,0, 0,1,0, color, 0.5f,0.5f) );

		// push indices
		for (u32 j=0; j<tessRows; j++)
		{
			for (u32 i=0; i<tessCircle; i++)
			{
				// top row contains just triangles, no quads
				if (j==tessRows-1)
				{
					s32 i0; // A
					s32 i1; // B
					s32 i2 = buffer->Vertices.size()-1; // C - top center

					// border
					if (i==tessCircle-1)
					{
						i0 = (j)*tessCircle + (i);	// A
						i1 = (j)*tessCircle + (0);	// B
					}
					// normal
					else
					{
						i0 = (j)*tessCircle + (i);	// A
						i1 = (j)*tessCircle + (i+1);	// B
					}
					buffer->Indices.push_back((u16)i0); // A
					buffer->Indices.push_back((u16)i2); // C
					buffer->Indices.push_back((u16)i1); // B
				}

				// bottom to top-1 rows consist of quad segments (each of 2 triangles)
				else
				{
					s32 i0;	// A
					s32 i1;	// B
					s32 i2;	// C
					s32 i3;	// D

					// border
					if (i==tessCircle-1)
					{
						i0 = (j)*tessCircle + (i);	// A
						i1 = (j+1)*tessCircle + (i);	// B
						i2 = (j+1)*tessCircle + (0);	// C
						i3 = (j)*tessCircle + (0);	// D
					}
					// normal
					else
					{
						i0 = (j)*tessCircle + (i);	// A
						i1 = (j+1)*tessCircle + (i);	// B
						i2 = (j+1)*tessCircle + (i+1);// C
						i3 = (j)*tessCircle + (i+1);	// D
					}
					buffer->Indices.push_back((u16)i0); // A
					buffer->Indices.push_back((u16)i1); // B
					buffer->Indices.push_back((u16)i2); // C
					buffer->Indices.push_back((u16)i0); // A
					buffer->Indices.push_back((u16)i2); // C
					buffer->Indices.push_back((u16)i3); // D
				}
			}
		}

		// add to mesh
		mesh->addMeshBuffer(buffer);
		core::aabbox3df bbox = mesh->getBoundingBox(); bbox.addInternalBox( buffer->getBoundingBox() );
		mesh->setBoundingBox( bbox );
		buffer->drop();
		buffer = 0;
	}

	//!----------------------------------------------------------------------------
	//! #3 lower-sphere-half
	//!----------------------------------------------------------------------------

	buffer = new SMeshBuffer();
	if (buffer)
	{
		SMeshBuffer* buffer = new SMeshBuffer();
		if (!buffer)
			return 0;

		// bbox
		buffer->BoundingBox = core::aabbox3df( -radius, y0, -radius, radius, y0-radius, radius);

		// material
		if (color.getAlpha()<255)
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		else
			buffer->Material.MaterialType = video::EMT_SOLID;

		buffer->Vertices.clear();
		buffer->Indices.clear();
		// buffer->Vertices.reallocate( (tessCircle+1)*(tessHull+1) );
		// buffer->Indices.reallocate( 6*tessCircle*tessHull );
		// buffer->Vertices.set_used( 0 );
		// buffer->Indices.set_used( 0 );
		for (u32 j=0; j<tessRows; ++j)
		{
			for (u32 i=0; i<tessCircle; ++i)
			{
				const f32 sinA = sinf( wa * (f32)i);
				const f32 cosA = cosf( wa * (f32)i);
				const f32 sinB = sinf( wb * (f32)j);
				const f32 cosB = cosf( wb * (f32)j);
				const f32 x = -sinA * cosB;				// equals the normal at point radius*(x,y,z)
				const f32 y = -sinB;					// equals the normal at point radius*(x,y,z)
				const f32 z =  cosA * cosB;				// equals the normal at point radius*(x,y,z)
				const f32 u = core::clamp( 0.5f-0.5f*cosB * sinA, core::ROUNDING_ERROR_f32, 1.0f-core::ROUNDING_ERROR_f32 );
				const f32 v = core::clamp( 0.5f+0.5f*cosB * cosA, core::ROUNDING_ERROR_f32, 1.0f-core::ROUNDING_ERROR_f32 );
				buffer->Vertices.push_back(
					video::S3DVertex( radius*x,y0+radius*y,radius*z, x,y,z, color, u,v ) );
			}
		}

		// lower-sphere-half bottom center vertex
		buffer->Vertices.push_back( video::S3DVertex(0.f,y0-radius,0.f, 0.f,-1.f,0.f, color, .5f,.5f) );

		// lower-sphere-half Indices
		for (u32 j=0; j<tessRows; j++)
		{
			for (u32 i=0; i<tessCircle; i++)
			{
				// Top just triangles
				if (j==tessRows-1)
				{
					s32 i0; // A
					s32 i1; // B
					s32 i2 = buffer->Vertices.size()-1; // C - top center

					// border
					if (i==tessCircle-1)
					{
						i0 = (j)*tessCircle + (i);	// A
						i1 = (j)*tessCircle + (0);	// B
					}
					// normal
					else
					{
						i0 = (j)*tessCircle + (i);	// A
						i1 = (j)*tessCircle + (i+1);	// B
					}
					buffer->Indices.push_back((u16)i1); // A
					buffer->Indices.push_back((u16)i2); // C
					buffer->Indices.push_back((u16)i0); // B
				}
				// Bottom to Top-1 consist each of 2 triangles
				else
				{
					s32 i0;	// A
					s32 i1;	// B
					s32 i2;	// C
					s32 i3;	// D

					// border
					if (i==tessCircle-1)
					{
						i0 = (j)*tessCircle + (i);	// A
						i1 = (j+1)*tessCircle + (i);	// B
						i2 = (j+1)*tessCircle + (0);	// C
						i3 = (j)*tessCircle + (0);	// D
					}
					// normal
					else
					{
						i0 = (j)*tessCircle + (i);	// A
						i1 = (j+1)*tessCircle + (i);	// B
						i2 = (j+1)*tessCircle + (i+1);// C
						i3 = (j)*tessCircle + (i+1);	// D
					}
					buffer->Indices.push_back((u16)i2); // A
					buffer->Indices.push_back((u16)i1); // B
					buffer->Indices.push_back((u16)i0); // C
					buffer->Indices.push_back((u16)i3); // A
					buffer->Indices.push_back((u16)i2); // C
					buffer->Indices.push_back((u16)i0); // D
				}
			}
		}

		// add to mesh
		mesh->addMeshBuffer(buffer);
		core::aabbox3df bbox = mesh->getBoundingBox(); bbox.addInternalBox( buffer->getBoundingBox() );
		mesh->setBoundingBox( bbox );
		buffer->drop();
		buffer = 0;
	}

	mesh->setHardwareMappingHint(EHM_STATIC);
	return mesh;
}

IMesh* CGeometryCreatorEx::createTubeMesh(
		f32 outerRadius,
		f32 innerRadius,
		f32 height,
		u32 tessCircle,
		u32 tessHull,						//! @todo add vertical tesselation to inner cylinder hull
		bool closeTop,
		bool closeBottom,
		bool bRepeatTextureCircle,
		bool bRepeatTextureHull,
		const video::SColor& color) const
{
	SMesh* mesh = new SMesh();
	if (!mesh)
		return 0;

	// constants
	core::CSinTablef sinTable(tessCircle);
	core::CCosTablef cosTable(tessCircle);
	const f32 sx = 1.f / (f32)tessCircle;
	const f32 sy = 1.f / (f32)tessHull;
	const f32 sy0 = -0.5f * height;
	const f32 sy1 =  0.5f * height;
	const f32 oi = innerRadius / outerRadius;

	//!----------------------------------------------------------------------------
	//! outer cylinder hull
	//!----------------------------------------------------------------------------

	SMeshBuffer* buffer = new SMeshBuffer();
	if (buffer)
	{
		// material
		if (color.getAlpha()<255)
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		else
			buffer->Material.MaterialType = video::EMT_SOLID;

		buffer->Vertices.reallocate( (tessCircle+1)*(tessHull+1) );
		buffer->Indices.reallocate( 6*tessCircle*tessHull );
		buffer->Vertices.set_used( 0 );
		buffer->Indices.set_used( 0 );

		// hull - vertices
		for (u32 y=0; y<=tessHull; y++)
		{
			for (u32 x=0; x<=tessCircle; x++)
			{
				const f32& s = sinTable[x];
				const f32& c = cosTable[x];

				buffer->Vertices.push_back(
					video::S3DVertex( outerRadius*s, sy0 + height*sy*y, outerRadius*c, s,0,c, color, 1.0f-sx*x, 1.0f-sy*y ) );
			}
		}

		const u32 pitch = tessCircle + 1; // vertices per row to skip

		// hull - indices
		for (u32 y=0; y<tessHull; y++)
		{
			for (u32 x=0; x<tessCircle; x++)
			{
				u32 ix=x+1;
	//			if (ix>tessCircle)
	//				ix=0;
				u32 iy=y+1;
	//			if (iy>=tessHull)
	//				iy=0;

				u32 iA = x + y*pitch;
				u32 iB = x + iy*pitch;
				u32 iC = ix + iy*pitch;
				u32 iD = ix + y*pitch;
				buffer->Indices.push_back(iA);
				buffer->Indices.push_back(iC);
				buffer->Indices.push_back(iB);
				buffer->Indices.push_back(iA);
				buffer->Indices.push_back(iD);
				buffer->Indices.push_back(iC);
			}
		}

		// hull - bbox
		buffer->recalculateBoundingBox();

		// add hull to mesh
		mesh->addMeshBuffer(buffer);
		buffer->drop();
		buffer = 0;
	}

	//!----------------------------------------------------------------------------
	//! inner cylinder-hull
	//!----------------------------------------------------------------------------

	buffer = new SMeshBuffer();
	if (buffer)
	{
		// material
		if (color.getAlpha()<255)
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		else
			buffer->Material.MaterialType = video::EMT_SOLID;

		buffer->Vertices.clear();
		buffer->Indices.clear();
		// buffer->Vertices.reallocate();
		// buffer->Vertices.set_used(0);
		// buffer->Indices.reallocate();
		// buffer->Indices.set_used(0);

		// inner-cylinder vertices
		for (u32 i=0; i<tessCircle+1; i++)
		{
			const f32& s = sinTable[i];
			const f32& c = cosTable[i];
			const f32 x = innerRadius*s;
			const f32 z = innerRadius*c;
			const f32 u = (f32)i*sx;// [0,1]

			buffer->Vertices.push_back(video::S3DVertex(x,sy0,z,-s,0,-c,color,u,1.0f));
			buffer->Vertices.push_back(video::S3DVertex(x,sy1,z,-s,0,-c,color,u,0.0f));
		}

		// inner-cylinder indices
		for (u32 i=0; i<tessCircle; i++)
		{
			buffer->Indices.push_back(2*i+3);
			buffer->Indices.push_back(2*i+0);
			buffer->Indices.push_back(2*i+1);
			buffer->Indices.push_back(2*i+2);
			buffer->Indices.push_back(2*i+0);
			buffer->Indices.push_back(2*i+3);
		}

		// inner-cylinder BBox
		buffer->recalculateBoundingBox();

		// inner-cylinder to mesh
		mesh->addMeshBuffer(buffer);
		buffer->drop();
		buffer=0;

	}

	//!----------------------------------------------------------------------------
	//! top-ring
	//!----------------------------------------------------------------------------

	buffer = new SMeshBuffer();
	if (buffer)
	{
		// material
		if (color.getAlpha()<255)
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		else
			buffer->Material.MaterialType = video::EMT_SOLID;

		buffer->Vertices.clear();
		buffer->Indices.clear();
		// buffer->Vertices.reallocate();
		// buffer->Vertices.set_used(0);
		// buffer->Indices.reallocate();
		// buffer->Indices.set_used(0);

		// top-ring vertices
		for (u32 i=0; i<tessCircle+1; i++)
		{
			const f32& s = sinTable[i];
			const f32& c = cosTable[i];

			buffer->Vertices.push_back(
				video::S3DVertex(
					-outerRadius*s, .5f*height, outerRadius*c,
					0.f,1.f,0.f, color,
					.5f-.5f*s, .5f-.5f*c));

			buffer->Vertices.push_back(
				video::S3DVertex(
					-innerRadius*s, .5f*height, innerRadius*c,
					0.f,1.f,0.f, color,
					.5f-.5f*oi*s, .5f-.5f*oi*c));
		}

		// top-ring indices
		for (u32 i=0; i<tessCircle; i++)
		{
			const u16 iA = i<<1; 		// 2*i
			const u16 iB = iA+1;		// 2*i + 1
			const u16 iD = (i+1)<<1; 	// 2*(i+1)
			const u16 iC = iD+1;		// 2*(i+1) + 1

			buffer->Indices.push_back(iA);	// A
			buffer->Indices.push_back(iB);	// B
			buffer->Indices.push_back(iC);	// C
			buffer->Indices.push_back(iA);	// A
			buffer->Indices.push_back(iC);	// C
			buffer->Indices.push_back(iD);	// D
		}

		// top-ring BoundingBox
		buffer->recalculateBoundingBox();

		// top-ring to mesh
		mesh->addMeshBuffer(buffer);
		buffer->drop();
		buffer=0;

	}

	//!----------------------------------------------------------------------------
	//! bottom-ring
	//!----------------------------------------------------------------------------

	buffer = new SMeshBuffer();
	if (buffer)
	{
		// material
		if (color.getAlpha()<255)
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		else
			buffer->Material.MaterialType = video::EMT_SOLID;

		buffer->Vertices.clear();
		buffer->Indices.clear();
	//	buffer->Vertices.reallocate();
	//	buffer->Vertices.set_used(0);
	//	buffer->Indices.reallocate();
	//	buffer->Indices.set_used(0);

		// bottom-ring vertices
		for (u32 i=0; i<tessCircle+1; i++)
		{
			const f32& s = sinTable[i];
			const f32& c = cosTable[i];

			buffer->Vertices.push_back(
				video::S3DVertex(
					-outerRadius*s, -.5f*height, outerRadius*c,
					0.f,-1.f,0.f, color,
					.5f-.5f*s, .5f+.5f*c));

			buffer->Vertices.push_back(
				video::S3DVertex(
					-innerRadius*s, -.5f*height, innerRadius*c,
					0.f,-1.f,0.f, color,
					.5f-.5f*oi*s, .5f+.5f*oi*c));
		}

		// bottom-ring indices
		for (u32 i=0; i<tessCircle; i++)
		{
			buffer->Indices.push_back(2*i);			// A
			buffer->Indices.push_back(2*(i+1)+1);	// C
			buffer->Indices.push_back(2*i+1);		// B
			buffer->Indices.push_back(2*i);			// A
			buffer->Indices.push_back(2*(i+1));		// D
			buffer->Indices.push_back(2*(i+1)+1);	// C
		}

		// bottom-ring BBox
		buffer->recalculateBoundingBox();

		// bottom-ring to mesh
		mesh->addMeshBuffer(buffer);
		buffer->drop();
		buffer=0;
	}

	// return mesh
	mesh->recalculateBoundingBox();
	mesh->setHardwareMappingHint(EHM_STATIC);
	return mesh;
}

IMesh*
CGeometryCreatorEx::createBoxMesh( 	const core::vector3df& size, // 3d-size
									const video::SColor& color, // vertexcolor
									u32 matCount) const // material count == meshbuffer count
{
	//! common vars
	const f32 x = 0.5f*size.X;
	const f32 y = 0.5f*size.Y;
	const f32 z = 0.5f*size.Z;
	const core::vector3df A(-x,-y,-z);
	const core::vector3df B(-x, y,-z);
	const core::vector3df C( x, y,-z);
	const core::vector3df D( x,-y,-z);
	const core::vector3df E(-x,-y, z);
	const core::vector3df F(-x, y, z);
	const core::vector3df G( x, y, z);
	const core::vector3df H( x,-y, z);
	const core::vector2df uv1( 0, 1 );
	const core::vector2df uv2( 0, 0 );
	const core::vector2df uv3( 1, 0 );
	const core::vector2df uv4( 1, 1 );

	//! six materials ( six possible textures, like flipped skybox for crates, cargoboxes, dice, etc... )
	if (matCount==6)
	{
		SMesh* mesh = new SMesh();
		if (!mesh)
			return 0;

		mesh->setBoundingBox( core::aabbox3df(-x,-y,-z, x,y,z) );

		for (u32 i=0; i<6; i++)
		{
			SMeshBuffer* buffer = new SMeshBuffer();
			if (buffer)
			{
				// material
				if (color.getAlpha()<255)
					buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
				else
					buffer->Material.MaterialType = video::EMT_SOLID;

				// memory
				buffer->Vertices.reallocate(4);
				buffer->Vertices.set_used(0);
				buffer->Indices.reallocate(6);
				buffer->Indices.set_used(0);

				// choose quad
				if (i==0)
				{
					// QUAD [1] neg x
					const core::vector3df n(-1, 0, 0);
					buffer->Vertices.push_back( video::S3DVertex( E, n, color, uv1) ); // C
					buffer->Vertices.push_back( video::S3DVertex( F, n, color, uv2) ); // F
					buffer->Vertices.push_back( video::S3DVertex( B, n, color, uv3) ); // B
					buffer->Vertices.push_back( video::S3DVertex( A, n, color, uv4) ); // A
					// buffer->Material.setTexture( 0, negX);
				}
				else if (i==1)
				{
					// QUAD [2] neg y
					const core::vector3df n(0, -1, 0);
					buffer->Vertices.push_back( video::S3DVertex( E, n, color, uv1) ); // C
					buffer->Vertices.push_back( video::S3DVertex( A, n, color, uv2) ); // A
					buffer->Vertices.push_back( video::S3DVertex( D, n, color, uv3) ); // B
					buffer->Vertices.push_back( video::S3DVertex( H, n, color, uv4) ); // D
					// buffer->Material.setTexture( 0, negY);
				}
				else if (i==2)
				{
					// QUAD [3] neg z
					const core::vector3df n(-1, 0, 0);
					buffer->Vertices.push_back( video::S3DVertex( A, n, color, uv1) ); // A
					buffer->Vertices.push_back( video::S3DVertex( B, n, color, uv2) ); // B
					buffer->Vertices.push_back( video::S3DVertex( C, n, color, uv3) ); // C
					buffer->Vertices.push_back( video::S3DVertex( D, n, color, uv4) ); // D
					// buffer->Material.setTexture( 0, negZ);
				}
				else if (i==3)
				{
					// QUAD [4] pos x
					const core::vector3df n(1, 0, 0);
					buffer->Vertices.push_back( video::S3DVertex( D, n, color, uv1) ); // D
					buffer->Vertices.push_back( video::S3DVertex( C, n, color, uv2) ); // C
					buffer->Vertices.push_back( video::S3DVertex( G, n, color, uv3) ); // G
					buffer->Vertices.push_back( video::S3DVertex( H, n, color, uv4) ); // H
					// buffer->Material.setTexture( 0, posX);
				}
				else if (i==4)
				{
					// QUAD [5] pos y
					const core::vector3df n(0, 1, 0);
					buffer->Vertices.push_back( video::S3DVertex( B, n, color, uv1) ); // B
					buffer->Vertices.push_back( video::S3DVertex( F, n, color, uv2) ); // F
					buffer->Vertices.push_back( video::S3DVertex( G, n, color, uv3) ); // G
					buffer->Vertices.push_back( video::S3DVertex( C, n, color, uv4) ); // C
					// buffer->Material.setTexture( 0, posY);
				}
				else if (i==5)
				{
					// QUAD [6] pos z
					const core::vector3df n(0, 0, 1);
					buffer->Vertices.push_back( video::S3DVertex( H, n, color, uv1) ); // E
					buffer->Vertices.push_back( video::S3DVertex( G, n, color, uv2) ); // F
					buffer->Vertices.push_back( video::S3DVertex( F, n, color, uv3) ); // G
					buffer->Vertices.push_back( video::S3DVertex( E, n, color, uv4) ); // H
					// buffer->Material.setTexture( 0, posZ);
				}

				// bbox
				buffer->recalculateBoundingBox();

				// indices
				buffer->Indices.push_back( 0 );
				buffer->Indices.push_back( 1 );
				buffer->Indices.push_back( 2 );
				buffer->Indices.push_back( 0 );
				buffer->Indices.push_back( 2 );
				buffer->Indices.push_back( 3 );

				// add to mesh
				mesh->addMeshBuffer( buffer );
				buffer->drop();
				buffer = 0;
			}
		}

		// return
		mesh->setHardwareMappingHint(EHM_STATIC);
		return mesh;
	}
	//! three materials ( three textures )
	if (matCount>2 && matCount<6)
	{
		SMesh* mesh = new SMesh();
		if (!mesh)
			return 0;

		mesh->setBoundingBox( core::aabbox3df(-x,-y,-z, x,y,z) );

		for (u32 i=0; i<3; i++)
		{
			SMeshBuffer* buffer = new SMeshBuffer();
			if (buffer)
			{
				// material
				if (color.getAlpha()<255)
					buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
				else
					buffer->Material.MaterialType = video::EMT_SOLID;

				// memory
				buffer->Vertices.reallocate(2*4);
				buffer->Vertices.set_used(0);
				buffer->Indices.reallocate(2*6);
				buffer->Indices.set_used(0);

				// choose x quads
				if (i==0)
				{
					// QUAD [1] neg x
					const core::vector3df n(-1, 0, 0);
					buffer->Vertices.push_back( video::S3DVertex( E, n, color, uv1) ); // C
					buffer->Vertices.push_back( video::S3DVertex( F, n, color, uv2) ); // F
					buffer->Vertices.push_back( video::S3DVertex( B, n, color, uv3) ); // B
					buffer->Vertices.push_back( video::S3DVertex( A, n, color, uv4) ); // A

					// QUAD [4] pos x
					const core::vector3df m(1, 0, 0);
					buffer->Vertices.push_back( video::S3DVertex( D, m, color, uv1) ); // D
					buffer->Vertices.push_back( video::S3DVertex( C, m, color, uv2) ); // C
					buffer->Vertices.push_back( video::S3DVertex( G, m, color, uv3) ); // G
					buffer->Vertices.push_back( video::S3DVertex( H, m, color, uv4) ); // H
					// buffer->Material.setTexture( 0, posX);
				}
				else if (i==1)
				{
					// QUAD [2] neg y
					const core::vector3df n(0, -1, 0);
					buffer->Vertices.push_back( video::S3DVertex( E, n, color, uv1) ); // C
					buffer->Vertices.push_back( video::S3DVertex( A, n, color, uv2) ); // A
					buffer->Vertices.push_back( video::S3DVertex( D, n, color, uv3) ); // B
					buffer->Vertices.push_back( video::S3DVertex( H, n, color, uv4) ); // D

					// QUAD [5] pos y
					const core::vector3df m(0, 1, 0);
					buffer->Vertices.push_back( video::S3DVertex( B, m, color, uv1) ); // B
					buffer->Vertices.push_back( video::S3DVertex( F, m, color, uv2) ); // F
					buffer->Vertices.push_back( video::S3DVertex( G, m, color, uv3) ); // G
					buffer->Vertices.push_back( video::S3DVertex( C, m, color, uv4) ); // C
					// buffer->Material.setTexture( 0, posY);
				}
				else
				{
					// QUAD [3] neg z
					const core::vector3df n(-1, 0, 0);
					buffer->Vertices.push_back( video::S3DVertex( A, n, color, uv1) ); // A
					buffer->Vertices.push_back( video::S3DVertex( B, n, color, uv2) ); // B
					buffer->Vertices.push_back( video::S3DVertex( C, n, color, uv3) ); // C
					buffer->Vertices.push_back( video::S3DVertex( D, n, color, uv4) ); // D

					// QUAD [6] pos z
					const core::vector3df m(0, 0, 1);
					buffer->Vertices.push_back( video::S3DVertex( H, m, color, uv1) ); // E
					buffer->Vertices.push_back( video::S3DVertex( G, m, color, uv2) ); // F
					buffer->Vertices.push_back( video::S3DVertex( F, m, color, uv3) ); // G
					buffer->Vertices.push_back( video::S3DVertex( E, m, color, uv4) ); // H
					// buffer->Material.setTexture( 0, posZ);
				}

				// bbox
				buffer->recalculateBoundingBox();

				// indices
				buffer->Indices.push_back( 0 );
				buffer->Indices.push_back( 1 );
				buffer->Indices.push_back( 2 );
				buffer->Indices.push_back( 0 );
				buffer->Indices.push_back( 2 );
				buffer->Indices.push_back( 3 );
				buffer->Indices.push_back( 0+4 );
				buffer->Indices.push_back( 1+4 );
				buffer->Indices.push_back( 2+4 );
				buffer->Indices.push_back( 0+4 );
				buffer->Indices.push_back( 2+4 );
				buffer->Indices.push_back( 3+4 );

				// add to mesh
				mesh->addMeshBuffer( buffer );
				buffer->drop();
				buffer = 0;
			}
		}

		// return
		mesh->setHardwareMappingHint(EHM_STATIC);
		return mesh;
	}
//	//! one material ( zero or one texture )
//	else
//	{
//		return createCubeMesh( size );
//	}

	return 0;
}

IMesh* CGeometryCreatorEx::createTorusMesh(
		f32 outerRadius,
		f32 innerRadius,
		u32 tessOuterRadius,
		u32 tessInnerRadius,
		const video::SColor& color) const
{
	// x=[R+r*cos(u)]-sin(v)
	// y=r*sin(u)
	// z=[R+r*cos(u)]cos(v)
	// R=outerRadius
	// r=innerRadius
	// u=0..2Pi - inner angle each circle segment
	// v=0..2Pi - outer angle

	SMesh* mesh = new SMesh();
	if (!mesh)
		return 0;

	// constants
	core::CSinTablef oSinTable(tessOuterRadius);
	core::CCosTablef oCosTable(tessOuterRadius);
	core::CSinTablef iSinTable(tessInnerRadius);
	core::CCosTablef iCosTable(tessInnerRadius);

	const f32 sx = 1.f / (f32)tessOuterRadius;
	const f32 sy = 1.f / (f32)tessInnerRadius;

	//!----------------------------------------------------------------------------
	//! torus hull
	//!----------------------------------------------------------------------------

	SMeshBuffer* buffer = new SMeshBuffer();
	if (buffer)
	{
		// hull - bbox
		buffer->setBoundingBox( core::aabbox3df( -outerRadius-innerRadius, -innerRadius, -outerRadius-innerRadius,
				outerRadius+innerRadius, innerRadius, outerRadius+innerRadius) );

		// material
		if (color.getAlpha()<255)
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		else
			buffer->Material.MaterialType = video::EMT_SOLID;

//		buffer->Vertices.clear();
//		buffer->Indices.clear();
		buffer->Vertices.reallocate( (tessOuterRadius+1)*(tessInnerRadius+1) );
		buffer->Indices.reallocate( 6*tessOuterRadius*tessInnerRadius );
		buffer->Vertices.set_used( 0 );
		buffer->Indices.set_used( 0 );

		// torus - vertices
		for (u32 i=0; i<=tessOuterRadius; i++)
		{
			for (u32 j=0; j<=tessInnerRadius; j++)
			{
				const f32& s = oSinTable[i];
				const f32& c = oCosTable[i];
				const f32& is = iSinTable[j];
				const f32& ic = iCosTable[j];
				const f32 x = (-s)*(outerRadius + innerRadius*ic);
				const f32 y = innerRadius*is;
				const f32 z = (c)*(outerRadius + innerRadius*ic);
				const f32 nx = -s*ic;
				const f32 ny = is;
				const f32 nz = c*ic;

				// tex coords
				const f32 u = core::clamp<f32>(sx*i, core::ROUNDING_ERROR_f32, 1.0f-core::ROUNDING_ERROR_f32);
				// have to shift the tex, because circle-segments start at wrong pos for now
				f32 v = 0.5f-sy*j; if (v>1.0f) v-=1.0f; if (v<0.0f) v+=1.0f;
					v = core::clamp<f32>(v, core::ROUNDING_ERROR_f32, 1.0f-core::ROUNDING_ERROR_f32);

				buffer->Vertices.push_back(	video::S3DVertex( x, y, z, nx,ny,nz, color, u,v ) );
			}
		}

		const u32 pitch = tessInnerRadius + 1; // vertices per circle segment to skip

		// torus - indices
		for (u32 i=0; i<tessOuterRadius; i++)
		{
			for (u32 j=0; j<tessInnerRadius; j++)
			{
//				buffer->Indices.push_back(i+j*(tessInnerRadius+1));
				u32 i2=i+1;
	//			if (ix>tessCircle)
	//				ix=0;
				u32 j2=j+1;
	//			if (iy>=tessHull)
	//				iy=0;

				u32 iA = j + i*pitch;
				u32 iB = j + i2*pitch;
				u32 iC = j2 + i2*pitch;
				u32 iD = j2 + i*pitch;
				buffer->Indices.push_back(iA);
				buffer->Indices.push_back(iC);
				buffer->Indices.push_back(iB);
				buffer->Indices.push_back(iA);
				buffer->Indices.push_back(iD);
				buffer->Indices.push_back(iC);
			}
		}

		// add to mesh
		mesh->addMeshBuffer(buffer);
		core::aabbox3df bbox = mesh->getBoundingBox();
		bbox.addInternalBox( buffer->getBoundingBox() );
		mesh->setBoundingBox( bbox );
		buffer->drop();
	}

	// return
	mesh->setHardwareMappingHint( EHM_STATIC );
	return mesh;
}

// linear 2d rectangle path stroker
IMesh* CGeometryCreatorEx::createLine2dMesh(
	const core::array<core::vector2df>& points,	const core::array<video::SColor>& colors,
	f32 thickness, s32 lineJoin, video::ITexture* pTexture, bool bRepeatTexture) const
{
	SMesh* mesh = new SMesh();
	if (!mesh)
		return 0;

	SMeshBuffer* buffer = new SMeshBuffer();
	if (!buffer)
		return 0;

	const video::SColor white(255,255,255,255);
	const u32 pointCount = points.size();
	const u32 colorCount = colors.size();
	const f32 h = 0.5f*thickness;

	buffer->Vertices.clear();
	buffer->Indices.clear();
	//buffer->Vertices.reallocate((pointCount)*4);
	//buffer->Vertices.set_used(0);
	//buffer->Indices.reallocate((pointCount)*6);
	//buffer->Indices.set_used(0);

	core::array<core::vector2df> AB;

	for (u32 i=0; i<pointCount-2; i++)
	{
		u32 I0 = i+0;
		u32 I1 = i+1;
		u32 I2 = i+2;

		const core::vector2df& P0 = points[I0];
		const core::vector2df& P1 = points[I1];
		const core::vector2df& P2 = points[I2];

		core::vector2df m01(P1.Y-P0.Y,P1.X-P0.X);
		core::vector2df n01(P0.X-P1.X,P1.Y-P0.Y);
		m01.normalize();
		n01.normalize(); // f32 b01 = core::squareroot( n01.X*n01.X + n01.Y*n01.Y ); if ( !core::equals(b01,0.0f) ) { n01/=b01; }
		n01*=h;

		core::vector2df m12(P2.Y-P1.Y,P2.X-P1.X);
		core::vector2df n12(P1.X-P2.X,P2.Y-P1.Y);
		m12.normalize();
		n12.normalize();// f32 b12 = core::squareroot( n12.X*n12.X + n12.Y*n12.Y ); if ( !core::equals(b12,0.0f) ) { n12/=b12; }
		n12*=h;

		core::vector2df A0 = P0 - n01;
		core::vector2df B0 = P0 + n01;
		core::vector2df A2 = P2 - n12;
		core::vector2df B2 = P2 + n12;

		//! line-line-intersection A0 + r*m01 = A2 - s*m12;
		core::vector2df n1 = n01+(n12-n01)*0.5f;
		n1.normalize();
		n1*=h;
		n1*=1.1f;
		if (n1.Y<0)
			n1.Y*=-1;
		core::vector2df A1 = P1-n1; // = A0+(A2-A0)*0.5f; // to be calculated with line-line-intersection
		core::vector2df B1 = P1+n1; // = P1-(A1-P1); // to be calculated with line-line-intersection

//		//! line-line-intersection B0 + r*m01 = B2 - s*m12;
//		core::line2df g1( A0, A0+(m01*1.5f) );
//		core::line2df g2( A2, A2-(m12*1.5f) );
//		core::line2df g3( B0, B0+(m01*1.5f) );
//		core::line2df g4( B2, B2-(m12*1.5f) );
//		bool isA1 = g1.intersectWith(g2,A1,false);
//		bool isB1 = g3.intersectWith(g4,B1,false);

//		#ifdef _DEBUG
//			printf("i=(%d),P[%d]=(%5.3lf,%5.3lf),P[%d]=(%5.3lf,%5.3lf),P[%d]=(%5.3lf,%5.3lf)\nisA1=(%s), isB1=(%s), A[%d]=(%5.3lf,%5.3lf), B[%d]=(%5.3lf,%5.3lf)\n",
//				i,i,(f64)P0.X,(f64)P0.Y,i+1,(f64)P1.X,(f64)P1.Y,i+2,(f64)P2.X,(f64)P2.Y,(isA1)?"true":"false",(isB1)?"true":"false",i+1,(f64)A1.X,(f64)A1.Y,i+1,(f64)B1.X,(f64)B1.Y);
//		#endif

//		if (A1.getLengthSQ()<B1.getLengthSQ())
//		{
//			B1 = P1-(A1-P1);
//		}
//		else
//		{
//			A1 = P1-(B1-P1);
//		}

		if (i==0)
		{
			AB.push_back( A0 );
			AB.push_back( B0 );
			AB.push_back( A1 );
			AB.push_back( B1 );
		}
		else if(i==pointCount-3)
		{
			AB.push_back( A1 );
			AB.push_back( B1 );
			AB.push_back( A2 );
			AB.push_back( B2 );
		}
		else
		{
			AB.push_back( A1 );
			AB.push_back( B1 );
		}

	} // end for

	// build meshbuffer from calculated points AB
	for (u32 i=0; i<pointCount-1; i++)
	{
		video::SColor color0 = white;
		video::SColor color1 = white;
		if (i<colorCount) {	color0 = colors[ i ]; }
		if (i<colorCount-1)	{ color1 = colors[ i+1 ]; }

		u32 k=buffer->Vertices.size();
		if (i==0)
		{
			buffer->Vertices.push_back( video::S3DVertex( AB[2*i].X,AB[2*i].Y,0, 0,0,-1, color0,0,1) ); // A
			buffer->Vertices.push_back( video::S3DVertex( AB[2*i+1].X,AB[2*i+1].Y,0, 0,0,-1, color0,0,0) ); // B
			buffer->Vertices.push_back( video::S3DVertex( AB[2*(i+1)].X,AB[2*(i+1)].Y,0, 0,0,-1, color1,1,1) ); // A'
			buffer->Vertices.push_back( video::S3DVertex( AB[2*(i+1)+1].X,AB[2*(i+1)+1].Y,0, 0,0,-1, color1,1,0) ); // B'
		}
		else
		{
			buffer->Vertices.push_back( video::S3DVertex( AB[2*i].X,AB[2*i].Y,0, 0,0,-1, color0,0,1) ); // A
			buffer->Vertices.push_back( video::S3DVertex( AB[2*i+1].X,AB[2*i+1].Y,0, 0,0,-1, color0,0,0) ); // B
			buffer->Vertices.push_back( video::S3DVertex( AB[2*(i+1)].X,AB[2*(i+1)].Y,0, 0,0,-1, color1,1,1) ); // A'
			buffer->Vertices.push_back( video::S3DVertex( AB[2*(i+1)+1].X,AB[2*(i+1)+1].Y,0, 0,0,-1, color1,1,0) ); // B'
		}
		buffer->Indices.push_back( k+0 ); // A
		buffer->Indices.push_back( k+1 ); // B
		buffer->Indices.push_back( k+3 ); // B'
		buffer->Indices.push_back( k+0 ); // A
		buffer->Indices.push_back( k+3 ); // B'
		buffer->Indices.push_back( k+2 ); // A'

	} // end for

	// flip indices
	for (u32 i=0; i<buffer->Indices.size(); i+=3)
	{
		u32 i0 = buffer->Indices[i];
		u32 i1 = buffer->Indices[i+1];
		u32 i2 = buffer->Indices[i+2];
		const core::vector3df& A = buffer->Vertices[i0].Pos;
		const core::vector3df& B = buffer->Vertices[i1].Pos;
		const core::vector3df& C = buffer->Vertices[i2].Pos;
		core::vector3df n = (B-A).crossProduct(C-A);
		if (n.Z>0.0f) // flip indices, if normale positive ( must be -1 )
		{
			printf("swap indices %d,%d\n",i1,i2);
			buffer->Indices[i+1]=i2;
			buffer->Indices[i+2]=i1;
		}
	}

	buffer->recalculateBoundingBox();
	mesh->addMeshBuffer( buffer );
	mesh->setBoundingBox( buffer->getBoundingBox() );
	buffer->drop();

	for (u32 i=0; i<points.size(); i++)
	{
		IMesh* circle = createCircleMesh(0.1f, 33, true, video::SColor(255,255,255,255));
		if (circle)
		{
			SMeshBuffer* buf = (SMeshBuffer*)circle->getMeshBuffer(0);
			if (buf)
			{
				for (u32 j=0; j<buf->Vertices.size(); j++)
				{
					buf->Vertices[j].Pos.X += points[i].X;
					buf->Vertices[j].Pos.Y += points[i].Y;
					buf->Vertices[j].Pos.Z += -0.01f;
				}
				buf->recalculateBoundingBox();
				mesh->addMeshBuffer( buf );
				mesh->BoundingBox.addInternalBox( buf->getBoundingBox());
			}
			circle->drop();
		}

	}

	mesh->setHardwareMappingHint(EHM_STATIC);
	return mesh;
}
//
////! linear paths
////! linear 3d path stroker with boxes or cylinderhull ( like pipes screensaver from win95 )
//IMesh* CGeometryCreatorEx::createLine3dMesh(
//	const core::array<core::vector3df>& points,	const core::array<video::SColor>& colors,
//	f32 thickness, s32 lineJoin, video::ITexture* pTexture, bool bRepeatTexture) const
//{
//	return 0;
//}

} // end namespace scene
} // end namespace irr

