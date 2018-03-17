#include "createTileTexture.hpp"

#include <irrlicht.h>
#include <assert.h>

namespace pioneers3d {

#if 0
irr::video::IImage*
createTileImage( irr::video::IVideoDriver * driver, ETileType const & type, int w, int h )
{
	irr::video::IImage* img = nullptr;
	switch( type )
	{
		case TileType::WASSER: img = createImageWasser(driver,w,h); break;
		case TileType::HOLZ: img = createImageHolz(driver,w,h); break;
		case TileType::LEHM: img = createImageLehm(driver,w,h); break;
		case TileType::WEIZEN: img = createImageWeizen(driver,w,h); break;
		case TileType::WOLLE: img = createImageSchaf(driver,w,h); break;
		case TileType::ERZ: img = createImageErz(driver,w,h); break;
		default: break;
	}

	return img;
}
#endif

irr::video::ITexture*
createTileTexture( irr::video::IVideoDriver* driver, TileType::ETileType const & tileType, int w, int h )
{
	irr::io::path name = "unknown.png";

	switch( tileType )
	{
		case TileType::WASSER: name = "wasser.png"; break;
		case TileType::HOLZ: name = "holz.png"; break;
		case TileType::LEHM: name = "lehm.png"; break;
		case TileType::WEIZEN: name = "weizen.png"; break;
		case TileType::WOLLE: name = "wolle.png"; break;
		case TileType::ERZ: name = "erz.png"; break;
		default: break;
	}

	irr::video::IImage* img = createTileImage( driver, tileType, w, h );

	irr::video::ITexture* tex = createTextureFromImage( driver, img );

	img->drop();

	return tex;
}


irr::video::IImage*
createImageWasser( irr::video::IVideoDriver* driver, int w, int h )
{
	irr::video::IImage* img = createImage( driver, w, h );

	srand( (unsigned int)time(NULL) );

	for ( irr::u32 y = 0; y < img->getDimension().Height; ++y )
	{
		for ( irr::u32 x = 0; x < img->getDimension().Width; ++x )
		{
			const int r = (rand() % 20) + 10;
			const int g = (rand() % 30) + 20;
			const int b = (rand() % 115) + 140;
			img->setPixel( x, y, irr::video::SColor( 255, r, g, b ) );
		}
	}

	return img;
}

irr::video::IImage*
createImageWeizen( irr::video::IVideoDriver* driver, int w, int h )
{
	irr::video::IImage* img = createImage( driver, w, h );

	srand( (unsigned int)time(NULL) );

	for ( irr::u32 y = 0; y < img->getDimension().Height; ++y )
	{
		for ( irr::u32 x = 0; x < img->getDimension().Width; ++x )
		{
			const int r = 255-(rand() % 65);
			const int g = 255-(rand() % 115);
			const int b = (rand() % 30) + 20;
			img->setPixel( x, y, irr::video::SColor( 255, r, g, b ) );
		}
	}

	return img;
}

irr::video::IImage*
createImageSchaf( irr::video::IVideoDriver* driver, int w, int h )
{
	irr::video::IImage* img = createImage( driver, w, h );

	srand( (unsigned int)time(NULL) );

	for ( irr::u32 y = 0; y < img->getDimension().Height; ++y )
	{
		for ( irr::u32 x = 0; x < img->getDimension().Width; ++x )
		{
			const int r = (rand() % 30) + 60;
			const int g = 255-(rand() % 100);
			const int b = (rand() % 30) + 60;
			img->setPixel( x, y, irr::video::SColor( 255, r, g, b ) );
		}
	}

	return img;
}

irr::video::IImage*
createImageLehm( irr::video::IVideoDriver* driver, int w, int h )
{
	irr::video::IImage* img = createImage( driver, w, h );

	srand( (unsigned int)time(NULL) );

	for ( irr::u32 y = 0; y < img->getDimension().Height; ++y )
	{
		for ( irr::u32 x = 0; x < img->getDimension().Width; ++x )
		{
			const int r = (rand() % 115) + 140;
			const int g = (rand() % 115) + 140;
			const int b = (rand() % 30) + 20;
			img->setPixel( x, y, irr::video::SColor( 255, r, g, b ) );
		}
	}

	return img;
}

irr::video::IImage*
createImageHolz( irr::video::IVideoDriver* driver, int w, int h )
{
	irr::video::IImage* img = createImage( driver, w, h );

	srand( (unsigned int)time(NULL) );

	for ( irr::u32 y = 0; y < img->getDimension().Height; ++y )
	{
		for ( irr::u32 x = 0; x < img->getDimension().Width; ++x )
		{
			const int r = (rand() % 20) + 10;
			const int g = (rand() % 115) + 140;
			const int b = (rand() % 30) + 20;
			img->setPixel( x, y, irr::video::SColor( 255, r, g, b ) );
		}
	}

	return img;
}

irr::video::IImage*
createImageErz( irr::video::IVideoDriver* driver, int w, int h )
{
	irr::video::IImage* img = createImage( driver, w, h );

	srand( (unsigned int)time(NULL) );

	for ( irr::u32 y = 0; y < img->getDimension().Height; ++y )
	{
		for ( irr::u32 x = 0; x < img->getDimension().Width; ++x )
		{
			//const int r = (rand() % 30) + 60;
			const int g = 255-(rand() % 190);
			//const int b = (rand() % 30) + 60;
			img->setPixel( x, y, irr::video::SColor( 255, g, g, g ) );
		}
	}

	return img;
}


} // end namespace pioneers3d

