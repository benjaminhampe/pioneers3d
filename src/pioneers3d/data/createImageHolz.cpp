#include "createImageHolz.hpp"

#include <irrlicht.h>

irr::video::IImage* 
createImageHolz( irr::video::IVideoDriver* driver, int w, int h )
{
	irr::video::IImage* img = irr::video::createImage( driver, w, h );
	
    srand( (unsigned int)time(NULL) );
	
    for ( irr::u32 y = 0; y < img->getDimension().Height; ++y )
    {
        for ( irr::u32 x = 0; x < img->getDimension().Width; ++x )
        {
            const int r = (rand() % 20) + 10;
			const int g = (rand() % 115) + 140;
			const int b = (rand() % 30) + 20;
            img->setPixel( x, y, irr::video::SColor( 255, r, g, b ) );
        }
    }

    return img;
}