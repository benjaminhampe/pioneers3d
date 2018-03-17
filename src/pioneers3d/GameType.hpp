#ifndef PIONEERS3D_GAME_TYPE_HPP
#define PIONEERS3D_GAME_TYPE_HPP

#include <stdint.h>

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
	COUNT,
	// FORCE32BIT = 0xffffffff
};

enum class eGameType : uint32_t
{
	GT_STANDARD = 0,
	GT_EXT_FISHER = 1,
	GT_EXT_PIRATES = 2,
	GT_EXT_THIEFS = 4,
	GT_EXT_CARDS = 8,
	// GT_FORCE32BIT = 0xffffffff
};

} // end namespace pioneers3d

#endif // PIONEERS3D_GAME_TYPE_HPP
