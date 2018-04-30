#ifndef GAME_WAYPOINTS_HPP
#define GAME_WAYPOINTS_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

class Player_t;
class Tile_t;

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
    //~Waypoint_t() { if (Node) Node->drop(); }
};

std::string Waypoint_toString( Waypoint_t const & w );

Waypoint_t* Waypoint_mouseOver( Game_t * game, bool isRoad );

void Waypoints_setVisible( Game_t* game, bool visible );
void Waypoints_R_setVisible( Game_t* game, bool visible );
void Waypoints_S_setVisible( Game_t* game, bool visible );

//void setWaypointsVisible( Game_t* game, bool visible, bool isRoad );

void clearWaypoints( Game_t* game );
void printWaypoints( Game_t* game );

Waypoint_t* findWaypoint( Game_t * game, glm::vec3 pos );

void addWaypoint( Game_t * game, float32_t r, float32_t h, uint32_t tesselation, glm::vec3 pos, float32_t angle, bool isRoad = false );
void createWaypoints( Game_t * game, float32_t radius, float32_t height, uint32_t tesselation, bool isRoad = false );

} // end namespace pioneers3d



#endif // GAME_WAYPOINTS_HPP
