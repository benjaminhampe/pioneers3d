// Copyright (C) 2002-2013 BenjaminHampe@gmx.de
// This file intends to advance the caps of the "Irrlicht Engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_C_LINEAR_COLOR_GRADIENT_H__
#define __IRR_C_LINEAR_COLOR_GRADIENT_H__

// #include <irrlicht.h>
#include <irrTypes.h>
#include <irrString.h>
#include <irrArray.h>
#include <SColor.h>
#include <EMaterialTypes.h>
#include <IImage.h>
#include <IVideoDriver.h>

namespace irr
{
	namespace video
	{
		core::stringc toString( const SColor& color );

		core::stringc toString( const SColorf& color );

		////////////////////////////////////////////////////////////////////////////
		///		class CLinearColorGradient
		////////////////////////////////////////////////////////////////////////////

		class CLinearColorGradient : public IReferenceCounted
		{
		public:

			CLinearColorGradient(); // const SColor& startColor = SColor(0,0,0,0), const SColor& endColor = SColor(255,255,255,255) );

			virtual ~CLinearColorGradient();

			virtual core::stringc getName( ) const;

			virtual CLinearColorGradient& setName( const core::stringc& name );

			virtual SColor getColor( f32 t ) const;

			virtual SColorf getColorf( f32 t ) const;

			virtual u32 getColorCount() const;

			virtual CLinearColorGradient& clear();

			virtual CLinearColorGradient& addColor( const SColor& stopColor, f32 t = 0.5f );

			virtual CLinearColorGradient& addColor( const SColorf& stopColor, f32 t = 0.5f );

			virtual CLinearColorGradient& setColor( u32 index, const SColor& stopColor, f32 t = 0.5f );

			virtual CLinearColorGradient& setColor( u32 index, const SColorf& stopColor, f32 t = 0.5f );

			virtual bool isTransparent( ) const;

			virtual E_MATERIAL_TYPE getMaterialType( ) const;

			virtual ECOLOR_FORMAT getColorFormat( ) const;

			virtual core::stringc toString( ) const;

			virtual IImage*	createImage( u32 w, u32 h, bool bVertical = false ) const;

		private:

			struct MyColorStruct
			{
				SColorf Color;
				f32 Position;			// in range 0..1
			};

			core::stringc Name;
			core::array<MyColorStruct> Colors;
		};

	} // end namespace video

} // end namespace irr

#endif // __IRR_C_LINEAR_COLOR_GRADIENT_H__
