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
struct Road_t
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
    bool                    IsRoad = false; // Default: false == can settle, true == only a road
    bool                    IsEnabled = true; // Can generate ressource cards ( no thief/robber )
    glm::vec3               Pos;
    AutoSceneNode*          Node = nullptr;
    int                     Points = 0; // default: 0
    Player_t*               Owner = nullptr;
    AutoSceneNode*          OwnerNode = nullptr;
    std::vector< Tile_t* >  Tiles; // collect neighbouring tiles 1-3
    float32_t 				Angle = 0;
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
    int32_t 					Angle60 = 0;
    std::vector< RoadPoint_t* > RoadPoints;
    std::vector< Waypoint_t* >  Waypoints;
    std::vector< irr::core::triangle3df > Triangles;
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
    uint32_t Erz = 0;			// Anzahl Erz
    uint32_t Holz = 0;			// Anzahl Holz
    uint32_t Lehm = 0;			// Anzahl Lehm
    uint32_t Weizen = 0;			// Anzahl Weizen
    uint32_t Wolle = 0;			// Anzahl Wolle
    std::string Name = "Bank";
    uint32_t getRessource( eTileType type )
    {
        switch( type )
        {
            case eTileType::HOLZ: return Holz;
            case eTileType::LEHM: return Lehm;
            case eTileType::WEIZEN: return Weizen;
            case eTileType::WOLLE: return Wolle;
            case eTileType::ERZ: return Erz;
            default: return 0;
        }
    }
};
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
    GUI_Card_t * Holz = nullptr;
    GUI_Card_t * Lehm = nullptr;
    GUI_Card_t * Weizen = nullptr;
    GUI_Card_t * Wolle = nullptr;
    GUI_Card_t * Erz = nullptr;
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
    GUI_Card_t * Roads = nullptr;
    GUI_Card_t * Settlements = nullptr;
    GUI_Card_t * Cities = nullptr;
    // Bank for ressource cards
    GUI_Card_t * Holz = nullptr;
    GUI_Card_t * Lehm = nullptr;
    GUI_Card_t * Weizen = nullptr;
    GUI_Card_t * Wolle = nullptr;
    GUI_Card_t * Erz = nullptr;
    // Bonus and Addons
    GUI_Card_t * EventCards = nullptr;
    GUI_Card_t * KnightCards = nullptr;
    GUI_Card_t * PointCards = nullptr;
    GUI_Card_t * BonusRoad = nullptr;
    GUI_Card_t * BonusArmy = nullptr;
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
    std::string             FontFileName;
    Fonts_t                 Fonts;

    void*                   Chat;

    eGameType 				Type;
    eGameState 				State;
    uint32_t                Round = 0;
    Dice_t                  Dice;

    Bank_t                  Bank;

    glm::ivec2              TileCount;
    glm::vec3               TileSize;
    std::vector< Tile_t >   Tiles;
    Tile_t*                 SelectedTile = nullptr;
    bool                    EnableCollisionDetectionForTiles = true;

    std::vector< Waypoint_t > Waypoints;
    Waypoint_t*             SelectedWaypointR = nullptr;
    Waypoint_t*             SelectedWaypointS = nullptr;
    bool                    EnableCollisionDetectionForWaypoints = true;

    std::vector< Player_t > Players;
    uint32_t 				Player = 0;

    Raueber_t               Raeuber;

    ePlaceObjectType        PlaceObjectType = ePlaceObjectType::ROBBER;
    AutoSceneNode*          PlaceObject = nullptr;

    GameUI_t                UI;
//    irr::scene::IMetaTriangleSelector* TileSelector = nullptr;
//    irr::scene::IMetaTriangleSelector* WaypointSelector = nullptr;
//    irr::scene::ISceneNode* HitSceneNode = nullptr;
//    irr::scene::ISceneNode* HitSceneNodeLast = nullptr;

};


} // end namespace pioneers3d

#endif // PIONEERS3D_TYPES_HPP
