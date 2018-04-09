#ifndef GAME_WAYPOINTS_HPP
#define GAME_WAYPOINTS_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

void Waypoints_clear( Game_t* game );

void Waypoints_print( Game_t * game );

Waypoint_t* Waypoint_findByPosition( Game_t * game, glm::vec3 pos );

void Waypoint_add( Game_t * game, float32_t r, float32_t h, uint32_t tesselation, glm::vec3 pos, bool isRoad = false );
void Waypoints_create( Game_t * game, float32_t radius, float32_t height, uint32_t tesselation, bool isRoad = false );

} // end namespace pioneers3d



#endif // GAME_WAYPOINTS_HPP
