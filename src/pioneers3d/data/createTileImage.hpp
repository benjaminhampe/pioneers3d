#ifndef P3D_CREATE_TILE_IMAGE_HPP
#define P3D_CREATE_TILE_IMAGE_HPP

#include "createImage.hpp"
#include <TileType.hpp>

irr::video::IImage*
createTileImage( irr::video::IVideoDriver* driver, TileType type, int w=256, int h=256 );

#endif // P3D_CREATE_TILE_IMAGE_HPP
