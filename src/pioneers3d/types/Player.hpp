/// (c) 2017 - 20190 Benjamin Hampe <benjaminhampe@gmx.de>

#ifndef PIONEERS3D_TYPES_PLAYER_HPP
#define PIONEERS3D_TYPES_PLAYER_HPP

#include <pioneers3d/types/Common.hpp>
#include <pioneers3d/types/Action.hpp>
#include <pioneers3d/types/TileType.hpp>
#include <pioneers3d/types/Bank.hpp>

namespace pioneers3d {

class Waypoint_t;
class Tile_t;
class Game_t;

class Player_t
{
public:
   int32_t Id = -1;   // Player id
   uint32_t Color = 0xFFFFFFFF;         // Player color
   uint8_t Type = 0;               // Player type - 0=Human, 1=CPU, 2=HumanTCP/IP, 3=HumanLAN
   bool IsActive = true;            // sagt aus ob Player in der Runde aktiviert ist.
   std::string Name = "Player";       // Player name
   irr::video::ITexture* Avatar = nullptr;
   eAction Action = eAction::UNKNOWN;
   Bank_t Bank;              // Ressource cards
   uint32_t NumPoints = 0;        // Anzahl Siegpunkte
   uint32_t NumRoads = 0;         // Anzahl Strassen
   uint32_t NumSettlements = 0;   // Anzahl Siedlungen
   uint32_t NumCities = 0;        // Anzahl Städte
   uint32_t NumHafen3zu1 = 0;     // Anzahl Hafen
   uint32_t NumHafenErz = 0;     // Anzahl Hafen
   uint32_t NumHafenHolz = 0;     // Anzahl Hafen
   uint32_t NumHafenLehm = 0;     // Anzahl Hafen
   uint32_t NumHafenWolle = 0;     // Anzahl Hafen
   uint32_t NumHafenWeizen = 0;     // Anzahl Hafen
   uint32_t NumEventCards = 0;    // Anzahl Ereigniskarten
   uint32_t NumKnightCards = 0;   // Anzahl Ritterkarten
   uint32_t NumVictoryCards = 0;  // Anzahl Siegpunktkarten
   uint32_t NumLongestRoute = 0;  // Anzahl Siegpunktkarten
   bool HasBonusArmy = false;      // Rittermacht
   bool HasBonusTrade = false;     // Laengste Handelsroute

   std::vector< Waypoint_t* > Waypoints; // Waypoints we own
   std::vector< Tile_t* > Tiles;       // Tiles we own, maybe use connection
   std::vector< AutoSceneNode* > Roads;       // Tiles we own, maybe use connection
   // ---------------------------------------------------------------------------------------

   //  int IconId;             // Icon des Players 64x64
   //  int IconBorder;         // Rahmen des Playericons 64x64
   //  int icon_strasse;       // Icon Strasse
   //  int icon_siedlung;      // Icon Siedlung
   //  int icon_stadt;         // Icon Stadt
   //  int tex_holz;           // Textur für Strassen, Siedlungen und Städte
   //
   std::string toString() const;
};

// =======================================================
// === Game logic
// =======================================================
void createStandardPlayers( Game_t* game ); // create 4 standard players
void addStandardPlayer( Game_t* game, int id, std::string const & name, uint32_t color );
void clearPlayers( Game_t* game );
int32_t getPlayerCount( Game_t* game );
Player_t* getPlayer( Game_t* game, int32_t playerIndex ); // get a player by index
Player_t* getPlayer( Game_t* game ); // get current player

// =======================================================
// === Quick helpers -> use current player
// =======================================================

inline uint32_t Player_getColor( Game_t* game ) { return getPlayer( game )->Color; }
inline std::string Player_getName( Game_t* game ) { return getPlayer( game )->Name; }
inline eAction Player_getAction( Game_t* game ) { return getPlayer( game )->Action; }
inline bool Player_isActionEnabled( Game_t* game, eAction action ) { return getPlayer( game )->Action.isEnabled( action ); }
inline void Player_setAction( Game_t* game, eAction action ) { getPlayer( game )->Action = action; }
inline void Player_setActionEnabled( Game_t* game, eAction action, bool enable ) { getPlayer( game )->Action.setEnabled( action, enable ); }
//inline void Player_toggleAction( Game_t* game, Action action ) { getPlayer( game )->Action.toggleAction( action ); }
inline uint32_t Player_getNumRoads( Game_t* game ) { return getPlayer( game )->NumRoads; }
inline uint32_t Player_getNumSettlements( Game_t* game ) { return getPlayer( game )->NumSettlements; }
inline uint32_t Player_getNumCities( Game_t* game ) { return getPlayer( game )->NumCities; }
inline uint32_t Player_getNumRessource( Game_t* game, TileType resType ) { return getPlayer( game )->Bank.get( resType ); }
inline uint32_t Player_getNumHolz( Game_t* game ) { return Player_getNumRessource( game, TileType::HOLZ ); }
inline uint32_t Player_getNumLehm( Game_t* game ) { return Player_getNumRessource( game, TileType::LEHM ); }
inline uint32_t Player_getNumWeizen( Game_t* game ) { return Player_getNumRessource( game, TileType::WEIZEN ); }
inline uint32_t Player_getNumWolle( Game_t* game ) { return Player_getNumRessource( game, TileType::WOLLE ); }
inline uint32_t Player_getNumErz( Game_t* game ) { return Player_getNumRessource( game, TileType::ERZ ); }

void Player_addRoad( Game_t* game, Waypoint_t* anchor );
void Player_addSettlement( Game_t* game, Waypoint_t* anchor );
void Player_addCity( Game_t* game, Waypoint_t* anchor );

// =======================================================
// === Uses player index
// =======================================================

inline bool
isPlayer( Game_t* game, int32_t playerIndex )
{
    return ( getPlayer( game, playerIndex ) != nullptr );
}

inline uint32_t
Player_getColor( Game_t* game, uint32_t playerIndex )
{
   Player_t* player = getPlayer( game, playerIndex );
   if ( !player ) { return 0xFFFFFFFF; }
   return player->Color;
}

inline std::string
Player_getName( Game_t* game, uint32_t playerIndex )
{
   Player_t* player = getPlayer( game, playerIndex );
   if ( !player ) { return "nullptr"; }
   return player->Name;
}

inline eAction
Player_getAction( Game_t* game, uint32_t playerIndex )
{
   Player_t* player = getPlayer( game, playerIndex );
   if ( !player ) { return eAction::UNKNOWN; }
   return player->Action;
}

inline void
Player_setAction( Game_t* game, uint32_t playerIndex, eAction action )
{
   Player_t* player = getPlayer( game, playerIndex );
   if ( !player ) { return; }
   player->Action = action;
}

inline bool
Player_isActionEnabled( Game_t* game, uint32_t playerIndex, eAction action )
{
   Player_t* player = getPlayer( game, playerIndex );
   if ( !player ) { return false; }
   return player->Action.isEnabled( action );
}

inline void
Player_setActionEnabled( Game_t* game, uint32_t playerIndex, eAction action, bool enabled )
{
   Player_t* player = getPlayer( game, playerIndex );
   if ( !player ) { return; }
   player->Action.setEnabled( action, enabled );
}

inline void
Player_toggleAction( Game_t* game, uint32_t playerIndex, eAction action )
{
   Player_t* player = getPlayer( game, playerIndex );
   if ( !player ) { return; }
   player->Action.toggle( action );
}

/*
uint32_t Player_getActionMask( Game_t* game, uint32_t player );
uint32_t Player_setActionMask( Game_t* game, uint32_t player, uint32_t actionMask );
*/

} // end namespace pioneers3d

#endif // PIONEERS3D_TYPES_PLAYER_HPP
