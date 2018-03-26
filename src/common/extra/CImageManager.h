// Copyright (C) 2002-2013 BenjaminHampe@gmx.de
// This file intends to advance the caps of the "Irrlicht Engine" 1.8 svn OpenGL C++ 0x11 amd64_86 ia686
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_C_IMAGE_MANAGER_H__
#define __IRR_C_IMAGE_MANAGER_H__

#include <irrlicht.h>
#include <EDeviceTypes.h>
#include <EDriverFeatures.h>

namespace irr
{
	namespace video
	{
		// ================================================================================================================
		//! \class CImageManager
		// ================================================================================================================

		class CImageManager : public IReferenceCounted
		{
		public:
			struct SImageEntity
			{
				video::IImage* Data;
				io::path Name;
				bool UseColorKey;
				video::SColor ColorKey;
			};

		public:
			//! constructor
			CImageManager( IVideoDriver* driver, ILogger* debugLog = 0);

			//! destructor
			virtual ~CImageManager();

			//! \return return number of currently managed images
			virtual u32 getImageCount( ) const;

			//! \return valid pointer, if image found by this index number
			virtual IImage* getImageByIndex( u32 indexNr = 1);

			//! \return valid pointer, if image found by this name
			virtual IImage* getImageByName( const io::path& fileName );

			//! \return valid indexNr, if image added to manager successfully
			virtual u32 addImage( IImage* src, const io::path& fileName = "" );

			//! \return return true, if image found by this valid index number from 1 to getImageCount()
			virtual bool existImage( u32 indexNr ) const;

			//! \return delete image under this valid index, if found
			virtual bool deleteImage( u32 indexNr );

			//! \return true, if color-key enabled
			virtual bool isColorKeyEnabled( u32 indexNr ) const;

			//! \brief enable or disable ColorKey
			virtual void setColorKeyEnabled( u32 indexNr, bool bEnabled = true );

			//! \brief set image color-key color
			virtual void setColorKey( u32 indexNr, const SColor& colorKey = SColor(0,0,0,0) );

			//! \return colorkey color
			virtual SColor getColorKey( u32 indexNr ) const;

		private:
			IVideoDriver* Driver;
			ILogger* Log;
			core::array<SImageEntity> Elements;
		};

	} // end namespace video
} // end namespace irr

#endif // __IRR_C_IMAGE_MANAGER_H__
