#include <pioneers3d/image/createTileTexture.hpp>

#include <pioneers3d/image/createTileImage.hpp>

#include <pioneers3d/image/createTextureFromImage.hpp>

namespace pioneers3d {

// ============================================================================
irr::video::ITexture* createTileTexture( irr::video::IVideoDriver* driver, TileType::ETileType const & tileType, int w, int h )
// ============================================================================
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

} // end namespace pioneers3d

