#include "createTileTexture.hpp"

// ============================================================================
irr::video::IImage* createTileImage( irr::video::IVideoDriver* driver, E_TILE_TYPE type, int w, int h )
// ============================================================================
{
    irr::video::IImage* img = nullptr;
    switch( type )
    {
        case E_TILE_TYPE_WASSER: img = createWasserImage(driver,w,h); break;
        case E_TILE_TYPE_HOLZ: img = createHolzImage(driver,w,h); break;
        case E_TILE_TYPE_LEHM: img = createLehmImage(driver,w,h); break;
        case E_TILE_TYPE_WEIZEN: img = createWeizenImage(driver,w,h); break;
        case E_TILE_TYPE_WOLLE: img = createSchafImage(driver,w,h); break;
        case E_TILE_TYPE_ERZ: img = createErzImage(driver,w,h); break;
        default: break;
    }

    return img;
}

// ============================================================================
irr::video::ITexture* createTileTexture( irr::video::IVideoDriver* driver, E_TILE_TYPE type, int w, int h )
// ============================================================================
{
    irr::io::path name = "unknown.png";

    switch( type )
    {
        case E_TILE_TYPE_WASSER: name = "wasser.png"; break;
        case E_TILE_TYPE_HOLZ: name = "holz.png"; break;
        case E_TILE_TYPE_LEHM: name = "lehm.png"; break;
        case E_TILE_TYPE_WEIZEN: name = "weizen.png"; break;
        case E_TILE_TYPE_WOLLE: name = "wolle.png"; break;
        case E_TILE_TYPE_ERZ: name = "erz.png"; break;
        default: break;
    }

    irr::video::ITexture* tex = createTextureFromImage( driver, createTileImage( driver, type, w, h ) );

    return tex;
}