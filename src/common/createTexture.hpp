#ifndef DE_ALPHASONIC_CREATE_TEXTURE_HPP
#define DE_ALPHASONIC_CREATE_TEXTURE_HPP

#include <sstream>

namespace irr {
namespace video {

	class IImage;
	class ITexture;
	class IVideoDriver;

} // end namespace video
} // end namespace irr

irr::video::ITexture*
createTextureFromImage(
	irr::video::IVideoDriver* driver,
	irr::video::IImage* img,
	std::string const & imgName = "" );

#endif // DE_ALPHASONIC_CREATE_TEXTURE_HPP
