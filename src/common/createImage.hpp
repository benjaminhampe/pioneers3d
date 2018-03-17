#ifndef DE_ALPHASONIC_CREATE_IMAGE_HPP
#define DE_ALPHASONIC_CREATE_IMAGE_HPP

namespace irr {
namespace video {

	class IVideoDriver;
	class IImage;

} // end namespace video
} // end namespace irr

irr::video::IImage*
createImage( irr::video::IVideoDriver* driver, int w, int h );

#endif // DE_ALPHASONIC_CREATE_IMAGE_HPP
