#include "createImageErz.hpp"

#include <irrlicht.h>
#include <time.h>

namespace pioneers3d {

    irr::video::IImage*
    createImageErz( irr::video::IVideoDriver* driver, int w, int h )
    {
        irr::video::IImage* img = createImage( driver, w, h );

        srand( (unsigned int)time(NULL) );

        for ( irr::u32 y = 0; y < img->getDimension().Height; ++y )
        {
            for ( irr::u32 x = 0; x < img->getDimension().Width; ++x )
            {
                //const int r = (rand() % 30) + 60;
                const int g = 255-(rand() % 190);
                //const int b = (rand() % 30) + 60;
                img->setPixel( x, y, irr::video::SColor( 255, g, g, g ) );
            }
        }

        return img;
    }

} // end namespace pioneers3d
