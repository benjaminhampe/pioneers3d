#ifndef P3D_CREATE_TEXTURE_FROM_IMAGE_HPP
#define P3D_CREATE_TEXTURE_FROM_IMAGE_HPP

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
	irr::video::IImage* img );
	
#endif // P3D_CREATE_TEXTURE_FROM_IMAGE_HPP
