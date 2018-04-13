#ifndef GAME_PLAYERS_HPP
#define GAME_PLAYERS_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

void Players_clear( Game_t* game );
void Players_create( Game_t* game ); // create 4 standard players
bool Player_isValidIndex( Game_t* game, int32_t playerIndex );
int32_t Player_getCount( Game_t* game );
int32_t Player_getCurrentIndex( Game_t* game );
Player_t* Player_getCurrentData( Game_t* game );
Player_t* Player_getData( Game_t* game, int32_t player );
uint32_t Player_getColor( Game_t* game, int32_t player );

} // end namespace pioneers3d

#endif // GAME_PLAYERS_HPP
