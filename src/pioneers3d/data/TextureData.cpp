#include "TextureData.hpp"

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

TextureData::TextureData( irr::video::IVideoDriver* driver )
{
    _driver = driver;

    srand( (unsigned int)time(NULL) );

    createAndSave("data");
    load("data");
}

TextureData::~TextureData()
{

}

// ============================================================================
QImage createImage_Augen( int augen, int kreise )
// ============================================================================
{
    int w = 128;
    int h = 128;

    QImage img(w,h,QImage::Format_ARGB32);
    img.fill( QColor(255,255,255,255) );
    QFont font( "FontAwesome", 36, QFont::Normal, false );
    QString text = QString::number(augen);
    QSize textSize = QFontMetrics( font ).boundingRect( text ).size();
    QColor lineColor(20,20,20,255);

    QPainter dc;
    if (dc.begin(&img))
    {
        dc.setPen( QPen( lineColor ) );
        dc.setBrush( Qt::NoBrush );
        dc.setFont( font );
        dc.drawText( img.rect(), text, QTextOption(Qt::AlignCenter) );

        dc.setPen( QPen(QBrush(lineColor), 8.0f ) );
        dc.drawEllipse( 0,0,w,h );

        if (kreise > 4)
        {
            int y2 = ((h + textSize.height())>>1);
            int x2 = w/2;
            dc.setPen( Qt::NoPen );
            dc.setBrush( QBrush( lineColor ) );
            dc.drawEllipse( QPoint(x2,y2-10), 5,5 );
        }
        dc.end();
    }

    return img;
}

// ============================================================================
QImage createImage_Wasser( int w, int h )
// ============================================================================
{
    QImage img(w,h,QImage::Format_ARGB32);
    img.fill( QColor(0,0,0,0) );
    for ( int y = 0; y < img.height(); ++y ) {
    for ( int x = 0; x < img.width(); ++x ) {
        const int rg = (rand() % 50) + 20;
        const int b = (rand() % 155) + 100;
        img.setPixelColor( x,y, QColor(rg,rg,b) );
    }}
    return img;
}

// ============================================================================
QImage createImage_Holz( int w, int h )
// ============================================================================
{
    QImage img(w,h,QImage::Format_ARGB32);
    img.fill( QColor(0,0,0,0) );
    for ( int y = 0; y < img.height(); ++y ) {
    for ( int x = 0; x < img.width(); ++x ) {
        const int g = 200-(rand() % 155);
        img.setPixelColor( x,y, QColor(0,g,0) );
    }}
    return img;
}

// ============================================================================
QImage createImage_Lehm( int w, int h )
// ============================================================================
{
    QImage img(w,h,QImage::Format_ARGB32);
    img.fill( QColor(0,0,0,0) );
    for ( int y = 0; y < img.height(); ++y ) {
    for ( int x = 0; x < img.width(); ++x ) {
        const int r = 225-(rand() % 100);
        const int g = r-50-(rand() % 75);
        img.setPixelColor( x,y, QColor(r,g,0) );
    }}
    return img;
}

// ============================================================================
QImage createImage_Weizen( int w, int h )
// ============================================================================
{
    QImage img(w,h,QImage::Format_ARGB32);
    img.fill( QColor(0,0,0,0) );
    for ( int y = 0; y < img.height(); ++y ) {
    for ( int x = 0; x < img.width(); ++x ) {
        const int r = 255;
        const int g = 255-(rand() % 55);
        img.setPixelColor( x,y, QColor(r,g,0) );
    }}
    return img;
}

// ============================================================================
QImage createImage_Wolle( int w, int h )
// ============================================================================
{
    QImage img(w,h,QImage::Format_ARGB32);
    img.fill( QColor(0,0,0,0) );
    for ( int y = 0; y < img.height(); ++y ) {
    for ( int x = 0; x < img.width(); ++x ) {
        const int g = 255-(rand() % 100);
        img.setPixelColor( x,y, QColor(100,g,100) );
    }}
    return img;
}

// ============================================================================
QImage createImage_Erz( int w, int h )
// ============================================================================
{
    QImage img(w,h,QImage::Format_ARGB32);
    img.fill( QColor(0,0,0,0) );
    for ( int y = 0; y < img.height(); ++y ) {
    for ( int x = 0; x < img.width(); ++x ) {
        const int rgb = 255-(rand() % 155);
        img.setPixelColor( x,y, QColor(rgb,rgb,rgb) );
    }}
    return img;
}

// ============================================================================
void TextureData::createAndSave( const QString& baseDir )
// ============================================================================
{
    /// CREATE

    QImage _img[E_SIEDLER_TEX_COUNT];
    _img[E_SIEDLER_TEX_WASSER] = createImage_Wasser( _texW, _texH );
    _img[E_SIEDLER_TEX_HOLZ] = createImage_Holz( _texW, _texH );
    _img[E_SIEDLER_TEX_LEHM] = createImage_Lehm( _texW, _texH );
    _img[E_SIEDLER_TEX_WEIZEN] = createImage_Weizen( _texW, _texH );
    _img[E_SIEDLER_TEX_WOLLE] = createImage_Wolle( _texW, _texH );
    _img[E_SIEDLER_TEX_ERZ] = createImage_Erz( _texW, _texH );
    _img[E_SIEDLER_TEX_AUGEN_2] = createImage_Augen(2,0);
    _img[E_SIEDLER_TEX_AUGEN_3] = createImage_Augen(3,0);
    _img[E_SIEDLER_TEX_AUGEN_4] = createImage_Augen(4,2);
    _img[E_SIEDLER_TEX_AUGEN_5] = createImage_Augen(5,3);
    _img[E_SIEDLER_TEX_AUGEN_6] = createImage_Augen(6,4);
    _img[E_SIEDLER_TEX_AUGEN_7] = createImage_Augen(7,5);
    _img[E_SIEDLER_TEX_AUGEN_8] = createImage_Augen(8,4);
    _img[E_SIEDLER_TEX_AUGEN_9] = createImage_Augen(9,3);
    _img[E_SIEDLER_TEX_AUGEN_10] = createImage_Augen(10,2);
    _img[E_SIEDLER_TEX_AUGEN_11] = createImage_Augen(11,0);
    _img[E_SIEDLER_TEX_AUGEN_12] = createImage_Augen(12,0);

    /// SAVE

    QDir().mkpath( baseDir );

    for ( int i = 0; i < E_SIEDLER_TEX_COUNT; ++i )
    {
        QString fileName = baseDir;
        fileName.append( "/" );
        fileName.append( E_SIEDLER_TEX_FILENAMES[i] );

        if (!_img[i].save( fileName ))
        {
            std::cout << "Cannot save image (" << fileName.toStdString() << ")" << std::endl;
        }
    }
}

void TextureData::load( const QString& baseDir )
{
    for ( int i = 0; i < E_SIEDLER_TEX_COUNT; ++i )
    {
        QString fileName = baseDir;
        fileName.append( "/" );
        fileName.append( E_SIEDLER_TEX_FILENAMES[i] );

        _tex[i] = loadTexture( _driver, fileName );

        if (!_tex[i])
        {
            std::cout << "Cannot load texture (" << fileName.toStdString() << ")" << std::endl;
        }
    }
}

#if 0
// ============================================================================
irr::video::ITexture* createTextureFromImage( irr::video::IVideoDriver* driver, irr::video::IImage* img )
// ============================================================================
{
    const bool didCreateMipmaps = driver->getTextureCreationFlag( irr::video::ETCF_CREATE_MIP_MAPS );
    const bool didCreateAlways32 = driver->getTextureCreationFlag( irr::video::ETCF_ALWAYS_32_BIT );
    const bool didCreateNonPower2 = driver->getTextureCreationFlag( irr::video::ETCF_ALLOW_NON_POWER_2 );

    driver->setTextureCreationFlag( irr::video::ETCF_CREATE_MIP_MAPS, false );
    driver->setTextureCreationFlag( irr::video::ETCF_ALWAYS_32_BIT, true );
    driver->setTextureCreationFlag( irr::video::ETCF_ALLOW_NON_POWER_2, true );

    irr::video::ITexture* tex = driver->addTexture( "", img, 0 );

    driver->setTextureCreationFlag( irr::video::ETCF_CREATE_MIP_MAPS, didCreateMipmaps );
    driver->setTextureCreationFlag( irr::video::ETCF_ALWAYS_32_BIT, didCreateAlways32 );
    driver->setTextureCreationFlag( irr::video::ETCF_ALLOW_NON_POWER_2, didCreateNonPower2 );

    return tex;
}

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

// ============================================================================
irr::video::IImage* createWasserImage( irr::video::IVideoDriver* driver, int w, int h )
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
            const int rg = (rand() % 50) + 20;
            const int b = (rand() % 155) + 100;
            img->setPixel( x,y, irr::video::SColor(255,rg,rg,b) );
        }
    }

    return img;
}

// ============================================================================
irr::video::IImage* createHolzImage( irr::video::IVideoDriver* driver, int w, int h )
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
            const int g = 255-(rand() % 155);
            img->setPixel( x,y, irr::video::SColor(255,0,g,0) );
        }
    }

    return img;
}

// ============================================================================
irr::video::IImage* createLehmImage( irr::video::IVideoDriver* driver, int w, int h )
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
            const int r = 255-(rand() % 100);
            const int g = r-100-(rand() % 55);
            img->setPixel( x,y, irr::video::SColor(255,r,g,0) );
        }
    }

    return img;
}

// ============================================================================
irr::video::IImage* createWeizenImage( irr::video::IVideoDriver* driver, int w, int h )
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
            const int r = 255;
            const int g = 255-(rand() % 55);
            img->setPixel( x,y,irr::video::SColor(255,r,g,0));
        }
    }

    return img;
}

// ============================================================================
irr::video::IImage* createSchafImage( irr::video::IVideoDriver* driver, int w, int h )
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
            const int g = 255-(rand() % 100);
            img->setPixel( x,y, irr::video::SColor(255,100,g,100) );
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

#endif
