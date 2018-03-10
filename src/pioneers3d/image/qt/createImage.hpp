#ifndef CREATE_IMAGE_HPP
#define CREATE_IMAGE_HPP

// ============================================================================

namespace irr { namespace video { class IVideoDriver; } }
namespace irr { namespace video { class IImage; } }

irr::video::IImage*	
createWaterImage( irr::video::IVideoDriver* driver, int w, int h );

// ============================================================================

class QImage;

QImage 
createWaterImage( int w, int h );

#endif // CREATE_IMAGE_HPP
