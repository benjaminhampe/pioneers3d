#ifndef PIONEERS3D_DATA_IMAGES_HPP
#define PIONEERS3D_DATA_IMAGES_HPP

#include <irrlicht.h>
#include <sstream>
#include <stdint.h>

namespace pioneers3d {

	class TextureType
	{
	public:
		enum ETextureType
		{
			UNKNOWN = 0,
			WASSER,	HOLZ, LEHM,	WEIZEN,	WOLLE, ERZ,
			HAFEN_4zu1, HAFEN_LEHM,	HAFEN_HOLZ,	HAFEN_WEIZEN, HAFEN_ERZ, HAFEN_WOLLE,
			CARD_BACG, EXTRA_,	HAFEN_HOLZ,	HAFEN_WEIZEN, HAFEN_ERZ, HAFEN_WOLLE,
			AUGEN_2,
			AUGEN_3,
			AUGEN_4,
			AUGEN_5,
			AUGEN_6,
			AUGEN_7,
			AUGEN_8,
			AUGEN_9,
			AUGEN_10,
			AUGEN_11,
			AUGEN_12,
			COUNT
		};

		const char* const s_TextureNames[] =
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

		// TextureType();
		// TextureType( irr::video::IVideoDriver* driver );
	};

} // end namespace pioneers3d

#endif // PIONEERS3D_DATA_IMAGES_HPP
