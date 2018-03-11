#include "createImage.hpp"

#include <QImage>
#include <QFont>
#include <QDir>
#include <QFileInfo>
#include <QFontMetrics>
#include <QColor>
#include <QPainter>
#include <QPen>
#include <QBrush>

QImage 
createImage( int w, int h )
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
