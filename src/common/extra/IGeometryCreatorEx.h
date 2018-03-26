// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_GEOMETRY_CREATOR_EX_H_INCLUDED__
#define __I_GEOMETRY_CREATOR_EX_H_INCLUDED__

#include "IReferenceCounted.h"
#include "IMesh.h"
#include "IImage.h"
#include "S3DVertex.h"
#include "EPrimitiveTypes.h"

namespace irr
{
namespace video
{
	class IVideoDriver;
	class SMaterial;
}

namespace scene
{

	// addons by BenjaminHampe@gmx.de

//! Helper class for creating geometry on the fly.
/** You can get an instance of this class through ISceneManager::getGeometryCreator() */
class IGeometryCreatorEx : public IReferenceCounted
{
public:

	/** MESH-BUFFER creation */


	//! Create a Triangle MeshBuffer with one color.
	/**
		supports 	EPT_POINTS, EPT_LINES, EPT_LINE_STRIP, EPT_LINE_LOOP, EPT_TRIANGLES
					EPT_TRIANGLE_STRIP, EPT_TRIANGLE_FAN

	\param pointA Vector of Point A
	\param pointB Vector of Point B
	\param pointC Vector of Point C
	\param color Color of Points
	\return Generated MeshBuffer.
	*/
	virtual IMeshBuffer* createTriangleMeshBuffer(
			const core::vector3df& A,
			const core::vector3df& B,
			const core::vector3df& C,
			const video::SColor& color,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

	//! Create a Triangle MeshBuffer with 3 colors.
	/**
	\param pointA Vector of Point A
	\param pointB Vector of Point B
	\param pointC Vector of Point C
	\param colorA Color of Point A
	\param colorB Color of Point B
	\param colorC Color of Point C
	\param thickness decides if shape is filled or outline ( thickness <= 0.0f then EPT_TRIANGLES else EPT_LINE_STRIP )
	\param lineStipple line-stipple of material ( only OpenGL driver )
	\param lineFactor line-factor of material ( only OpenGL driver )
	\return Generated mesh.
	*/
	virtual IMeshBuffer* createTriangleMeshBuffer(
			const core::vector3df& A,
			const core::vector3df& B,
			const core::vector3df& C,
			const video::SColor& colorA,
			const video::SColor& colorB,
			const video::SColor& colorC,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

	//! Create a Rectangular MeshBuffer with one color.
	/**
	\param width Width of the rect
	\param height Height of the rect
	\param bottomLeftColor Color of 1st vertex
	\param topLeftColor Color of 2nd vertex
	\param topRightColor Color of 3rd vertex
	\param bottomRightColor Color of 4th vertex
	\param thickness decides if shape is filled or outline ( thickness <= 0.0f then EPT_TRIANGLES else EPT_LINE_STRIP )
	\param lineStipple line-stipple of material ( only OpenGL driver )
	\param lineFactor line-factor of material ( only OpenGL driver )
	\return Generated mesh.
	*/
	virtual IMeshBuffer* createRectMeshBuffer(
			f32 width,
			f32 height,
			const video::SColor& color,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

	//! Create a Rectangular MeshBuffer with four colors.
	/**
	\param width Width of the rect
	\param height Height of the rect
	\param bottomLeftColor Color of 1st vertex
	\param topLeftColor Color of 2nd vertex
	\param topRightColor Color of 3rd vertex
	\param bottomRightColor Color of 4th vertex
	\param thickness decides if shape is filled or outline ( thickness <= 0.0f then EPT_TRIANGLES else EPT_LINE_STRIP )
	\param lineStipple line-stipple of material ( only OpenGL driver )
	\param lineFactor line-factor of material ( only OpenGL driver )
	\return Generated mesh.
	*/
	virtual IMeshBuffer* createRectMeshBuffer(
			f32 width,
			f32 height,
			const video::SColor& bottomLeftColor,
			const video::SColor& topLeftColor,
			const video::SColor& topRightColor,
			const video::SColor& bottomRightColor,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

	//! Create a RoundRect MeshBuffer with one color.
	/**
	\param width Width of the rounded rect,
	\param height Height of the rounded rect
	\param rx Radius in direction of width
	\param ry Radius in direction of height
	\param bFullyTextured When false the border (rx,ry) is not textured
	\param outlineColor Outer color of the rounded-rect
	\param centerColor Inner color of the rounded-rect
	\param thickness decides if shape is filled or outline ( thickness <= 0.0f then EPT_TRIANGLES else EPT_LINE_STRIP )
	\param lineStipple line-stipple of material ( only OpenGL driver )
	\param lineFactor line-factor of material ( only OpenGL driver )
	\return Generated mesh.
	*/
	virtual IMeshBuffer* createRoundRectMeshBuffer(
			f32 width,
			f32 height,
			f32 rx,
			f32 ry,
			const video::SColor& color,
			u32 segments = 12,
			bool bFullyTextured = true,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;


	//! Create a hexagon MeshBuffer with one color.
	/**
	\param size Size of the hexagon
	\param closeHull If true, close the hull of the hexagon.
	\param closeBottom If true, close the lower end of the hexagon.
	\param color Color of vertices.
	\param thickness decides if shape is filled or outline ( thickness <= 0.0f then EPT_TRIANGLES else EPT_LINE_STRIP )
	\param lineStipple line-stipple of material ( only OpenGL driver )
	\param lineFactor line-factor of material ( only OpenGL driver )
	\return Generated mesh.
	*/
	virtual IMeshBuffer* createHexagonMeshBuffer(
			const core::vector3df& size,
			const video::SColor& color,
			bool closeHull = false,
			bool closeBottom = false,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

	//! Create a circle MeshBuffer with one color.
	/**
	\param radius Radius of the circle/disk
	\param tesselation Number of circle segments
	\param outerColor Color of the outline vertices
	\param innerColor Color of the center Vertices
	\param thickness decides if shape is filled or outline ( thickness <= 0.0f then EPT_TRIANGLES else EPT_LINE_STRIP )
	\param lineStipple line-stipple of material ( only OpenGL driver )
	\param lineFactor line-factor of material ( only OpenGL driver )
	\return Generated mesh.
	*/
	virtual IMeshBuffer* createCircleMeshBuffer(
			f32 radius,
			const video::SColor& color,
			u32 segments = 12,
			u32 tesselation = 1,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

	//! Create a circle MeshBuffer with two colors.
	/**
	\param radius Radius of the circle/disk
	\param tesselation Number of circle segments
	\param outerColor Color of the outline vertices
	\param innerColor Color of the center Vertices
	\param thickness decides if shape is filled or outline ( thickness <= 0.0f then EPT_TRIANGLES else EPT_LINE_STRIP )
	\param lineStipple line-stipple of material ( only OpenGL driver )
	\param lineFactor line-factor of material ( only OpenGL driver )
	\return Generated mesh.
	*/
	virtual IMeshBuffer* createCircleMeshBuffer(
			f32 radius,
			const video::SColor& outerColor,
			const video::SColor& innerColor,
			u32 segments = 12,
			u32 tesselation = 1,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

	//! Create a ellipse MeshBuffer with one color.
	/**
	\param radiusX Radius of the ellipse in x-direction
	\param radiusY Radius of the ellipse in y-direction
	\param tesselation Number of ellipse segments
	\param outerColor Color of the outline vertices
	\param innerColor Color of the center Vertices
	\param thickness decides if shape is filled or outline ( thickness <= 0.0f then EPT_TRIANGLES else EPT_LINE_STRIP )
	\param lineStipple line-stipple of material ( only OpenGL driver )
	\param lineFactor line-factor of material ( only OpenGL driver )
	\return Generated mesh.
	*/
	virtual IMeshBuffer* createEllipseMeshBuffer(
			f32 radiusX,
			f32 radiusY,
			const video::SColor& color,
			u32 segments = 12,
			u32 tesselation = 1,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

	//! Create a ellipse MeshBuffer with two colors.
	/**
	\param radiusX Radius of the ellipse in x-direction
	\param radiusY Radius of the ellipse in y-direction
	\param tesselation Number of ellipse segments
	\param outerColor Color of the outline vertices
	\param innerColor Color of the center Vertices
	\param thickness decides if shape is filled or outline ( thickness <= 0.0f then EPT_TRIANGLES else EPT_LINE_STRIP )
	\param lineStipple line-stipple of material ( only OpenGL driver )
	\param lineFactor line-factor of material ( only OpenGL driver )
	\return Generated mesh.
	*/
	virtual IMeshBuffer* createEllipseMeshBuffer(
			f32 radiusX,
			f32 radiusY,
			const video::SColor& outerColor,
			const video::SColor& innerColor,
			u32 segments = 12,
			u32 tesselation = 1,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

	//! Create a ring MeshBuffer with one color.
	/**
	\param outerRadius Outer radius of the ring
	\param innerRadius Inner radius of the ring
	\param tesselation Number of ring segments
	\param outerColor Color of the outer vertices
	\param innerColor Color of the inner Vertices
	\return Generated mesh.
	*/
	virtual IMeshBuffer* createRingMeshBuffer(
			f32 outerRadius,
			f32 innerRadius,
			const video::SColor& color,
			bool bRepeatTexture = false,
			u32 segments = 12,
			u32 tesselation = 1,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

	//! Create a ring MeshBuffer with two colors.
	/**
	\param outerRadius Outer radius of the ring
	\param innerRadius Inner radius of the ring
	\param tesselation Number of ring segments
	\param outerColor Color of the outer vertices
	\param innerColor Color of the inner Vertices
	\return Generated mesh.
	*/
	virtual IMeshBuffer* createRingMeshBuffer(
			f32 outerRadius,
			f32 innerRadius,
			const video::SColor& outerColor,
			const video::SColor& innerColor,
			bool bRepeatTexture = false,
			u32 segments = 12,
			u32 tesselation = 1,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

	//! Create a Arc MeshBuffer with one color.
	/**
	\param outerRadius Outer radius of the arc
	\param innerRadius Inner radius of the arc
	\param angleStart Start angle in pos x direction in degrees
	\param angleEnd End angle after ccw rotation in degrees
	\param tesselation Number of arc segments
	\param bRepeatTexture If true, each segment show the texture once
	\param outerColor Color of the outer vertices
	\param innerColor Color of the inner Vertices
	\return Generated mesh.
	*/
	virtual IMeshBuffer* createArcMeshBuffer(
			f32 outerRadius,
			f32 innerRadius,
			f32 angleStart,
			f32 angleEnd,
			const video::SColor& color,
			bool bRepeatTexture = true,
			u32 segments = 12,
			u32 tesselation = 1,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

	//! Create a Arc MeshBuffer with two colors.
	/**
	\param outerRadius Outer radius of the arc
	\param innerRadius Inner radius of the arc
	\param angleStart Start angle in pos x direction in degrees
	\param angleEnd End angle after ccw rotation in degrees
	\param tesselation Number of arc segments
	\param bRepeatTexture If true, each segment show the texture once
	\param outerColor Color of the outer vertices
	\param innerColor Color of the inner Vertices
	\return Generated mesh.
	*/
	virtual IMeshBuffer* createArcMeshBuffer(
			f32 outerRadius,
			f32 innerRadius,
			f32 angleStart,
			f32 angleEnd,
			const video::SColor& outerColor,
			const video::SColor& innerColor,
			bool bRepeatTexture = true,
			u32 segments = 12,
			u32 tesselation = 1,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

	//! Create a cylinder MeshBuffer with one material.
	/**
	\param radius Radius of the cylinder.
	\param height Heigth of the cylinder.
	\param tessCircle Number of quads around the circumference of the cylinder.
	\param tessHull Number of segments in direction of height
	\param closeTop If true, close the upper end of the cylinder, otherwise leave it open.
	\param closeBottom If true, close the lower end of the cylinder, otherwise leave it open.
	\param bOneMaterial If false, every face (hull,top,bottom) gets a material
	\param color The default vertex-color of the cylinder.
	\param topColor The vertex-color of the top of the cylinder.
	\param bottomColor The vertex-color of the bottom of the cylinder.
	\return Generated mesh.
	*/
	virtual IMeshBuffer* createCylinderMeshBuffer(
			f32 radius,
			f32 height,
			const video::SColor& color,
			u32 tessCircle = 12,
			u32 tessHull = 1,
			bool closeTop = true,
			bool closeBottom = true,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

	//! Create a UpperSphereHalf MeshBuffer (skydome) with one color.
	/**
	\param radius Radius of half-sphere
	\param tessCircle Number of circle-segments of the sphere-half
	\param tessRows Number of rows of the sphere-half
	\param color Color of the mesh
	\return Generated mesh.
	*/
	virtual IMeshBuffer* createUpperSphereHalfMeshBuffer(
			f32 radius,
			const video::SColor& color,
			u32 tessCircle = 7,
			u32 tessRows = 7,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

	//! Create a LowerSphereHalf MeshBuffer with one color.
	/**
	\param radius Radius of half-sphere
	\param tessCircle Number of circle-segments of the sphere-half
	\param tessRows Number of rows of the sphere-half
	\param color Color of the mesh
	\return Generated mesh.
	*/
	virtual IMeshBuffer* createLowerSphereHalfMeshBuffer(
			f32 radius,
			const video::SColor& color,
			u32 tessCircle = 7,
			u32 tessRows = 7,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

	//! Create a Capsule MeshBuffer with one color.
	/**
	\param radius Radius of half-spheres
	\param height Height of the cylinder-hull -> full height = 2*radius + height
	\param tessCircle Number of used circle-segments
	\param tessHull Number of used cylinder-hull segments
	\param bOneMaterial If false, the top and bottom can be textured separately
	\param defaultColor Default color of the mesh
	\param topColor Only used when bOneMaterial == false
	\param bottomColor Only used when bOneMaterial == false
	\return Generated mesh.
	*/
	virtual IMeshBuffer* createCapsuleMeshBuffer(
			f32 radius,
			f32 height,
			const video::SColor& color,
			u32 tessCircle = 7,
			u32 tessRows = 7,
			u32 tessHull = 1,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

	//! Create a Tube MeshBuffer with one color.
	/**
	\param outerRadius Outer radius of the tube
	\param innerRadius Inner radius of the tube
	\param height Height of the tube
	\param tessCircle Number of circle-segments
	\param tessHull Number of hull-segments
	\param bRepeatTextureCircle If true, each circle segment shows the texture once
	\param bRepeatTextureHull If true, each cylinder-hull segment shows the texture once
	\param color Color of the vertices
	\return Generated mesh.
	*/
	virtual IMeshBuffer* createTubeMeshBuffer(
			f32 outerRadius,
			f32 innerRadius,
			f32 height,
			const video::SColor& color,
			u32 tessCircle = 12,
			u32 tessHull = 1,
			bool closeTop = true,
			bool closeBottom = true,
			bool bRepeatTexture = false,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

	//! Create a Box MeshBuffer with one color.
    virtual IMeshBuffer* createBoxMeshBuffer(
			const core::vector3df& size,
	        const video::SColor& color,
	        bool closeNegX = true,
	        bool closeNegY = true,
	        bool closeNegZ = true,
	        bool closePosX = true,
	        bool closePosY = true,
	        bool closePosZ = true,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

	//! Create a Box MeshBuffer with six colors.
    virtual IMeshBuffer* createBoxMeshBuffer(
			const core::vector3df& size,
	        const video::SColor& colorNegX,
	        const video::SColor& colorNegY,
	        const video::SColor& colorNegZ,
	        const video::SColor& colorPosX,
	        const video::SColor& colorPosY,
	        const video::SColor& colorPosZ,
	        bool closeNegX = true,
	        bool closeNegY = true,
	        bool closeNegZ = true,
	        bool closePosX = true,
	        bool closePosY = true,
	        bool closePosZ = true,
			f32 thickness = 0.0f, /* filled == 0 (default: EPT_TRIANGLES), outlined > 0 (default: EPT_LINE_STRIP)*/
			video::E_VERTEX_TYPE vType = video::EVT_STANDARD,
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES,
			u16 lineStipple = 0xffff,
			s32 lineFactor = 1) const = 0;

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
			s32 lineFactor = 1) const = 0;

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
			s32 lineFactor = 1) const = 0;
	/**
		MESH creation ( can contain more than one meshbuffer )
	*/

	//! Create a hexagon MeshBuffer with one color.
	/**
	\param size Size of the hexagon
	\param closeHull If true, close the hull of the hexagon.
	\param closeBottom If true, close the lower end of the hexagon.
	\param color Color of vertices.
	\param thickness decides if shape is filled or outline ( thickness <= 0.0f then EPT_TRIANGLES else EPT_LINE_STRIP )
	\param lineStipple line-stipple of material ( only OpenGL driver )
	\param lineFactor line-factor of material ( only OpenGL driver )
	\return Generated mesh.
	*/
	virtual IMesh* createHexagonMesh(
			const core::vector3df& size = core::vector3df(10,10,1),
			bool closeHull = false,
			bool closeBottom = false,
			const video::SColor& color = 0xffffffff) const = 0;

	//! Create a cylinder mesh.
	/**
	\param radius Radius of the cylinder.
	\param height Heigth of the cylinder.
	\param tessCircle Number of quads around the circumference of the cylinder.
	\param tessHull Number of segments in direction of height
	\param closeTop If true, close the upper end of the cylinder, otherwise leave it open.
	\param closeBottom If true, close the lower end of the cylinder, otherwise leave it open.
	\param bOneMaterial If false, every face (hull,top,bottom) gets a material
	\param color The default vertex-color of the cylinder.
	\param topColor The vertex-color of the top of the cylinder.
	\param bottomColor The vertex-color of the bottom of the cylinder.
	\return Generated mesh.
	*/
	virtual IMesh* createCylinderMesh(
			f32 radius,
			f32 height,
			u32 tessCircle = 12,
			u32 tessHull = 1,
			bool closeTop = true,
			bool closeBottom = true,
			bool bOneMaterial = false,
			const video::SColor& color = 0xffffffff,
			const video::SColor& topColor = 0xffffffff,
			const video::SColor& bottomColor = 0xffffffff) const = 0;

	//! Create a ellipsoid mesh. ( football or earth, can be done by scaling sphere )
	/**
	\param radiusX Radius of the ellipsoid in x-direction
	\param radiusY Radius of the ellipsoid in y-direction
	\param radiusZ Radius of the ellipsoid in z-direction
	\param tessX Number of polys in x-direction
	\param tessY Number of polys in y-direction
	\param tessZ Number of polys in z-direction
	\param color Color of the mesh
	\return Generated mesh.
	*/
	virtual IMesh* createEllipsoidMesh(
			f32 radiusX = 0.5f,
			f32 radiusY = 0.3f,
			f32 radiusZ = 0.4f,
			u32 tessX = 12,
			u32 tessY = 12,
			u32 tessZ = 12,
			const video::SColor& color = 0xffffffff) const = 0;

	//! Create a UpperSphereHalf mesh (skydome).
	/**
	\param radius Radius of half-sphere
	\param tessCircle Number of circle-segments of the sphere-half
	\param tessRows Number of rows of the sphere-half
	\param color Color of the mesh
	\return Generated mesh.
	*/
	virtual IMesh* createUpperSphereHalfMesh(
			f32 radius = .5f,
			u32 tessCircle = 7,
			u32 tessRows = 7,
			const video::SColor& color = 0xffffffff,
			bool closeBottom = false) const = 0;

	//! Create a LowerSphereHalf mesh.
	/**
	\param radius Radius of half-sphere
	\param tessCircle Number of circle-segments of the sphere-half
	\param tessRows Number of rows of the sphere-half
	\param color Color of the mesh
	\return Generated mesh.
	*/
	virtual IMesh* createLowerSphereHalfMesh(
			f32 radius = .5f,
			u32 tessCircle = 7,
			u32 tessRows = 7,
			const video::SColor& color = 0xffffffff,
			bool closeTop = false) const = 0;

	//! Create a Capsule mesh.
	/**
	\param radius Radius of half-spheres
	\param height Height of the cylinder-hull -> full height = 2*radius + height
	\param tessCircle Number of used circle-segments
	\param tessHull Number of used cylinder-hull segments
	\param bOneMaterial If false, the top and bottom can be textured separately
	\param defaultColor Default color of the mesh
	\param topColor Only used when bOneMaterial == false
	\param bottomColor Only used when bOneMaterial == false
	\return Generated mesh.
	*/
	virtual IMesh* createCapsuleMesh(
			f32 radius = .5f,
			f32 height = 1.0f,
			u32 tessCircle = 7,
			u32 tessRows = 7,
			u32 tessHull = 1,
			bool bOneMaterial = true,
			const video::SColor& color = 0xffffffff,
			const video::SColor& topColor = 0xffffffff,
			const video::SColor& bottomColor = 0xffffffff) const = 0;

	//! Create a Tube mesh.
	/**
	\param outerRadius Outer radius of the tube
	\param innerRadius Inner radius of the tube
	\param height Height of the tube
	\param tessCircle Number of circle-segments
	\param tessHull Number of hull-segments
	\param bRepeatTextureCircle If true, each circle segment shows the texture once
	\param bRepeatTextureHull If true, each cylinder-hull segment shows the texture once
	\param color Color of the vertices
	\return Generated mesh.
	*/
	virtual IMesh* createTubeMesh(
			f32 outerRadius = .5f,
			f32 innerRadius = .4f,
			f32 height = 1.0f,
			u32 tessCircle = 12,
			u32 tessHull = 1,
			bool closeTop = true,
			bool closeBottom = true,
			bool bRepeatTextureCircle = false,
			bool bRepeatTextureHull = false,
			const video::SColor& color = 0xffffffff) const = 0;

	//! Create a Box mesh with zero to six textures possible (Dice, Crate, CargoContainerObject).
	/**
	\param size 3d size of the box
	\param color Same color for all vertices
	\param matCount Set number of MeshBuffers used by Mesh (Material+Texture), resulting mesh has ( 6 quads ).
		matCount == 6     - default six textures ( 1 quad per buffer ), used for sceneobjects like dices, crates, cargo-container
		matCount == 3,4,5 - three textures ( 2 quads per buffer ), each opposite planes have same texture
		matCount == 1,2   - one texture ( all 6 quads in buffer ), like createCubeMesh()
		matCount == 0     - no texture ( all 6 quads in buffer ), like createCubeMesh() without texture ( just vertex-color + vertex-alpha )
		\return Generated mesh.
	*/
    virtual IMesh* createBoxMesh(
			const core::vector3df& size = core::vector3df(1,1,2),
	        const video::SColor& color = 0xffffffff,
	        u32 matCount = 6) const = 0;

	//! Create a Torus mesh.
	/**
	\param outerRadius Outer radius of the tube
	\param innerRadius Inner radius of the tube
	\param height Height of the tube
	\param tessCircle Number of circle-segments
	\param tessHull Number of hull-segments
	\param bRepeatTextureCircle If true, each circle segment shows the texture once
	\param bRepeatTextureHull If true, each cylinder-hull segment shows the texture once
	\param color Color of the vertices
	\return Generated mesh.
	*/
	virtual IMesh* createTorusMesh(
			f32 outerRadius = .5f,
			f32 innerRadius = .1f,
			u32 tessOuterRadius = 12,
			u32 tessInnerRadius = 8,
			const video::SColor& color = 0xffffffff) const = 0;




/** State: pre-alpha, untested */


//	//! Create a Line mesh.
//	/**
//	\param pointA Vector of Point A
//	\param pointB Vector of Point B
//	\param colorA Color of Point A
//	\param colorB Color of Point B
//	\param thickness line-width of material
//	\param lineStipple line-stipple of material ( only OpenGL driver )
//	\param lineFactor line-factor of material ( only OpenGL driver )
//	\return Generated mesh.
//	*/
//	virtual IMesh* createLineMesh(
//			const core::vector3df& A = core::vector3df(0,0,0),
//			const core::vector3df& B = core::vector3df(0.5f,1,0),
//			const video::SColor& colorA = 0xffffffff,
//			const video::SColor& colorB = 0xffffffff,
//			f32 thickness = 1.0f, u16 lineStipple = 0xffff, s32 lineFactor = 1) const = 0;

//	//! Create a LinePath mesh ( EPT_LINE_STRIP )
//	/**
//	\param points Array of 3d points forming the line-path
//	\param pointB Colors of 3d points ( if size == 0 then 0xffffffff, if size > 0 then colors[0] ... colors[size-1] )
//	\param thickness line-width of material
//	\param lineStipple line-stipple of material ( only OpenGL driver )
//	\param lineFactor line-factor of material ( only OpenGL driver )
//	\return Generated mesh.
//	*/
//	virtual IMesh* createLinePathMesh(
//			core::array<core::vector3df> points,
//			core::array<video::SColor> colors,
//			f32 thickness = 1.0f, u16 lineStipple = 0xffff, s32 lineFactor = 1) const = 0;
//
//	virtual IMesh* createLineMesh(
//		const core::array<core::vector2df>& points,	const video::SColor& color,
//		f32 thickness, s32 lineJoin, bool bRepeatTexture,
//		core::rectf* clipRect = 0, bool bZoomData = false) const = 0;
//
//	virtual IMesh* createPath2dMesh(
//		const core::array<core::vector2df>& points,	const core::array<video::SColor>& colors,
//		f32 thickness, s32 lineJoin, bool bRepeatTexture,
//		core::rectf* clipRect = 0, bool bZoomData = false) const = 0;
//
//	virtual IMesh* createPath2dMesh(
//		const core::array<core::vector2df>& points,	const core::array<video::SColor>& colors,
//		f32 thickness, s32 lineJoin, bool bRepeatTexture,
//		core::rectf* clipRect = 0, bool bZoomData = false) const = 0;

//	//! Create a 2d path mesh consisting of 2 triangles per segments between 2 points ( miter or bevel, or more triangles = round ).
	/**
	\param points DataPoints of LinePath
	\param color Color of the vertices
	\param thickness Height of the rects
	\param linejoin Miter=0, Round=1, Bevel=2
	\param bRepeatTexture default=false
	\return Generated mesh.
	*/

	// linear 2d rectangle path stroker
	virtual IMesh* createLine2dMesh(
		const core::array<core::vector2df>& points,	// all containing points get connected by min. one quad
		const core::array<video::SColor>& colors, // color-array
		f32 thickness = 1.0f,
		s32 lineJoin = 0, // 0 == rect-miter, 1==rect-bevel, >2 == circle-round segments
		video::ITexture* pTexture = 0,
		bool bRepeatTexture=true) const = 0; // false = each segments has full tex, if true, planar uv mapping on boundingrect

//	// linear 3d path stroker with boxes or cylinderhull ( like pipes screensaver from win95 )
//	virtual IMesh* createLine3dMesh(
//		const core::array<core::vector3df>& points,	// all containing points get connected by min. one box or cylinderhull segment
//		const core::array<video::SColor>& colors, // color-array
//		f32 thickness = 1.0f, // height of box segment or 2*radius of surrounding cylinderhull
//		s32 lineJoin = 0, // 0 == box-miter, 1==box-bevel, >2 == cylinder-round segments
//		video::ITexture* pTexture = 0,
//		bool bRepeatTexture=true) const = 0;
//
//#ifdef _IRR_COMPILE_WITH_FREETYPE2_
//
//	//! Create a 2D-Text mesh ( core::recti screenRect ) with FreeType2 Outline Vectorizer.
//	/**
//	\param text_data,
//	\param size_2d Size of Mesh ( size z = 0 )
//	\param text_color Color of vertices
//	\param font_name Font FileName (*.ttf, *.otf)
//	\param align_h Horizontal text align.
//	\param align_v Vertical text align.
//	\param library FreeType2 Library,
//	\param debugLog Irrlicht LogStream
//	\return Generated mesh.
//	*/
//	virtual IMesh* createText2dMesh(
//			const core::stringw& text_data,
//			const core::recti& size_2d = core::recti(0,0,0,0);
//			const video::SColor& text_color = video::SColor(255,255,255,255),
//			const io::path& font_name = "../../media/courier_new.ttf",
//			s32 align_h = 0,
//			s32 align_v = 0,
//			FT_Library* library = 0,
//			ILogger* debugLog = 0) const = 0;
//
//	//! Create a 3D-Text mesh ( core::vector3df worldSize ) with FreeType2 Outline Vectorizer.
//	/**
//	\param text_data,
//	\param size_3d Size of Mesh
//	\param text_color Color of vertices
//	\param font_name FontFile
//	\param align_h horizontal text align
//	\param align_v vertical text align
//	\param library FreeType2 Library,
//	\param debugLog Irrlicht LogStream
//	\return Generated mesh.
//	*/
//	virtual IMesh* createText3dMesh(
//			const core::stringw& text_data,
//			const core::vector3df& size_3d = core::vector3df(400,24,1),
//			const video::SColor& text_color = video::SColor(255,255,255,255),
//			const io::path& font_name = "../../media/courier_new.ttf",
//			s32 align_h = 0,
//			s32 align_v = 0,
//			FT_Library* library = 0,
//			ILogger* debugLog = 0) const = 0;
//
//#endif // _IRR_COMPILE_WITH_FREETYPE2_


};

} // end namespace scene
} // end namespace irr

#endif // __I_GEOMETRY_CREATOR_EX_H_INCLUDED__

