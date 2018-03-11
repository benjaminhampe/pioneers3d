#ifndef CREATE_IMAGE_HPP
#define CREATE_IMAGE_HPP

namespace irr { 
namespace video {

	class IVideoDriver; 
	class IImage;

	IImage*	
	createImage( IVideoDriver* driver, int w, int h );

} // end namespace video 
} // end namespace irr

#endif // CREATE_IMAGE_HPP
