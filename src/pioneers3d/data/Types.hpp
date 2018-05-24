#ifndef PIONEERS3D_COMMON_DATA_TYPES_HPP
#define PIONEERS3D_COMMON_DATA_TYPES_HPP

#include <pioneers3d/CompileConfig.hpp>
#include <pioneers3d/data/eAction.hpp>
#include <pioneers3d/data/eGameType.hpp>
#include <pioneers3d/data/eGameState.hpp>
#include <pioneers3d/data/eTexture.hpp>
#include <pioneers3d/data/eTileType.hpp>

#include <pioneers3d/data/UI.hpp>

namespace pioneers3d {

    int32_t safeMod( int32_t a, int32_t b );

    /// Hexagon ( ver_2018 ):
    /**
                     D        triangles: ABF, BCE, BEF, CDE
                     /\
                  C /  \ E    M (x=0,y=0,z=0,u=0.5,v=0.5)
                   |----|     F(  .5, 0, -.25,  1, 0.25 )
                   |  M |     E(  .5, 0,  .25,  1, 0.75 )
                   |----|     D(   0, 0,  .50, .5, 1.00 )
                  B \  / F    C( -.5, 0,  .25,  0, 0.75 )
                     \/       B( -.5, 0, -.25,  0, 0.25 )
                     A        A(   0, 0, -.50, .5, 0.00 )
    */

    void getHexagonTriangles( std::vector< irr::core::triangle3df > & container, glm::vec2 const & tile_size, glm::vec3 const & tile_pos = glm::vec3(0,0,0) );

    glm::vec3 getHexagonCorner( int i, glm::vec2 const & tile_size, glm::vec3 const & tile_pos = glm::vec3(0,0,0) );

    glm::vec3 getHexagonEdgeCenter( int i, glm::vec2 const & tile_size, glm::vec3 const & tile_pos = glm::vec3(0,0,0) );

    float32_t getHexagonEdgeAngle( int i, glm::vec2 const & tile_size );

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

    class Dice_t;
    class Bank_t;
    class Raeuber_t;
    class Waypoint_t;
    class Tile_t;
    class Board_t;
    class Player_t;
    class Game_t;

    // ---------------------------------------------------------------------------------------

    class Dice_t
    {
    public:
        Dice_t() : A(1), B(1) { srand( static_cast< uint32_t >( time( nullptr ) ) ); }
        void randomizeA() { A = rand()%6 + 1; }
        void randomizeB() { B = rand()%6 + 1; }
        void randomize() { randomizeA(); randomizeB(); }
        int32_t sum() const { return A + B; }
        int32_t max() const { return std::max(A,B); }
        int32_t min() const { return std::min(A,B); }
        public:
        int32_t A;
        int32_t B;
    };

    class Bank_t
    {
    public:
        void clear()
        {
            Holz = Lehm = Weizen = Wolle = Erz = 0;
        }

        int32_t getTotal() const
        {
            return Holz + Lehm + Weizen + Wolle + Erz;
        }

        bool canRobberSteal() const
        {
            return getTotal() >= 7;
        }

        std::string toString() const
        {
            std::stringstream s;
            s << "Bank: "<< Name << "; "
            << "Holz:" << Holz << "; "
            << "Lehm:" << Lehm << "; "
            << "Weizen:" << Weizen << "; "
            << "Wolle:" << Wolle << "; "
            << "Erz:" << Erz << "; "
            << ";";
            return s.str();
        }

        int32_t get( eTileType type ) const
        {
            int32_t n = 0;
            if ( type.contains( eTileType::HOLZ ) ) n += Holz;
            if ( type.contains( eTileType::LEHM ) ) n += Lehm;
            if ( type.contains( eTileType::WEIZEN ) ) n += Weizen;
            if ( type.contains( eTileType::WOLLE ) ) n += Wolle;
            if ( type.contains( eTileType::ERZ ) ) n += Erz;
            return n;
        }

        void set( eTileType type, int32_t value )
        {
            if ( type.contains( eTileType::HOLZ ) ) Holz=value;
            if ( type.contains( eTileType::LEHM ) ) Lehm=value;
            if ( type.contains( eTileType::WEIZEN ) ) Weizen=value;
            if ( type.contains( eTileType::WOLLE ) ) Wolle=value;
            if ( type.contains( eTileType::ERZ ) ) Erz=value;
        }

        void add( eTileType type, int32_t value )
        {
            if ( type.contains( eTileType::HOLZ ) ) Holz+=value;
            if ( type.contains( eTileType::LEHM ) ) Lehm+=value;
            if ( type.contains( eTileType::WEIZEN ) ) Weizen+=value;
            if ( type.contains( eTileType::WOLLE ) ) Wolle+=value;
            if ( type.contains( eTileType::ERZ ) ) Erz+=value;
        }

    public:
        int32_t Holz = 0;			// Anzahl Holz
        int32_t Lehm = 0;			// Anzahl Lehm
        int32_t Weizen = 0;			// Anzahl Weizen
        int32_t Wolle = 0;			// Anzahl Wolle
        int32_t Erz = 0;			// Anzahl Erz
        std::string Name = "Bank";
    };

    struct Raueber_t
    {
        glm::ivec2 					BoardIndex;
        glm::vec3                   Pos;
        irr::scene::ISceneNode*     Node = nullptr;
        //~Raueber_t() { if (Node) Node->drop(); }
    };

    class Waypoint_t
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
    public:
        //~Waypoint_t() { if (Node) Node->drop(); }
        std::string toString() const;
    };

    class Tile_t
    {
    public:
        eTileType 					Type = eTileType::WASSER;
        glm::ivec2 					BoardIndex;
        glm::vec3                   Pos;
        glm::vec3                   Size;
        int32_t 					DiceValue = 0;
        int32_t 					Angle60 = 0;
        //std::vector< RoadPoint_t* > RoadPoints;
        std::vector< Waypoint_t* >  Waypoints;
        std::vector< irr::core::triangle3df > Triangles;
        AutoSceneNode*              Node = nullptr;
        irr::scene::ITriangleSelector* TriangleSelector = nullptr;
    public:
        // Tile_t() {}
        //~Tile_t() { if (Node) Node->drop(); }
        std::string toString() const;


    };

    class Player_t
    {
    public:
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
    public:
        //
        std::string toString() const;
    };

    class Game_t
    {
    public:
        std::string             ExeFile;
        std::string             ExeDir;
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

    //Board_t					Board;
    //public:
    //  std::string             Name;
        glm::ivec2              TileCount;
        glm::vec3               TileSize;
        std::vector< Tile_t >   Tiles;
        std::vector< Waypoint_t > Waypoints;

        Tile_t*                 SelectedTile = nullptr;
        bool                    EnableCollisionDetectionForTiles = true;

        Waypoint_t*             SelectedWaypointR = nullptr;
        Waypoint_t*             SelectedWaypointS = nullptr;
        bool                    EnableCollisionDetectionForWaypoints = true;

        std::vector< Player_t > Players;
        uint32_t 				Player = 0;

        Raueber_t               Raeuber;
        ePlaceObjectType        PlaceObjectType = ePlaceObjectType::ROBBER;
        AutoSceneNode*          PlaceObject = nullptr;

        GameUI_t                UI;

        Game_t() {}
        ~Game_t() {}
    };

} // end namespace pioneers3d

#endif // PIONEERS3D_COMMON_DATA_TYPES_HPP
