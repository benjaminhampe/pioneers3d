#ifndef GAME_PLAYERS_HPP
#define GAME_PLAYERS_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

int32_t getCurrentPlayer( Game_t* game );

eAction     getPlayerAction( Game_t* game, int32_t playerIndex );
void        setPlayerAction( Game_t* game, int32_t playerIndex, eAction action );

bool        isPlayerActionEnabled( Game_t* game, int32_t playerIndex, eAction action );
void        setPlayerActionEnabled( Game_t* game, int32_t playerIndex, eAction action, bool enable );
void        togglePlayerAction( Game_t* game, int32_t playerIndex, eAction action );

void        clearPlayers( Game_t* game );
void        createStandardPlayers( Game_t* game ); // create 4 standard players
bool        isPlayer( Game_t* game, int32_t playerIndex );
int32_t     getPlayerCount( Game_t* game );
Player_t*   getPlayer( Game_t* game, int32_t player );
uint32_t    getPlayerColor( Game_t* game, int32_t player );
std::string getPlayerName( Game_t* game, int32_t playerIndex );

} // end namespace pioneers3d

#endif // GAME_PLAYERS_HPP
