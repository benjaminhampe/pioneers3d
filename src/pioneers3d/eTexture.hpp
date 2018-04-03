/// (c) 2017 - 2018 Benjamin Hampe <benjaminhampe@gmx.de>
/// All rights reserved, except the following natural persons:
/// Only free for Persian princesses that have a github account
/// and upgrade their PC (personal flying carpet) with a Raspberry Pi,
/// or people that speak AND live the words of Jesus Christ.

#ifndef PIONEERS3D_E_TEXTURE_HPP
#define PIONEERS3D_E_TEXTURE_HPP

#include <common/Types.hpp>

namespace pioneers3d {

enum class eTexture : uint32_t
{
    UNKNOWN = 0,
    SKYBOX_TOP,
    SKYBOX_BOTTOM,
    SKYBOX_LEFT,
    SKYBOX_RIGHT,
    SKYBOX_FRONT,
    SKYBOX_BACK,
    TILE_BORDER,
    WASSER,
    LAND_WUESTE,
    LAND_HOLZ,
    LAND_LEHM,
    LAND_WEIZEN,
    LAND_WOLLE,
    LAND_ERZ,
    HAFEN_3zu1,
    HAFEN_HOLZ,
    HAFEN_LEHM,
    HAFEN_WEIZEN,
    HAFEN_WOLLE,
    HAFEN_ERZ,
    CARD_UNKNOWN,
    CARD_HOLZ,
    CARD_LEHM,
    CARD_WEIZEN,
    CARD_WOLLE,
    CARD_ERZ,
    CHIP_HOLZ,
    CHIP_LEHM,
    CHIP_WEIZEN,
    CHIP_WOLLE,
    CHIP_ERZ,
    ROBBER,
    ROAD,
    SETTLEMENT = ROAD,
    CITY = ROAD,
    DICE_1,
    DICE_2,
    DICE_3,
    DICE_4,
    DICE_5,
    DICE_6,
    CHIP_2,
    CHIP_3,
    CHIP_4,
    CHIP_5,
    CHIP_6,
    //CHIP_7,
    CHIP_8,
    CHIP_9,
    CHIP_10,
    CHIP_11,
    CHIP_12,
    ICON_UNKNOWN = 400,
    ICON_PLAYER_1,
    ICON_PLAYER_2,
    ICON_PLAYER_3,
    ICON_PLAYER_4,
    EVTCARD_UNKNOWN,
    EVTCARD_KNIGHT,
    EVTCARD_VICTORY_POINT,
    EVTCARD_INVENTION,
    EVTCARD_FREE_BANK,
    BONUS_UNKNOWN,
    BONUS_LONGEST_ROAD,
    BONUS_BIGGEST_ARMY,
    BUY_EVENT_CARD,
    PLAN_BG,
    PLAN_STANDARD,
    COUNT
};

/*
inline bool addStandardTextures(
    std::map< eTexture, irr::video::ITexture* > & texMap,
    irr::video::IVideoDriver * driver,
    std::string const & mediaDir = "../../media/" )
{
    if ( !driver ) return false;

    auto addTexture = [ &driver, &texMap, &mediaDir ] ( eTexture type, std::string const & fileName ) -> void
    {
        std::string const tmp = mediaDir + fileName.c_str();

        texMap[ type ] = driver->getTexture( tmp.c_str() );

        if ( texMap[ type ] )
        {
            std::cout << "Loaded tex-file(" << tmp << ")\n";
        }
        else
        {
            std::cout << "Cannot load tex-file(" << tmp << ")\n";
        }
    };

    addTexture( eTexture::UNKNOWN, "unknown.jpg" );
    addTexture( eTexture::WASSER, "wasser.png" );
    addTexture( eTexture::LAND_WUESTE, "land_wueste.jpg" );
    addTexture( eTexture::LAND_HOLZ, "land_holz.png" );
    addTexture( eTexture::LAND_LEHM, "land_lehm.png" );
    addTexture( eTexture::LAND_WEIZEN, "land_weizen.jpg" );
    addTexture( eTexture::LAND_WOLLE, "land_wolle.jpg" );
    addTexture( eTexture::LAND_ERZ, "land_erz.jpg" );
    addTexture( eTexture::HAFEN_3zu1, "wasser.png" );
    addTexture( eTexture::HAFEN_HOLZ, "wasser.png" );
    addTexture( eTexture::HAFEN_LEHM, "wasser.png" );
    addTexture( eTexture::HAFEN_WEIZEN, "wasser.png" );
    addTexture( eTexture::HAFEN_WOLLE, "wasser.png" );
    addTexture( eTexture::HAFEN_ERZ, "wasser.png" );

    addTexture( eTexture::ROBBER, "unknown.png" );
    addTexture( eTexture::ROAD, "wasser.png" );

    addTexture( eTexture::DICE_1, "dice1.png" );
    addTexture( eTexture::DICE_2, "dice2.png" );
    addTexture( eTexture::DICE_3, "dice3.png" );
    addTexture( eTexture::DICE_4, "dice4.png" );
    addTexture( eTexture::DICE_5, "dice5.png" );
    addTexture( eTexture::DICE_6, "dice6.png" );

    addTexture( eTexture::CHIP_2, "chip02.png" );
    addTexture( eTexture::CHIP_3, "chip03.png" );
    addTexture( eTexture::CHIP_4, "chip04.png" );
    addTexture( eTexture::CHIP_5, "chip05.png" );
    addTexture( eTexture::CHIP_6, "chip06.png" );
    addTexture( eTexture::CHIP_8, "chip08.png" );
    addTexture( eTexture::CHIP_9, "chip09.png" );
    addTexture( eTexture::CHIP_10, "chip10.png" );
    addTexture( eTexture::CHIP_11, "chip11.png" );
    addTexture( eTexture::CHIP_12, "chip12.png" );

    // ICON_PLAYER_1,
    // ICON_PLAYER_2,
    // ICON_PLAYER_3,
    // ICON_PLAYER_4,
    // CARD_UNKNOWN,
    // CARD_HOLZ,
    // CARD_LEHM,
    // CARD_WEIZEN,
    // CARD_WOLLE,
    // CARD_ERZ,
    // EVTCARD_UNKNOWN,
    // EVTCARD_KNIGHT,
    // EVTCARD_VICTORY_POINT,
    // EVTCARD_INVENTION,
    // EVTCARD_FREE_BANK,
    // BONUS_UNKNOWN,
    // BONUS_LONGEST_ROAD,
    // BONUS_BIGGEST_ARMY,
    // BUY_EVENT_CARD,
    // PLAN_BG,
    // PLAN_STANDARD,
    // COUNT

}
*/

} // end namespace pioneers3d

/*

const char* const sStandardTextureNames[] =
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

*/

#endif // PIONEERS3D_E_TEXTURE_HPP
