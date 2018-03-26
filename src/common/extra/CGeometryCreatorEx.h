// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_GEOMETRY_CREATOR_H_INCLUDED__
#define __C_GEOMETRY_CREATOR_H_INCLUDED__

#include <irrlicht.h>

#include "IGeometryCreatorEx.h"

namespace irr
{

namespace scene
{

// addons by BenjaminHampe@gmx.de

//! class for creating geometry on the fly
class CGeometryCreatorEx : public IGeometryCreatorEx
{
	void addToBuffer(const video::S3DVertex& v, SMeshBuffer* Buffer) const;
public:

	//! Create a Triangle MeshBuffer with one color.
	virtual IMeshBuffer* createTriangleMeshBuffer(
			const core::vector3df& A,
			const core::vector3df& B,
			const core::vector3df& C,
			const video::SColor& color,
			f32 thickness,
			video::E_VERTEX_TYPE vType,
			E_PRIMITIVE_TYPE pType,
			u16 lineStipple,
			s32 lineFactor) const;

	//! Create a Triangle MeshBuffer with 3 colors.
	virtual IMeshBuffer* createTriangleMeshBuffer(
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
			s32 lineFactor) const;

	//! Create a Rectangular MeshBuffer with one color.
	virtual IMeshBuffer* createRectMeshBuffer(
			f32 width,
			f32 height,
			const video::SColor& color,
			f32 thickness,
			video::E_VERTEX_TYPE vType,
			E_PRIMITIVE_TYPE pType,
			u16 lineStipple,
			s32 lineFactor) const;

	//! Create a Rectangular MeshBuffer with four colors.
	virtual IMeshBuffer* createRectMeshBuffer(
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
			s32 lineFactor) const;

	//! Create a RoundRect MeshBuffer with one color.
	virtual IMeshBuffer* createRoundRectMeshBuffer(
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
			s32 lineFactor) const;


	//! Create a hexagon MeshBuffer with one color.
	virtual IMeshBuffer* createHexagonMeshBuffer(
			const core::vector3df& size,
			const video::SColor& color,
			bool closeHull,
			bool closeBottom,
			f32 thickness,
			video::E_VERTEX_TYPE vType,
			E_PRIMITIVE_TYPE pType,
			u16 lineStipple,
			s32 lineFactor) const;

	//! Create a circle MeshBuffer with one color.
	virtual IMeshBuffer* createCircleMeshBuffer(
			f32 radius,
			const video::SColor& color,
			u32 segments,
			u32 tesselation,
			f32 thickness,
			video::E_VERTEX_TYPE vType,
			E_PRIMITIVE_TYPE pType,
			u16 lineStipple,
			s32 lineFactor) const;

	//! Create a circle MeshBuffer with two colors.
	virtual IMeshBuffer* createCircleMeshBuffer(
			f32 radius,
			const video::SColor& outerColor,
			const video::SColor& innerColor,
			u32 segments,
			u32 tesselation,
			f32 thickness,
			video::E_VERTEX_TYPE vType,
			E_PRIMITIVE_TYPE pType,
			u16 lineStipple,
			s32 lineFactor) const;

	//! Create a ellipse MeshBuffer with one color.
	virtual IMeshBuffer* createEllipseMeshBuffer(
			f32 radiusX,
			f32 radiusY,
			const video::SColor& color,
			u32 segments,
			u32 tesselation,
			f32 thickness,
			video::E_VERTEX_TYPE vType,
			E_PRIMITIVE_TYPE pType,
			u16 lineStipple,
			s32 lineFactor) const;

	//! Create a ellipse MeshBuffer with two colors.
	virtual IMeshBuffer* createEllipseMeshBuffer(
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
			s32 lineFactor) const;

	//! Create a ring MeshBuffer with one color.
	virtual IMeshBuffer* createRingMeshBuffer(
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
			s32 lineFactor) const;

	//! Create a ring MeshBuffer with two colors.
	virtual IMeshBuffer* createRingMeshBuffer(
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
			s32 lineFactor) const;

	//! Create a Arc MeshBuffer with one color.
	virtual IMeshBuffer* createArcMeshBuffer(
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
			s32 lineFactor) const;

	//! Create a Arc MeshBuffer with two colors.
	virtual IMeshBuffer* createArcMeshBuffer(
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
			s32 lineFactor) const;

	//! Create a cylinder MeshBuffer with one material.
	virtual IMeshBuffer* createCylinderMeshBuffer(
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
			s32 lineFactor) const;

	//! Create a UpperSphereHalf MeshBuffer (skydome) with one color.
	virtual IMeshBuffer* createUpperSphereHalfMeshBuffer(
			f32 radius,
			const video::SColor& color,
			u32 tessCircle,
			u32 tessRows,
			f32 thickness,
			video::E_VERTEX_TYPE vType,
			E_PRIMITIVE_TYPE pType,
			u16 lineStipple,
			s32 lineFactor) const;

	//! Create a LowerSphereHalf MeshBuffer with one color.
	virtual IMeshBuffer* createLowerSphereHalfMeshBuffer(
			f32 radius,
			const video::SColor& color,
			u32 tessCircle,
			u32 tessRows,
			f32 thickness,
			video::E_VERTEX_TYPE vType,
			E_PRIMITIVE_TYPE pType,
			u16 lineStipple,
			s32 lineFactor) const;

	//! Create a Capsule MeshBuffer with one color.
	virtual IMeshBuffer* createCapsuleMeshBuffer(
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
			s32 lineFactor) const;

	//! Create a Tube MeshBuffer with one color.
	virtual IMeshBuffer* createTubeMeshBuffer(
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
			s32 lineFactor) const;

	//! Create a Box MeshBuffer with one color.
    virtual IMeshBuffer* createBoxMeshBuffer(
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
			s32 lineFactor) const;

	//! Create a Box MeshBuffer with six colors.
    virtual IMeshBuffer* createBoxMeshBuffer(
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
			s32 lineFactor) const;

	//! Create a Torus MeshBuffer with one color.
	virtual IMeshBuffer* createTorusMeshBuffer(
			f32 outerRadius,
			f32 innerRadius,
			const video::SColor& color = 0xffffffff,
			u32 tessOuterRadius = 12,
			u32 tessInnerRadius = 8,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const;

	//! Create a OuterTorusHalf MeshBuffer with one color.
	virtual IMeshBuffer* createOuterTorusHalfMeshBuffer(
			f32 outerRadius,
			f32 innerRadius,
			const video::SColor& color = 0xffffffff,
			u32 tessOuterRadius = 12,
			u32 tessInnerRadius = 8,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const;







	IMesh* createTriangleMesh(
			const core::vector3df& A,
			const core::vector3df& B,
			const core::vector3df& C,
			const video::SColor& colorA,
			const video::SColor& colorB,
			const video::SColor& colorC) const;

	IMesh* createRectMesh(
			f32 width = 1.f,
			f32 height = 1.f,
			const video::SColor& bottomLeftColor = 0xffffffff,
			const video::SColor& topLeftColor = 0xffffffff,
			const video::SColor& topRightColor = 0xffffffff,
			const video::SColor& bottomRightColor = 0xffffffff) const;

	IMesh* createRoundRectMesh(
			f32 width = 1.0f,
			f32 height = 1.0f,
			f32 rx = .1f,
			f32 ry = .1f,
			u32 tesselation = 12,
			bool bFullyTextured = true,
			const video::SColor& outlineColor = 0xffffffff,
			const video::SColor& centerColor = 0xffffffff) const;

	IMesh* createHexagonMesh(
			const core::vector3df& size = core::vector3df(10,10,1),
			bool closeHull = false,
			bool closeBottom = false,
			const video::SColor& color = 0xffffffff) const;

	IMesh* createCircleMesh(
			f32 radius = 0.5f,
			u32 tesselation = 12,
			bool filled = true,
			const video::SColor& outerColor = 0xffffffff,
			const video::SColor& innerColor = 0xffffffff) const;

	IMesh* createEllipseMesh(
			f32 radiusX = 0.5f,
			f32 radiusY = 0.4f,
			u32 tesselation = 12,
			const video::SColor& outerColor = 0xffffffff,
			const video::SColor& innerColor = 0xffffffff) const;

	IMesh* createEllipsoidMesh(
			f32 radiusX = 0.5f,
			f32 radiusY = 0.3f,
			f32 radiusZ = 0.4f,
			u32 tessX = 12,
			u32 tessY = 12,
			u32 tessZ = 12,
			const video::SColor& color = 0xffffffff) const;

	IMesh* createRingMesh(
			f32 outerRadius = 0.5f,
			f32 innerRadius = 0.25f,
			u32 tesselation = 12,
			bool bRepeatTexture = false,
			const video::SColor& outerColor = 0xffffffff,
			const video::SColor& innerColor = 0xffffffff) const;

	IMesh* createArcMesh(
			f32 outerRadius = .5f,
			f32 innerRadius = .25f,
			f32 angleStart = 0.0f,
			f32 angleEnd = 180.0f,
			u32 tesselation = 12,
			bool bRepeatTexture = true,
			const video::SColor& outerColor = 0xffffffff,
			const video::SColor& innerColor = 0xffffffff) const;

	IMesh* createCylinderMesh(
			f32 radius,
			f32 height,
			u32 tessCircle = 12,
			u32 tessHull = 1,
			bool closeTop = true,
			bool closeBottom = true,
			bool bOneMaterial = false,
			const video::SColor& color = 0xffffffff,
			const video::SColor& topColor = 0xffffffff,
			const video::SColor& bottomColor = 0xffffffff) const;

	IMesh* createUpperSphereHalfMesh(
			f32 radius = .5f,
			u32 tessCircle = 7,
			u32 tessRows = 7,
			const video::SColor& color = 0xffffffff,
			bool closeBottom = false) const;

	IMesh* createLowerSphereHalfMesh(
			f32 radius = .5f,
			u32 tessCircle = 7,
			u32 tessRows = 7,
			const video::SColor& color = 0xffffffff,
			bool closeTop = false) const;

	IMesh* createCapsuleMesh(
			f32 radius = .5f,
			f32 height = 1.0f,
			u32 tessCircle = 7,
			u32 tessRows = 7,
			u32 tessHull = 1,
			bool bOneMaterial = true,
			const video::SColor& color = 0xffffffff,
			const video::SColor& topColor = 0xffffffff,
			const video::SColor& bottomColor = 0xffffffff) const;

	IMesh* createTubeMesh(
			f32 outerRadius = .5f,
			f32 innerRadius = .4f,
			f32 height = 1.0f,
			u32 tessCircle = 12,
			u32 tessHull = 1,
			bool closeTop = true,
			bool closeBottom = true,
			bool bRepeatTextureCircle = false,
			bool bRepeatTextureHull = false,
			const video::SColor& color = 0xffffffff) const;

    IMesh* createBoxMesh(
			const core::vector3df& size,
	        const video::SColor& color = 0xffffffff,
	        u32 matCount = 6) const;

	IMesh* createTorusMesh(
			f32 outerRadius = .5f,
			f32 innerRadius = .1f,
			u32 tessOuterRadius = 12,
			u32 tessInnerRadius = 8,
			const video::SColor& color = 0xffffffff) const;

// linear 2d rectangle path stroker
	IMesh* createLine2dMesh(
		const core::array<core::vector2df>& points,	// all containing points get connected by min. one quad
		const core::array<video::SColor>& colors, // color-array
		f32 thickness = 1.0f,
		s32 lineJoin = 0, // 0 == rect-miter, 1==rect-bevel, >2 == circle-round segments
		video::ITexture* pTexture = 0,
		bool bRepeatTexture=true) const; // false = each segments has full tex, if true, planar uv mapping on boundingrect

//// linear 3d path stroker with boxes or cylinderhull ( like pipes screensaver from win95 )
//	IMesh* createLine3dMesh(
//		const core::array<core::vector3df>& points,	// all containing points get connected by min. one box or cylinderhull segment
//		const core::array<video::SColor>& colors, // color-array
//		f32 thickness = 1.0f, // height of box segment or 2*radius of surrounding cylinderhull
//		s32 lineJoin = 0, // 0 == box-miter, 1==box-bevel, >2 == cylinder-round segments
//		video::ITexture* pTexture = 0,
//		bool bRepeatTexture=true) const;

	}; // end class CGeometryCreator

} // end namespace scene
} // end namespace irr

#endif

