#ifndef UI_PLAYER_HPP
#define UI_PLAYER_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

void GameUI_createPlayerAction( Game_t * game, irr::core::recti const & pos );
void GameUI_createPlayerInfo( Game_t * game, irr::core::recti const & pos );

void GameUI_updatePlayerAction( Game_t * game );
} // end namespace pioneers3d

#endif // UI_PLAYER_HPP
