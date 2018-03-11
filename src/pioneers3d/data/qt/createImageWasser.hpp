#ifndef P3D_CREATE_WATER_IMAGE_HPP
#define P3D_CREATE_WATER_IMAGE_HPP

#include <QImage>

QImage 
createWaterImageQt( int w, int h )

// ============================================================================

#include <irrlicht.h>

irr::video::IImage*	
createWaterImageIrr( irr::video::IVideoDriver* driver, int w=256, int h=256 );

#endif // P3D_CREATE_WATER_IMAGE_HPP
