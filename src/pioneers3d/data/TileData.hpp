#ifndef P3D_TILEDATA_HPP
#define P3D_TILEDATA_HPP

#include <TileType.hpp>

irr::video::IImage* 	
createTileImage( irr::video::IVideoDriver* driver, E_TILE_TYPE type, int w=256, int h=256 );

irr::video::ITexture* 	
createTileTexture( irr::video::IVideoDriver* driver, E_TILE_TYPE type, int w=256, int h=256 );

struct TileData
{	
    TileData();

    ~TileData();

    void build( std::string const & baseDir );

    void load( std::string const & baseDir );
};

} // end namespace p3d

#endif // P3D_TILEDATA_HPP
