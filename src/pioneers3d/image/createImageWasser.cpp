#include "createImageWasser.hpp"

#include <irrlicht.h>
#include <time.h>

namespace pioneers3d {

irr::video::IImage*
createImageWasser( irr::video::IVideoDriver* driver, int w, int h )
{
    irr::video::IImage* img = createImage( driver, w, h );

    srand( (unsigned int)time(NULL) );

    for ( irr::u32 y = 0; y < img->getDimension().Height; ++y )
    {
        for ( irr::u32 x = 0; x < img->getDimension().Width; ++x )
        {
            const int r = (rand() % 20) + 10;
            const int g = (rand() % 30) + 20;
            const int b = (rand() % 115) + 140;
            img->setPixel( x, y, irr::video::SColor( 255, r, g, b ) );
        }
    }

    return img;
}

} // end namespace pioneers3d
