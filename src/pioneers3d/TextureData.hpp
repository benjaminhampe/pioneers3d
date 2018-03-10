#ifndef P3D_TEXTURES_HPP
#define P3D_TEXTURES_HPP

#include <common/Types.hpp>

namespace p3d {

enum ETextureType
{
    TEX_WASSER = 0,
    TEX_HOLZ,
    TEX_LEHM,
    TEX_WEIZEN,
    TEX_WOLLE,
    TEX_ERZ,
    TEX_AUGEN_2,
    TEX_AUGEN_3,
    TEX_AUGEN_4,
    TEX_AUGEN_5,
    TEX_AUGEN_6,
    TEX_AUGEN_7,
    TEX_AUGEN_8,
    TEX_AUGEN_9,
    TEX_AUGEN_10,
    TEX_AUGEN_11,
    TEX_AUGEN_12,
    TEX_COUNT
};

const char* const sTextureNames[] =
{
    "TEX_WASSER.png",
    "TEX_HOLZ.png",
    "TEX_LEHM.png",
    "TEX_WEIZEN.png",
    "TEX_WOLLE.png",
    "TEX_ERZ.png",
    "TEX_AUGEN_02.png",
    "TEX_AUGEN_03.png",
    "TEX_AUGEN_04.png",
    "TEX_AUGEN_05.png",
    "TEX_AUGEN_06.png",
    "TEX_AUGEN_07.png",
    "TEX_AUGEN_08.png",
    "TEX_AUGEN_09.png",
    "TEX_AUGEN_10.png",
    "TEX_AUGEN_11.png",
    "TEX_AUGEN_12.png"
};

#if 0
// Generic as much as possible
irr::video::ITexture* 	createTextureFromImage( irr::video::IVideoDriver* driver, irr::video::IImage* img );

// Specific for pioneers
irr::video::IImage*		createWasserImage( irr::video::IVideoDriver* driver, int w=256, int h=256 );
irr::video::IImage* 	createHolzImage( irr::video::IVideoDriver* driver, int w=256, int h=256 );
irr::video::IImage* 	createLehmImage( irr::video::IVideoDriver* driver, int w=256, int h=256 );
irr::video::IImage* 	createWeizenImage( irr::video::IVideoDriver* driver, int w=256, int h=256 );
irr::video::IImage* 	createSchafImage( irr::video::IVideoDriver* driver, int w=256, int h=256 );
irr::video::IImage* 	createErzImage( irr::video::IVideoDriver* driver, int w=256, int h=256 );

irr::video::IImage* 	createTileImage( irr::video::IVideoDriver* driver, E_TILE_TYPE type, int w=256, int h=256 );
irr::video::ITexture* 	createTileTexture( irr::video::IVideoDriver* driver, E_TILE_TYPE type, int w=256, int h=256 );
#endif

// Texture handle using irrlicht-engine
struct TextureData
{
    irr::video::IVideoDriver* m_Driver = nullptr;

	irr::video::ITexture* m_Textures[ TEX_COUNT ];
	
    TextureData( irr::video::IVideoDriver* driver );

    ~TextureData();

    void build( std::string const & baseDir );

    void load( std::string const & baseDir );
};



} // end namespace p3d

#endif // P3D_TEXTURES_HPP
