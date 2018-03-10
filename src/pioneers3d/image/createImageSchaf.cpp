#include "createImageSchaf.hpp"

#include <irrlicht.h>

irr::video::IImage* 
createImageSchaf( irr::video::IVideoDriver* driver, int w, int h )
{
	irr::video::IImage* img = irr::video::createImage( driver, w, h );
	
    srand( (unsigned int)time(NULL) );
	
    for ( irr::u32 y = 0; y < img->getDimension().Height; ++y )
    {
        for ( irr::u32 x = 0; x < img->getDimension().Width; ++x )
        {
            const int r = (rand() % 30) + 60;
			const int g = 255-(rand() % 100);
			const int b = (rand() % 30) + 60;
            img->setPixel( x, y, irr::video::SColor( 255, r, g, b ) );
        }
    }

    return img;
}

// ============================================================================
irr::video::IImage* createErzImage( irr::video::IVideoDriver* driver, int w, int h )
// ============================================================================
{
    irr::video::IImage* img = driver->createImage( irr::video::ECF_A8R8G8B8, irr::core::dimension2du(w,h) );
    irr::core::dimension2du img_size = img->getDimension();

    img->fill( irr::video::SColor(0,0,0,0) );

    srand( (unsigned int)time(NULL) );

    for ( irr::u32 y = 0; y < img_size.Height; ++y )
    {
        for ( irr::u32 x = 0; x < img_size.Width; ++x )
        {
            const int rgb = 255-(rand() % 155);
            img->setPixel( x,y,irr::video::SColor(255,rgb,rgb,rgb));
        }
    }

    return img;
}
