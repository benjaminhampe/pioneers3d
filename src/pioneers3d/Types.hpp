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

struct RoadPoint_t;
struct Waypoint_t;
struct Tile_t;
//struct Board_t;
struct Bank_t;
struct Player_t;

struct RoadPoint_t
{
public:
    glm::vec3 Pos;
    bool IsEnabled = true; // Can generate ressource cards ( no thief/robber )
    Player_t* Owner = nullptr;
    std::vector< Tile_t* > Tiles; // collect neighbouring tiles 1-1
};

struct Waypoint_t
{
public:
    glm::vec3               Pos;
    int                     Points; // default: 0
    bool                    IsEnabled = true; // Can generate ressource cards ( no thief/robber )
    bool                    IsRoad = false; // Default: false == can settle, true == only a road
    Player_t*               Owner = nullptr;
    std::vector< Tile_t* >  Tiles; // collect neighbouring tiles 1-3
    AutoSceneNode*          Node = nullptr;
    //~Waypoint_t() { if (Node) Node->drop(); }
};

struct Tile_t
{
public:
    eTileType 					Type = eTileType::WASSER;
    glm::ivec2 					BoardIndex;
    glm::vec3                   Pos;
    glm::vec3                   Size;
    int32_t 					DiceValue = 0;
    int32_t 					TexAngle60 = 0;
    std::vector< RoadPoint_t* > RoadPoints;
    std::vector< Waypoint_t* >  Waypoints;
    AutoSceneNode*              Node = nullptr;
    //~Tile_t() { if (Node) Node->drop(); }
};

struct Raueber_t
{
    glm::ivec2 					BoardIndex;
    glm::vec3                   Pos;
    irr::scene::ISceneNode*     Node = nullptr;
    //~Raueber_t() { if (Node) Node->drop(); }
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

    std::string toString() const;
};

struct Player_t
{
// ---------------------------------------------------------------------------------------
    int Id;                 // Player id
    int Type;				// Player type - 0=Human, 1=CPU, 2=HumanTCP/IP, 3=HumanLAN
    std::string Name;       // Player name
    uint32_t Color;			// Player color
    irr::video::ITexture*   Avatar = nullptr;
    bool IsActive;			// sagt aus ob Player in der Runde aktiviert ist.
// ---------------------------------------------------------------------------------------
    short Dice1;			// Wuerfelwert
    short Dice2;			// Wuerfelwert
    Bank_t Bank;			// Ressource cards
    int VictoryPoints;      // Anzahl Siegpunkte
    int Roads;              // Anzahl Strassen
    int Settlements;     // Anzahl Siedlungen
    int Cities;          // Anzahl Städte
    int KnightCards;		// Anzahl Ritterkarten
    int VictoryCards;    // Anzahl Siegpunktkarten
    int EventCards;      // Anzahl Ereigniskarten
    bool HasHafen3zu1;		// Has Player Hafen-3zu1
    bool HasHafenErz;		// Has Player Hafen-Erz
    bool HasHafenHolz;		// Has Player Hafen-Holz
    bool HasHafenLehm;		// Has Player Hafen-Lehm
    bool HasHafenWeizen;	// Has Player Hafen-Weizen
    bool HasHafenWolle;		// Has Player Hafen-Wolle
    bool HasBonusArmy;      // Rittermacht
    bool HasBonusTrade;     // Laengste Handelsroute
// ---------------------------------------------------------------------------------------
//	int IconId;				// Icon des Players 64x64
//	int IconBorder;         // Rahmen des Playericons 64x64
//	int icon_strasse;		// Icon Strasse
//	int icon_siedlung;		// Icon Siedlung
//	int icon_stadt;			// Icon Stadt
//	int tex_holz;			// Textur für Strassen, Siedlungen und Städte
    std::vector< Waypoint_t* > Waypoints; // Waypoints we own
    //std::vector< Tile_t* > Tiles; // Tiles
    std::string toString() const;
};


struct GUI_Menu_t
{
    irr::gui::IGUIWindow* Window = nullptr;
    irr::gui::IGUIButton* Start = nullptr;
    irr::gui::IGUIButton* Options = nullptr;
    irr::gui::IGUIButton* Exit = nullptr;
};

struct GUI_Card_t
{
    irr::gui::IGUIStaticText* Name = nullptr;
    irr::gui::IGUIImage* Image = nullptr;
    irr::gui::IGUIStaticText* Value = nullptr;
};

struct GUI_PlayerAction_t
{
    irr::gui::IGUIWindow* Window = nullptr;
    irr::gui::IGUIButton* Dice = nullptr;
    irr::gui::IGUIButton* Bank = nullptr;
    irr::gui::IGUIButton* Trade = nullptr;
    irr::gui::IGUIButton* BuyCard = nullptr;
    irr::gui::IGUIButton* BuyRoad = nullptr;
    irr::gui::IGUIButton* BuySett = nullptr;
    irr::gui::IGUIButton* BuyCity = nullptr;
    irr::gui::IGUIButton* EndRound = nullptr;
};

struct GUI_PlayerInfo_t
{
    irr::gui::IGUIWindow* Window = nullptr;
    irr::gui::IGUIStaticText* Name = nullptr;
    irr::gui::IGUIImage* Avatar = nullptr;

    GUI_Card_t Holz;
    GUI_Card_t Lehm;
    GUI_Card_t Weizen;
    GUI_Card_t Wolle;
    GUI_Card_t Erz;

    GUI_Card_t Roads;
    GUI_Card_t Settlements;
    GUI_Card_t Cities;

    GUI_Card_t EventCards;
    GUI_Card_t KnightCards;
    GUI_Card_t PointCards;
    //GUI_Card_t EventCards;
    GUI_Card_t BonusLongestRoad;
    GUI_Card_t BonusBiggestArmy;
    irr::gui::IGUIStaticText* LogBox = nullptr;
};

struct GUI_ChatBox_t
{
    irr::gui::IGUIWindow* Window = nullptr;
    irr::gui::IGUIEditBox* Input = nullptr;
    irr::gui::IGUIButton* Send = nullptr;
    irr::gui::IGUIListBox* LogBox = nullptr;
};

struct GUI_Dice_t
{
    irr::gui::IGUIWindow* Window = nullptr;
    irr::gui::IGUIButton* A = nullptr;
    irr::gui::IGUIButton* B = nullptr;
};

struct GameUI_t
{
    GUI_Menu_t          MainMenu;
    GUI_PlayerAction_t  PlayerAction;
    GUI_PlayerInfo_t    PlayerInfo;
    GUI_ChatBox_t       Chat;
    GUI_Dice_t          Dice;
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

    // Player_t
    std::vector< Player_t > Players;
    uint32_t 				CurrentPlayer;
    Raueber_t               Raeuber;
    GameUI_t                UI;
};


} // end namespace pioneers3d

#endif // PIONEERS3D_TYPES_HPP
