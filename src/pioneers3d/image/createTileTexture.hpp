#ifndef P3D_DATA_CREATE_TILE_TEXTURE_HPP
#define P3D_DATA_CREATE_TILE_TEXTURE_HPP

#include <pioneers3d/data/TileType.hpp>

namespace pioneers3d {

    irr::video::ITexture*
    createTileTexture(
        irr::video::IVideoDriver* driver,
        TileType::ETileType const & tileType,
        int w,
        int h
    );

} // end namespace pioneers3d

#endif // P3D_DATA_CREATE_TILE_TEXTURE_HPP
