#include "createImage.hpp"

#include <irrlicht.h>
#include <assert.h>

namespace pioneers3d {

irr::video::IImage*
createImage( irr::video::IVideoDriver* driver, int w, int h )
{
    assert( driver );

    assert( w > 0 );

    assert( h > 0 );

    irr::video::IImage * img = driver->createImage( irr::video::ECF_A8R8G8B8, irr::core::dimension2du( w, h ) );

    assert( img );

    assert( img->getDimension().Width > 0 );

    assert( img->getDimension().Height > 0 );

    img->fill( irr::video::SColor(0,0,0,0) );

    return img;
}

} // end namespace pioneers3d
