#ifndef GAME_WAYPOINTS_HPP
#define GAME_WAYPOINTS_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

void setWaypointsVisible( Game_t* game, bool visible );
void setWaypointsVisible( Game_t* game, bool visible, bool isRoad );

void clearWaypoints( Game_t* game );
void printWaypoints( Game_t* game );

Waypoint_t* findWaypoint( Game_t * game, glm::vec3 pos );

void addWaypoint( Game_t * game, float32_t r, float32_t h, uint32_t tesselation, glm::vec3 pos, bool isRoad = false );
void createWaypoints( Game_t * game, float32_t radius, float32_t height, uint32_t tesselation, bool isRoad = false );

} // end namespace pioneers3d



#endif // GAME_WAYPOINTS_HPP
