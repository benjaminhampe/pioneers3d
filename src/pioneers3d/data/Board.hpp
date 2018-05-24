#ifndef PIONEERS3D_DATA_BOARD_HPP
#define PIONEERS3D_DATA_BOARD_HPP

#include <pioneers3d/data/Types.hpp>
#include <functional>

namespace pioneers3d {

std::string Board_toString( Game_t * game );
void 		Board_printWaypoints( Game_t* game );

void 		Board_clear( Game_t * game );
void        Board_clearTiles( Game_t* game );
void 		Board_clearWaypoints( Game_t* game );

void        Board_create( Game_t * game );
void		Board_createStandardTiles( Game_t * game );
void		Board_addTile( Game_t * game, eTileType tileType, int i, int j, int diceValue, int angle60 );

void 		Board_createWaypoints( Game_t * game, float32_t radius, float32_t height, uint32_t tesselation, bool isRoad = false );
void 		Board_addWaypoint( Game_t * game, float32_t r, float32_t h, uint32_t tesselation, glm::vec3 pos, float32_t angle, bool isRoad = false );

Tile_t *	Board_isMouseOverTile( Game_t * game );
Waypoint_t* Board_isMouseOverWaypoint( Game_t * game, bool isRoad );

Waypoint_t* Board_findWaypoint( Game_t * game, glm::vec3 pos );

//  std::vector< Tile_t* >
//          Board_collectTilesByPosition( Game_t * game, glm::vec3 pos );

//void 		Board_setVisible_Tiles( Game_t* game, bool visible );
//void 		Board_setVisible_Tiles( Game_t* game, bool visible, eTileType filter );
void 		Board_setVisible_Waypoints( Game_t* game, bool visible );

void 		Board_setVisible_WaypointsR( Game_t* game, bool visible );
void 		Board_setVisible_WaypointsS( Game_t* game, bool visible );

void        forEachTile( Game_t * game, std::function<void(Tile_t * t)> const & lambda );
void        forEachWaypoint(  Game_t * game, std::function<void(Waypoint_t * w)> const & lambda );
void        forEachWaypointR( Game_t * game, std::function<void(Waypoint_t * w)> const & lambda );
void        forEachWaypointS( Game_t * game, std::function<void(Waypoint_t * w)> const & lambda );

inline Waypoint_t* Board_isMouseOverWaypointR( Game_t * game ) { return Board_isMouseOverWaypoint( game, true ); }
inline Waypoint_t* Board_isMouseOverWaypointS( Game_t * game ) { return Board_isMouseOverWaypoint( game, false ); }

inline void Board_showWaypoints( Game_t* game ) { Board_setVisible_Waypoints( game, true ); }
inline void Board_showWaypointsR( Game_t* game ) { Board_setVisible_WaypointsR( game, true ); }
inline void Board_showWaypointsS( Game_t* game ) { Board_setVisible_WaypointsS( game, true ); }

inline void Board_hideWaypoints( Game_t* game ) { Board_setVisible_Waypoints( game, false ); }
inline void Board_hideWaypointsR( Game_t* game ) { Board_setVisible_WaypointsR( game, false ); }
inline void Board_hideWaypointsS( Game_t* game ) { Board_setVisible_WaypointsS( game, false ); }



} // end namespace pioneers3d

#endif // PIONEERS3D_DATA_BOARD_HPP
