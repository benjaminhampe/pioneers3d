#ifndef GAME_WAYPOINTS_HPP
#define GAME_WAYPOINTS_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

void Game_clearWaypoints( Game_t* game );
void Game_createWaypoints( Game_t * game );
void Game_printWaypoints( Game_t * game );

Waypoint_t* Waypoint_findByPosition( Game_t * game, glm::vec3 pos );

} // end namespace pioneers3d



#endif // GAME_WAYPOINTS_HPP
