#ifndef TEXTURE_DATA_BUILDER_HPP
#define TEXTURE_DATA_BUILDER_HPP

#include <irrlicht.h>

irr::video::ITexture* 	createTextureFromImage( irr::video::IVideoDriver* driver, irr::video::IImage* img );

#if 0
// Specific for pioneers
irr::video::IImage*		createWasserImage( irr::video::IVideoDriver* driver, int w=256, int h=256 );
irr::video::IImage* 	createHolzImage( irr::video::IVideoDriver* driver, int w=256, int h=256 );
irr::video::IImage* 	createLehmImage( irr::video::IVideoDriver* driver, int w=256, int h=256 );
irr::video::IImage* 	createWeizenImage( irr::video::IVideoDriver* driver, int w=256, int h=256 );
irr::video::IImage* 	createSchafImage( irr::video::IVideoDriver* driver, int w=256, int h=256 );
irr::video::IImage* 	createErzImage( irr::video::IVideoDriver* driver, int w=256, int h=256 );

irr::video::IImage* 	createTileImage( irr::video::IVideoDriver* driver, E_TILE_TYPE type, int w=256, int h=256 );
irr::video::ITexture* 	createTileTexture( irr::video::IVideoDriver* driver, E_TILE_TYPE type, int w=256, int h=256 );
#endif

#endif // TEXTURE_DATA_BUILDER_HPP
