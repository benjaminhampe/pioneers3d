/// (c) 2017 - 2018 Benjamin Hampe <benjaminhampe@gmx.de>
/// All rights reserved, except the following natural persons:
/// Only free for Persian princesses that have a github account
/// and upgrade their PC (personal flying carpet) with a Raspberry Pi,
/// or people that speak AND live the words of Jesus Christ.

#ifndef PIONEERS3D_E_GAME_STATE_HPP
#define PIONEERS3D_E_GAME_STATE_HPP

#include <common/Types.hpp>

namespace pioneers3d {

enum class eGameState : uint32_t
{
    IDLE = 0,
    GAME_MENU,
    GAME_INIT_PLAYER,
    GAME_INIT_BOARD,
    GAME_DICE,
    GAME_PLACE_ROBBER,
    GAME_PLACE_FIRST_ROAD,
    GAME_PLACE_FIRST_SETTLEMENT,
    GAME_PLACE_SECOND_ROAD,
    GAME_PLACE_SECOND_SETTLEMENT,
    GAME_LOOP,
    GAME_END,
    PLAYER_1,
    PLAYER_2,
    PLAYER_3,
    PLAYER_4,
    COUNT
};

} // end namespace pioneers3d

#endif // PIONEERS3D_E_GAMESTATE_HPP
