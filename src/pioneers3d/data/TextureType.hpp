#ifndef P3D_DATA_TEXTURETYPE_HPP
#define P3D_DATA_TEXTURETYPE_HPP

namespace pioneers3d {

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

class TextureType
{
public:
    enum ETextureType
    {
        WASSER = 0,
        HOLZ,
        LEHM,
        WEIZEN,
        WOLLE,
        ERZ,
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



    // TextureType();

    // TextureType( irr::video::IVideoDriver* driver );
};

} // end namespace pioneers3d

#endif // P3D_DATA_TEXTURETYPE_HPP
