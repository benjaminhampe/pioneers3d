#ifndef UI_PLAYER_HPP
#define UI_PLAYER_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

void PlayerUI_create( Game_t * game, irr::core::recti const & pos );
void PlayerUI_update( Game_t * game );

} // end namespace pioneers3d

#endif // UI_PLAYER_HPP
