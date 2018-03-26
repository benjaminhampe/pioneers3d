// Copyright (C) 2002-2013 BenjaminHampe@gmx.de
// This file intends to advance the caps of the "Irrlicht Engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CLinearColorGradient.h"

//#include <irrlicht.h>
#include <irrTypes.h>
#include <irrString.h>
#include <irrArray.h>
#include <SColor.h>
#include <EMaterialTypes.h>
#include <IImage.h>
#include <IVideoDriver.h>
#include <../source/Irrlicht/os.h>
#include <../source/Irrlicht/CImage.h>

namespace irr
{
namespace video
{

core::stringc toString( const SColor& color )
{
	core::stringc s("SColor(");
	s += color.getAlpha();
	s += ",";
	s += color.getRed();
	s += ",";
	s += color.getGreen();
	s += ",";
	s += color.getBlue();
	s += ")";
	return s;
}

core::stringc toString( const SColorf& color )
{
	core::stringc s("SColorf(");
	s += color.getAlpha();
	s += ",";
	s += color.getRed();
	s += ",";
	s += color.getGreen();
	s += ",";
	s += color.getBlue();
	s += ")";
	return s;
}

CLinearColorGradient::CLinearColorGradient() // const SColor& startColor, const SColor& endColor)
: Name("")
{
	#if _DEBUG
		os::Printer::log( "CLinearColorGradient::ctr()", ELL_INFORMATION );
	#endif // _DEBUG
//	addColor( startColor, 0.0f );
//	addColor( endColor, 1.0f );
}

CLinearColorGradient::~CLinearColorGradient()
{
	#if _DEBUG
		os::Printer::log( "CLinearColorGradient::dtr()", ELL_INFORMATION );
	#endif // _DEBUG
	clear();
}

CLinearColorGradient& CLinearColorGradient::clear()
{
	Colors.clear();
}


CLinearColorGradient& CLinearColorGradient::addColor( const SColor& stopColor, f32 t )
{
	return addColor( video::SColorf(stopColor), t);
}

CLinearColorGradient& CLinearColorGradient::addColor( const SColorf& stopColor, f32 t )
{
	#if _DEBUG
		os::Printer::log( "CLinearColorGradient::addColor()", ELL_INFORMATION );
	#endif // _DEBUG

	MyColorStruct entry;
	entry.Color = stopColor;
	entry.Position = core::clamp<f32>( t, 0.0f, 1.0f );

	const u32 c = getColorCount();

	if (c==0)
	{
		Colors.push_back( entry );
	}
	else // if (c>0)
	{
		bool found_greater_t = false;
		u32 greater_t_index = 0;

		for (u32 i=0; i<c; i++)
		{
			if ( core::equals(t, Colors[i].Position) )
			{
				return *this;	// dont insert if any t does equal one of array-elements
			}
			else if ( Colors[i].Position > t )
			{
				found_greater_t = true;
				greater_t_index = i;
				break;
			}
		}

		if (found_greater_t)
			Colors.insert( entry, greater_t_index);
		else
			Colors.push_back( entry );
	}
	return *this;
}

CLinearColorGradient& CLinearColorGradient::setColor( u32 index, const SColor& stopColor, f32 t )
{
	const u32 size0 = getColorCount();
	if (index >= size0)
		return *this;

	Colors[index].Color = video::SColorf(stopColor);
	Colors[index].Position = core::clamp<f32>( t, 0.0f, 1.0f );
	return *this;
}

CLinearColorGradient& CLinearColorGradient::setColor( u32 index, const SColorf& stopColor, f32 t )
{
	const u32 size0 = getColorCount();
	if (index >= size0)
		return *this;

	Colors[index].Color = stopColor;
	Colors[index].Position = core::clamp<f32>( t, 0.0f, 1.0f );
	return *this;
}


SColor CLinearColorGradient::getColor( f32 t ) const
{
	return getColorf(t).toSColor();
}

SColorf CLinearColorGradient::getColorf( f32 t ) const
{

//	#if _DEBUG
//		os::Printer::log( "CLinearColorGradient::getColor()", ELL_INFORMATION );
//	#endif // _DEBUG

	const u32 colorCount = getColorCount();

	// find maximum and minimum neighbors

	bool found_greater_t = false;
	u32 greater_t_index = 0;

	for (u32 i=0; i<colorCount; i++)
	{
		if ( core::equals(t, Colors[i].Position) )
		{
			return Colors[i].Color;
		}
		else if (Colors[i].Position > t)
		{
			found_greater_t = true;
			greater_t_index = i;
			break;
		}
	}

	if (!found_greater_t)
	{
		return Colors[colorCount-1].Color;
	}

	// interpolate between prev and next neighbor color
	const SColorf& A = Colors[greater_t_index-1].Color;
	const SColorf& B = Colors[greater_t_index].Color;
	const f32 min_t = Colors[greater_t_index-1].Position;
	const f32 max_t = Colors[greater_t_index].Position;
	const f32 dx = core::abs_<f32>( (t - min_t) / (max_t - min_t) );
	const f32 fa = A.getAlpha() + dx*( B.getAlpha() - A.getAlpha() );
	const f32 fr = A.getRed() + dx*( B.getRed() - A.getRed() );
	const f32 fg = A.getGreen() + dx*( B.getGreen() - A.getGreen() );
	const f32 fb = A.getBlue() + dx*( B.getBlue() - A.getBlue() );

	return video::SColorf( fr,fg,fb,fa );
}

u32 CLinearColorGradient::getColorCount() const
{
	return Colors.size();
}

core::stringc CLinearColorGradient::getName( ) const
{
	return Name;
}

CLinearColorGradient& CLinearColorGradient::setName( const core::stringc& name )
{
	Name = name;
	return *this;
}

bool CLinearColorGradient::isTransparent( ) const
{
	bool bTransparent = false;
	u32 i=0;
	u32 c=getColorCount();

	while (i<c)
	{
		if (Colors[i].Color.getAlpha() < 1.0f) // not 255
		{
			bTransparent = true;
			break;
		}
		i++; // dont ever forget again foo
	}

	return bTransparent;
}

E_MATERIAL_TYPE CLinearColorGradient::getMaterialType( ) const
{
	if (isTransparent())
		return EMT_TRANSPARENT_ALPHA_CHANNEL;
	else
		return EMT_SOLID;
}

ECOLOR_FORMAT CLinearColorGradient::getColorFormat( ) const
{
	if (isTransparent())
		return ECF_A8R8G8B8;
	else
		return ECF_R8G8B8;
}

// old
//IImage*	CLinearColorGradient::createImage( IVideoDriver* driver, u32 w, u32 h, bool bVertical ) const

// new
IImage*	CLinearColorGradient::createImage( u32 w, u32 h, bool bVertical ) const
{
	#if _DEBUG
	os::Printer::log( "CLinearColorGradient::createImage()", ELL_INFORMATION );
	#endif // _DEBUG

	if (w==0 || h==0)
	{
		os::Printer::log( "Can't create Image of size zero.", ELL_ERROR );
		return 0;
	}

	// old
	//IImage* tmp = driver->createImage( this->getColorFormat(), core::dimension2du(w,h) );

	// new
	IImage* tmp = (IImage*)new CImage( this->getColorFormat(), core::dimension2du(w,h) );
	if (!tmp)
	{
		os::Printer::log( "Could not create CImage", ELL_ERROR );
		return 0;
	}

	const core::dimension2du& ImageSize = tmp->getDimension();

//	#if _DEBUG
//		// os::Printer::log( core::sprintf("Created new CImage(%d,%d,%d)", ImageSize.Width, ImageSize.Height, tmp->getBitsPerPixel()).c_str(), ELL_INFORMATION );
//		// os::Printer::log( "start filling", ELL_INFORMATION );
//	#endif // _DEBUG

	// vertical filling
	if ( bVertical )
	{
		const f32 fy = 1.0f / (f32)h;

		for (u32 y=0; y<ImageSize.Height; y++)
		{
			video::SColor color = getColor( fy*y );

			for (u32 x=0; x<ImageSize.Width; x++)
			{
				tmp->setPixel( x,y,color );
			}
		}

	}
	// horizontal filling
	else
	{
		const f32 fx = 1.0f / (f32)w ;

		for (u32 x=0; x<ImageSize.Width; x++)
		{
			video::SColor color = getColor( fx*x );

			for (u32 y=0; y<ImageSize.Height; y++)
			{
				tmp->setPixel( x,y,color );
			}
		}
	}

//	#if _DEBUG
//		os::Printer::log( "finish image filling with CLinearColorGradient", ELL_INFORMATION );
//	#endif // _DEBUG

	return tmp;
}

core::stringc CLinearColorGradient::toString( ) const
{
	core::stringc s("CLinearColorGradient[");

	// print number of colors used
	u32 c = getColorCount();
	s += (s32)c;

	// print name
	if (Name.size()>0)
	{
		s += Name;
		s += ", ";
	}

	// print
	s += "] = {\n";

	// print colors
	for (u32 i=0; i<c; i++)
	{
		s += "\t{ ";
		s += video::toString( Colors[i].Color.toSColor() );
		s += ", ";
		s += Colors[i].Position;
		s += " }";
		if (i<c)
		{
			s += ",";
		}
		s += "\n";
	}

	// print
	s += "};\n";
	return s;
}

//IImage* createImageFromLinearColorGradient( u32 w, u32 h, bool bVertical, CLinearColorGradient* gradient, bool deleteGradient)
//{
//	if (!gradient)
//		return 0;
//
//	IImage* tmp = gradient->createImage( w,h,bVertical );
//
//	if (deleteGradient)
//	{
//		delete gradient;
//	}
//
//	return tmp;
//}

} // end namespace video

} // end namespace irr
