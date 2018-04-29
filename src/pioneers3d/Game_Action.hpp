#ifndef GAME_ACTION_HPP
#define GAME_ACTION_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

void Action_Abort( Game_t* game );

void Action_Dice( Game_t* game );
void Action_Bank( Game_t* game );
void Action_Trade( Game_t* game );
void Action_BuyEventCard( Game_t* game );
void Action_BuyRoad( Game_t* game );
void Action_BuySettlement( Game_t* game );
void Action_BuyCity( Game_t* game );
void Action_EndTurn( Game_t* game );

void Action_PlayEventCard( Game_t* game );

void Action_PlaceRobber( Game_t* game );
void Action_PlaceRoad( Game_t* game );
void Action_PlaceSettlement( Game_t* game );
void Action_PlaceCity( Game_t* game );

void Action_Win( Game_t* game );

/*
uint32_t Player_getActionMask( Game_t* game, uint32_t player );
uint32_t Player_setActionMask( Game_t* game, uint32_t player, uint32_t actionMask );
*/

} // end namespace pioneers3d

#endif // GAME_ACTION_HPP
