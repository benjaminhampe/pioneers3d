// ---------------------------------------------------------------------------------------
#ifndef PIONEERS3D_TYPES_HPP
#define PIONEERS3D_TYPES_HPP
// ---------------------------------------------------------------------------------------
#include <common/AlphaSonic.hpp>
#include <pioneers3d/eAction.hpp>
#include <pioneers3d/eGameType.hpp>
#include <pioneers3d/eGameState.hpp>
#include <pioneers3d/eTexture.hpp>
#include <pioneers3d/eTileType.hpp>
// ---------------------------------------------------------------------------------------
namespace pioneers3d {
// ---------------------------------------------------------------------------------------
struct Dice_t;
struct RoadPoint_t;
struct Waypoint_t;
struct Tile_t;
//struct Board_t;
struct Bank_t;
struct Player_t;
// ---------------------------------------------------------------------------------------
enum class eFontType : uint32_t
{
    DEFAULT = 0,
    CHAT_BG,
    CHAT,
    AWESOME,
    FPS_COUNTER,
    H1,
    H2,
    H3,
    SMALL,
};
// ---------------------------------------------------------------------------------------
struct Font_t
{
    eFontType Type;
    std::string FileName;
    int32_t Size;
    int32_t Style;
    irr::gui::CGUITTFont* Font;
};

typedef std::vector< Font_t > Fonts_t;

// ---------------------------------------------------------------------------------------
struct Dice_t
{
    int32_t A;
    int32_t B;
    Dice_t() : A(1), B(1) { srand( static_cast< uint32_t >( time( nullptr ) ) ); }
    void randomizeA() { A = rand()%6 + 1; }
    void randomizeB() { B = rand()%6 + 1; }
    void randomize() { randomizeA(); randomizeB(); }
    int32_t sum() const { return A + B; }
    int32_t max() const { return std::max(A,B); }
    int32_t min() const { return std::min(A,B); }
};

// ---------------------------------------------------------------------------------------
struct RoadPoint_t
{
public:
    glm::vec3 Pos;
    bool IsEnabled = true; // Can generate ressource cards ( no thief/robber )
    Player_t* Owner = nullptr;
    std::vector< Tile_t* > Tiles; // collect neighbouring tiles 1-1
};
// ---------------------------------------------------------------------------------------
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
// ---------------------------------------------------------------------------------------
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
    irr::scene::ITriangleSelector* TriangleSelector = nullptr;

    //~Tile_t() { if (Node) Node->drop(); }
};
// ---------------------------------------------------------------------------------------
struct Raueber_t
{
    glm::ivec2 					BoardIndex;
    glm::vec3                   Pos;
    irr::scene::ISceneNode*     Node = nullptr;
    //~Raueber_t() { if (Node) Node->drop(); }
};
// ---------------------------------------------------------------------------------------
struct Bank_t
{
    int Erz;			// Anzahl Erz
    int Holz;			// Anzahl Holz
    int Lehm;			// Anzahl Lehm
    int Weizen;			// Anzahl Weizen
    int Wolle;			// Anzahl Wolle
    std::string Name;
};
// ---------------------------------------------------------------------------------------
struct Player_t
{
    int Id;                 // Player id
    int Type;				// Player type - 0=Human, 1=CPU, 2=HumanTCP/IP, 3=HumanLAN
    std::string Name;       // Player name
    uint32_t Color;			// Player color
    irr::video::ITexture*   Avatar = nullptr;
    eAction                 Action = eAction::UNKNOWN;
    bool IsActive = false;			// sagt aus ob Player in der Runde aktiviert ist.
    short Dice1 = 0;			// Wuerfelwert
    short Dice2 = 0;			// Wuerfelwert
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

    std::vector< Waypoint_t* > Waypoints; // Waypoints we own

    std::vector< Tile_t* > Tiles;       // Tiles we own, maybe use connection

    // ---------------------------------------------------------------------------------------

    //	int IconId;				// Icon des Players 64x64
    //	int IconBorder;         // Rahmen des Playericons 64x64
    //	int icon_strasse;		// Icon Strasse
    //	int icon_siedlung;		// Icon Siedlung
    //	int icon_stadt;			// Icon Stadt
    //	int tex_holz;			// Textur für Strassen, Siedlungen und Städte
};
// =============================================================================================

struct GUI_Menu_t
{
    BaseWindow* Window = nullptr;
    irr::gui::IGUIButton* Start = nullptr;
    irr::gui::IGUIButton* Options = nullptr;
    irr::gui::IGUIButton* Exit = nullptr;
};

class GUI_Card_t : public irr::gui::IGUIElement
{
public:
    GUI_Card_t( irr::gui::IGUIEnvironment* env,
            irr::gui::IGUIElement* parent,
            int id,
            irr::core::recti const & pos );

    virtual ~GUI_Card_t();

    virtual void draw() override;

    void setTitle( Text_t&& title ) { m_Title = std::move( title ); }
    void setValue( Text_t&& value ) { m_Value = std::move( value ); }
    void setTexture( irr::video::ITexture* tex ) { m_Tex = tex; }
public:
    Text_t m_Title;
    Text_t m_Value;
    irr::video::ITexture* m_Tex;
};

struct GUI_Bank_t
{
    BaseWindow * Window = nullptr;
    GUI_Card_t * Holz;
    GUI_Card_t * Lehm;
    GUI_Card_t * Weizen;
    GUI_Card_t * Wolle;
    GUI_Card_t * Erz;
};

struct GUI_Action_t
{
    BaseWindow* Window = nullptr;
    irr::gui::IGUIButton* Dice = nullptr;
    irr::gui::IGUIButton* Bank = nullptr;
    irr::gui::IGUIButton* Trade = nullptr;
    irr::gui::IGUIButton* PlayCard = nullptr;
    irr::gui::IGUIButton* BuyCard = nullptr;
    irr::gui::IGUIButton* BuyRoad = nullptr;
    irr::gui::IGUIButton* BuySett = nullptr;
    irr::gui::IGUIButton* BuyCity = nullptr;
    irr::gui::IGUIButton* PlaceRobber = nullptr;
    irr::gui::IGUIButton* PlaceRoad = nullptr;
    irr::gui::IGUIButton* PlaceSett = nullptr;
    irr::gui::IGUIButton* PlaceCity = nullptr;
    irr::gui::IGUIButton* EndRound = nullptr;
};

struct GUI_Player_t
{
    BaseWindow* Window = nullptr;
    irr::gui::IGUIStaticText* Name = nullptr;
    irr::gui::IGUIImage* Avatar = nullptr;
    GUI_Card_t * Roads;
    GUI_Card_t * Settlements;
    GUI_Card_t * Cities;
    // Bank for ressource cards
    GUI_Card_t * Holz;
    GUI_Card_t * Lehm;
    GUI_Card_t * Weizen;
    GUI_Card_t * Wolle;
    GUI_Card_t * Erz;
    // Bonus and Addons
    GUI_Card_t * EventCards;
    GUI_Card_t * KnightCards;
    GUI_Card_t * PointCards;
    GUI_Card_t * BonusRoad;
    GUI_Card_t * BonusArmy;
    // A lotbox
    irr::gui::IGUIStaticText* LogBox = nullptr;
};

struct GUI_ChatBox_t
{
    BaseWindow* Window = nullptr;
    irr::gui::IGUIEditBox* Input = nullptr;
    irr::gui::IGUIButton* Send = nullptr;
    irr::gui::IGUIListBox* LogBox = nullptr;
};

struct GUI_Dice_t
{
    BaseWindow* Window = nullptr;
    irr::gui::IGUIButton* A = nullptr;
    irr::gui::IGUIButton* B = nullptr;
};


struct GameUI_t
{
    GUI_Menu_t          Menu;
    GUI_Bank_t          Bank;
    GUI_Action_t        Action;
    GUI_Player_t        Player;
    GUI_ChatBox_t       Chat;
    GUI_Dice_t          Dice;

    std::vector< irr::gui::IGUIWindow* > Windows;
};

struct Game_t
{
    std::string             MediaDir;
    irr::IrrlichtDevice*    Device = nullptr;
    irr::IEventReceiver*    Receiver = nullptr;
    irr::video::SColor      ClearColor;
    // game stats
    uint32_t                RoundCounter = 0;
    Bank_t                  RessourceCounter;
    void*                   Chat;

    irr::scene::ISceneNode* HitSceneNode = nullptr;
    irr::scene::ISceneNode* HitSceneNodeLast = nullptr;

    std::string             FontFileName;
    Fonts_t                 Fonts;
    eGameType 				Type;
    eGameState 				State;
    eAction                 Action;
    Dice_t                  Dice;
    glm::ivec2              TileCount;
    glm::vec3               TileSize;
    std::vector< Tile_t >   Tiles;
    irr::scene::IMetaTriangleSelector* TileSelector = nullptr;
    std::vector< Waypoint_t > Waypoints;
    irr::scene::IMetaTriangleSelector* WaypointSelector = nullptr;
    std::vector< Player_t > Players;
    int32_t 				Player = -1;
    Raueber_t               Raeuber;

    GameUI_t                UI;
};


} // end namespace pioneers3d

#endif // PIONEERS3D_TYPES_HPP
