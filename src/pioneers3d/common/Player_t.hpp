#ifndef GAME_PLAYERS_HPP
#define GAME_PLAYERS_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

// ---------------------------------------------------------------------------------------
struct Player_t
{
    int                     Id = -1;                 // Player id
    int                     Type = 0;				// Player type - 0=Human, 1=CPU, 2=HumanTCP/IP, 3=HumanLAN
    std::string             Name = "Player";       // Player name
    uint32_t                Color = 0xFFFFFFFF;			// Player color
    irr::video::ITexture*   Avatar = nullptr;
    eAction                 Action = eAction::UNKNOWN;
    bool                    IsActive = true;			// sagt aus ob Player in der Runde aktiviert ist.
    Bank_t                  Bank;			// Ressource cards
    int                     NumPoints = 0;      // Anzahl Siegpunkte
    int                     NumRoads = 0;              // Anzahl Strassen
    int NumSettlements = 0;     // Anzahl Siedlungen
    int NumCities = 0;          // Anzahl Städte
    int NumEventCards = 0;      // Anzahl Ereigniskarten
    int NumKnightCards = 0;		// Anzahl Ritterkarten
    int NumVictoryCards = 0;    // Anzahl Siegpunktkarten
    bool HasHafen3zu1 = false;		// Has Player Hafen-3zu1
    bool HasHafenErz = false;		// Has Player Hafen-Erz
    bool HasHafenHolz = false;		// Has Player Hafen-Holz
    bool HasHafenLehm = false;		// Has Player Hafen-Lehm
    bool HasHafenWeizen = false;	// Has Player Hafen-Weizen
    bool HasHafenWolle = false;		// Has Player Hafen-Wolle
    bool HasBonusArmy = false;      // Rittermacht
    bool HasBonusTrade = false;     // Laengste Handelsroute

    std::vector< Waypoint_t* > Waypoints; // Waypoints we own
    std::vector< Tile_t* > Tiles;       // Tiles we own, maybe use connection
    std::vector< AutoSceneNode* > Roads;       // Tiles we own, maybe use connection
    // ---------------------------------------------------------------------------------------

    //	int IconId;				// Icon des Players 64x64
    //	int IconBorder;         // Rahmen des Playericons 64x64
    //	int icon_strasse;		// Icon Strasse
    //	int icon_siedlung;		// Icon Siedlung
    //	int icon_stadt;			// Icon Stadt
    //	int tex_holz;			// Textur für Strassen, Siedlungen und Städte
};
// =============================================================================================

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
