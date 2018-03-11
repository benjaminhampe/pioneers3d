#include "createTileImage.hpp"

#include "createImageWasser.hpp"
#include "createImageHolz.hpp"
#include "createImageLehm.hpp"
#include "createImageWeizen.hpp"
#include "createImageSchaf.hpp"
#include "createImageErz.hpp"

using irr::video::IImage;
using irr::video::IVideoDriver;

IImage* 
createTileImage( IVideoDriver * driver, TileType type, int w, int h )
{
    IImage* img = nullptr;
    switch( type )
    {
        case TypeType::WASSER: img = createImageWasser(driver,w,h); break;
        case TypeType::HOLZ: img = createImageHolz(driver,w,h); break;
        case TypeType::LEHM: img = createImageLehm(driver,w,h); break;
        case TypeType::WEIZEN: img = createImageWeizen(driver,w,h); break;
        case TypeType::WOLLE: img = createImageSchaf(driver,w,h); break;
        case TypeType::ERZ: img = createImageErz(driver,w,h); break;
        default: break;
    }

    return img;
}