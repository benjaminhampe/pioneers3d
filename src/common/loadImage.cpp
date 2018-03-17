#include "loadImage.hpp"

#include <irrlicht.h>
#include <time.h>

namespace pioneers3d {

	irr::video::IImage*
	loadImage( irr::video::IVideoDriver* driver, std::string const & fileName )
	{
		irr::video::IImage* img = createImage( driver, w, h );

		srand( (unsigned int)time(NULL) );

		for ( irr::u32 y = 0; y < img->getDimension().Height; ++y )
		{
			for ( irr::u32 x = 0; x < img->getDimension().Width; ++x )
			{
				const int r = 255-(rand() % 65);
				const int g = 255-(rand() % 115);
				const int b = (rand() % 30) + 20;
				img->setPixel( x, y, irr::video::SColor( 255, r, g, b ) );
			}
		}

		return img;
	}

} // end namespace pioneers3d
