// Copyright (C) 2002-2013 BenjaminHampe@gmx.de
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CImageManager.h"

#include <irrlicht.h>
#include <../source/Irrlicht/CImage.h>
#include <../source/Irrlicht/os.h>

namespace irr{
namespace video{

//! constructor
CImageManager::CImageManager( IVideoDriver* driver, ILogger* debugLog)
: Driver(driver)
, Log(debugLog)
{
	Elements.reallocate(32);
	Elements.set_used(0);
}

//! destructor
CImageManager::~CImageManager()
{
//	for (u32 e=0; e<Elements.size(); e++)
//	{
//		if (Elements[e].Data)
//		{
//			Elements[e].Data)
//		}
//	}
}

//! \return return number of currently managed images
u32 CImageManager::getImageCount( ) const
{
	return Elements.size();
}

//! \return valid pointer, if image found by this index number
IImage* CImageManager::getImageByIndex( u32 indexNr )
{
	if (indexNr<1)
		return 0;

	u32 count = Elements.size();
	if ( indexNr>count )
		return 0;

	return Elements[indexNr-1].Data;
}

//! \return valid pointer, if image found by this name
IImage* CImageManager::getImageByName( const io::path& fileName )
{
	if (fileName == io::path("") )
		return 0;

	u32 count = Elements.size();
	u32 index = 0;
	while(index<count)
	{
		if (Elements[index].Name == fileName)
		{
			return Elements[index].Data;
		}
		index++;
	}
	return 0;
}

//! \return return true, if image found by this valid index number from 1 to getImageCount()
bool CImageManager::existImage( u32 indexNr ) const
{
	if (indexNr<1)
		return false;

	u32 count = Elements.size();
	if ( indexNr>count )
		return false;

	return (!(Elements[indexNr-1].Data));
}

//! \return delete image under this valid index, if found
bool CImageManager::deleteImage( u32 indexNr )
{
	if (!existImage( indexNr ))
		return false;

	if (Elements[indexNr-1].Data)
	{
		Elements[indexNr-1].Data->drop();
		Elements[indexNr-1].Data=0;
		return true;
	}
	return false;
}

//! \return valid indexNr, if image added to manager successfully
u32 CImageManager::addImage( IImage* src, const io::path& fileName )
{
	if (!src)
		return 0;

	SImageEntity entity;
	entity.Data = src;
	entity.Data->grab();
	entity.Name = fileName;
	entity.UseColorKey = false;
	entity.ColorKey.set(255,255,255,255);
	Elements.push_back(entity);
	return Elements.size();
}

//! \return true, if color-key enabled
bool CImageManager::isColorKeyEnabled( u32 indexNr ) const
{

}


//! \brief enable or disable ColorKey
void CImageManager::setColorKeyEnabled( u32 indexNr, bool bEnabled )
{

}


//! \brief set image color-key color
void CImageManager::setColorKey( u32 indexNr, const SColor& colorKey )
{

}


//! \return colorkey color
SColor CImageManager::getColorKey( u32 indexNr ) const
{

}

} // end namespace video
} // end namespace irr
