/// (c) 2017 - 2018 Benjamin Hampe <benjaminhampe@gmx.de>
/// All rights reserved, except the following natural persons:
/// Only free for Persian princesses that have a github account
/// and upgrade their PC (personal flying carpet) with a Raspberry Pi,
/// or people that speak AND live the words of Jesus Christ.

#ifndef PIONEERS3D_E_TEXTURE_HPP
#define PIONEERS3D_E_TEXTURE_HPP

#include <common/AlphaSonic.hpp>

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
    DICE_1,
    DICE_2,
    DICE_3,
    DICE_4,
    DICE_5,
    DICE_6,
    CHIP_W,
    CHIP_S,
    CHIP_HOLZ,
    CHIP_LEHM,
    CHIP_WEIZEN,
    CHIP_WOLLE,
    CHIP_ERZ,
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
    TILE_WASSER,
    TILE_WUESTE,
    TILE_HOLZ,
    TILE_LEHM,
    TILE_WEIZEN,
    TILE_WOLLE,
    TILE_ERZ,
    PLAYER_ICON,
    PLAYER_ICON_1,
    PLAYER_ICON_2,
    PLAYER_ICON_3,
    PLAYER_ICON_4,
    PLAYER_HOLZ,
    PLAYER_LEHM,
    PLAYER_WEIZEN,
    PLAYER_WOLLE,
    PLAYER_ERZ,
    PLAYER_ROAD,
    PLAYER_SETTLEMENT,
    PLAYER_CITY,
    PLAYER_EVENT_CARD,
    PLAYER_KNIGHT_CARD,
    PLAYER_POINT_CARD,
    PLAYER_BONUS_UNKNOWN,
    PLAYER_BONUS_LONGEST_ROAD,
    PLAYER_BONUS_BIGGEST_ARMY,
    PLAYER_ACTION_DICE,
    PLAYER_ACTION_ENDTURN,
    PLAYER_ACTION_TRADE,
    PLAYER_ACTION_BANK,
    PLAYER_ACTION_BUY_EVENT_CARD,
    PLAYER_ACTION_PLAY_EVENT_CARD,
    PLAYER_ACTION_BUY_ROAD,
    PLAYER_ACTION_BUY_SETTLEMENT,
    PLAYER_ACTION_BUY_CITY,
    TEX_ROBBER,
    TEX_TILE_BORDER,
    TEX_ROAD,
    TEX_SETTLEMENT = TEX_ROAD,
    TEX_CITY = TEX_ROAD,
    BUY_EVENT_CARD,
    PLAN_BG,
    PLAN_STANDARD,
    COUNT
};


} // end namespace pioneers3d

#endif // PIONEERS3D_E_TEXTURE_HPP
