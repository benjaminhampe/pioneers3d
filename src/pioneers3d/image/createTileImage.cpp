#include "createTileImage.hpp"

#include "createImageWasser.hpp"
#include "createImageHolz.hpp"
#include "createImageLehm.hpp"
#include "createImageWeizen.hpp"
#include "createImageSchaf.hpp"
#include "createImageErz.hpp"

namespace pioneers3d {

irr::video::IImage*
createTileImage( irr::video::IVideoDriver * driver, TileType::ETileType const & type, int w, int h )
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

} // end namespace pioneers3d

