// Copyright (C) 2002-2013 BenjaminHampe@gmx.de
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CImageFactory.h"

#include <irrlicht.h>
#include <../source/Irrlicht/CImage.h>
#include <../source/Irrlicht/os.h>

//#include "../core/mathExt.h"

namespace irr{
namespace video{

//! constructor
CImageFactory::CImageFactory( ILogger* debugLog)
{

}

//! destructor
CImageFactory::~CImageFactory()
{

}

//! @author extension 2012 by BenjaminHampe@gmx.de
//! @brief width from image
//! @return width of image
u32 CImageFactory::getWidth( IImage* src ) const
{
	if (!src)
		return 0;

	return src->getDimension().Width;
}

//! @author extension 2012 by BenjaminHampe@gmx.de
//! @brief width from image
//! @return width of height
u32 CImageFactory::getHeight( IImage* src ) const
{
	if (!src)
		return 0;

	return src->getDimension().Height;
}

//! \return Blends two Pixel together
SColor CImageFactory::blendColor( const SColor& start, const SColor& ende, video::E_BLEND_OPERATION blend_op, video::E_BLEND_FACTOR f ) const
{
	os::Printer::log("CImageFactory::blendColor() not implemented!", ELL_WARNING);
	return 0;
}

//! @author extension 2012 by BenjaminHampe@gmx.de
//! @brief blends pixel fg on pixel bg
//! @param color fg
//! @param color bg
//! @return blended ARGB color
SColor CImageFactory::getColorFromLinearInterpolation(const SColor& src1, const SColor& src2, f32 alpha) const
{
	const f32 fR = (f32)src1.getRed()+(f32)(src2.getRed()*src2.getAlpha())/255.0f;
	const f32 fG = (f32)src1.getGreen()+(f32)(src2.getGreen()*src2.getAlpha())/255.0f;
	const f32 fB = (f32)src1.getBlue()+(f32)(src2.getBlue()*src2.getAlpha())/255.0f;
	s32 sR = (s32)fR; if (sR>255) sR=255; if (sR<0) sR=0;
	s32 sG = (s32)fG; if (sG>255) sG=255; if (sG<0) sG=0;
	s32 sB = (s32)fB; if (sB>255) sB=255; if (sB<0) sB=0;
	s32 sA = (src1.getAlpha()>src2.getAlpha() ? src1.getAlpha() : src2.getAlpha());
	return SColor( (u32)sA, (u32)sR, (u32)sG, (u32)sB );
}

//IImage* CImageFactory::blend( IImage* src, E_BLEND_OPERATION op, E_COLOR_PLANE planes) const
//{
//	return 0;
//}
//

//! returns a new image from user-defined color-planes and writes them to user-defined planes only
//! if ECP_ALPHA not set, then ALPHA = 0

IImage* CImageFactory::extract( IImage* src, E_COLOR_PLANE srcPlanes, E_COLOR_PLANE dstPlanes ) const
{
	if (!src)
		return 0;

	IImage* img = (IImage*)new CImage( src->getColorFormat(), src->getDimension() );
	if (!img)
		return 0;

	if (srcPlanes == ECP_NONE)
	{
		src->fill(0);
		return img;
	}

	const core::dimension2du Size = src->getDimension();

	for (u32 y=0; y<Size.Height; ++y)
	{
		for (u32 x=0; x<Size.Width; ++x)
		{
			SColor c(0);
			SColor d = src->getPixel(x,y);

			if (srcPlanes^ECP_ALPHA)
			{
				c.setAlpha(d.getAlpha());
			}
			else if (srcPlanes^ECP_RED)
			{
				c.setRed(d.getRed());
			}
			else if (srcPlanes^ECP_GREEN)
			{
				c.setGreen(d.getGreen());
			}
			else if (srcPlanes^ECP_BLUE)
			{
				c.setBlue(d.getBlue());
			}

			img->setPixel(x,y,c);
		}
	}
	return img;
}


//! @author extension 2012 by BenjaminHampe@gmx.de
//! @brief set pixel for signed integer coords only if inside (0,0,w,h)
//! @param signed 32bit x-coord
//! @param signed 32bit y-coord
//! @param set this ARGB color, when (x,y) outside of (0,0,w,h) then skip write attemp
//! @param blend to pixel already at pos (x,y)
//! @return nothing
void CImageFactory::setPixelEx( IImage* src, s32 x, s32 y, const SColor& color, bool blend ) const
{
	if (!src) return;
	if (x<0) return;
	if (y<0) return;
    src->setPixel( (u32)x, (u32)y, color, blend);
}

//! @brief set pixel for signed integer coords always - simple border align
//! @author extension 2012 by BenjaminHampe@gmx.de
//! @param signed 32bit x-coord
//! @param signed 32bit y-coord
//! @param set this ARGB color at (x,y), when (x,y) outside of (0,0,w,h) then clamp to (0,0,w,h) - simple border align
//! @param blend to pixel already at pos (x,y)
//! @return nothing
void CImageFactory::setPixelAlways( IImage* src, s32 x, s32 y, const SColor& color, bool blend ) const
{
	if (!src) return;
	if (x<0) x=0;
	if (y<0) y=0;

	const core::dimension2du& Size = src->getDimension();

	if (x>=(s32)Size.Width) x=(s32)Size.Width-1;
	if (y>=(s32)Size.Height) y=(s32)Size.Height-1;
    src->setPixel( (u32)x, (u32)y, color, blend);
}

//! @brief get pixel from signed integer coords only if inside (0,0,w,h) else SColor(0,0,0,0)
//! @author extension 2012 by BenjaminHampe@gmx.de
//! @param signed 32bit x-coord
//! @param signed 32bit y-coord
//! @return ARGB color, when (x,y) outside of (0,0,w,h) return SColor(0,0,0,0)
SColor CImageFactory::getPixelEx( IImage* src, s32 x, s32 y ) const
{
	if (!src) return SColor(0,0,0,0);
	if (x<0) return SColor(0,0,0,0);
	if (y<0) return SColor(0,0,0,0);
	const core::dimension2du& Size = src->getDimension();
	if (x>(s32)Size.Width-1) return SColor(0,0,0,0);
	if (y>(s32)Size.Height-1) return SColor(0,0,0,0);
	return src->getPixel((u32)x,(u32)y);
}

//! @author extension 2012 by BenjaminHampe@gmx.de
//! @brief get pixel from signed integer coords (always)
//!        reads always a pixel in area (0,0,w,h),
//!        needed for scaling functions that need a interpolating pixel better than SColor(0,0,0,0) to give good dsts
//! @param signed 32bit x-coord
//! @param signed 32bit y-coord
//! @return ARGB color, when (x,y) outside of (0,0,w,h) then clamp to (0,0,w,h) - simple border align
SColor CImageFactory::getPixelAlways( IImage* src, s32 x, s32 y ) const
{
	if (!src) return SColor(0,0,0,0);
	if (x<0) x=0;
	if (y<0) y=0;
	const core::dimension2du& Size = src->getDimension();
	if (x>=(s32)Size.Width) x=(s32)Size.Width-1;
	if (y>=(s32)Size.Height) y=(s32)Size.Height-1;
	return src->getPixel( (u32)x, (u32)y);
}

//! create software image with specified format ( no initial filling occurs! )
IImage* CImageFactory::createImage( const core::dimension2du& size, ECOLOR_FORMAT format) const
{
	// return (IImage*)new video::CImage( format, core::dimension2du(width,height));
	return (IImage*)new video::CImage( format, size);
}


//! fill surface with one color
IImage* CImageFactory::createImageFromTexture( IVideoDriver* driver, ITexture* src) const
{
    if (!driver)
        return 0;

    if (!src)
        return 0;

	video::IImage* dst = new video::CImage( src->getColorFormat(), src->getSize() );
    if (!dst)
        return 0;

	return dst;
}

ITexture* CImageFactory::createTexture( IVideoDriver* driver, IImage* src, ILogger* logger) const
{
	if (!driver)
		return 0;

	if (!src)
		return 0;

	ITexture* tex = 0;

	//! my RainbowTexture
	const core::dimension2du SourceSize = src->getDimension();

	core::stringw name(L"img_");
	name+= (s32)SourceSize.Width;
	name+= L"_";
	name+= (s32)SourceSize.Height;
	name+= L"_";
	name+= (s32)video::IImage::getBitsPerPixelFromFormat( src->getColorFormat() );
	name+= L"_";
	name+= (s32)src->getImageDataSizeInBytes();

	//! save states
	bool b0 = driver->getTextureCreationFlag(ETCF_ALLOW_NON_POWER_2);
	bool b1 = driver->getTextureCreationFlag(ETCF_ALWAYS_16_BIT);
	bool b2 = driver->getTextureCreationFlag(ETCF_ALWAYS_32_BIT);
	bool b3 = driver->getTextureCreationFlag(ETCF_CREATE_MIP_MAPS);
	bool b4 = driver->getTextureCreationFlag(ETCF_FORCE_32_BIT_DO_NOT_USE);
	bool b5 = driver->getTextureCreationFlag(ETCF_NO_ALPHA_CHANNEL);
	bool b6 = driver->getTextureCreationFlag(ETCF_OPTIMIZED_FOR_QUALITY);
	bool b7 = driver->getTextureCreationFlag(ETCF_OPTIMIZED_FOR_SPEED);

	//! my states
	driver->setTextureCreationFlag(ETCF_ALLOW_NON_POWER_2,true);
	driver->setTextureCreationFlag(ETCF_ALWAYS_16_BIT,false);
	driver->setTextureCreationFlag(ETCF_ALWAYS_32_BIT,true);
	driver->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS,true);
	driver->setTextureCreationFlag(ETCF_FORCE_32_BIT_DO_NOT_USE,false);
	driver->setTextureCreationFlag(ETCF_NO_ALPHA_CHANNEL,false);
	driver->setTextureCreationFlag(ETCF_OPTIMIZED_FOR_QUALITY,true);
	driver->setTextureCreationFlag(ETCF_OPTIMIZED_FOR_SPEED,false);

	tex = driver->addTexture(name.c_str(), src, 0);

	//! restore states
	driver->setTextureCreationFlag(ETCF_ALLOW_NON_POWER_2,b0);
	driver->setTextureCreationFlag(ETCF_ALWAYS_16_BIT,b1);
	driver->setTextureCreationFlag(ETCF_ALWAYS_32_BIT,b2);
	driver->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS,b3);
	driver->setTextureCreationFlag(ETCF_FORCE_32_BIT_DO_NOT_USE,b4);
	driver->setTextureCreationFlag(ETCF_NO_ALPHA_CHANNEL,b5);
	driver->setTextureCreationFlag(ETCF_OPTIMIZED_FOR_QUALITY,b6);
	driver->setTextureCreationFlag(ETCF_OPTIMIZED_FOR_SPEED,b7);

	return tex;
} // END FUNCTION

	//! quick copy part of image
//! Extensions by _neo_cortex aka BenjaminHampe@gmx.de
//! These functions create a new image and leave the source as it was -> const
IImage* CImageFactory::copyImage( IImage* src, const core::recti& area, video::E_COLOR_PLANE planes ) const
{
    IImage* dst = new CImage( src->getColorFormat(), core::dimension2du( (u32)area.getWidth(), (u32)area.getHeight()) );

    if (!dst)
        return 0;

	//!Blit
    s32 x = area.UpperLeftCorner.X;
    s32 y = area.UpperLeftCorner.Y;
//    u32 bytesPerRow = Pitch * Size.Width * BytesPerPixel;
    u8* ptrSrc = (u8*)src->lock() + ((y*src->getPitch()+x) * src->getBytesPerPixel());
    u8* ptrDst = (u8*)dst->lock() + ((y*dst->getPitch()+x) * dst->getBytesPerPixel());
    for (s32 j = 0; j < (s32)dst->getDimension().Height; j++)
    {
        memcpy( (void*)ptrDst, (void*)ptrSrc, dst->getDimension().Width * dst->getBytesPerPixel());
        ptrSrc += src->getPitch() * src->getDimension().Width;
        ptrDst += dst->getPitch() * dst->getDimension().Width;
    }

	return dst;
}

//! quick copy hole image
IImage* CImageFactory::cloneImage( IImage* src ) const
{
    if (!src)
        return 0;

    IImage* dst = new CImage( src->getColorFormat(), src->getDimension() );
    if (!dst)
        return 0;

	void* srcPtr = src->lock();
	void* dstPtr = dst->lock();
    memcpy( dstPtr, srcPtr, src->getPitch() * src->getDimension().Height );
	dst->unlock();
//	dst->setColorKeyEnabled( IsColorKeyEnabled );
//	dst->setColorKey( ColorKey );
//	dst->setMemoryOwner( true );
	return dst;
}

SColor CImageFactory::getColorFromWavelength( f64 lambda, f64 gamma) const
{
    // setze ? ? [380, 780]
    if (lambda < 380.0) lambda = 380.0;
    if (lambda > 780.0) lambda = 780.0;

    // Fallunterscheidung
    f64 r,g,b,f;

    if ((lambda >= 380.0) && (lambda < 440.0)) { r = (440.0-lambda)/(440.0-380.0); g = 0.0; b = 1.0; }
    else if ((lambda >= 440.0) && (lambda < 490.0)) { r = 0.0; g = (lambda-440.0)/(490.0-440.0); b = 1.0; }
    else if ((lambda >= 490.0) && (lambda < 510.0)) { r = 0.0; g = 1.0; b = (510.0-lambda)/(510.0-490.0); }
    else if ((lambda >= 510.0) && (lambda < 580.0)) { r = (lambda-510.0)/(580.0-510.0); g = 1.0; b = 0.0; }
    else if ((lambda >= 580.0) && (lambda < 645.0)) { r = 1.0; g = (645.0-lambda)/(645.0-580.0); b = 0.0; }
    else /* if ((lambda >= 645.0) && (lambda <= 780.0)) */ { r = 1.0; g = 0.0; b = 0.0; }

    // reduce intesity at the borders
    if ((lambda >= 380.0) && (lambda < 420.0)) { f = 0.3 + 0.7*(lambda-380.0)/(420.0-380.0); }
    else if ((lambda >= 420.0) && (lambda <= 700.0)) { f = 1.0; }
    else /* if ((lambda > 700.0) && (lambda <= 780.0)) */ { f = 0.3 + 0.7*(780.0-lambda)/(780.0-700.0); }

    // eigentliche Korrektur
    if (f!=1.0) { r *= f; g *= f; b *= f; }

    // Gamma Korrektur
    if (gamma!=1.0) { r = pow(r, gamma); g = pow(g, gamma); b = pow(b, gamma); }

    // Clamping to [0,255]
    r *= 255.0; g *= 255.0; b *= 255.0;

    // hoffentlicht optimiert der compiler dies mit mmx und sse befehlen
    if (r<0.0) r=0.0; if (g<0.0) g=0.0; if (b<0.0) b=0.0;

    if (r>255.0) r=255.0; if (g>255.0) g=255.0; if (b>255.0) b=255.0;

    // return ARGB 32bit color (Alpha = 'opaque' = 'nicht transparent' = '255')
    return SColor(255,(u32)r, (u32)g, (u32)b );
}

SColor CImageFactory::getColorFromRainbow( u32 i, u32 count, f64 gamma) const
{
    //! division by zero would lead to runtime error !!!
    if (count < 1) return SColor(255,255,255,255);
	//! just a simple wrapper function, that linear inperpolates
    return getColorFromWavelength(380.0 + 400.0*(f64)i/(f64)count, gamma);
}

//! @author BenjaminHampe@gmx.de
//! @brief fill user defined color-planes with color-planes from another image or blend together
//! @param image to copy color-planes (all pixels involed) from
//! @param image to copy color-planes (all pixels involed) from
//! @param signed 32bit y-coord
//! @return nothing
void CImageFactory::fill( IImage* dst, const SColor& color, E_COLOR_PLANE planes, bool blend) const
{
	if (!dst) return; 														// abort

	SColor c;
	const core::dimension2du& Size = dst->getDimension();
	for (u32 y=0; y<Size.Height; y++)													// loop y
	{	for (u32 x=0; x<Size.Width; x++)												// loop x
		{
			c = color;
			const SColor& old = dst->getPixel(x,y);							// read pixel
			if (!(planes&ECP_ALPHA)) c.setAlpha(old.getAlpha());		// set alpha channel to old pixel, if channel not used
			if (!(planes&ECP_RED)) c.setRed(old.getRed());				// set red channel to old pixel, if channel not used
			if (!(planes&ECP_GREEN)) c.setGreen(old.getGreen());		// set green channel to old pixel, if channel not used
			if (!(planes&ECP_RED)) c.setBlue(old.getBlue());			// set blue channel to old pixel, if channel not used
			dst->setPixel(x,y,c,blend);									// write pixel
		}
	}
}

//! @author extension 2012 by BenjaminHampe@gmx.de
//! @brief count ARGB colors in the image, but better use getUniqueColorArray().size()
//! @param color-planes that will be taken into account during the unique-count-count
//! @return amount of unique ARGB colors in the image
u32 CImageFactory::getUniqueColorCount( IImage* src, E_COLOR_PLANE planes) const
{
	return getUniqueColorArray( src, planes ).size();
}

//! @author extension 2012 by BenjaminHampe@gmx.de
//! @brief array of all unique ARGB colors of the image
//! @param color-planes that will be taken into account during the unique-count-count
//! @return array of all unique ARGB colors of the image
core::array< SColor > CImageFactory::getUniqueColorArray( IImage* src, E_COLOR_PLANE planes) const
{
    core::array< SColor > container;

	if (!src)
		return container;

    if (src->getDimension() == core::dimension2du(0,0))
        return container;

    container.reallocate( src->getDimension().Width * src->getDimension().Height );
    container.set_used(0);

    for (u32 y=0; y<src->getDimension().Height; y++)
    {
        for (u32 x=0; x<src->getDimension().Width; x++)
        {
            SColor color = src->getPixel(x,y);

            if (!(planes & ECP_ALPHA))
				color.setAlpha(0);
            if (!(planes & ECP_RED))
				color.setRed(0);
            if (!(planes & ECP_GREEN))
				color.setGreen(0);
            if (!(planes & ECP_BLUE))
				color.setBlue(0);

            bool found = false;
            for (u32 i=0; i<container.size(); i++)
            {
                if (container[i] == color)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                container.push_back(color);
            }
        }
    }

    return container;
}


IImage* CImageFactory::filter( IImage* dst, E_IMAGE_FILTER myFilter, u32 param) const
{
	switch (myFilter)
	{
		case EIF_SHARPEN: return filter( dst, new CImageFilterSharpenf, true ); break;
		case EIF_SMOOTHEN: return filter( dst, new CImageFilterSmoothingf, true ); break;
		case EIF_BLUR: return filter( dst, new CImageFilterGaussianBlurf, true ); break;
		case EIF_MEAN_REMOVAL: return filter( dst, new CImageFilterMeanRemovalf, true ); break;
		case EIF_EMBOSS: return filter( dst, new CImageFilterEmbossf, true ); break;
		case EIF_EMBOSS_ALL: return filter( dst, new CImageFilterEmbossAllf, true ); break;
		case EIF_EMBOSS_LOSSY: return filter( dst, new CImageFilterEmbossLossyf, true ); break;
		case EIF_EMBOSS_H: return filter( dst, new CImageFilterEmbossHf, true ); break;
		case EIF_EMBOSS_V: return filter( dst, new CImageFilterEmbossVf, true ); break;
		case EIF_EDGE_DETECT: return filter( dst, new CImageFilterEdgeDetectf, true ); break;
		case EIF_SEPIA: return sepia(dst); break;
		case EIF_INVERT: return invert(dst); break;
		case EIF_BLACKWHITE: return blackwhite(dst, param); break;
		case EIF_GREYSCALES: return greyscales(dst); break;
		case EIF_AVERAGE: return average(dst); break;
		case EIF_HDR: return hdr(dst, param); break;
		case EIF_SATURATE: return saturate(dst); break;
		default: break;
	}
	return 0;
}

IImage* CImageFactory::filter( IImage* src, CImageFilter<f32>* filter, bool deleteFilter ) const
{
    if (!src) return 0;
    if (!filter) return 0;
	const core::dimension2du& Size = src->getDimension();

    IImage* dst = new CImage( src->getColorFormat(), Size );

    for (s32 y=0; y<(s32)Size.Height; ++y)
    {
        for (s32 x=0; x<(s32)Size.Width; ++x)
        {
            // use my function getPixel()! to be save at bounds, returns pixel at nearest pos
            SColor c00 = getPixelEx(src, x-1,y-1);
            SColor c01 = getPixelEx(src, x  ,y-1);
            SColor c02 = getPixelEx(src, x+1,y-1);
            SColor c10 = getPixelEx(src, x-1,y  );
            SColor c11 = getPixelEx(src, x  ,y  ); // current pixel (x,y)
            SColor c12 = getPixelEx(src, x+1,y  );
            SColor c20 = getPixelEx(src, x-1,y+1);
            SColor c21 = getPixelEx(src, x  ,y+1);
            SColor c22 = getPixelEx(src, x+1,y+1);

            f32 r =	(f32)c00.getRed()*filter->get(0,0)+
                    (f32)c01.getRed()*filter->get(0,1)+
                    (f32)c02.getRed()*filter->get(0,2)+
                    (f32)c10.getRed()*filter->get(1,0)+
                    (f32)c11.getRed()*filter->get(1,1)+
                    (f32)c12.getRed()*filter->get(1,2)+
                    (f32)c20.getRed()*filter->get(2,0)+
                    (f32)c21.getRed()*filter->get(2,1)+
                    (f32)c22.getRed()*filter->get(2,2);

            f32 g = (f32)c00.getGreen()*filter->get(0,0)+
                    (f32)c01.getGreen()*filter->get(0,1)+
                    (f32)c02.getGreen()*filter->get(0,2)+
                    (f32)c10.getGreen()*filter->get(1,0)+
                    (f32)c11.getGreen()*filter->get(1,1)+
                    (f32)c12.getGreen()*filter->get(1,2)+
                    (f32)c20.getGreen()*filter->get(2,0)+
                    (f32)c21.getGreen()*filter->get(2,1)+
                    (f32)c22.getGreen()*filter->get(2,2);

            f32 b = (f32)c00.getBlue()*filter->get(0,0)+
                    (f32)c01.getBlue()*filter->get(0,1)+
                    (f32)c02.getBlue()*filter->get(0,2)+
                    (f32)c10.getBlue()*filter->get(1,0)+
                    (f32)c11.getBlue()*filter->get(1,1)+
                    (f32)c12.getBlue()*filter->get(1,2)+
                    (f32)c20.getBlue()*filter->get(2,0)+
                    (f32)c21.getBlue()*filter->get(2,1)+
                    (f32)c22.getBlue()*filter->get(2,2);

            setPixelEx(dst, x, y, SColor(c11.getAlpha(),
										(u32)core::s32_clamp( core::round32(r), 0, 255),
										(u32)core::s32_clamp( core::round32(g), 0, 255),
										(u32)core::s32_clamp( core::round32(b), 0, 255)));
        }
    }

	if (deleteFilter)
		delete filter;

    return dst;
}


IImage* CImageFactory::sepia( IImage* src ) const
{
	return 0;
}


IImage* CImageFactory::invert( IImage* src ) const
{
	return 0;
}

IImage* CImageFactory::invert( IImage* src, E_COLOR_PLANE planes ) const
{
	return 0;
}

IImage* CImageFactory::blackwhite( IImage* src, u32 threshold ) const
{
	if (!src)
		return 0;

	IImage* dst = new CImage( src->getColorFormat(), src->getDimension() );
	if (!dst)
		return 0;

	if (threshold<1)
	{
		dst->fill( SColor(255,0,0,0) );
		return dst;
	}
	else if (threshold>=255)
	{
		dst->fill( SColor(255,255,255,255) );
		return dst;
	}
	else
	{
		const core::dimension2du& Size = src->getDimension();
		for (u32 y=0; y<Size.Height; y++)
		{
			for (u32 x=0; x<Size.Width; x++)
			{
				SColor color = src->getPixel(x,y);
				if (((color.getRed() + color.getGreen() + color.getBlue()) / 3) >= threshold)
					color.set(color.getAlpha(),255,255,255);
				else
					color.set(color.getAlpha(),0,0,0);
				dst->setPixel(x,y,color,false);
			}
		}
	}
	return dst;
}


IImage* CImageFactory::greyscales( IImage* src ) const
{
	return 0;
}


IImage* CImageFactory::average( IImage* src ) const
{
	if (!src)
		return 0;

	core::dimension2du Size = src->getDimension();
	video::ECOLOR_FORMAT Format = src->getColorFormat();

	IImage* dst = new CImage( Format, Size );
	if (dst)
	{
		dst->fill( SColor(0,0,0,0) );
		for (u32 y=0; y<Size.Height; y++)
		{
			for (u32 x=0; x<Size.Width; x++)
			{
				SColor color = src->getPixel(x,y);
				const u32 average = color.getAverage();
				color.set( color.getAlpha(), average, average, average);
				dst->setPixel(x,y,color,false);
			}
		}

	}
	return dst;
}


IImage* CImageFactory::hdr( IImage* src, u32 threshold ) const
{
	return 0;
}

//! returns a saturated image
IImage* CImageFactory::saturate( IImage* src ) const
{
	if (!src)
		return 0;

	IImage* dst = new CImage( src->getColorFormat(), src->getDimension() );
	if (!dst)
		return 0;

	u8 max_A(0);
	u8 max_R(0);
	u8 max_G(0);
	u8 max_B(0);
	u8 min_A(255);
	u8 min_R(255);
	u8 min_G(255);
	u8 min_B(255);

	const core::dimension2du& Size = src->getDimension();
	for (u32 y=0; y<Size.Height; y++)
	{
		for (u32 x=0; x<Size.Width; x++)
		{
			const video::SColor& color = src->getPixel(x,y);

			if ( min_A > color.getAlpha()) min_A = color.getAlpha();
			if ( min_R > color.getRed()) min_R = color.getRed();
			if ( min_G > color.getGreen()) min_G = color.getGreen();
			if ( min_B > color.getBlue()) min_B = color.getBlue();

			if ( max_A < color.getAlpha()) max_A = color.getAlpha();
			if ( max_R < color.getRed()) max_R = color.getRed();
			if ( max_G < color.getGreen()) max_G = color.getGreen();
			if ( max_B < color.getBlue()) max_B = color.getBlue();
		}
	}

	const u32 A_diff = max_A-min_A;
	const u32 R_diff = max_R-min_R;
	const u32 G_diff = max_G-min_G;
	const u32 B_diff = max_B-min_B;

	for (u32 y=0; y<Size.Height; y++)
	{
		for (u32 x=0; x<Size.Width; x++)
		{
			video::SColor color = src->getPixel(x,y);
			u32 A = (u32)core::clamp( core::round32( 255.0f*color.getAlpha()/(f32)A_diff ), 0, 255);
			u32 R = (u32)core::clamp( core::round32( 255.0f*color.getRed()/(f32)R_diff ), 0, 255);
			u32 G = (u32)core::clamp( core::round32( 255.0f*color.getGreen()/(f32)G_diff ), 0, 255);
			u32 B = (u32)core::clamp( core::round32( 255.0f*color.getBlue()/(f32)B_diff ), 0, 255);
			dst->setPixel( x,y, SColor(A,R,G,B), false);
		}
	}

	return dst;
}

//! returns a sharpened image
IImage* CImageFactory::sharpen( IImage* src, f32 value ) const
{
	video::IImage* dst = new video::CImage( src->getColorFormat(), src->getDimension(), 0, false, true);
	if (!dst)
	{
		return 0;
	}
	filter(dst, new CImageFilterSharpenf(), true);
    return dst;
}

SColor CImageFactory::getNearestPixel( IImage* src, f32 fx, f32 fy ) const
{
	const s32 i=core::round32(fx);
	const s32 j=core::round32(fy);
	return getPixelAlways(src,i,j);
}

SColor CImageFactory::getBilinearPixelFast( IImage* src, f32 fx, f32 fy ) const
{
	const s32 i=(s32)fx;
	const s32 j=(s32)fy;
	const f32 x=fx-(f32)i;
	const f32 y=fy-(f32)j;
	const core::dimension2du& Size = src->getDimension();
	const s32 ii = (i+1>=(s32)Size.Width) ? i : i+1;
	const s32 jj = (j+1>=(s32)Size.Height) ? j : j+1;
	const SColor& cA=getPixelAlways(src,i,j);
	const SColor& cB=getPixelAlways(src,ii,j);
	const SColor& cC=getPixelAlways(src,ii,jj);
	const SColor& cD=getPixelAlways(src,i,jj);
	const f32 rA=(f32)cA.getRed();
	const f32 rB=(f32)cB.getRed();
	const f32 rC=(f32)cC.getRed();
	const f32 rD=(f32)cD.getRed();
	const f32 gA=(f32)cA.getGreen();
	const f32 gB=(f32)cB.getGreen();
	const f32 gC=(f32)cC.getGreen();
	const f32 gD=(f32)cD.getGreen();
	const f32 bA=(f32)cA.getBlue();
	const f32 bB=(f32)cB.getBlue();
	const f32 bC=(f32)cC.getBlue();
	const f32 bD=(f32)cD.getBlue();
	const f32 e=(1.0f-x);
	const f32 f=(1.0f-y);
	const f32 fr = rA*e*f+rB*x*f+rC*x*y+rD*e*y;
	const f32 fg = gA*e*f+gB*x*f+gC*x*y+gD*e*y;
	const f32 fb = bA*e*f+bB*x*f+bC*x*y+bD*e*y;
	return SColor(255,(u32)fr,(u32)fg,(u32)fb);
}

SColor CImageFactory::getBilinearPixel( IImage* src, f32 fx, f32 fy, E_COLOR_PLANE planes, SColor* colorKey) const
{
	const s32 i=(s32)fx;     // dirty round (fast)
	const s32 j=(s32)fy;     // dirty round (fast)
	const f32 x=fx-(f32)i;   // dirty difference from pixel (fast)
	const f32 y=fy-(f32)j;   // dirty difference from pixel (fast)
	const f32 e=(1.0f-x);    // A+AB*t = B+AB*(1-t) = B-AB*t = B+BA*t
	const f32 f=(1.0f-y);    // A+AB*t = B+AB*(1-t) = B-AB*t = B+BA*t
	const SColor& A=getPixelAlways(src, i,   j); // read pixel, even if out of bounds (gets most nearest pixel)
	const SColor& B=getPixelAlways(src, i+1, j); // read pixel, even if out of bounds (gets most nearest pixel)
	const SColor& C=getPixelAlways(src, i+1, j+1); // read pixel, even if out of bounds (gets most nearest pixel)
	const SColor& D=getPixelAlways(src, i,   j+1); // read pixel, even if out of bounds (gets most nearest pixel)

    if (colorKey && ((A==*colorKey) || (B==*colorKey) || (C==*colorKey) || (D==*colorKey)))
        return *colorKey;

    u32 a(0),r(0),g(0),b(0);

    if (planes & ECP_ALPHA)
    {   f32 fa = A.getAlpha()*e*f+B.getAlpha()*x*f+C.getAlpha()*x*y+D.getAlpha()*e*y;
        a = (u32)core::s32_clamp( (s32)core::round32(fa), 0, 255);
    }
    if (planes & ECP_RED)
    {   f32 fr = A.getRed()*e*f+B.getRed()*x*f+C.getRed()*x*y+D.getRed()*e*y;
        r = (u32)core::s32_clamp( (s32)core::round32(fr), 0, 255);
    }
    if (planes & ECP_GREEN)
    {   f32 fg = A.getGreen()*e*f+B.getGreen()*x*f+C.getGreen()*x*y+D.getGreen()*e*y;
        g = (u32)core::s32_clamp( (s32)core::round32(fg), 0, 255);
    }
    if (planes & ECP_BLUE)
    {   f32 fb = A.getBlue()*e*f+B.getBlue()*x*f+C.getBlue()*x*y+D.getBlue()*e*y;
        b = (u32)core::s32_clamp( (s32)core::round32(fb), 0, 255);
    }
    return SColor(a,r,g,b);
}

f32 CImageFactory::getBicubicFactor(const f32& arg) const
{
	const f32 f1 = arg>0.0f?arg:0.0f; const f32 f2 = arg-1.0f; const f32 f3 = arg+1.0f; const f32 f4 = arg+2.0f;
	const f32 n1 = f2>0.0f?f2:0.0f;	const f32 n2 = f3>0.0f?f3:0.0f;	const f32 n3 = f4>0.0f?f4:0.0f;
	return (f32)((n3*n3*n3 - 4.0f*n2*n2*n2 + 6.0f*f1*f1*f1 - 4.0f*n1*n1*n1)/6.0f);
}

SColor CImageFactory::getBicubicPixel( IImage* src, f32 fx, f32 fy, E_COLOR_PLANE planes, SColor* colorKey) const
{
	// abort, if nothing todo
	if (planes == ECP_NONE)
		return ((colorKey) ? (*colorKey) : SColor(0,0,0,0));

	// calculate 4x4 indices
	const s32 x1=(s32)fx-(fx>=0?0:1);	const s32 x2=x1-1;	const s32 x3=x1+1;	const s32 x4=x3+1;
	const s32 y1=(s32)fy-(fy>=0?0:1);	const s32 y2=y1-1;  const s32 y3=y1+1;	const s32 y4=y3+1;
	const f32 dx=fx-x1;	const f32 dy=fy-y1;

	// 4x4 Pixels for bicubic Interpolation
	const SColor& C0 = getPixelAlways(src, x2,y2);	const SColor& C1 = getPixelAlways(src, x1,y2);
	const SColor& C2 = getPixelAlways(src, x3,y2);	const SColor& C3 = getPixelAlways(src, x4,y2);
	const SColor& C4 = getPixelAlways(src, x2,y1);	const SColor& C5 = getPixelAlways(src, x1,y1);
	const SColor& C6 = getPixelAlways(src, x3,y1);	const SColor& C7 = getPixelAlways(src, x4,y1);
	const SColor& C8 = getPixelAlways(src, x2,y3);	const SColor& C9 = getPixelAlways(src, x1,y3);
	const SColor& CA = getPixelAlways(src, x3,y3);	const SColor& CB = getPixelAlways(src, x4,y3);
	const SColor& CC = getPixelAlways(src, x2,y4);	const SColor& CD = getPixelAlways(src, x1,y4);
	const SColor& CE = getPixelAlways(src, x3,y4);	const SColor& CF = getPixelAlways(src, x4,y4);

	// abort, if nothing todo
	// --> return ColorKey as dst, if min 1 out of 16 pixel equals ColorKey --> sharp edges, but some pixel are lost
	if (colorKey && ((C0==*colorKey) || (C1==*colorKey) || (C2==*colorKey) || (C3==*colorKey) ||
					(C4==*colorKey) || (C5==*colorKey) || (C6==*colorKey) || (C7==*colorKey) ||
                    (C8==*colorKey) || (C9==*colorKey) || (CA==*colorKey) || (CB==*colorKey) ||
                    (CC==*colorKey) || (CD==*colorKey) || (CE==*colorKey) || (CF==*colorKey))) return *colorKey;

	// calculate factors
	const f32 Fx1 = getBicubicFactor(-1.0f-dx );	const f32 Fx2 = getBicubicFactor( 0.0f+dx );
	const f32 Fx3 = getBicubicFactor( 1.0f-dx );	const f32 Fx4 = getBicubicFactor( 2.0f-dx );
	const f32 Fy1 = getBicubicFactor( dy+1.0f );	const f32 Fy2 = getBicubicFactor( dy+0.0f );
	const f32 Fy3 = getBicubicFactor( dy-1.0f );	const f32 Fy4 = getBicubicFactor( dy-2.0f );

	// calculate final color, default SColor(0,0,0,0)
	u32 uA(0), uR(0), uG(0), uB(0);
	if (planes & ECP_ALPHA)
	{
		f32 fa = Fx1*Fy1*C0.getAlpha() + Fx2*Fy1*C1.getAlpha() + Fx3*Fy1*C2.getAlpha() + Fx4*Fy1*C3.getAlpha() +
		Fx1*Fy2*C4.getAlpha() + Fx2*Fy2*C5.getAlpha() + Fx3*Fy2*C6.getAlpha() + Fx4*Fy2*C7.getAlpha() +
        Fx1*Fy3*C8.getAlpha() + Fx2*Fy3*C9.getAlpha() + Fx3*Fy3*CA.getAlpha() + Fx4*Fy3*CB.getAlpha() +
        Fx1*Fy4*CC.getAlpha() + Fx2*Fy4*CD.getAlpha() + Fx3*Fy4*CE.getAlpha() + Fx4*Fy4*CF.getAlpha();
        uA = (u32)core::clamp( core::round32(fa), 0, 255);
	}

	if (planes & ECP_RED)
	{
		f32 fr = Fx1*Fy1*C0.getRed() + Fx2*Fy1*C1.getRed() + Fx3*Fy1*C2.getRed() + Fx4*Fy1*C3.getRed() +
		Fx1*Fy2*C4.getRed() + Fx2*Fy2*C5.getRed() + Fx3*Fy2*C6.getRed() + Fx4*Fy2*C7.getRed() +
		Fx1*Fy3*C8.getRed() + Fx2*Fy3*C9.getRed() + Fx3*Fy3*CA.getRed() + Fx4*Fy3*CB.getRed() +
		Fx1*Fy4*CC.getRed() + Fx2*Fy4*CD.getRed() + Fx3*Fy4*CE.getRed() + Fx4*Fy4*CF.getRed();
		uR = (u32)core::clamp( core::round32(fr), 0, 255);
	}

	if (planes & ECP_GREEN)
	{
		f32 fg = Fx1*Fy1*C0.getGreen() + Fx2*Fy1*C1.getGreen() + Fx3*Fy1*C2.getGreen() + Fx4*Fy1*C3.getGreen() +
		Fx1*Fy2*C4.getGreen() + Fx2*Fy2*C5.getGreen() + Fx3*Fy2*C6.getGreen() + Fx4*Fy2*C7.getGreen() +
		Fx1*Fy3*C8.getGreen() + Fx2*Fy3*C9.getGreen() + Fx3*Fy3*CA.getGreen() + Fx4*Fy3*CB.getGreen() +
		Fx1*Fy4*CC.getGreen() + Fx2*Fy4*CD.getGreen() + Fx3*Fy4*CE.getGreen() + Fx4*Fy4*CF.getGreen();
        uG = (u32)core::clamp( core::round32(fg), 0, 255);
	}

	if (planes & ECP_BLUE)
	{
        f32 fb = Fx1*Fy1*C0.getBlue() + Fx2*Fy1*C1.getBlue() + Fx3*Fy1*C2.getBlue() + Fx4*Fy1*C3.getBlue() +
        Fx1*Fy2*C4.getBlue() + Fx2*Fy2*C5.getBlue() + Fx3*Fy2*C6.getBlue() + Fx4*Fy2*C7.getBlue() +
        Fx1*Fy3*C8.getBlue() + Fx2*Fy3*C9.getBlue() + Fx3*Fy3*CA.getBlue() + Fx4*Fy3*CB.getBlue() +
        Fx1*Fy4*CC.getBlue() + Fx2*Fy4*CD.getBlue() + Fx3*Fy4*CE.getBlue() + Fx4*Fy4*CF.getBlue();
        uB = (u32)core::clamp( core::round32(fb), 0, 255);
	}

	// return final color
    return SColor(uA,uR,uG,uB);
}

IImage* CImageFactory::resize( IImage* src, const core::dimension2du& newSize, s32 scaleOp, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen) const
{
	if (!src)
		return 0;

    switch((video::E_IMAGE_SCALE_OPERATION)scaleOp)
    {
        case EISO_FAST: return resizeFast(src, newSize,planes); break;
        case EISO_NEAREST: return resizeNearest(src, newSize,planes); break;
        case EISO_BILINEAR: return resizeBilinear(src, newSize,planes); break;
        case EISO_BICUBIC: return resizeBicubic(src, newSize,planes); break;
        default: break;
    }
    return 0;
}

IImage* CImageFactory::resizeNearest( IImage* src, const core::dimension2du& newSize, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen) const
{
	// abort
	if (!src)
		return 0;

	// abort
	if (newSize == core::dimension2du(0,0)) return 0;

	// abort
	const core::dimension2du& Size = src->getDimension();
	if (newSize == Size)
	{
		return cloneImage(src);
	}

    core::dimension2du nSize = newSize;

	// calculate width from aspect-ratio
	if (nSize.Width == 0)
		nSize.Width = (u32)((f32)nSize.Height*(f32)Size.Width/(f32)Size.Height);

	// calculate height from aspect-ratio
	if (nSize.Height == 0)
		nSize.Height = (u32)((f32)nSize.Width*(f32)Size.Height/(f32)Size.Width);

    // create new image 32bit ARGB, fill with zero
	IImage* dst = (IImage*)new CImage(src->getColorFormat(), nSize);
	if (!dst)
        return 0;

    const f32 zoomX = ((f32)nSize.Width)/((f32)Size.Width);
	const f32 zoomY = ((f32)nSize.Height)/((f32)Size.Height);

	// RGB color planes ( alphachannel always 255 == not transparent)
	if (planes==ECP_RGB)
	{
		for (u32 y=0; y<nSize.Height; y++)
        {
            for (u32 x=0; x<nSize.Width; x++)
            {
                u32 u=(u32)((f32)x/zoomX); // interpolate pos of current pixel in img to nearest of src
                u32 v=(u32)((f32)y/zoomY); // interpolate pos of current pixel in img to nearest of src
                SColor color = getPixelAlways(src,u,v);
                color.setAlpha(255);
                dst->setPixel(x,y,color,false);
            }
        }
	}
    else
	{
		for (u32 y=0; y<nSize.Height; y++)
        {
            for (u32 x=0; x<nSize.Width; x++)
            {
                u32 u=(u32)((f32)x/zoomX); // interpolate pos of current pixel in img to nearest of src
                u32 v=(u32)((f32)y/zoomY); // interpolate pos of current pixel in img to nearest of src
                SColor color = getPixelAlways(src,u,v);
                dst->setPixel(x,y,color,false);
            }
        }
	}

	return dst;
}

IImage* CImageFactory::resizeFast( IImage* src, const core::dimension2du& newSize, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen ) const
{
	// abort
	if (!src)
		return 0;

	// abort
	if (newSize == core::dimension2du(0,0)) return 0;

	// abort
	const core::dimension2du& Size = src->getDimension();
	if (newSize == Size)
	{
		return cloneImage(src);
	}

    core::dimension2du nSize = newSize;

	// calculate width from aspect-ratio
	if (nSize.Width == 0)
		nSize.Width = (u32)((f32)nSize.Height*(f32)Size.Width/(f32)Size.Height);

	// calculate height from aspect-ratio
	if (nSize.Height == 0)
		nSize.Height = (u32)((f32)nSize.Width*(f32)Size.Height/(f32)Size.Width);

    // create new image 32bit ARGB, fill with zero
	IImage* dst = (IImage*)new CImage(src->getColorFormat(), nSize);
	if (!dst)
        return 0;

    const f32 zoomX = ((f32)nSize.Width)/((f32)Size.Width);
	const f32 zoomY = ((f32)nSize.Height)/((f32)Size.Height);

    for (u32 y=0; y<nSize.Height; y++)
    {
        for (u32 x=0; x<nSize.Width; x++)
        {
            f32 u=(f32)x/zoomX; // interpolate pos of current pixel in img LINEAR to src
            f32 v=(f32)y/zoomY; // interpolate pos of current pixel in img LINEAR to src
            SColor color = getBilinearPixelFast(src,u,v);
            dst->setPixel(x,y,color,false);
        }
    }
	return dst;
}

IImage* CImageFactory::resizeBilinear( IImage* src, const core::dimension2du& newSize, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen) const
{
	// abort
	if (!src) return 0;

	// abort
	if (newSize == core::dimension2du(0,0)) return 0;

	// abort
	const core::dimension2du& Size = src->getDimension();
	if (newSize == Size)
	{
		return cloneImage(src);
	}

    core::dimension2du nSize = newSize;

	// calculate width from aspect-ratio
	if (nSize.Width == 0)
		nSize.Width = (u32)((f32)nSize.Height*(f32)Size.Width/(f32)Size.Height);

	// calculate height from aspect-ratio
	if (nSize.Height == 0)
		nSize.Height = (u32)((f32)nSize.Width*(f32)Size.Height/(f32)Size.Width);

    // create new image 32bit ARGB, fill with zero
	IImage* dst = (IImage*)new CImage(src->getColorFormat(), nSize);
	if (!dst)
        return 0;

    const f32 zoomX = ((f32)nSize.Width)/((f32)Size.Width);
	const f32 zoomY = ((f32)nSize.Height)/((f32)Size.Height);

    for (u32 y=0; y<nSize.Height; y++)
    {
        for (u32 x=0; x<nSize.Width; x++)
        {
            f32 u=(f32)x/zoomX; // interpolate pos of current pixel in img LINEAR to src
            f32 v=(f32)y/zoomY; // interpolate pos of current pixel in img LINEAR to src
            SColor color = getBilinearPixel(src,u,v,planes);
            dst->setPixel(x,y,color,false);
        }
    }
	return dst;
}

IImage* CImageFactory::resizeBicubic( IImage* src, const core::dimension2du& newSize, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen) const
{
	// abort
	if (!src)
		return 0;

	// abort
	if (newSize == core::dimension2du(0,0)) return 0;

	// abort
	const core::dimension2du& Size = src->getDimension();
	if (newSize == Size)
	{
		return cloneImage(src);
	}

    core::dimension2du nSize = newSize;

	// calculate width from aspect-ratio
	if (nSize.Width == 0)
		nSize.Width = (u32)((f32)nSize.Height*(f32)Size.Width/(f32)Size.Height);

	// calculate height from aspect-ratio
	if (nSize.Height == 0)
		nSize.Height = (u32)((f32)nSize.Width*(f32)Size.Height/(f32)Size.Width);

    // create new image 32bit ARGB, fill with zero
	IImage* dst = (IImage*)new CImage(src->getColorFormat(), nSize);
	if (!dst)
        return 0;

    const f32 zoomX = ((f32)nSize.Width)/((f32)Size.Width);
	const f32 zoomY = ((f32)nSize.Height)/((f32)Size.Height);

    for (u32 y=0; y<nSize.Height; y++)
    {
        for (u32 x=0; x<nSize.Width; x++)
        {
            f32 u=(f32)x/zoomX; // interpolate pos of current pixel in img LINEAR to src
            f32 v=(f32)y/zoomY; // interpolate pos of current pixel in img LINEAR to src
            SColor color = getBicubicPixel(src,u,v,planes);
            dst->setPixel(x,y,color,false);
        }
    }
	return dst;
}

IImage* CImageFactory::scale( IImage* src, const core::vector2df& scaleXY, s32 scaleOp, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen) const
{
	if (!src)
		return 0;

 	u32 pixelX = (u32)core::clamp<f32>(scaleXY.X*src->getDimension().Width,0,4096);
 	u32 pixelY = (u32)core::clamp<f32>(scaleXY.Y*src->getDimension().Height,0,4096);
    return resize( src, core::dimension2du(pixelX,pixelY), scaleOp, planes, bPreserveAspect, bSharpen );
}

IImage* CImageFactory::scaleNearest( IImage* src, const core::vector2df& scaleXY, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen) const
{
	if (!src)
		return 0;

 	u32 pixelX = (u32)core::clamp<f32>(scaleXY.X*src->getDimension().Width,0,4096);
 	u32 pixelY = (u32)core::clamp<f32>(scaleXY.Y*src->getDimension().Height,0,4096);
    return resizeNearest( src, core::dimension2du(pixelX,pixelY), planes, bPreserveAspect, bSharpen );
}

IImage* CImageFactory::scaleFast( IImage* src, const core::vector2df& scaleXY, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen) const
{
	if (!src)
		return 0;

 	u32 pixelX = (u32)core::clamp<f32>(scaleXY.X*src->getDimension().Width,0,4096);
 	u32 pixelY = (u32)core::clamp<f32>(scaleXY.Y*src->getDimension().Height,0,4096);
    return resizeFast( src, core::dimension2du(pixelX,pixelY), planes, bPreserveAspect, bSharpen );
}

IImage* CImageFactory::scaleBilinear( IImage* src, const core::vector2df& scaleXY, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen) const
{
	if (!src)
		return 0;

 	u32 pixelX = (u32)core::clamp<f32>(scaleXY.X*src->getDimension().Width,0,4096);
 	u32 pixelY = (u32)core::clamp<f32>(scaleXY.Y*src->getDimension().Height,0,4096);
    return resizeBilinear( src, core::dimension2du(pixelX,pixelY), planes, bPreserveAspect, bSharpen );
}

IImage* CImageFactory::scaleBicubic( IImage* src, const core::vector2df& scaleXY, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen) const
{
	if (!src)
		return 0;

 	u32 pixelX = (u32)core::clamp<f32>(scaleXY.X*src->getDimension().Width,0,4096);
 	u32 pixelY = (u32)core::clamp<f32>(scaleXY.Y*src->getDimension().Height,0,4096);
    return resizeBicubic( src, core::dimension2du(pixelX,pixelY), planes, bPreserveAspect, bSharpen );
}


IImage* CImageFactory::rotateLeft( IImage* src ) const
{
	if (!src)
		return 0;

	const core::dimension2du& Size = src->getDimension();

	IImage* dst = new CImage( src->getColorFormat(), Size );
	if (!dst)
		return 0;

	for (u32 y=0; y<Size.Height; y++)
	{
		for (u32 x=0; x<Size.Width; x++)
		{
			SColor color = src->getPixel(x,y);
			dst->setPixel(y, Size.Width-1-x, color);
		}
	}

	return dst;
}


IImage*	CImageFactory::rotateRight( IImage* src ) const
{
	if (!src)
		return 0;

	const core::dimension2du& Size = src->getDimension();

	IImage* dst = new CImage( src->getColorFormat(), Size );
	if (!dst)
		return 0;

	for (u32 y=0; y<Size.Height; y++)
	{
		for (u32 x=0; x<Size.Width; x++)
		{
			SColor color = src->getPixel(x,y);
			dst->setPixel(Size.Height-1-y, x, color);
		}
	}

	return dst;
}

bool CImageFactory::flipH( IImage* dst ) const
{
	if (!dst) return false;
	const core::dimension2du& Size = dst->getDimension();
	u32 HalfWidth = Size.Width >> 1;
	SColor color1, color2;

	for (u32 y=0; y<Size.Height; y++)
	{
		for (u32 x=0; x<HalfWidth; x++)
		{
			color1 = dst->getPixel(x,y);
			color2 = dst->getPixel(Size.Width-1-x,y);
			dst->setPixel(x,y,color2);
			dst->setPixel(Size.Width-1-x,y,color1);
		}
	}
	return true;
}

bool CImageFactory::flipV( IImage* dst ) const
{
	if (!dst) return false;
	const core::dimension2du& Size = dst->getDimension();

	u32 HalfHeight = Size.Height >> 1;
	SColor color1, color2;

	for (u32 y=0; y<HalfHeight; y++)
	{
		for (u32 x=0; x<Size.Width; x++)
		{
			color1 = dst->getPixel(x,y);
			color2 = dst->getPixel(x,Size.Height-1-y);
			dst->setPixel(x,y,color2);
			dst->setPixel(x,Size.Height-1-y,color1);
		}
	}
	return true;
}

bool CImageFactory::rotate180( IImage* dst ) const
{
	if (!dst) return false;
	const core::dimension2du& Size = dst->getDimension();

	u32 m = Size.Height >> 1;
	SColor color1, color2;

	for (u32 y=0; y<m; y++)
	{
		for (u32 x=0; x<Size.Width; x++)
		{
			color1 = dst->getPixel(x,y);
			color2 = dst->getPixel(x,Size.Height-1-y);
			dst->setPixel(x,y,color2);
			dst->setPixel(x,Size.Height-1-y,color1);
		}
	}
	return true;
}

IImage*	CImageFactory::rotate( IImage* src, f32 angleDegreesCCW, SColor* colorKey ) const
{
	if (!src)
		return 0;

	const core::dimension2du& Size = src->getDimension();

	// Winkel
	while (angleDegreesCCW<0.0f)	{	angleDegreesCCW+=360.0f;	}
	while (angleDegreesCCW>=360.0f)	{	angleDegreesCCW-=360.0f;	}

	//
	if (core::equals(angleDegreesCCW,0.0f))
	{
		return cloneImage(src);
	}
	else if (core::equals(angleDegreesCCW,90.0f))
	{
		return rotateLeft(src);
	}
	else if (core::equals(angleDegreesCCW,270.0f))
	{
		return rotateRight(src);
	}
	else if (core::equals(angleDegreesCCW,180.0f))
    {
        IImage* tmp = cloneImage(src);
		rotate180(tmp);
        return tmp;
    }
    else
    {
        // alpha
        const f32 a=(360.0f-angleDegreesCCW)*core::DEGTORAD;
        const f32 sa=sinf(a);
        const f32 ca=cosf(a);

        // gamma
        const f32 g=angleDegreesCCW*core::DEGTORAD;
        const f32 sg=sinf(g);
        const f32 cg=cosf(g);

        // BERECHNNUNG des Mittelpunktes von MEM
        const f32 mXh=0.5f*(f32)Size.Width;
        const f32 mYh=0.5f*(f32)Size.Height;

        // BERECHNNUNG der Eckpunkte
        const f32 Ax= mXh, 	Ay=-mYh;
        const f32 Bx=-mXh,	By=-mYh;
        const f32 Cx=-mXh, 	Cy= mYh;
        const f32 Dx= mXh, 	Dy= mYh;

        // TRANSFORMATION der Eckpunkte
        f32 Anx=Ax*ca - Ay*sa;
        f32 Any=Ax*sa + Ay*ca;
        f32 Bnx=Bx*ca - By*sa;
        f32 Bny=Bx*sa + By*ca;
        f32 Cnx=Cx*ca - Cy*sa;
        f32 Cny=Cx*sa + Cy*ca;
        f32 Dnx=Dx*ca - Dy*sa;
        f32 Dny=Dx*sa + Dy*ca;

        // BERECHNUNG der FINAL WIDTH and HEIGHT
        f32 minX=0.0f, maxX=0.0f;
        f32 minY=0.0f, maxY=0.0f;
        if (Anx<minX) minX=Anx;		 if (Any<minY) minY=Any;
        if (Anx>maxX) maxX=Anx;		 if (Any>maxY) maxY=Any;
        if (Bnx<minX) minX=Bnx;		 if (Bny<minY) minY=Bny;
        if (Bnx>maxX) maxX=Bnx;		 if (Bny>maxY) maxY=Bny;
        if (Cnx<minX) minX=Cnx;		 if (Cny<minY) minY=Cny;
        if (Cnx>maxX) maxX=Cnx;		 if (Cny>maxY) maxY=Cny;
        if (Dnx<minX) minX=Dnx;		 if (Dny<minY) minY=Dny;
        if (Dnx>maxX) maxX=Dnx;		 if (Dny>maxY) maxY=Dny;

        f32 fdx=maxX-minX;
        f32 fdy=maxY-minY;

        u32 dx=(u32)core::abs_<s32>( core::round32(fdx) );
        u32 dy=(u32)core::abs_<s32>( core::round32(fdy) );

		core::stringc txt = "New Image with size (";
		txt += dx;
		txt += ", ";
		txt += dy;
		txt += ")";
		os::Printer::log(txt.c_str(), ELL_INFORMATION);

        // FINAL MEMBLOCK
        IImage* dst = new CImage( src->getColorFormat(), core::dimension2du(dx,dy));
        if (!dst)
            return 0;

		const core::dimension2du& Size2 = dst->getDimension();

        // BERECHNUNG des Mittelpunktes von FINAL
        f32 fdxh=0.5f*fdx;
        f32 fdyh=0.5f*fdy;

        // LET'S ROTATE
        s32 x,y;
        SColor color;
        f32 x0,y0,x1,y1;

		os::Printer::log("OK", ELL_INFORMATION);
        // Fuer alle Punkte im Zielbild den entsprechenden Punkt im Ausgangsbild
        // suchen. Dadurch entstehen keine Luecken im Bild.
        for (u32 j=0; j<dy; j++)
        {
            for (u32 i=0; i<dx; i++)
            {
                if ( (i<Size2.Width) && (j<Size2.Height) )
                {
					x0=(f32)i-fdxh; // relativ zu FinalMem Mittelpunkt
					y0=(f32)j-fdyh; // relativ zu FinalMem Mittelpunkt
					x1=(cg*x0-sg*y0)+mXh; // relativ zu SourceMem Mittelpunkt
					y1=(cg*y0+sg*x0)+mYh; // relativ zu SourceMem Mittelpunkt
					x=core::round32(x1);
					y=core::round32(y1);

					// PIXEL von SourceMem
					if ((x>=0) && (y>=0) && (x<Size.Width) && (y<Size.Height))
					{
						color=src->getPixel((u32)x, (u32)y);
					}
					else
					{
						if (colorKey)
							color=*colorKey;
						else
							color.color = 0;
					}

					dst->setPixel( i,j,color );
                }
            }
        }
        return dst;
    }
    return 0;
}

//! returns a (u,v) repeated image (tiles will be scaled bilinear if necessary)
IImage*	CImageFactory::repeat( IImage* src, u32 w, u32 h, f32 uRepeat, f32 vRepeat, s32 scaleOP, bool bPreserveAspect, bool bSharpen) const
{
	return 0;
}


void CImageFactory::drawImage( IImage* src, IImage* dst, const Point& pos, const core::dimension2d<u32>& size, bool bTransparent, bool blend) const
{
	if (!src) return;

	const u32 x_max = core::min_<u32>( dst->getDimension().Width, src->getDimension().Width );
	const u32 y_max = core::min_<u32>( dst->getDimension().Height, src->getDimension().Height );

	for (u32 y=0; y<y_max; y++)
	{
		for (u32 x=0; x<x_max; x++)
		{
			const SColor& colorNow = src->getPixel(x,y);
			setPixelEx( dst, (s32)x+pos.X, (s32)y+pos.Y, colorNow, blend);
		}
	}
}

// //! draw chess-board pattern with 2 colors and each rect with size tileSize
void CImageFactory::drawCheckered( IImage* dst, const core::dimension2du& tileSize, const video::SColor& c1, const video::SColor& c2 ) const
{
	const core::dimension2du& Size = dst->getDimension();
	core::dimension2d<u32> dPixel =  tileSize;

	if (dPixel.Width < 2)
		dPixel.Width = 2;

	if (dPixel.Height < 2)
		dPixel.Height = 2;

	if (dPixel.Width > Size.Width)
		dPixel.Width = Size.Width;

	if (dPixel.Height > Size.Height)
		dPixel.Height = Size.Height;

	SColor color;
	s32 m(0),n(0);
	for (u32 y=0; y<Size.Height; y+=dPixel.Height)
	{
		for (u32 x=0; x<Size.Width; x+=dPixel.Width)
		{
			if ( (m+n)%2 == 0 )
			{
				color = c1;
			}
			else
			{
				color = c2;
			}
			drawRect(dst, core::recti( (s32)x, (s32)y, (s32)(x+dPixel.Width), (s32)(y+dPixel.Height) ), color, 0, false);
			m++;
		}
		if (m%2==1)
		{
			m++; // make sure (m) is even
		}
		n++;
	}

}

//! draw a Bresenham-line, 1 color, option to blend
void CImageFactory::drawLine( IImage* dst, const Point& p1, const Point& p2, const SColor& color, bool blend) const
{
	if (!dst)
		return;

	const core::dimension2du& Size = dst->getDimension();
	const s32 dx = core::abs_<s32>(p2.X - p1.X);
	const s32 dy = core::abs_<s32>(p2.Y - p1.Y);

	if (dx==0 && dy==0)
		return;

	s32 sx = 1; // traverse direction sign, default +1
	s32 sy = 1; // traverse direction sign, default +1
	if (p1.X > p2.X) // if traverse left x direction sign = -1
		sx = -1;
	if (p1.Y > p2.Y) // if traverse down y direction sign = -1
		sy = -1;

	s32 err = dx-dy;
	s32 e2 = 0;
	s32 x = p1.X;
	s32 y = p1.Y;

	while (1)
	{
		setPixelEx(dst, x,y,color,blend);

		if (x == p2.X && y == p2.Y)
			break;

		e2 = err << 1;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}

		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
}

//! draw a Bresenham-line, 2 colors, option to blend
void CImageFactory::drawLine( IImage* dst, const Point& p1, const Point& p2, const SColor& c1, const SColor& c2, bool blend) const
{
	if (!dst)
		return;

	const core::dimension2du& Size = dst->getDimension();
	const s32 dx = core::abs_<s32>(p2.X - p1.X);
	const s32 dy = core::abs_<s32>(p2.Y - p1.Y);

	if (dx==0 && dy==0)
		return;

	s32 sx = 1; // sign
	s32 sy = 1; // sign
	if (p1.X > p2.X)
		sx = -1;
	if (p1.Y > p2.Y)
		sy = -1;

	s32 err = dx-dy;
	s32 e2 = 0;
	s32 x = p1.X;
	s32 y = p1.Y;

	s32 numpixels = 0;

	// count pixels
	while (1)
	{
		numpixels++;

		if (x == p2.X && y == p2.Y)
			break;

		e2 = err << 1;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}

		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}

	}

	// reset vars;
	err = dx-dy;
	e2 = 0;
	x = p1.X;
	y = p1.Y;

	// values for linear color interpolation
	const f32 fA1=(f32)c1.getAlpha();
	const f32 fR1=(f32)c1.getRed();
	const f32 fG1=(f32)c1.getGreen();
	const f32 fB1=(f32)c1.getBlue();
	const f32 fAdiff=(f32)c2.getAlpha()-fA1;
	const f32 fRdiff=(f32)c2.getRed()-fR1;
	const f32 fGdiff=(f32)c2.getGreen()-fG1;
	const f32 fBdiff=(f32)c2.getBlue()-fB1;

	// actual drawing
	f32 f=0.f;
	s32 k=0;
	u32 cR=0, cG=0, cB=0, cA=0;
	while (1)
	{
		f = (f32)k/(f32)numpixels;
		k++;

		// maybe faster under the assumption that colors have most likely same alpha value
		if (core::equals(fAdiff, 0.f))
			cA = c1.getAlpha();
		else
			cA = (u32)core::clamp( core::round32(fA1+fAdiff*f), 0, 255);

		cR = (u32)core::clamp( core::round32(fR1+fRdiff*f), 0, 255);
		cG = (u32)core::clamp( core::round32(fG1+fGdiff*f), 0, 255);
		cB = (u32)core::clamp( core::round32(fB1+fBdiff*f), 0, 255);

		// draw pixel
       setPixelEx( dst, x, y, SColor( cA, cR, cG, cB), blend);

		if (x == p2.X && y == p2.Y)
			break;

		e2 = err << 1;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}

		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
}

//! MS Paint Style
bool CImageFactory::floodFill( IImage* dst, s32 x, s32 y, const SColor& fillcolor, const SColor& old) const
{
	if (!dst)
		return false;

	SColor oldcolor(old);
	if (old.color==0)
		oldcolor=getPixelEx(dst,x,y);

	if (getPixelEx(dst,x,y)==fillcolor)
       return false;

	s32 lg, rg, px=x;
	while(x>=0 && getPixelEx(dst,x,y)==oldcolor)
	{
		setPixelEx(dst,x,y,fillcolor);
		x--;
	}

	lg=x+1;
	x=px+1;

	const core::dimension2du& Size = dst->getDimension();
	while(x<(s32)Size.Width && getPixelEx(dst,x,y)==oldcolor)
	{
		setPixelEx(dst,x,y,fillcolor);
		x++;
	}
	rg=x-1;

	for(x=rg; x>=lg; x--)
	{
		//! alle Zeilen oberhalb
		if((getPixelEx(dst,x,y-1)==oldcolor) && (y-1>0))
			floodFill( dst,x, y-1, fillcolor, oldcolor);
		//! alle Zeilen unterhalb
		if((getPixelEx(dst,x,y+1)==oldcolor) && (y<(s32)Size.Height-1))
			floodFill( dst,x,y+1,fillcolor,oldcolor);
	}

	return true;
}

//void CImageFactory::drawTriangle( IImage* dst, s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3, const SColor& color, s32 border, bool blend) const
//{
//	drawLine( dst, Point(x1,y1), Point(x2,y2), color,border,blend);
//	drawLine( dst, Point(x2,y2), Point(x3,y3), color,border,blend);
//	drawLine( dst, Point(x3,y3), Point(x1,y1), color,border,blend);
//}
//
//void CImageFactory::drawTriangle( IImage* dst, s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3, const SColor& c1, const SColor& c2, const SColor& c3, s32 border, bool blend) const
//{
//	drawLine( dst, Point(x1,y1), Point(x2,y2), c1,c2, blend);
//	drawLine( dst, Point(x2,y2), Point(x3,y3), c2,c3, blend);
//	drawLine( dst, Point(x3,y3), Point(x1,y1), c3,c1, blend);
//}

void CImageFactory::drawTriangle( IImage* dst, const Point& p1, const Point& p2, const Point& p3, const SColor& color, s32 border, bool blend) const
{
	drawLine( dst, p1,p2, color, blend);
	drawLine( dst, p2,p3, color, blend);
	drawLine( dst, p3,p1, color, blend);
}

void CImageFactory::drawTriangle( IImage* dst, const Point& p1, const Point& p2, const Point& p3, const SColor& c1, const SColor& c2, const SColor& c3, s32 border, bool blend) const
{
	drawLine( dst, p1,p2, c1,c2, blend);
	drawLine( dst, p2,p3, c2,c3, blend);
	drawLine( dst, p3,p1, c3,c1, blend);
}


//void CImageFactory::drawFilledTriangle( IImage* dst, s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3, const SColor& color, bool blend) const
//{
//	drawLine( dst, Point(x1,y1), Point(x2,y2), color,blend);
//	drawLine( dst, Point(x2,y2), Point(x3,y3), color,blend);
//	drawLine( dst, Point(x3,y3), Point(x1,y1), color,blend);
//}
//
//void CImageFactory::drawFilledTriangle( IImage* dst, s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3, const SColor& c1, const SColor& c2, const SColor& c3, bool blend) const
//{
//	drawLine( dst, Point(x1,y1), Point(x2,y2), c1,c2,blend);
//	drawLine( dst, Point(x2,y2), Point(x3,y3), c2,c3,blend);
//	drawLine( dst, Point(x3,y3), Point(x1,y1), c3,c1,blend);
//}

void CImageFactory::drawFilledTriangle( IImage* dst, const Point& p1, const Point& p2, const Point& p3, const SColor& color, bool blend) const
{
	drawLine( dst, p1,p2,color,blend);
	drawLine( dst, p2,p3,color,blend);
	drawLine( dst, p3,p1,color,blend);
}

void CImageFactory::drawFilledTriangle( IImage* dst, const Point& p1, const Point& p2, const Point& p3, const SColor& c1, const SColor& c2, const SColor& c3, bool blend) const
{
	drawLine( dst, p1,p2,c1,blend);
	drawLine( dst, p2,p3,c2,blend);
	drawLine( dst, p3,p1,c3,blend);
}

//! draw rect
void CImageFactory::drawRect( IImage* dst, const core::recti& pos, const SColor& color, s32 border, bool blend) const
{
	if (border==0)
	{
		for (s32 y=pos.UpperLeftCorner.Y; y<=pos.LowerRightCorner.Y; y++)
		{
			for (s32 x=pos.UpperLeftCorner.X; x<=pos.LowerRightCorner.X; x++)
			{
				setPixelEx( dst, x, y, color, blend);
			}
		}
	}
	else if (border == 1)
	{
		const s32 x = pos.LowerRightCorner.X-1;
		const s32 y = pos.LowerRightCorner.Y-1;
		drawLine( dst, pos.UpperLeftCorner, Point(x, pos.UpperLeftCorner.Y), color, blend);
		drawLine( dst, pos.UpperLeftCorner, Point(pos.UpperLeftCorner.X, y), color, blend);
		drawLine( dst, Point(x, pos.UpperLeftCorner.Y), Point(x,y), color, blend);
		drawLine( dst, Point(pos.UpperLeftCorner.X, y), Point(x,y), color, blend);
	}
	else if ( border > 1)
	{
		for (s32 b=0; b<border; b++)
		{
			drawRect( dst, core::recti(
				pos.UpperLeftCorner.X + b,
				pos.UpperLeftCorner.Y + b,
				pos.LowerRightCorner.X - b,
				pos.LowerRightCorner.Y - b), color, 1, false);
		}
	}
}

void CImageFactory::drawRect( IImage* dst, const core::recti& pos, const SColor& topLeft, const SColor& topRight, const SColor& bottomRight, const SColor& bottomLeft, s32 border, bool blend) const
{
	if (border==0)
	{
		const s32& x1 = pos.UpperLeftCorner.X;
		const s32& x2 = pos.LowerRightCorner.X;
		const s32& y1 = pos.UpperLeftCorner.Y;
		const s32& y2 = pos.LowerRightCorner.Y;

		// common factor for all colors ( 1 / (dx * dy) )
		const f32 n_inv = core::reciprocal( (f32)(x2 - x1) * (f32)(y2 - y1) );

		for (s32 y=y1; y<=y2; y++)
		{
			for (s32 x=x1; x<=x2; x++)
			{
				const f32 f11 = (f32)(x2 - x) * (f32)(y2 - y) * n_inv; // topLeft
				const f32 f21 = (f32)(x - x1) * (f32)(y2 - y) * n_inv; // topRight
				const f32 f12 = (f32)(x2 - x) * (f32)(y - y1) * n_inv; // bottomLeft
				const f32 f22 = (f32)(x - x1) * (f32)(y - y1) * n_inv; // bottomRight

				const f32 fA = 	(f32)topLeft.getAlpha() * f11 +
								(f32)topRight.getAlpha() * f21 +
								(f32)bottomRight.getAlpha() * f12 +
								(f32)bottomLeft.getAlpha() * f22;

				const f32 fR = 	(f32)topLeft.getRed() * f11 +
								(f32)topRight.getRed() * f21 +
								(f32)bottomRight.getRed() * f12 +
								(f32)bottomLeft.getRed() * f22;

				const f32 fG = 	(f32)topLeft.getGreen() * f11 +
								(f32)topRight.getGreen() * f21 +
								(f32)bottomRight.getGreen() * f12 +
								(f32)bottomLeft.getGreen() * f22;

				const f32 fB = 	(f32)topLeft.getBlue() * f11 +
								(f32)topRight.getBlue() * f21 +
								(f32)bottomRight.getBlue() * f12 +
								(f32)bottomLeft.getBlue() * f22;

				SColor color(
					(u32)core::clamp( core::round32(fA), 0, 255),
					(u32)core::clamp( core::round32(fR), 0, 255),
					(u32)core::clamp( core::round32(fG), 0, 255),
					(u32)core::clamp( core::round32(fB), 0, 255) );

				setPixelEx( dst, x, y, color, blend);
			}
		}
	}
	else if ( border == 1)
	{
//		drawLine( pos.UpperLeftCorner, Point(pos.LowerRightCorner.X, pos.UpperLeftCorner.Y), color, blend);
//		drawLine( pos.UpperLeftCorner, Point(pos.UpperLeftCorner.X, pos.LowerRightCorner.Y), color, blend);
//		drawLine( Point(pos.LowerRightCorner.X, pos.UpperLeftCorner.Y), pos.LowerRightCorner, color, blend);
//		drawLine( Point(pos.UpperLeftCorner.X, pos.LowerRightCorner.Y), pos.LowerRightCorner, color, blend);
//
		const s32 x = pos.LowerRightCorner.X-1;
		const s32 y = pos.LowerRightCorner.Y-1;
		drawLine( dst, pos.UpperLeftCorner, Point(x, pos.UpperLeftCorner.Y), topLeft, topRight, blend);
		drawLine( dst, pos.UpperLeftCorner, Point(pos.UpperLeftCorner.X, y), topLeft, bottomLeft, blend);
		drawLine( dst, Point(x, pos.UpperLeftCorner.Y), Point(x,y), topRight, bottomRight, blend);
		drawLine( dst, Point(pos.UpperLeftCorner.X, y), Point(x,y), bottomLeft, bottomRight, blend);
	}
	else if ( border > 1)
	{
		IImage* tmp = new CImage( dst->getColorFormat(), core::dimension2du( (u32)pos.getWidth(), (u32)pos.getHeight() ) );
		if (!tmp)
			return;

		const SColor black(  0,  0,  0,  0);
		const SColor white(255,255,255,255);

		tmp->fill( black );
		drawRect( tmp, core::recti( Point(0,0), tmp->getDimension()), white, border, blend);

		// common factor for all colors ( 1 / (w * h) )
		const u32 w = tmp->getDimension().Width;
		const u32 h = tmp->getDimension().Height;
		const f32 n_inv = core::reciprocal( (f32)w * (f32)h );

		for (u32 y = 0; y < h; y++)
		{
			u32 x = 0;
			while (x < w)
			{
				const SColor& colorNow = tmp->getPixel(x,y);

				if (colorNow == white)
				{
					const f32 f11 = (f32)(w-1-x) * (f32)(h-1-y) * n_inv; // topLeft
					const f32 f21 = (f32)(x) * (f32)(h-1-y) * n_inv; // topRight
					const f32 f12 = (f32)(w-1-x) * (f32)(y) * n_inv; // bottomLeft
					const f32 f22 = (f32)(x) * (f32)(y) * n_inv; // bottomRight

					const f32 fA = 	(f32)topLeft.getAlpha() * f11 +
									(f32)topRight.getAlpha() * f21 +
									(f32)bottomRight.getAlpha() * f12 +
									(f32)bottomLeft.getAlpha() * f22;

					const f32 fR = 	(f32)topLeft.getRed() * f11 +
									(f32)topRight.getRed() * f21 +
									(f32)bottomRight.getRed() * f12 +
									(f32)bottomLeft.getRed() * f22;

					const f32 fG = 	(f32)topLeft.getGreen() * f11 +
									(f32)topRight.getGreen() * f21 +
									(f32)bottomRight.getGreen() * f12 +
									(f32)bottomLeft.getGreen() * f22;

					const f32 fB = 	(f32)topLeft.getBlue() * f11 +
									(f32)topRight.getBlue() * f21 +
									(f32)bottomRight.getBlue() * f12 +
									(f32)bottomLeft.getBlue() * f22;

					SColor color(
						(u32)core::clamp( core::round32(fA), 0, 255),
						(u32)core::clamp( core::round32(fR), 0, 255),
						(u32)core::clamp( core::round32(fG), 0, 255),
						(u32)core::clamp( core::round32(fB), 0, 255) );

					tmp->setPixel( x, y, color, blend);
				}
//				else
//				{
//					x += ( w - (border<<1)) - 2; // skip pixels to increase speed
//				}
				x++;
			}
		}

		drawImage( tmp, dst, pos.UpperLeftCorner, tmp->getDimension(), true, false);
		tmp->drop();

	}
}

//! draw a Bresenham-lined Grid, 1 color, option to blend
void CImageFactory::drawGrid( IImage* dst, const core::recti& pos, const core::dimension2du& gridSize, const SColor& color, bool blend ) const
{
	const core::dimension2du& Size = dst->getDimension();
	s32 x1 = core::s32_max( pos.UpperLeftCorner.X, 0);
	s32 y1 = core::s32_max( pos.UpperLeftCorner.Y, 0);
	s32 x2 = core::s32_min( pos.LowerRightCorner.X, Size.Width-1);
	s32 y2 = core::s32_min( pos.LowerRightCorner.Y, Size.Height-1);

	s32 x = x1;
	s32 y = y1;

	while( x <= x2 )
	{
		drawLine( dst, Point(x,y1), Point(x,y2), color, blend);
		x+=gridSize.Width;
	}

	while( y <= y2 )
	{
		drawLine( dst, Point(x1,y), Point(x2,y), color, blend);
		y+=gridSize.Height;
	}
}

//! draw a Bresenham-lined Grid, 4 colors, option to blend
void CImageFactory::drawGrid( IImage* dst, const core::recti& pos, const core::dimension2du& gridSize, const SColor& topLeft, const SColor& topRight, const SColor& bottomRight, const SColor& bottomLeft, bool blend ) const
{
	if (!dst) return;
	const core::dimension2du& Size = dst->getDimension();
	s32 x1 = core::s32_max( pos.UpperLeftCorner.X, 0);
	s32 y1 = core::s32_max( pos.UpperLeftCorner.Y, 0);
	s32 x2 = core::s32_min( pos.LowerRightCorner.X, Size.Width-1);
	s32 y2 = core::s32_min( pos.LowerRightCorner.Y, Size.Height-1);

	s32 x = x1;
	s32 y = y1;

	while( x <= x2 )
	{
		drawLine( dst, Point(x,y1), Point(x,y2), topLeft, bottomLeft, blend);
		x+=gridSize.Width;
	}

	while( y <= y2 )
	{
		drawLine( dst, Point(x1,y), Point(x2,y), topRight, bottomRight, blend);
		y+=gridSize.Height;
	}
}

//! Bresenham circle
void CImageFactory::drawCircle( IImage* dst, const Point& center, s32 radius, const SColor& color, s32 border, bool blend) const
{
	// abort
	if (!dst) return;

	// abort
	if ( radius == -1 )
	{
		setPixelEx( dst, center.X, center.Y, color, blend);
	}

	// abort
	if (radius < 0)
		return;

	if (radius == 0)
	{
		setPixelEx( dst, center.X, center.Y, color, blend);
		return;
	}
	else if (radius == 1)
	{
		setPixelEx( dst,center.X,center.Y-1,color,blend);
		setPixelEx( dst,center.X,center.Y,color,blend);
		setPixelEx( dst,center.X,center.Y+1,color,blend);
		setPixelEx( dst,center.X-1,center.Y,color,blend);
		setPixelEx( dst,center.X+1,center.Y,color,blend);
		return;
	}
	else if (radius == 2)
	{
		setPixelEx( dst,center.X-1,center.Y+2,color,blend);
		setPixelEx( dst,center.X,center.Y+2,color,blend);
		setPixelEx( dst,center.X,center.Y+1,color,blend);
		setPixelEx( dst,center.X+1,center.Y+1,color,blend);
		setPixelEx( dst,center.X-1,center.Y+1,color,blend);
		setPixelEx( dst,center.X-2,center.Y+1,color,blend);
		setPixelEx( dst,center.X,center.Y,color,blend);
		setPixelEx( dst,center.X+1,center.Y,color,blend);
		setPixelEx( dst,center.X-1,center.Y,color,blend);
		setPixelEx( dst,center.X-2,center.Y,color,blend);
		setPixelEx( dst,center.X,center.Y-1,color,blend);
		setPixelEx( dst,center.X+1,center.Y-1,color,blend);
		return;
	}
	else
	{
		// 'Bresenham' Algorithmus (Achtelkreis Symmetrie)
		// ohne Trigonometrische- und Wurzel-Funktionen
		// und Spiegelung auf Restliche 7/8

		if (border==0) // filled
		{
			s32 i,j,F;
			i = 0;
			j = radius;
			F = 1 - radius;

			while (i < j)
			{
				++i;
				if (F < 0)
				{
					F += (i<<1) - 1;
				}
				else
				{
					F += ((i - j)<<1);
					--j;
				}

				// Verbesserungen by Benjamin Hampe (c) 2012
				drawLine( dst, Point( center.X-i,center.Y+j-1 ), Point(center.X+i-1,center.Y+j-1), color, blend);
				drawLine( dst, Point( center.X-j,center.Y+i-1 ), Point(center.X+j-1,center.Y+i-1), color, blend);
				drawLine( dst, Point( center.X-j,center.Y-i ), Point(center.X+j-1,center.Y-i), color, blend);
				drawLine( dst, Point( center.X-i,center.Y-j ), Point(center.X+i-1,center.Y-j), color, blend);
			}
		}

		// 'Bresenham' Algorithmus (Achtelkreis Symmetrie)
		// ohne Trigonometrische- und Wurzel-Funktionen
		// und Spiegelung auf Restliche 7/8

		else if (border == 1)
		{
			s32 i,j,F;
			i = 0;
			j = radius;
			F = 1 - radius;

			while (i < j)
			{
				++i;
				if (F < 0)
				{
					F += (i<<1) - 1;
				}
				else
				{
					F += ((i - j)<<1);
					--j;
				}
				// Verbesserungen by Benjamin Hampe (c) 2012
				setPixelEx( dst, center.X+i-1,center.Y-j,color, blend); // 1st quadrant
				setPixelEx( dst, center.X+j-1,center.Y-i,color, blend); // 1st quadrant
				setPixelEx( dst, center.X+i-1,center.Y+j-1,color, blend); // 2nd quadrant
				setPixelEx( dst, center.X+j-1,center.Y+i-1,color, blend); // 2nd quadrant
				setPixelEx( dst, center.X-i,center.Y+j-1,color, blend); // 3rd quadrant
				setPixelEx( dst, center.X-j,center.Y+i-1,color, blend); // 3rd quadrant
				setPixelEx( dst, center.X-i,center.Y-j,color, blend); // 4th quadrant
				setPixelEx( dst, center.X-j,center.Y-i,color, blend); // 4th quadrant
			}
		}

		// by Benjamin Hampe
		// create circle from undistorted temporary image

		else if (border > 1)
		{
			if (radius - border > 1)
			{
				IImage* tmp = new CImage( dst->getColorFormat(), core::dimension2du( radius<<1, radius<<1) );
				if (!tmp)
					return;

//				tmp->enableColorKey();
				tmp->fill( 0 );
				drawCircle( tmp, Point(radius,radius), radius, color, 0, blend);
				drawCircle( tmp, Point(radius,radius), radius - border, 0, 0, blend);
				drawImage( tmp, dst, center - Point(radius,radius), tmp->getDimension(), true, false);
				tmp->drop();
			}
		}
	}
}

//! Bresenham circle
void CImageFactory::drawCircle( IImage* dst, const Point& center, s32 radius, const SColor& c1, const SColor& c2, s32 border, bool blend) const
{
	// abort
	if (!dst) return;

	// abort
	if (radius < 0)
	{
		return;
	}
	else if (radius == 0)
	{
		setPixelEx( dst,center.X,center.Y,c2,blend);
		return;
	}
	else if (radius == 1)
	{
		setPixelEx( dst,center.X,center.Y,c2,blend);
		setPixelEx( dst,center.X,center.Y-1,c1,blend);
		setPixelEx( dst,center.X,center.Y+1,c1,blend);
		setPixelEx( dst,center.X+1,center.Y,c1,blend);
		setPixelEx( dst,center.X-1,center.Y,c1,blend);
		return;
	}
	else
	{
		if (border==0) // filled
		{
			IImage* tmp = new CImage( dst->getColorFormat(), core::dimension2du( radius<<1, radius<<1) );
			if (!tmp)
				return;
			tmp->fill( 0 );
			drawCircle( tmp, Point(radius,radius), radius, SColor(255,255,255,255), 0, blend);

			const f32 fA = (f32)c1.getAlpha(), fdA = (f32)c2.getAlpha() - fA;
			const f32 fR = (f32)c1.getRed(), fdR = (f32)c2.getRed() - fR;
			const f32 fG = (f32)c1.getGreen(), fdG = (f32)c2.getGreen() - fG;
			const f32 fB = (f32)c1.getBlue(), fdB = (f32)c2.getBlue() - fB;
			const SColor white(255,255,255,255);
			const f32 fw = 0.5f*(f32)tmp->getDimension().Width;
			const f32 fh = 0.5f*(f32)tmp->getDimension().Height;
			const f32 invRadius = core::reciprocal( (f32)radius );

			const core::dimension2du& Size = tmp->getDimension();
			for (u32 y = 0; y < Size.Height; y++)
			{
				for (u32 x = 0; x < Size.Width; x++)
				{
					const SColor& colorNow = tmp->getPixel(x,y);
					if (colorNow == white)
					{
						const f32 dx = (f32)x - fw;
						const f32 dy = (f32)y - fh;
						f32 f = core::squareroot( dx*dx + dy*dy ) * invRadius;
						u32 uA = (u32)core::s32_clamp( core::round32( fA + f*fdA ), 0, 255);
						u32 uR = (u32)core::s32_clamp( core::round32( fR + f*fdR ), 0, 255);
						u32 uG = (u32)core::s32_clamp( core::round32( fG + f*fdG ), 0, 255);
						u32 uB = (u32)core::s32_clamp( core::round32( fB + f*fdB ), 0, 255);
						tmp->setPixel( x, y, SColor(uA,uR,uG,uB), blend );
					}
				}
			}

			drawImage( tmp, dst, center - Point(radius,radius), tmp->getDimension(), true, false);
			tmp->drop();
			return;
		}
		else if (border == 1) // outline with color c1
		{
			drawCircle( dst, center, radius, c1, 1, blend);
		}
		else if (border > 1)
		{
			if (radius - border > 0)
			{
				IImage* tmp = new CImage( dst->getColorFormat(), core::dimension2du( radius<<1, radius<<1) );
				if (!tmp)
					return;

				const SColor black(  0,  0,  0,  0);
				const SColor white(255,255,255,255);

				tmp->fill( black );
				drawCircle( tmp, Point(radius,radius), radius, white, 0, blend);
				drawCircle( tmp, Point(radius,radius), radius-border, black, 0, blend);

				const f32 fA = (f32)c1.getAlpha(), fdA = (f32)c2.getAlpha() - fA;
				const f32 fR = (f32)c1.getRed(), fdR = (f32)c2.getRed() - fR;
				const f32 fG = (f32)c1.getGreen(), fdG = (f32)c2.getGreen() - fG;
				const f32 fB = (f32)c1.getBlue(), fdB = (f32)c2.getBlue() - fB;

				const core::dimension2du& Size = tmp->getDimension();

				const f32 fw = 0.5f*(f32)Size.Width;
				const f32 fh = 0.5f*(f32)Size.Height;
				const f32 invRadius = core::reciprocal( (f32)border );
				const s32 innerCircle = radius-border;

				for (u32 y = 0; y < Size.Height; y++)
				{
					for (u32 x = 0; x < Size.Width; x++)
					{
						const SColor& colorNow = tmp->getPixel(x,y);
						if (colorNow == white)
						{
							const f32 dx = (f32)x - fw;
							const f32 dy = (f32)y - fh;

							f32 f = (core::squareroot( dx*dx + dy*dy ) - (f32)innerCircle ) * invRadius;
							u32 uA = (u32)core::s32_clamp( core::round32( fA + f*fdA ), 0, 255);
							u32 uR = (u32)core::s32_clamp( core::round32( fR + f*fdR ), 0, 255);
							u32 uG = (u32)core::s32_clamp( core::round32( fG + f*fdG ), 0, 255);
							u32 uB = (u32)core::s32_clamp( core::round32( fB + f*fdB ), 0, 255);
							tmp->setPixel( x, y, SColor(uA,uR,uG,uB), blend );
						}
					}
				}

				drawImage( tmp, dst, center - Point(radius,radius), tmp->getDimension(), true, false);
				tmp->drop();
			}
		}
	}
}

//! draw a Bresenham-ellipse, 1 color, filled or outlined, option to blend
void CImageFactory::drawEllipse( IImage* dst, const Point& center, s32 rx, s32 ry, const SColor& color, s32 border, bool blend) const
{
	if (!dst) return; // abort
//			const s32 w = dest->getDimension().Width;
//			const s32 h = dest->getDimension().Height;

	// Abbruchbedingung
	if (rx < 1 && ry < 1) return;
	if (rx==0) rx = ry;
	if (ry==0) ry = rx;

	if (rx==ry)
		drawCircle( dst, center, rx, color, border, blend);

	//if (rw==1 && rh==1) dest->setPixel(x,y,color);

	const s32 rx2=rx*rx; // Ellipsen Radien Quadrate
	const s32 ry2=ry*ry; // Ellipsen Radien Quadrate
	s32 x = center.X;
	s32 y = center.Y;
//	const s32 mx = center.X;	 // Ellipsen Mittelpunkt
//	const s32 my = center.Y; 	 // Ellipsen Mittelpunkt

	// Bresenham Anfangswerte
	// Trick: nur 1/4 Ellipse berechne und restliche 3/4 durch Spiegelung (gerade Ellipse!!!)
	s32 ddF_x=0;
	s32 ddF_y=((rx2*ry)<<1);
	x=0;
	y=ry;

	// Bresenham Alghorithmus
	s32 F=core::round32((f32)(ry2-rx2*ry)+(f32)rx2*0.25f);
	while( ddF_x < ddF_y )
	{
		if (F >= 0)
		{
			y     -= 1;        // south
			ddF_y -= (rx2<<1);
			F     -= ddF_y;
		}
		x     += 1;          // east
		ddF_x += (ry2<<1);
		F     += ddF_x + ry2;

		if (border==0)
		{
			drawLine( dst, Point(center.X-x, center.Y+y), Point(center.X+x, center.Y+y), color, blend);
			drawLine( dst, Point(center.X-x, center.Y-y), Point(center.X+x, center.Y-y), color, blend);
		}
		else
		{
			setPixelEx( dst, x+center.X, y+center.Y, color, blend);
			setPixelEx( dst, -x+center.X, y+center.Y, color, blend);
			setPixelEx( dst, x+center.X, -y+center.Y, color, blend);
			setPixelEx( dst, -x+center.X, -y+center.Y, color, blend);

			// Spiegelung mit meinen Anpassungen
			// setPixelEx( dst, x+mx, y+my, color, blend);
			// setPixelEx( dst, -x+mx+1, y+my, color, blend);
			// setPixelEx( dst, x+mx, -y+my+1, color, blend);
			// setPixelEx( dst, -x+mx+1, -y+my+1, color, blend);
		}
	}

	// Bresenham Alghorithmus
	F = core::round32((f32)ry2*((f32)x+0.5f)*((f32)x+0.5f) + (f32)(rx2*(y-1)*(y-1) - rx2*ry2));
	while( y > 0 )
	{
		if(F <= 0)
		{
			x     += 1;        // east
			ddF_x += (ry2<<1);
			F     += ddF_x;
		}
		y     -= 1;           // south
		ddF_y -= (rx2<<1);
		F     += rx2 - ddF_y;

		if (border==0)
		{
			drawLine( dst, Point(center.X-x, center.Y+y), Point(center.X+x, center.Y+y), color, blend);
			drawLine( dst, Point(center.X-x, center.Y-y), Point(center.X+x, center.Y-y), color, blend);
		}
		else
		{
			setPixelEx( dst, x+center.X, y+center.Y, color, blend);
			setPixelEx( dst, -x+center.X, y+center.Y, color, blend);
			setPixelEx( dst, x+center.X, -y+center.Y, color, blend);
			setPixelEx( dst, -x+center.X, -y+center.Y, color, blend);

			// Spiegelung mit meinen Anpassungen
//			setPixelEx( dst, x+mx, y+my, color, blend);
//			setPixelEx( dst, -x+mx+1, y+my, color, blend);
//			setPixelEx( dst, x+mx, -y+my+1, color, blend);
//			setPixelEx( dst, -x+mx+1, -y+my+1, color, blend);
		}
	}
}

//! Bresenham ellipse
void CImageFactory::drawEllipse( IImage* dst, const Point& center, s32 rx, s32 ry, const SColor& c1, const SColor& c2, s32 border, bool blend) const
{
	if (!dst) return; // abort
//			const s32 w = dest->getDimension().Width;
//			const s32 h = dest->getDimension().Height;

	// Abbruchbedingung
	if (rx < 1 && ry < 1) return;
	if (rx==0) rx = ry;
	if (ry==0) ry = rx;

	if (rx==ry)
		drawCircle( dst, center, rx, c1, c2, border, blend);

	//if (rw==1 && rh==1) dest->setPixel(x,y,color);

	const s32 rx2=rx*rx; // Ellipsen Radien Quadrate
	const s32 ry2=ry*ry; // Ellipsen Radien Quadrate
	s32 x = center.X;
	s32 y = center.Y;
//	const s32 mx = center.X;	 // Ellipsen Mittelpunkt
//	const s32 my = center.Y; 	 // Ellipsen Mittelpunkt

	// Bresenham Anfangswerte
	// Trick: nur 1/4 Ellipse berechne und restliche 3/4 durch Spiegelung (gerade Ellipse!!!)
	s32 ddF_x=0;
	s32 ddF_y=((rx2*ry)<<1);
	x=0;
	y=ry;

	// Bresenham Alghorithmus
	s32 F=core::round32((f32)(ry2-rx2*ry)+(f32)rx2*0.25f);
	while( ddF_x < ddF_y )
	{
		if (F >= 0)
		{
			y     -= 1;        // south
			ddF_y -= (rx2<<1);
			F     -= ddF_y;
		}
		x     += 1;          // east
		ddF_x += (ry2<<1);
		F     += ddF_x + ry2;

		if (border==0)
		{
			drawLine( dst, Point(center.X-x, center.Y+y), Point(center.X+x, center.Y+y), c1, blend);
			drawLine( dst, Point(center.X-x, center.Y-y), Point(center.X+x, center.Y-y), c1, blend);
		}
		else
		{
			setPixelEx( dst, x+center.X, y+center.Y, c1, blend);
			setPixelEx( dst, -x+center.X, y+center.Y, c1, blend);
			setPixelEx( dst, x+center.X, -y+center.Y, c1, blend);
			setPixelEx( dst, -x+center.X, -y+center.Y, c1, blend);
		}
	}

	// Bresenham Alghorithmus
	F = core::round32((f32)ry2*((f32)x+0.5f)*((f32)x+0.5f) + (f32)(rx2*(y-1)*(y-1) - rx2*ry2));
	while( y > 0 )
	{
		if(F <= 0)
		{
			x     += 1;        // east
			ddF_x += (ry2<<1);
			F     += ddF_x;
		}
		y     -= 1;           // south
		ddF_y -= (rx2<<1);
		F     += rx2 - ddF_y;

		if (border==0)
		{
			drawLine( dst, Point(center.X-x, center.Y+y), Point(center.X+x, center.Y+y), c1, blend);
			drawLine( dst, Point(center.X-x, center.Y-y), Point(center.X+x, center.Y-y), c1, blend);
		}
		else
		{
			setPixelEx( dst, x+center.X, y+center.Y, c1, blend);
			setPixelEx( dst, -x+center.X, y+center.Y, c1, blend);
			setPixelEx( dst, x+center.X, -y+center.Y, c1, blend);
			setPixelEx( dst, -x+center.X, -y+center.Y, c1, blend);
		}
	}
}


//! draw a Bresenham-round-rect, 1 colors, filled (border=0) or outlined with border, option to blend
void CImageFactory::drawRoundRect( IImage* dst, const core::recti& pos, s32 rx, s32 ry, const SColor& color, s32 border, bool blend) const
{
	// abort
	if (!dst)
		return;

	// abort
	if (rx < 1 && ry < 1)
		return;

	// set equal, if one radius is zero --> circle
	if (rx==0) rx = ry;
	if (ry==0) ry = rx;

	s32 w = pos.getWidth();
	s32 h = pos.getHeight();

//	Point m = pos.getCenter();
//	Point dA( (w-1)>>1, ry);
//	Point lowerRight(w-1-rx, ry);
//	Point upperLeft(rx, h-1-ry);
//	Point upperRight(w-1-rx, h-1-ry);

	Point lowerLeft = Point(rx, ry) + pos.UpperLeftCorner;
	Point lowerRight = Point(w-1-rx, ry) + pos.UpperLeftCorner;
	Point upperLeft = Point(rx, h-1-ry) + pos.UpperLeftCorner;
	Point upperRight = Point(w-1-rx, h-1-ry) + pos.UpperLeftCorner;

	// draw a filled round-rect
	if (border == 0)
	{
		// Ellipsen-Code
		const s32 rx2=rx*rx; // Ellipsen Radien Quadrate
		const s32 ry2=ry*ry; // Ellipsen Radien Quadrate
		s32 x = 0;
		s32 y = 0;

		// Bresenham Ellipse Anfangswerte
		s32 ddF_x=0;
		s32 ddF_y=((rx2*ry)<<1);
		x=0;
		y=ry;

		// Bresenham Alghorithmus
		s32 F=core::round32((f32)(ry2-rx2*ry)+(f32)rx2*0.25f);
		while( ddF_x < ddF_y )
		{
			if (F >= 0)
			{
				y     -= 1;        // south
				ddF_y -= (rx2<<1);
				F     -= ddF_y;
			}
			x     += 1;          // east
			ddF_x += (ry2<<1);
			F     += ddF_x + ry2;
			drawLine( dst, Point(upperLeft.X-x, upperLeft.Y+y), Point(upperRight.X+x, upperRight.Y+y), color, blend);
			drawLine( dst, Point(lowerLeft.X-x, lowerLeft.Y-y), Point(lowerRight.X+x, lowerRight.Y-y), color, blend);
		}

		// Bresenham Alghorithmus
		F = core::round32((f32)ry2*((f32)x+0.5f)*((f32)x+0.5f) + (f32)(rx2*(y-1)*(y-1) - rx2*ry2));
		while( y > 0 )
		{
			if(F <= 0)
			{
				x     += 1;        // east
				ddF_x += (ry2<<1);
				F     += ddF_x;
			}
			y     -= 1;           // south
			ddF_y -= (rx2<<1);
			F     += rx2 - ddF_y;

			drawLine( dst, Point(upperLeft.X-x, upperLeft.Y+y), Point(upperRight.X+x, upperRight.Y+y), color, blend);
			drawLine( dst, Point(lowerLeft.X-x, lowerLeft.Y-y), Point(lowerRight.X+x, lowerRight.Y-y), color, blend);
		}

		s32 y1 = pos.UpperLeftCorner.Y + ry;
		s32 y2 = pos.UpperLeftCorner.Y + pos.getHeight() - ry;
		y = y1;
		while( y < y2 )
		{
			drawLine( dst, Point( pos.UpperLeftCorner.X , y), Point( pos.LowerRightCorner.X, y), color, blend);
			y++;
		}

	}
	// draw a bordered round-rect
	else
	{
		if (border == 1)
		{
			PointList points = traverseEllipse( Point(0,0), rx,ry);

			for (u32 i=0; i<points.size(); i++)
			{
				dst->setPixel(upperRight.X + points[i].X, upperRight.Y + points[i].Y, color);
				dst->setPixel(lowerRight.X + points[i].X, lowerRight.Y - points[i].Y, color);
				dst->setPixel(upperLeft.X - points[i].X, upperLeft.Y + points[i].Y, color);
				dst->setPixel(lowerLeft.X - points[i].X, lowerLeft.Y - points[i].Y, color);
			}

			//! recti has flaws, i.e. it does not guarantee that UpperLeftCorner is more upper and left than LowerRightCorner !!!
			const s32 x1 = core::s32_min( pos.UpperLeftCorner.X, pos.LowerRightCorner.X);
			const s32 y1 = core::s32_min( pos.UpperLeftCorner.Y, pos.LowerRightCorner.Y);
			const s32 x2 = core::s32_max( pos.UpperLeftCorner.X, pos.LowerRightCorner.X);
			const s32 y2 = core::s32_max( pos.UpperLeftCorner.Y, pos.LowerRightCorner.Y);

			drawLine( dst, Point( x1+rx, y1), Point( x2-1-rx, y1), color, blend);
			drawLine( dst, Point( x1+rx, y2-1), Point( x2-1-rx, y2-1), color, blend);
			drawLine( dst, Point( x1, y1+ry), Point( x1, y2-1-ry), color, blend);
			drawLine( dst, Point( x2-1, y1+ry), Point( x2-1, y2-1-ry), color, blend);
		}
		else
		{
			IImage* tmp = new CImage( dst->getColorFormat(), core::dimension2du(w+1,h+1));
			if (!tmp)
				return;

			tmp->fill(0);
			drawRoundRect( tmp, core::recti(0,0,(s32)w, (s32)h), rx,ry, color, 0, false);
			drawRoundRect( tmp, core::recti(border, border, (s32)w-border, (s32)h-border), rx,ry, 0, 0, false);

			drawImage( tmp, dst, pos.UpperLeftCorner, tmp->getDimension(), true, false);
			tmp->drop();

//			floodFill(x1)
		}
	}
}

void CImageFactory::drawRoundRect( IImage* dst, const core::recti& pos, s32 rx, s32 ry, const SColor& topLeft, const SColor& topRight, const SColor& bottomRight, const SColor& bottomLeft, s32 border, bool blend) const
{
	// abort
	if (!dst)
		return;

	//! recti has flaws, i.e. it does not guarantee that UpperLeftCorner is more upper and left than LowerRightCorner !!!
	const s32 x1 = core::s32_min( pos.UpperLeftCorner.X, pos.LowerRightCorner.X);
	const s32 y1 = core::s32_min( pos.UpperLeftCorner.Y, pos.LowerRightCorner.Y);
	const s32 x2 = core::s32_max( pos.UpperLeftCorner.X, pos.LowerRightCorner.X);
	const s32 y2 = core::s32_max( pos.UpperLeftCorner.Y, pos.LowerRightCorner.Y);

	core::dimension2du size( (u32)(x2-x1)+1, (u32)(y2-y1)+1 );

	// abort
	if ((size.Width == 0) || (size.Height == 0))
		return;

	// create temporary canvas-image
	IImage* tmp = new CImage( dst->getColorFormat(), size);

	// abort
	if (!tmp)
		return;

	const SColor black(0,0,0,0);
	const SColor white(255,255,255,255);

	tmp->fill( black );
	drawRoundRect( tmp, core::recti( Point(0,0), size), rx,ry, white, border, false);

	// interpolate colors
	// common factor for all colors ( 1 / (dx * dy) )
	const f32 n_inv = core::reciprocal( (f32)(x2 - x1) * (f32)(y2 - y1) );

	for (u32 y=0; y<size.Height; y++)
	{
		for (u32 x=0; x<size.Width; x++)
		{
			if (getPixelEx( tmp,x,y ) == white)
			{
				const f32 f11 = (f32)(size.Width-1-x) * (f32)(size.Height-1 - y) * n_inv; // topLeft
				const f32 f21 = (f32)(x) * (f32)(size.Height-1 - y) * n_inv; // topRight
				const f32 f12 = (f32)(size.Width-1 - x) * (f32)(y) * n_inv; // bottomLeft
				const f32 f22 = (f32)(x) * (f32)(y) * n_inv; // bottomRight

				const f32 fA = 	(f32)topLeft.getAlpha() * f11 +
								(f32)topRight.getAlpha() * f21 +
								(f32)bottomRight.getAlpha() * f12 +
								(f32)bottomLeft.getAlpha() * f22;

				const f32 fR = 	(f32)topLeft.getRed() * f11 +
								(f32)topRight.getRed() * f21 +
								(f32)bottomRight.getRed() * f12 +
								(f32)bottomLeft.getRed() * f22;

				const f32 fG = 	(f32)topLeft.getGreen() * f11 +
								(f32)topRight.getGreen() * f21 +
								(f32)bottomRight.getGreen() * f12 +
								(f32)bottomLeft.getGreen() * f22;

				const f32 fB = 	(f32)topLeft.getBlue() * f11 +
								(f32)topRight.getBlue() * f21 +
								(f32)bottomRight.getBlue() * f12 +
								(f32)bottomLeft.getBlue() * f22;

				SColor color(
					(u32)core::clamp( core::round32(fA), 0, 255),
					(u32)core::clamp( core::round32(fR), 0, 255),
					(u32)core::clamp( core::round32(fG), 0, 255),
					(u32)core::clamp( core::round32(fB), 0, 255) );

				setPixelEx( tmp, x, y, color, blend);
			}
		}
	}

	// drawing finished and copy dst to srcImage
	drawImage( dst, tmp, Point(x1,y1), size, true, false);
	tmp->drop();
}

//void CImageFactory::drawText( IImage* dst, const Point& pos, const core::stringw& txt, s32 hAlign, s32 vAlign, core::recti* clipRect) const
//{
//	IImage* img = createImageFromText(txt);
//	if (img)
//	{
//		// paste( IImage* src, const Point& pos, const core::dimension2d<u32>& size, bool bTransparent, bool blend)
//		paste(img, pos, img->getDimension(), true, false);
//		img->drop();
//	}
//}

CImageFactory::PointList CImageFactory::traverseLine( const Point& A, const Point& B ) const
{
	PointList dst( core::abs_<s32>(B.X-A.X)+core::abs_<s32>(B.Y-A.Y) );
	return dst;
}

CImageFactory::PointList CImageFactory::traverseCircle( const Point& center, s32 radius ) const
{
	PointList dst( radius+3 );
	dst.set_used(0);

	// Bresenham
	s32 i,j,F;
	i = 0;
	j = radius;
	F = 1 - radius;

	while (i < j)
	{
		++i;
		if (F < 0)
		{
			F += (i<<1) - 1;
		}
		else
		{
			F += ((i - j)<<1);
			--j;
		}
		// Verbesserungen by Benjamin Hampe (c) 2012
		dst.push_back( Point( center.X+i,center.Y+j ) );
		dst.push_back( Point( center.X+j,center.Y+i ) );
	}
	return dst;
}

CImageFactory::PointList CImageFactory::traverseEllipse( const Point& center, s32 rx, s32 ry ) const
{
//	const s32 w = dest->getDimension().Width;
//	const s32 h = dest->getDimension().Height;

	if (rx==ry)
		return traverseCircle( center, rx );

	PointList dst(rx+ry);
	dst.set_used(0);

	// Abbruchbedingung
	if ( (rx==0) && (ry==0) )
		return dst;

	const s32 rx2=rx*rx; // Ellipsen Radien Quadrate
	const s32 ry2=ry*ry; // Ellipsen Radien Quadrate
	s32 x = center.X;
	s32 y = center.Y;
//	const s32 mx = center.X;	 // Ellipsen Mittelpunkt
//	const s32 my = center.Y; 	 // Ellipsen Mittelpunkt

	// Bresenham Anfangswerte
	// Trick: nur 1/4 Ellipse berechne und restliche 3/4 durch Spiegelung (gerade Ellipse!!!)
	s32 ddF_x=0;
	s32 ddF_y=((rx2*ry)<<1);
	x=0;
	y=ry;

	// Bresenham Alghorithmus
	s32 F=core::round32((f32)(ry2-rx2*ry)+(f32)rx2*0.25f);
	while( ddF_x < ddF_y )
	{
		if (F >= 0)
		{
			y     -= 1;        // south
			ddF_y -= (rx2<<1);
			F     -= ddF_y;
		}
		x     += 1;          // east
		ddF_x += (ry2<<1);
		F     += ddF_x + ry2;

		dst.push_back( Point( center.X+x, center.Y+y) );
	}

	// Bresenham Alghorithmus
	F = core::round32((f32)ry2*((f32)x+0.5f)*((f32)x+0.5f) + (f32)(rx2*(y-1)*(y-1) - rx2*ry2));
	while( y > 0 )
	{
		if(F <= 0)
		{
			x     += 1;        // east
			ddF_x += (ry2<<1);
			F     += ddF_x;
		}
		y     -= 1;           // south
		ddF_y -= (rx2<<1);
		F     += rx2 - ddF_y;

		dst.push_back( Point( center.X+x, center.Y+y) );
	}
	return dst;
}

CImageFactory::PointList CImageFactory::traverseArc( const Point& center, s32 radius, f32 phiStart, f32 phiEnd ) const
{
	PointList dst(radius);
	dst.set_used(0);

	return dst;
}






//
//core::array<IImage*> CImageFactory::split( u32 rows, u32 cols, u32 tileW, u32 tileH) const
//{
//	core::array<IImage*> container;
//
//	//abort
//	if (!dst)
//		return container;
//
//	//abort
//	if (rows<1 && tileW<1)
//		return container;
//
//	//abort
//	if (cols<1 && tileH<1)
//		return container;
//
//	//calculate row-count or tileSizeW
//	if (rows==0)
//		rows = core::floor32( (f32)Size.Width / (f32)tileW );
//	else
//		tileW = core::floor32( (f32)Size.Width / (f32)rows );
//
//	//calculate col-count or tileSizeH
//	if (cols==0)
//		cols = core::floor32( (f32)Size.Height / (f32)tileH );
//	else
//		tileH = core::floor32( (f32)Size.Height / (f32)cols );
//
//	//abort
//	if (rows<1 || cols<1)
//		return container;
//
//
//	for (u32 j=0; j<rows; j++)
//		for (u32 i=0; i<cols; i++)
//			container.push_back( copy( core::recti(i*tileW, j*tileH, tileW, tileH)) );
//
//	return container;
//}
//
//
//core::array<(core::array<(IImage*)>)> CImageFactory::split2d( u32 rows, u32 cols, u32 tileW, u32 tileH) const
//{
//	core::array<(core::array<(IImage*)>)> container;
//
//	//abort
//	if (!dst)
//		return container;
//
//	//abort
//	if (rows<1 && tileW<1)
//		return container;
//
//	//abort
//	if (cols<1 && tileH<1)
//		return container;
//
//	//calculate row-count or tileSizeW
//	if (rows==0)
//		rows = core::floor32( (f32)Size.Width / (f32)tileW );
//	else
//		tileW = core::floor32( (f32)Size.Width / (f32)rows );
//
//	//calculate col-count or tileSizeH
//	if (cols==0)
//		cols = core::floor32( (f32)Size.Height / (f32)tileH );
//	else
//		tileH = core::floor32( (f32)Size.Height / (f32)cols );
//
//	//abort
//	if (rows<1 || cols<1)
//		return container;
//
//
//	for (u32 j=0; j<rows; j++)
//    {
//        core::array<(IImage*)> row( cols );
//        row.set_used(0);
//
//		for (u32 i=0; i<cols; i++)
//        {
//            row.push_back( copy( core::recti(i*tileW, j*tileH, tileW, tileH)) );
//        }
//
//        container.push_back( row );
//    }
//
//	return container;
//}
//! fill surface with one color
//IImage* CImageFactory::createImageFromColor( u32 width, u32 height, const SColor& color) const
//{
//	video::CImage* p = new video::CImage( ECF_A8R8G8B8, core::dimension2du(width,height));
//    if (!p)
//        return 0;
//
//	return p;
//}
//
//IImage* CImageFactory::createImageFromColor( const core::dimension2du& size, const SColor& color) const
//{
//	video::CImage* p = new video::CImage( ECF_A8R8G8B8, size );
//    if (!p)
//        return 0;
//
//	return p;
//}

//IImage* CImageFactory::createRainbowImage( u32 w, u32 h, u8 transparency, f64 gamma) const
//{
//	// create image
//	core::dimension2du size(w,h);
//
//	IImage* img = (IImage*)new CImage(ECF_A8R8G8B8, size);
//
//	if (!img) return 0;
//
//	size = img->getDimension();
//
//	// loop pixels per col
//	for (u32 y=0; y<size.Height; y++)
//	{
//		// calculate rainbow-color
//		SColor c = getRainbowColor( y, size.Height, gamma);
//
//		// set transparency
//		c.setAlpha(transparency);
//
//		// write one row with same color
//		for (u32 x=0; x<size.Width; x++)
//		{
//			// write rainbow-color
//			img->setPixel(x,y,c,false);
//		}
//	}
//
//	return img;
//}

//
////! set color-format, colors will be interpolated
//void CImageFactory::setColorFormat( IImage* src, ECOLOR_FORMAT format ) const
//{
//
//}
//
////! set unique color-count, colors will be interpolated
//void CImageFactory::setColorCount( IImage* src, u32 ColorCount ) const
//{
//
//}







} // end namespace video
} // end namespace irr
