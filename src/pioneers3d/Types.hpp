/// (c) 2017 - 2018 Benjamin Hampe <benjaminhampe@gmx.de>
/// All rights reserved, except the following natural persons:
/// Only free for Persian princesses that have a github account
/// and upgrade their PC (personal flying carpet) with a Raspberry Pi,
/// or people that speak AND live the words of Jesus Christ.

#ifndef PIONEERS3D_TYPES_HPP
#define PIONEERS3D_TYPES_HPP

#include <common/AlphaSonic.hpp>
#include <pioneers3d/eTexture.hpp>
#include <pioneers3d/eTileType.hpp>
#include <pioneers3d/eGameType.hpp>
#include <pioneers3d/eGameState.hpp>

namespace pioneers3d {

struct Board_t;
struct Waypoint_t;
struct Tile_t;
struct Player_t;

struct Waypoint_t
{
public:
    bool IsEnabled; // Can generate ressource cards ( no thief/robber )
    bool CanHaveOwner; // Can have an owner
    Player_t* Owner;
    int VictoryPoints;
    std::vector< Tile_t* > Neighbours; // Parents
};

struct Tile_t
{
public:
    glm::ivec2 					BoardIndex;
    glm::vec3                   Pos;
    eTileType 					TileType = eTileType::WASSER;
    int32_t 					DiceValue = 0;
    int32_t 					TexAngle60 = 0;
    std::vector< Waypoint_t* >  Waypoints;
};

struct Bank_t
{
    int Erz;			// Anzahl Erz
    int Holz;			// Anzahl Holz
    int Lehm;			// Anzahl Lehm
    int Weizen;			// Anzahl Weizen
    int Wolle;			// Anzahl Wolle

    int getTotalCardCount() const
    {
        return Erz + Holz + Lehm + Weizen + Wolle;
    }

    bool canRobberSteal() const
    {
        return getTotalCardCount() >= 7;
    }
};

struct Player_t
{
// ---------------------------------------------------------------------------------------
    int Id;                 // Player id
    int Type;				// Player type - 0=Human, 1=CPU, 2=HumanTCP/IP, 3=HumanLAN
    std::string Name;       // Player name
    uint32_t Color;			// Player color
    bool IsActive;			// sagt aus ob Player in der Runde aktiviert ist.
// ---------------------------------------------------------------------------------------
    short Dice1;			// Wuerfelwert
    short Dice2;			// Wuerfelwert
// ---------------------------------------------------------------------------------------
    Bank_t Bank;			// Ressource cards
// ---------------------------------------------------------------------------------------
    int HasVictoryPoints;	// Anzahl Siegpunkte
    int HasRoads;           // Anzahl Strassen
    int HasSettlements;     // Anzahl Siedlungen
    int HasCities;          // Anzahl Städte
    int HasKnightCards;		// Anzahl Ritterkarten
    int HasVictoryCards;    // Anzahl Siegpunktkarten
    int HasEventCards;      // Anzahl Ereigniskarten
// ---------------------------------------------------------------------------------------
    bool HasHafen3zu1;		// Has Player Hafen-3zu1
    bool HasHafenErz;		// Has Player Hafen-Erz
    bool HasHafenHolz;		// Has Player Hafen-Holz
    bool HasHafenLehm;		// Has Player Hafen-Lehm
    bool HasHafenWeizen;	// Has Player Hafen-Weizen
    bool HasHafenWolle;		// Has Player Hafen-Wolle
// ---------------------------------------------------------------------------------------
    bool HasBonusArmy;      // Rittermacht
    bool HasBonusTrade;     // Laengste Handelsroute
// ---------------------------------------------------------------------------------------
//	int IconId;				// Icon des Players 64x64
//	int IconBorder;         // Rahmen des Playericons 64x64
//	int icon_strasse;		// Icon Strasse
//	int icon_siedlung;		// Icon Siedlung
//	int icon_stadt;			// Icon Stadt
//	int tex_holz;			// Textur für Strassen, Siedlungen und Städte
};

struct Game_t
{
    eGameType 				Type;
    eGameState 				State;
    std::string             MediaDir;
    irr::IrrlichtDevice*    Device;
    irr::IEventReceiver*    Receiver;
    irr::video::SColor      ClearColor;

    // RessourcenManager_t
    //std::map< eTexture, irr::video::ITexture* > Textures;

    // Board_t
    glm::ivec2 TileCount;
    glm::vec3 TileSize;
    std::vector< Tile_t > Tiles;
    std::vector< Waypoint_t > Waypoints;
    // PlayerList_t
    std::vector< Player_t > Players;
    uint32_t 				CurrentPlayer;
};


} // end namespace pioneers3d

#endif // PIONEERS3D_TYPES_HPP
