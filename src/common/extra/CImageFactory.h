// Copyright (C) 2002-2013 BenjaminHampe@gmx.de
// This file intends to advance the caps of the "Irrlicht Engine" 1.8 svn OpenGL C++ 0x11 amd64_86 ia686
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_C_IMAGE_FACTORY_H__
#define __IRR_C_IMAGE_FACTORY_H__

#include <irrlicht.h>
#include <EDeviceTypes.h>
#include <EDriverFeatures.h>

namespace irr
{

const char* const E_DEVICE_TYPE_STRINGS[] = {
	"EIDT_WIN32","EIDT_WINCE","EIDT_X11","EIDT_OSX","EIDT_SDL","EIDT_FRAMEBUFFER","EIDT_CONSOLE","EIDT_BEST","EIDT_COUNT" };

namespace core
{

enum E_METRIC {
	EM_PX=0, EM_INCH, EM_CM, EM_MM, EM_PT, EM_PERCENT, EM_EM, EM_EX, EM_PC, EM_COUNT };

enum E_ALIGN_H {
	EAH_LEFT=0, EAH_CENTER, EAH_RIGHT, EAH_COUNT };

enum E_ALIGN_V {
	EAV_TOP=0, EAV_MIDDLE, EAV_BASELINE, EAV_BOTTOM, EAV_COUNT };

enum E_TEXT_DIRECTION {
	ETD_LEFT_TO_RIGHT=0, ETD_RIGHT_TO_LEFT, ETD_TOP_TO_BOTTOM, ETD_BOTTOM_TO_TOP, ETD_COUNT };

const char* const E_METRIC_STRINGS[] = {
	"EM_EM","EM_EX","EM_PX","EM_INCH","EM_CM","EM_MM","EM_PT","EM_PC","EM_PERCENT","EM_COUNT" };

const char* const E_ALIGN_H_STRINGS[] = {
	"EAH_LEFT","EAH_CENTER","EAH_RIGHT","EAH_COUNT" };

const char* const E_ALIGN_V_STRINGS[] = {
	"EAV_TOP", "EAV_MIDDLE", "EAV_BASELINE", "EAV_BOTTOM", "EAV_COUNT" };

const char* const E_TEXT_DIRECTION_STRINGS[] = {
	"ETD_LEFT_TO_RIGHT", "ETD_RIGHT_TO_LEFT", "ETD_TOP_TO_BOTTOM", "ETD_BOTTOM_TO_TOP","EVT_COUNT"	};

//	const dimension2du DINA0_300DPI(14043,9933);
//	const dimension2du DINA1_300DPI(9933,7016);
//	const dimension2du DINA2_300DPI(7016,4961);
//	const dimension2du DINA3_300DPI(4961,3508);
//	const dimension2du DINA4_300DPI(3508,2480);
//	const dimension2du DINA5_300DPI(2480,1748);
//	const dimension2du DINA6_300DPI(1748,1240);
//	const dimension2du DINA7_300DPI(1240,874);
//	const dimension2du DINA8_300DPI(874,614);
//	const dimension2du DINA9_300DPI(614,437);
//	const dimension2du DINA10_300DPI(437,307);

} // end namespace core

namespace scene
{

const char* const E_PRIMITIVE_TYPE_STRINGS[] = {
	"EPT_POINTS", "EPT_LINE_STRIP",	"EPT_LINE_LOOP", "EPT_LINES", "EPT_TRIANGLE_STRIP",	"EPT_TRIANGLE_FAN",	"EPT_TRIANGLES",
	"EPT_QUAD_STRIP", "EPT_QUADS", "EPT_POLYGON", "EPT_POINT_SPRITES"
};

const char* const E_VERTEX_TYPE_STRINGS[] = {
	"EVT_STANDARD", "EVT_2TCOORDS",	"EVT_TANGENT", "EVT_COUNT"
};

const char* const E_INDEX_TYPE_STRINGS[] = {
	"EIT_16BIT", "EIT_32BIT", "EIT_COUNT"
};

} // end namespace scene

namespace video
{

const char* const E_COLOR_FORMAT_STRINGS[] = {
	"ECF_A1R5G5B5","ECF_R5G6B5","ECF_R8G8B8","ECF_A8R8G8B8",
	"ECF_DXT1","ECF_DXT2","ECF_DXT3","ECF_DXT4","ECF_DXT5",
	"ECF_R16F","ECF_G16R16F","ECF_A16B16G16R16F",
	"ECF_R32F","ECF_G32R32F","ECF_A32B32G32R32F","ECF_UNKNOWN"
};

const char* const E_VIDEO_DRIVER_FEATURE_STRINGS[] = {
	"EVDF_RENDER_TO_TARGET","EVDF_HARDWARE_TL","EVDF_MULTITEXTURE","EVDF_BILINEAR_FILTER","EVDF_MIP_MAP","EVDF_MIP_MAP_AUTO_UPDATE",
	"EVDF_STENCIL_BUFFER","EVDF_VERTEX_SHADER_1_1","EVDF_VERTEX_SHADER_2_0","EVDF_VERTEX_SHADER_3_0","EVDF_PIXEL_SHADER_1_1",
	"EVDF_PIXEL_SHADER_1_2","EVDF_PIXEL_SHADER_1_3","EVDF_PIXEL_SHADER_1_4","EVDF_PIXEL_SHADER_2_0","EVDF_PIXEL_SHADER_3_0",
	"EVDF_ARB_VERTEX_PROGRAM_1","EVDF_ARB_FRAGMENT_PROGRAM_1","EVDF_ARB_GLSL","EVDF_HLSL","EVDF_TEXTURE_NSQUARE","EVDF_TEXTURE_NPOT",
	"EVDF_FRAMEBUFFER_OBJECT","EVDF_VERTEX_BUFFER_OBJECT","EVDF_ALPHA_TO_COVERAGE","EVDF_COLOR_MASK","EVDF_MULTIPLE_RENDER_TARGETS",
	"EVDF_MRT_BLEND","EVDF_MRT_COLOR_MASK","EVDF_MRT_BLEND_FUNC","EVDF_GEOMETRY_SHADER","EVDF_OCCLUSION_QUERY","EVDF_POLYGON_OFFSET",
	"EVDF_BLEND_OPERATIONS","EVDF_TEXTURE_MATRIX","EVDF_TEXTURE_COMPRESSED_DXT","EVDF_COUNT"
};

const char* const E_MATERIAL_FLAG_STRINGS[] = {
	"EMF_WIREFRAME", "EMF_POINTCLOUD", "EMF_GOURAUD_SHADING", "EMF_LIGHTING", "EMF_ZBUFFER", "EMF_ZWRITE_ENABLE", "EMF_BACK_FACE_CULLING",
	"EMF_FRONT_FACE_CULLING", "EMF_BILINEAR_FILTER", "EMF_TRILINEAR_FILTER", "EMF_ANISOTROPIC_FILTER", "EMF_FOG_ENABLE", "EMF_NORMALIZE_NORMALS",
	"EMF_TEXTURE_WRAP", "EMF_ANTI_ALIASING", "EMF_COLOR_MASK", "EMF_COLOR_MATERIAL"
};

enum E_IMAGE_SCALE_OPERATION {
	EISO_FAST=0, EISO_NEAREST, EISO_BILINEAR, EISO_BICUBIC,	EISO_COUNT
};

const char* const E_IMAGE_SCALE_OPERATION_STRINGS[] = {
	"EISO_FAST", "EISO_NEAREST", "EISO_BILINEAR", "EISO_BICUBIC", "EISO_COUNT"
};

enum E_IMAGE_FILTER {
	EIF_SHARPEN=0, EIF_SMOOTHEN, EIF_BLUR, EIF_MEAN_REMOVAL, EIF_EMBOSS, EIF_EMBOSS_ALL, EIF_EMBOSS_LOSSY, EIF_EMBOSS_H, EIF_EMBOSS_V,
	EIF_EDGE_DETECT, EIF_SEPIA, EIF_INVERT, EIF_BLACKWHITE, EIF_GREYSCALES,	EIF_AVERAGE, EIF_HDR, EIF_SATURATE, EIF_COUNT
};

const char* const E_IMAGE_FILTER_STRINGS[] = {
	"EIF_SHARPEN", "EIF_SMOOTHEN", "EIF_BLUR", "EIF_MEAN_REMOVAL", "EIF_EMBOSS",
	"EIF_EMBOSS_ALL", "EIF_EMBOSS_LOSSY", "EIF_EMBOSS_H", "EIF_EMBOSS_V",
	"EIF_EDGE_DETECT", "EIF_SEPIA","EIF_INVERT", "EIF_BLACKWHITE", "EIF_GREYSCALES",
	"EIF_AVERAGE", "EIF_HDR", "EIF_SATURATE", "EIF_COUNT"
};

//! ================================================================================================================
//! template class CImageFilter
//! ================================================================================================================

template <class T>
class CImageFilter : public IReferenceCounted
{
public:
	explicit CImageFilter(
		T e00=T(0), T e01=T(0), T e02=T(0),
		T e10=T(0), T e11=T(1), T e12=T(0),
		T e20=T(0), T e21=T(0), T e22=T(0),
		T factor=T(1),
		T offset=T(0)) // default constructor
	{
		this->pixels[0][0]=e00;
		this->pixels[0][1]=e01;
		this->pixels[0][2]=e02;
		this->pixels[1][0]=e10;
		this->pixels[1][1]=e11;
		this->pixels[1][2]=e12;
		this->pixels[2][0]=e20;
		this->pixels[2][1]=e21;
		this->pixels[2][2]=e22;
		if (factor==T(0))
			factor=T(1);
		this->factor=factor;
		this->offset=offset;
	}

	T get(s32 index)
	{
		index = index%9;
		s32 col = index%3;
		s32 row = (index-col)/3;
		return (pixels[row][col]/factor) + offset;
	}

	T get(s32 row, s32 col)
	{
		if (row<0) row=0; if (row>2) row=2;
		if (col<0) col=0; if (col>2) col=2;
		return (T)(((f32)pixels[row][col]/(f32)factor) + (f32)offset);
	}
public:
	// (matrix / factor) + offset
	T pixels[3][3]; // pixels weight matrix3x3
	T factor;		  // factor
	T offset;		  // offset
};

template <class T> class CImageFilterSharpen : public CImageFilter<T>{public:CImageFilterSharpen():CImageFilter<T>(0,-2,0,-2,11,-2,0,-2,0,3,0){}};
template <class T> class CImageFilterSmoothing : public CImageFilter<T>{public:CImageFilterSmoothing():CImageFilter<T>(1,1,1,1,1,1,1,1,1,9,0){}};
template <class T> class CImageFilterGaussianBlur : public CImageFilter<T>{public:CImageFilterGaussianBlur():CImageFilter<T>(1,2,1,2,4,2,1,2,1,16,0){}};
template <class T> class CImageFilterMeanRemoval : public CImageFilter<T>{public:CImageFilterMeanRemoval():CImageFilter<T>(-1,-1,-1,-1,9,-1,-1,-1,-1,1,0){}};
template <class T> class CImageFilterEmboss : public CImageFilter<T>{public:CImageFilterEmboss():CImageFilter<T>(-1,0,-1,0,4,0,-1,0,-1,1,0){}};
template <class T> class CImageFilterEmbossAll : public CImageFilter<T>{public:CImageFilterEmbossAll():CImageFilter<T>(-1,-1,-1,-1,8,-1,-1,-1,-1,1,0){}};
template <class T> class CImageFilterEmbossLossy : public CImageFilter<T>{public:CImageFilterEmbossLossy():CImageFilter<T>(1,-2,1,-2,4,-2,-2,1,-2,1,127){}};
template <class T> class CImageFilterEmbossH : public CImageFilter<T>{public:CImageFilterEmbossH():CImageFilter<T>(0,0,0,-1,2,-1,0,0,0,1,127){}};
template <class T> class CImageFilterEmbossV : public CImageFilter<T>{public:CImageFilterEmbossV():CImageFilter<T>(0,-1,0,0,0,0,0,1,0,1,127){}};
template <class T> class CImageFilterEdgeDetect : public CImageFilter<T>{public:CImageFilterEdgeDetect():CImageFilter<T>(1,1,1,0,0,0,-1,-1,-1,1,0){}};

typedef CImageFilterSharpen<f32> CImageFilterSharpenf;
typedef CImageFilterSmoothing<f32> CImageFilterSmoothingf;
typedef CImageFilterGaussianBlur<f32> CImageFilterGaussianBlurf;
typedef CImageFilterMeanRemoval<f32> CImageFilterMeanRemovalf;
typedef CImageFilterEmboss<f32> CImageFilterEmbossf;
typedef CImageFilterEmbossAll<f32> CImageFilterEmbossAllf;
typedef CImageFilterEmbossLossy<f32> CImageFilterEmbossLossyf;
typedef CImageFilterEmbossH<f32> CImageFilterEmbossHf;
typedef CImageFilterEmbossV<f32> CImageFilterEmbossVf;
typedef CImageFilterEdgeDetect<f32> CImageFilterEdgeDetectf;

// ================================================================================================================
//! \class CImageFactory
// ================================================================================================================
//!
//! software painting and image manipulation
//! creates a variaty of different patterend images:
//!
//			virtual ITexture* createTexture( IVideoDriver* driver, IImage* src, ILogger* logger = 0) const;
//			virtual IImage* createFromTexture( IVideoDriver* driver, ITexture* src) const;
//			virtual IImage* createCopy( IImage* src, const core::recti& area, video::E_COLOR_PLANE planes = ECP_ALL ) const;
//			virtual IImage* createClone( IImage* src ) const;
//			virtual IImage* createFromColor( u32 sizeX, u32 sizeY, const SColor& color) const;
//			virtual IImage* createFromColor( const core::dimension2du& sizeXY, const SColor& color) const;

//! patterns: texture, gradients, noise, rainbow, range, checkered (transparent backgrounds), lines, fractals
//! resize operations: scale(), resize() - with nearest, bilinear or bicubic filtering, also bool preserveAspect
//! filter operations: threshold(), average(), saturate(), sharpen(), invert(), smooth, blur
//! rotate operations: flipH(), flipV(), rotateLeft()/Right()/180(),
//!					   rotate() - fine-rotation, calculates new rect and fills empty space with color, also sharpen)
// ================================================================================================================

class CImageFactory : public IReferenceCounted
{
public:
	typedef core::position2di Point;
	typedef core::array<Point> PointList;

	//! \return Get width of image in pixels
	virtual u32 getWidth( IImage* src ) const;

	//! \return Get height of image in pixels
	virtual u32 getHeight( IImage* src ) const;

	//! empty constructor
	CImageFactory( ILogger* debugLog = 0);

	//! empty destructor
	virtual ~CImageFactory();

	//! create GPU texture from RAM image
	virtual ITexture* createTexture( IVideoDriver* driver, IImage* src, ILogger* logger = 0) const;

	//! create software image with specified format ( no initial filling occurs! )
	virtual IImage* createImage( const core::dimension2du& size, ECOLOR_FORMAT format = ECF_A8R8G8B8) const;

	//! create software image from GPU texture
	virtual IImage* createImageFromTexture( IVideoDriver* driver, ITexture* src) const;

//	//! create software image with fillcolor
//	virtual IImage* createImageFromColor( const core::dimension2du& size, const SColor& color) const;
//
//	//! create software image with rainbow filling-color gradient, color = func ( wavelength lambda in nm, gamma exponent that shifts spectrum to white noise)
//	virtual IImage* createImageFromRainbowColors( const core::dimension2du& size, u8 transparency = 127, f64 gamma = 1.0) const;

	//! create software image from copied area of source-image
	virtual IImage* copyImage( IImage* src, const core::recti& area, video::E_COLOR_PLANE planes = ECP_ALL ) const;

	//! create software image from full copy of source-image
	virtual IImage* cloneImage( IImage* src ) const;

	//! \return Blends two Pixel together
	virtual SColor blendColor( const SColor& start, const SColor& ende, video::E_BLEND_OPERATION blend_op, video::E_BLEND_FACTOR f ) const;

	//! calculates SColor from a wavelength in nanometer
	//! only valid in range ? ? [380, 780] nm
	//! which are the visible colors for human eyes (blue to red)
	//! uses algorithm from Bruton which is a linear approximation
	//! of the CIE color system, that defines 3 (more complex) functions for the base-colors RGB
	virtual SColor getColorFromWavelength(	f64 lambda = 380.0f /*blue end*/, f64 gamma = 1.0) const;

	//! create rainbow filling color gradient, color = func ( wavelength lambda in nm, gamma exponent that shifts spectrum to white noise)
	//! uses colorFromWaveLength and calculates an amount "count"
	//! of rainbowcolors from ? ? [380, 780] nm --> interpolates
	virtual SColor getColorFromRainbow( u32 i = 0, u32 count = 64, f64 gamma = 1.0) const;

	//! get color from a linear gradient
	virtual SColor getColorFromLinearInterpolation(	const SColor& start, const SColor& ende, f32 t = 0.5f ) const;

	//! sets a pixel by signed integer coords, does not set if outside (0;0), (w-1;h-1)
	virtual void setPixelEx( IImage* src, s32 x, s32 y, const SColor& color, bool blend = false ) const;

	//! sets a pixel by signed integer coords, sets on border if outside (0;0), (w-1;h-1)
	virtual void setPixelAlways( IImage* src, s32 x, s32 y, const SColor& color, bool blend = false ) const;

	//! \param src image pointer we want to read from (Source, read only)
	//! \param x image pixel position x, does not return if outside (0;0), (w-1;h-1)
	//! \param y image pixel position y, does not return if outside (0;0), (w-1;h-1)
	//! \return SColor pixel at signed integer coords (x,y) from image src, does not return if outside (0;0), (w-1;h-1)
	virtual SColor getPixelEx( IImage* src, s32 x, s32 y ) const;

	//! \param src image pointer we want to read from (Source, read only)
	//! \param x image pixel position x, does not return if outside (0;0), (w-1;h-1)
	//! \param y image pixel position y, does not return if outside (0;0), (w-1;h-1)
	//! \return SColor pixel at signed integer coords (x,y) from image src, returns border-pixel if outside (0;0), (w-1;h-1)
	virtual SColor getPixelAlways( IImage* src, s32 x, s32 y ) const;

	//! \return Calculate nearest (1x1) filtered pixel
	virtual SColor getNearestPixel( IImage* src, f32 fx, f32 fy) const;

	//! \return Calculate bilinear (2x2) filtered pixel
	virtual SColor getBilinearPixelFast( IImage* src, f32 fx, f32 fy) const;

	//! \return Calculate bilinear (2x2) filtered pixel
	virtual SColor getBilinearPixel( IImage* src, f32 fx, f32 fy, E_COLOR_PLANE planes = ECP_RGB, SColor* colorKey = 0) const;

	//! \return Calculate bicubic (4x4) factor
	virtual f32  getBicubicFactor( const f32& arg) const;

	//! \return Calculate bicubic (4x4) filtered pixel
	virtual SColor getBicubicPixel( IImage* src, f32 fx, f32 fy, E_COLOR_PLANE planes = ECP_RGB, SColor* colorKey = 0) const;

	//! fill complete surface with fillcolor
	virtual void fill( IImage* src, const SColor& color, E_COLOR_PLANE planes = ECP_ALL, bool blend = false ) const;

	//! fill 4-neighbor - MS Paint style floodfill-can ( recusive 4 neighbor search (N,E,S,W) scanline algorithm )
	virtual bool floodFill( IImage* dst, s32 x, s32 y, const SColor& fillcolor, const SColor& old = SColor(0)) const;

	//! paste image to image ( row-wise blitting )
	virtual void drawImage( IImage* dst, IImage* src, const Point& pos, const core::dimension2d<u32>& size, bool bTransparent = true, bool blend = false) const;

	//! \function Draw a Bresenham line with one or two (lin. gradient) color(s), with option to blend in background
//	virtual void drawLine( IImage* dst, s32 x1, s32 y1, s32 x2, s32 y2, const SColor& color = SColor(255,255,255,255), bool blend = false ) const;
//	virtual void drawLine( IImage* dst, s32 x1, s32 y1, s32 x2, s32 y2, const SColor& color1, const SColor& color2, bool blend = false ) const;
	virtual void drawLine( IImage* dst, const Point& p1, const Point& p2, const SColor& color, bool blend = false) const;
	virtual void drawLine( IImage* dst, const Point& p1, const Point& p2, const SColor& color1, const SColor& color2, bool blend = false) const;

//	virtual void drawLineAA( IImage* dst, const Point& p1, const Point& p2, const SColor& color, bool blend = false) const;
//	virtual void drawLineAA( IImage* dst, const Point& p1, const Point& p2, const SColor& color1, const SColor& color2, bool blend = false) const;

	//! draw a rect, 4 colors, filled (border=0) or outlined with border, option to blend
//	virtual void drawRect( IImage* dst, s32 x1, s32 y1, s32 x2, s32 y2, const SColor& color, s32 border = 0, bool blend = false) const;
//	virtual void drawRect( IImage* dst, s32 x1, s32 y1, s32 x2, s32 y2, const SColor& topLeft, const SColor& topRight, const SColor& bottomRight, const SColor& bottomLeft, s32 border = 0, bool blend = false) const;
	virtual void drawRect( IImage* dst, const core::rect<s32>& pos, const SColor& color, s32 border = 0, bool blend = false) const;
	virtual void drawRect( IImage* dst, const core::rect<s32>& pos, const SColor& topLeft, const SColor& topRight, const SColor& bottomRight, const SColor& bottomLeft, s32 border = 0, bool blend = false) const;

	//! draw a triangle, 3 colors, outlined with border
//	virtual void drawTriangle( IImage* dst, s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3, const SColor& color, s32 border = 1, bool blend = false) const;
//	virtual void drawTriangle( IImage* dst, s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3, const SColor& color1, const SColor& color2, const SColor& c3, s32 border = 1, bool blend = false) const;
	virtual void drawTriangle( IImage* dst, const Point& p1, const Point& p2, const Point& p3, const SColor& color, s32 border = 1, bool blend = false) const;
	virtual void drawTriangle( IImage* dst, const Point& p1, const Point& p2, const Point& p3, const SColor& color1, const SColor& color2, const SColor& c3, s32 border = 1, bool blend = false) const;

	//! draw a filled triangle, 3 colors, with linear gradient
//	virtual void drawFilledTriangle( IImage* dst, s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3, const SColor& color, bool blend = false) const;
//	virtual void drawFilledTriangle( IImage* dst, s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3, const SColor& color1, const SColor& color2, const SColor& c3, bool blend) const;
	virtual void drawFilledTriangle( IImage* dst, const Point& p1, const Point& p2, const Point& p3, const SColor& color, bool blend = false) const;
	virtual void drawFilledTriangle( IImage* dst, const Point& p1, const Point& p2, const Point& p3, const SColor& color1, const SColor& color2, const SColor& c3, bool blend) const;

	//! draw chess-board pattern with 2 colors and each rect with size tileSize
	virtual void drawCheckered( IImage* dst, const core::dimension2d<u32>& tileSize = core::dimension2d<u32>(8,8), const SColor& color1 = SColor(127,225,225,225), const SColor& color2 = SColor(127,235,235,235) ) const;

	//! draw a Bresenham-lined Grid, 1 color, option to blend
//	virtual void drawGrid( IImage* dst, f32 x, f32 y ) const;
	virtual void drawGrid( IImage* dst, const core::recti& pos, const core::dimension2du& gridSize, const SColor& color, bool blend = false ) const;
	virtual void drawGrid( IImage* dst, const core::recti& pos, const core::dimension2du& gridSize, const SColor& topLeft, const SColor& topRight, const SColor& bottomRight, const SColor& bottomLeft, bool blend = false ) const;

	//! draw a Bresenham-circle, 1 colors, filled (border=0) or outlined with border, option to blend
//	virtual void drawCircle( IImage* dst, f32 x, f32 y, f32 radius ) const;
	virtual void drawCircle( IImage* dst, const Point& center, s32 radius, const SColor& color, s32 border = 0, bool blend = false) const;
	virtual void drawCircle( IImage* dst, const Point& center, s32 radius, const SColor& color1, const SColor& color2, s32 border = 0, bool blend = false) const;

	//! draw a Bresenham-ellipse, 1 color, filled or outlined, option to blend
//	virtual void drawEllipse( IImage* dst, f32 x, f32 y, f32 rx, f32 ry ) const;
	virtual void drawEllipse( IImage* dst, const Point& center, s32 rx, s32 ry, const SColor& color, s32 border = 0, bool blend = false) const;
	virtual void drawEllipse( IImage* dst, const Point& center, s32 rx, s32 ry, const SColor& color1, const SColor& color2, s32 border = 0, bool blend = false) const;

	//! draw a Bresenham-round-rect, 1 colors, filled (border=0) or outlined with border, option to blend
//	virtual void drawRoundRect( IImage* dst, f32 x1, f32 y1, f32 x2, f32 y2, f32 rx, f32 ry ) const;
	virtual void drawRoundRect( IImage* dst, const core::rect<s32>& pos, s32 rx, s32 ry, const SColor& color, s32 border = 0, bool blend = false) const;
	virtual void drawRoundRect( IImage* src, const core::rect<s32>& pos, s32 rx, s32 ry, const SColor& topLeft, const SColor& topRight, const SColor& bottomRight, const SColor& bottomLeft, s32 border = 0, bool blend = false) const;

//	//! draw a Bresenham-path with lines
//	virtual void drawPolyLine( IImage* dst, core::array<core::vector2df> points, const SColor& color, bool blend = false   ) const;
//
//	//! draw a Bresenham-path with lines
//	virtual void drawPolyLine( IImage* dst, core::array<core::vector2df> points, const SColor& color, bool blend = false ) const;
//
//	//! draw a Bresenham-path with lines
//	virtual void drawPolyLine( IImage* dst, core::array<core::vector2df> points, const SColor& color, bool blend = false ) const;
//
//	//! draw a Bresenham-path with lines
//	virtual void drawPolygon( IImage* dst, const scene::IMeshBuffer* const src, const SColor& color, bool blend = false ) const;

	//! draw a Bresenham-path with lines
//	virtual void drawPath( IImage* dst, const core::array< core::vector2di >& points, const SColor& color, bool blend = false ) const;

	//! draw a 2d text unicode string
//	virtual void drawText( IImage* dst, const Point& pos, const core::stringw& txt, s32 hAlign = 0, s32 vAlign = 0, core::recti* clipRect = 0) const;

	virtual PointList traverseLine( const Point& A, const Point& B ) const;
	virtual PointList traverseCircle( const Point& center, s32 radius ) const;
	virtual PointList traverseEllipse( const Point& center, s32 rx, s32 ry ) const;
	virtual PointList traverseArc( const Point& center, s32 radius, f32 phiStart, f32 phiEnd ) const;

//	virtual void moveTo( const Point& pos = Point(0,0)) const;
//	virtual void lineTo( const Point& pos = Point(0,0)) const;
//	virtual void cubicTo( const Point& pos = Point(0,0)) const;
//	virtual void conicTo( const Point& pos = Point(0,0)) const;
//	virtual IImage* transform( IImage* src, const core::matrix4& transformMatrix = core::IdentityMatrix ) const;

	//! \return creates new image from extracted color planes from source to target planes
	//! \param srcPlanes Set source planes, can extract each channel to a new image
	//! \param dstPlanes Set target planes, like write-permissions for channel-overwrite
	virtual IImage* extract( IImage* src, E_COLOR_PLANE srcPlanes = ECP_ALPHA, E_COLOR_PLANE dstPlanes = ECP_RGB) const;

	//! quickly flip image horizontally
	virtual bool flipH( IImage* src ) const;

	//! quickly flip image vertically
	virtual bool flipV( IImage* src ) const;

	//! quickly rotate image 180 degrees
	virtual bool rotate180( IImage* src ) const;

	//! \return creates new image from a fine-rotated image in degrees
	virtual IImage* rotate( IImage* src, f32 angleDegreesCCW, SColor* colorKey = 0) const;

	//! \return creates new image from a 90 degrees left ccw rotated image
	virtual IImage* rotateLeft( IImage* src ) const;

	//! \return creates new image from a 90 degrees right cw rotated image
	virtual IImage* rotateRight( IImage* src ) const;

//	//! shifts a image, by px vertical-lines left (can be negative)
//	virtual void shiftLeft( IImage* src, s32 px ) const;
//
//	//! shifts a image, by px vertical-lines right (can be negative)
//	virtual void shiftRight( IImage* src, s32 px ) const;
//
//	//! shifts a image, by px horizontal-lines up (can be negative)
//	virtual void shiftUp( IImage* src, s32 px ) const;
//
//	//! shifts a image, by px horizontal-lines down (can be negative)
//	virtual void shiftDown( IImage* src, s32 px ) const;
//
//	//! transforms a image diagonale
//	virtual IImage* skewH( IImage* src, f32 angle) const;
//
//	//! transforms a image diagonale
//	virtual IImage* skewV( IImage* src, f32 angle) const;




	//! \return creates new image from scaled image, preserving the aspect ratio if needed
	virtual IImage* resize( IImage* src, const core::dimension2du& pixelSize, s32 scaleOp = 1,	E_COLOR_PLANE planes = ECP_ALL,	bool bPreserveAspect = false, bool bSharpen = false ) const;

	//! \return creates new image from scaled image, preserving the aspect ratio if needed
	virtual IImage* resizeNearest( IImage* src, const core::dimension2du& newSize, E_COLOR_PLANE planes = ECP_ALL, bool bPreserveAspect = false, bool bSharpen = false) const;

	//! \return creates new image from resized image (pixels), preserving the aspect ratio if needed
	virtual IImage* resizeFast(	IImage* src, const core::dimension2du& newSize,	E_COLOR_PLANE planes = ECP_ALL, bool bPreserveAspect = false, bool bSharpen = false) const;

	//! \return creates new image from resized image (pixels), preserving the aspect ratio if needed
	virtual IImage* resizeBilinear(	IImage* src, const core::dimension2du& newSize,	E_COLOR_PLANE planes = ECP_ALL, bool bPreserveAspect = false, bool bSharpen = false) const;

	//! \return creates new image from resized image (pixels), preserving the aspect ratio if needed
	virtual IImage* resizeBicubic( IImage* src, const core::dimension2du& newSize, E_COLOR_PLANE planes = ECP_ALL, bool bPreserveAspect = false, bool bSharpen = false) const;

	//! \return creates new image from resized image, preserving the aspect ratio if needed
	virtual IImage* scale( IImage* src, const core::vector2df& scaleXY, s32 scaleOp = 1, E_COLOR_PLANE planes = ECP_RGB,	bool bPreserveAspect = false, bool bSharpen = false ) const;

	//! \return creates new image from scaled image, preserving the aspect ratio if needed
	virtual IImage* scaleNearest( IImage* src, const core::vector2df& scaleXY, E_COLOR_PLANE planes = ECP_ALL, bool bPreserveAspect = false, bool bSharpen = false ) const;

	//! \return creates new image from scaled image, preserving the aspect ratio if needed
	virtual IImage* scaleFast( IImage* src, const core::vector2df& scaleXY, E_COLOR_PLANE planes = ECP_ALL,	bool bPreserveAspect = false, bool bSharpen = false) const;

	//! \return creates new image from scaled image, preserving the aspect ratio if needed
	virtual IImage* scaleBilinear( IImage* src, const core::vector2df& scaleXY,	E_COLOR_PLANE planes = ECP_ALL, bool bPreserveAspect = false, bool bSharpen = false) const;

	//! \return creates new image from scaled image, preserving the aspect ratio if needed
	virtual IImage* scaleBicubic( IImage* src, const core::vector2df& scaleXY, E_COLOR_PLANE planes = ECP_ALL, bool bPreserveAspect = false, bool bSharpen = false) const;

	//! \return creates new image from a (u,v) repeated image (tiles will be scaled bilinear if necessary)
	virtual IImage* repeat( IImage* src, u32 w = 1024, u32 h = 1024, f32 uRepeat = 8.0f, f32 vRepeat = 8.0f, s32 scaleOP = 1, bool bPreserveAspect = true, bool bSharpen = false) const;

//	//! de/increase color-depth
//	virtual void setColorFormat( IImage* src, ECOLOR_FORMAT format ) const;
//
//	//! de/increase color-depth by giving a total number of unique colors
//	virtual void setColorCount( IImage* src, u32 colorCount ) const;

	//! counts all existing unique ARGB color tupels
	virtual u32 getUniqueColorCount( IImage* src, E_COLOR_PLANE planes = ECP_ALL) const;

	//! counts all existing unique ARGB color tupels
	virtual core::array< SColor > getUniqueColorArray( IImage* src, E_COLOR_PLANE planes = ECP_ALL) const;

	//! \return creates array of new images of size "tileSize" as linear array row per row
//	virtual IImage*	blend(
//		IImage* src,
// 		E_BLEND_OPERATION op,
//		E_COLOR_PLANE planes = ECP_ALL) const;

	//! \return creates array of new images of size "tileSize" as linear array row per row
//	virtual core::array<IImage*> split( const core::dimension2du& tileSize) const;

	//! \return creates array of new images of size "tileSize" as linear array row per row
//	virtual core::array<IImage*> splitf( const core::vector2df& splitCount) const;

	//! \return creates new image from filtered image
	virtual IImage* filter( IImage* src, E_IMAGE_FILTER myFilter, u32 param = 0) const;

	//! \return creates new image from filtered image
	virtual IImage* filter( IImage* src, CImageFilter<f32>* filter, bool deleteFilter = false ) const;

	//! \return creates new image from saturated image
	virtual IImage* saturate( IImage* src ) const;

	//! \return creates new image from sharpened image
	virtual IImage* sharpen( IImage* src, f32 value = 1.35f ) const;

	//! \return creates new image from inverted image
	virtual IImage* invert( IImage* src ) const;

	//! \return creates new image from inverted image
	virtual IImage* invert( IImage* src, E_COLOR_PLANE planes ) const;

	//! \return creates new image from 2 colored image, using a threshold-value to decide when black or white
	virtual IImage* blackwhite( IImage* src, u32 threshold ) const;

	//! \return creates new image from average greyscaled image
	virtual IImage* greyscales( IImage* src ) const;

	//! \return creates new image from average greyscaled image
	virtual IImage* average( IImage* src ) const;

	//! \return creates new image from sepia-filtered image
	virtual IImage* sepia( IImage* src ) const;

	//! \return creates new image from enhanced image
	virtual IImage* hdr( IImage* src, u32 threshold ) const;

}; // end class CImageFactory

} // end namespace video
} // end namespace irr


#endif // __IRR_C_IMAGE_FACTORY_H__

