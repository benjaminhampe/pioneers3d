#ifndef GAME_PLAYERS_HPP
#define GAME_PLAYERS_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

void        clearPlayers( Game_t* game );
void        createStandardPlayers( Game_t* game ); // create 4 standard players

uint32_t    getPlayerCount( Game_t* game );
bool        isPlayer( Game_t* game, uint32_t playerIndex );
Player_t*   getPlayer( Game_t* game, uint32_t playerIndex );
uint32_t    Player_getColor( Game_t* game, uint32_t playerIndex );
std::string Player_getName( Game_t* game, uint32_t playerIndex );
eAction     Player_getAction( Game_t* game, uint32_t playerIndex );
void        Player_setAction( Game_t* game, uint32_t playerIndex, eAction action );
bool        Player_isActionEnabled( Game_t* game, uint32_t playerIndex, eAction action );
void        Player_setActionEnabled( Game_t* game, uint32_t playerIndex, eAction action, bool enable );
void        Player_toggleAction( Game_t* game, uint32_t playerIndex, eAction action );

////// Current Player helper
inline Player_t*    getPlayer( Game_t* game )           { return getPlayer( game, game->Player ); }
inline uint32_t     Player_getColor( Game_t* game )     { return Player_getColor( game, game->Player ); }
inline std::string  Player_getName( Game_t* game )      { return Player_getName( game, game->Player ); }
inline eAction      Player_getAction( Game_t* game )    { return Player_getAction( game, game->Player ); }
inline bool         Player_isActionEnabled( Game_t* game, eAction action ) { return Player_isActionEnabled( game, game->Player, action ); }
inline void         Player_setAction( Game_t* game, eAction action ) { Player_setAction( game, game->Player, action ); }
inline void         Player_setActionEnabled( Game_t* game, eAction action, bool enable ) { Player_setActionEnabled( game, game->Player, action, enable ); }
inline void         Player_toggleAction( Game_t* game, eAction action ) { Player_toggleAction( game, game->Player, action ); }

void Player_addRoad( Game_t* game, Waypoint_t* anchor );
void Player_addSettlement( Game_t* game, Waypoint_t* anchor );
void Player_addCity( Game_t* game, Waypoint_t* anchor );

uint32_t Player_getNumRoads( Game_t* game );
uint32_t Player_getNumSettlements( Game_t* game );
uint32_t Player_getNumCities( Game_t* game );
uint32_t Player_getNumRessource( Game_t* game, eTileType resType );

inline uint32_t Player_getNumHolz( Game_t* game ) { return Player_getNumRessource( game, eTileType::HOLZ ); }
inline uint32_t Player_getNumLehm( Game_t* game ) { return Player_getNumRessource( game, eTileType::LEHM ); }
inline uint32_t Player_getNumWeizen( Game_t* game ) { return Player_getNumRessource( game, eTileType::WEIZEN ); }
inline uint32_t Player_getNumWolle( Game_t* game ) { return Player_getNumRessource( game, eTileType::WOLLE ); }
inline uint32_t Player_getNumErz( Game_t* game ) { return Player_getNumRessource( game, eTileType::ERZ ); }


} // end namespace pioneers3d

#endif // GAME_PLAYERS_HPP
