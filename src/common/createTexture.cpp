#include <createTexture.hpp>

#include <irrlicht.h>
#include <assert.h>

irr::video::ITexture*
createTextureFromImage(
	irr::video::IVideoDriver* driver,
	irr::video::IImage* img, std::string const & imgName )
{
	assert( driver );

	assert( img );

	const bool hasMipmaps = driver->getTextureCreationFlag( irr::video::ETCF_CREATE_MIP_MAPS );
	const bool hasAlways32 = driver->getTextureCreationFlag( irr::video::ETCF_ALWAYS_32_BIT );
	const bool hasNonPower2 = driver->getTextureCreationFlag( irr::video::ETCF_ALLOW_NON_POWER_2 );

	driver->setTextureCreationFlag( irr::video::ETCF_CREATE_MIP_MAPS, false );
	driver->setTextureCreationFlag( irr::video::ETCF_ALWAYS_32_BIT, true );
	driver->setTextureCreationFlag( irr::video::ETCF_ALLOW_NON_POWER_2, true );

	irr::video::ITexture * tex = driver->addTexture( imgName.empty() ? "" : imgName.c_str(), img, 0 );

	assert( tex );

	driver->setTextureCreationFlag( irr::video::ETCF_CREATE_MIP_MAPS, hasMipmaps );
	driver->setTextureCreationFlag( irr::video::ETCF_ALWAYS_32_BIT, hasAlways32 );
	driver->setTextureCreationFlag( irr::video::ETCF_ALLOW_NON_POWER_2, hasNonPower2 );

	return tex;
}
