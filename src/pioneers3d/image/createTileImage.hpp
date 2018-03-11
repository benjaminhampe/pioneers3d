#ifndef P3D_CREATE_TILE_IMAGE_HPP
#define P3D_CREATE_TILE_IMAGE_HPP

#include "createImage.hpp"
#include <pioneers3d/data/TileType.hpp>

namespace pioneers3d {

irr::video::IImage*

    createTileImage(

        irr::video::IVideoDriver* driver,

        TileType::ETileType const & type,

        int w,

        int h
    );


} // end namespace pioneers3d

#endif // P3D_CREATE_TILE_IMAGE_HPP
