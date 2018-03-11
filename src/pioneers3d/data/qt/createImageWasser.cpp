#include "createImageWasser.hpp"

#include <iostream>
#include <time.h>
#include <QImage>
#include <QFont>
#include <QDir>
#include <QFileInfo>
#include <QFontMetrics>
#include <QColor>
#include <QPainter>
#include <QPen>
#include <QBrush>

// ============================================================================

irr::video::IImage* 
createImageWasser( irr::video::IVideoDriver* driver, int w, int h )
{
    srand( (unsigned int)time(NULL) );

    irr::video::IImage* img = driver->createImage( irr::video::ECF_A8R8G8B8, irr::core::dimension2du( w, h ) );
    
	irr::core::dimension2du siz = img->getDimension();

    img->fill( irr::video::SColor(0,0,0,0) );

    for ( irr::u32 y = 0; y < siz.Height; ++y )
    {
        for ( irr::u32 x = 0; x < siz.Width; ++x )
        {
            const int rg = (rand() % 50) + 20;
            const int b = (rand() % 155) + 100;
            img->setPixel( x,y, irr::video::SColor(255,rg,rg,b) );
        }
    }

    return img;
}


// ============================================================================

QImage 
createImageWasserQt( int w, int h )
{
    srand( (unsigned int)time(NULL) );
	
    QImage img( w, h, QImage::Format_ARGB32 );
	
    img.fill( QColor(0,0,0,0) );
    
	for ( int y = 0; y < img.height(); ++y ) 
	{
		for ( int x = 0; x < img.width(); ++x ) 
		{
			int const r = (rand() % 50) + 10;
			int const g = (rand() % 50) + 20;
			int const b = (rand() % 155) + 100;
			img.setPixelColor( x, y, QColor( r, g, b ) );
		}
	}
    return img;
}

