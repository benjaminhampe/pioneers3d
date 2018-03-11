#ifndef P3D_DATA_CREATE_TILE_TEXTURE_HPP
#define P3D_DATA_CREATE_TILE_TEXTURE_HPP

#include <TileType.hpp>

irr::video::IImage* 	
createTileImage( irr::video::IVideoDriver* driver, E_TILE_TYPE type, int w=256, int h=256 );

irr::video::ITexture* 	
createTileTexture( irr::video::IVideoDriver* driver, E_TILE_TYPE type, int w=256, int h=256 );

#endif // P3D_DATA_CREATE_TILE_TEXTURE_HPP
