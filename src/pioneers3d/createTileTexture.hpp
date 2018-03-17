#ifndef P3D_CREATE_TEXTURE_FROM_IMAGE_HPP
#define P3D_CREATE_TEXTURE_FROM_IMAGE_HPP

#include <pioneers3d/data/TileType.hpp>

namespace irr {
namespace video {

	class IImage;
	class ITexture;
	class IVideoDriver;

} // end namespace video
} // end namespace irr

namespace pioneers3d {

	irr::video::IImage*
	createImage( irr::video::IVideoDriver* driver, int w, int h );

	irr::video::IImage*
	createImageWasser( irr::video::IVideoDriver* driver, int w, int h );

	irr::video::IImage*
	createImageSchaf( irr::video::IVideoDriver* driver, int w, int h );

	irr::video::IImage*
	createImageWeizen( irr::video::IVideoDriver* driver, int w, int h );

	irr::video::IImage*
	createImageLehm( irr::video::IVideoDriver* driver, int w, int h );

	irr::video::IImage*
	createImageHolz( irr::video::IVideoDriver* driver, int w, int h );

	irr::video::IImage*
	createImageErz( irr::video::IVideoDriver* driver, int w, int h );

	irr::video::ITexture*
	createTileTexture(
		irr::video::IVideoDriver* driver,
		TileType::ETileType const & tileType,
		int w,
		int h
	);

} // end namespace pioneers3d

#endif // P3D_CREATE_TEXTURE_FROM_IMAGE_HPP
