#ifndef PIONEERS3D_GAME_BOARD_HPP
#define PIONEERS3D_GAME_BOARD_HPP

#include <pioneers3d/types/Common.hpp>
#include <pioneers3d/types/TileType.hpp>
#include <pioneers3d/types/Bank.hpp>
#include <pioneers3d/types/Waypoint.hpp>
#include <pioneers3d/types/BoardObjects.hpp>

namespace pioneers3d {

class Game_t;
class Board_t;
//class Waypoint_t;

class Tile_t
{
public:
   Board_t*					Board = nullptr;
   //std::vector< Tile_t* > 	NeighbourTiles;
    TileType                   	Type = TileType::WASSER;
    glm::ivec2                  BoardIndex;
    glm::vec3                   Pos;
    glm::vec3                   Size;
    int32_t                     DiceValue = 0;
    int32_t                     Angle60 = 0;
    std::vector< Waypoint_t* >  Waypoints;
    //std::vector< RoadPoint_t* > RoadPoints;
    std::vector< irr::core::triangle3df > Triangles;
    AutoSceneNode*              Node = nullptr;
    irr::scene::ITriangleSelector* TriangleSelector = nullptr;
public:
    // Tile_t() {}
    //~Tile_t() { if (Node) Node->drop(); }
    std::string toString() const;

};

typedef uint32_t BoardType;

class Board_t
{
public:
   Game_t*                 Game;
   std::string             Name;
   BoardType               Type;
   Bank_t                  Bank;
   glm::ivec2              TileCount;
   glm::vec3               TileSize;
   std::vector< Tile_t >   Tiles;
   std::vector< Waypoint_t > Waypoints;

   //    Tile_t*                 SelectedTile = nullptr;
   //    bool                    EnableCollisionDetectionForTiles = true;
   //    Waypoint_t*             SelectedWaypointR = nullptr;
   //    Waypoint_t*             SelectedWaypointS = nullptr;
   //    bool                    EnableCollisionDetectionForWaypoints = true;

   Raueber_t               Raeuber;
   AutoSceneNode*          Object = nullptr;

   Board_t();
   ~Board_t();
   std::string toString() const;

void printWaypoints()
{
    std::cout << Waypoints;
}

void clear()
{
   clearWaypoints();
   clearTiles();
}

void clearTiles()
{
   for ( size_t i = 0; i < Tiles.size(); ++i )
   {
      Tile_t & tile = Tiles[ i ];
      if ( tile.Node )
      {
         tile.Node->drop();
         tile.Node = nullptr;
      }
   }
   Tiles.clear();
}

void clearWaypoints()
{
   for ( size_t i = 0; i < Waypoints.size(); ++i )
   {
      Waypoint_t & waypoint = Waypoints[ i ];
      if ( waypoint.Node )
      {
         waypoint.Node->drop();
         waypoint.Node = nullptr;
      }
   }
   Waypoints.clear();
}

Waypoint_t*
findWaypoint( glm::vec3 pos )
{
   for ( uint32_t i = 0; i < Waypoints.size(); ++i )
   {
      Waypoint_t & w = Waypoints[ i ];
      if ( equals( w.Pos, pos ) )
      {
         //std::cout << __FUNCTION__ << " [Found] :: Waypoint(" << i << ") at pos(" << toString(pos) << ")\n";
         return &w;
      }
   }
   return nullptr;
}

void forEachTile( std::function<void(Tile_t * t)> const & lambda )
{
   for ( size_t i = 0; i < Tiles.size(); ++i )
   {
      lambda( &Tiles[i] );
   }
}

void forEachWaypoint( std::function<void(Waypoint_t * w)> const & lambda )
{
   for ( size_t i = 0; i < Waypoints.size(); ++i )
   {
      lambda( &Waypoints[i] );
   }
}

void forEachWaypointR( std::function<void(Waypoint_t * w)> const & lambda )
{
   for ( size_t i = 0; i < Waypoints.size(); ++i )
   {
      if ( Waypoints[ i ].IsRoad )
      {
         lambda( &Waypoints[i] );
      }
   }
}

void forEachWaypointS( std::function<void(Waypoint_t * w)> const & lambda )
{
   for ( size_t i = 0; i < Waypoints.size(); ++i )
   {
      if ( !Waypoints[ i ].IsRoad )
      {
         lambda( &Waypoints[i] );
      }
   }
}

};

Board_t*    getBoard( Game_t * game );
inline std::string Board_toString( Game_t * game );
inline void Board_printWaypoints( Game_t* game ) { getBoard( game )->printWaypoints(); }
inline void Board_clear( Game_t * game ) { getBoard( game )->clear(); }
inline void Board_clearTiles( Game_t* game ) { getBoard( game )->clearTiles(); }
inline void Board_clearWaypoints( Game_t* game ) { getBoard( game )->clearWaypoints(); }
inline Waypoint_t* Board_findWaypoint( Game_t * game, glm::vec3 const & pos ) { return getBoard( game )->findWaypoint( pos ); }
inline void forEachTile( Game_t * game, std::function<void(Tile_t * t)> const & lambda ) { getBoard( game )->forEachTile( lambda ); }
inline void forEachWaypoint(  Game_t * game, std::function<void(Waypoint_t * w)> const & lambda ) { getBoard( game )->forEachWaypoint( lambda ); }
inline void forEachWaypointR( Game_t * game, std::function<void(Waypoint_t * w)> const & lambda ) { getBoard( game )->forEachWaypointR( lambda ); }
inline void forEachWaypointS( Game_t * game, std::function<void(Waypoint_t * w)> const & lambda ) { getBoard( game )->forEachWaypointS( lambda ); }

// ---------------------------------------------------------------------------------------
void        Board_create( Game_t * game );
void        Board_createStandardTiles( Game_t * game );
void        Board_addTile( Game_t * game, TileType tileType, int i, int j, int diceValue, int angle60 );
void        Board_createWaypoints( Game_t * game, float32_t radius, float32_t height, uint32_t tesselation, bool isRoad = false );
void        Board_addWaypoint( Game_t * game, float32_t r, float32_t h, uint32_t tesselation, glm::vec3 pos, float32_t angle, bool isRoad = false );
Tile_t *    Board_isMouseOverTile( Game_t * game );
Waypoint_t* Board_isMouseOverWaypoint( Game_t * game, bool isRoad );
//          Board_collectTilesByPosition( Game_t * game, glm::vec3 pos );
//void      Board_setVisible_Tiles( Game_t* game, bool visible );
//void      Board_setVisible_Tiles( Game_t* game, bool visible, TileType filter );
void        Board_setVisible_Waypoints( Game_t* game, bool visible );
void        Board_setVisible_WaypointsR( Game_t* game, bool visible );
void        Board_setVisible_WaypointsS( Game_t* game, bool visible );
inline Waypoint_t* Board_isMouseOverWaypointR( Game_t * game ) { return Board_isMouseOverWaypoint( game, true ); }
inline Waypoint_t* Board_isMouseOverWaypointS( Game_t * game ) { return Board_isMouseOverWaypoint( game, false ); }
inline void Board_showWaypoints( Game_t* game ) { Board_setVisible_Waypoints( game, true ); }
inline void Board_showWaypointsR( Game_t* game ) { Board_setVisible_WaypointsR( game, true ); }
inline void Board_showWaypointsS( Game_t* game ) { Board_setVisible_WaypointsS( game, true ); }
inline void Board_hideWaypoints( Game_t* game ) { Board_setVisible_Waypoints( game, false ); }
inline void Board_hideWaypointsR( Game_t* game ) { Board_setVisible_WaypointsR( game, false ); }
inline void Board_hideWaypointsS( Game_t* game ) { Board_setVisible_WaypointsS( game, false ); }

} // end namespace pioneers3d

#endif // PIONEERS3D_STANDARD_GAME_HPP
