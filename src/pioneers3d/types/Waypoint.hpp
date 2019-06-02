/// (c) 2017 - 20190 Benjamin Hampe <benjaminhampe@gmx.de>

#ifndef PIONEERS3D_TYPES_WAYPOINT_HPP
#define PIONEERS3D_TYPES_WAYPOINT_HPP

#include <pioneers3d/types/Common.hpp>

namespace pioneers3d {

class Game_t;
class Board_t;
class Player_t;
class Tile_t;

class Waypoint_t
{
public:
   Board_t*                Board = nullptr;
   bool                    IsRoad = false; // Default: false == can settle, true == only a road
   bool                    IsEnabled = true; // Can generate ressource cards ( no thief/robber )
   glm::vec3               Pos;
   AutoSceneNode*          Node = nullptr;
   int                     Points = 0; // default: 0
   Player_t*               Owner = nullptr;
   AutoSceneNode*          OwnerNode = nullptr;
   std::vector< Tile_t* >  Tiles; // collect neighbouring tiles 1-3
   float32_t               Angle = 0;
public:
   //~Waypoint_t() { if (Node) Node->drop(); }
   std::string toString() const;
};

} // end namespace pioneers3d

inline std::ostream &
operator<< ( std::ostream & o, pioneers3d::Waypoint_t const & waypoint )
{
   o << waypoint.toString();
   return o;
}

inline std::ostream &
operator<< ( std::ostream & o, std::vector< pioneers3d::Waypoint_t > const & waypoints )
{
   o << "Waypoints.size() = " << waypoints.size() << "\n";
   for ( size_t i = 0; i < waypoints.size(); ++i )
   {
      o << "Waypoint[" << i << "] " << waypoints[ i ] << "\n";
   }
   return o;
}

#endif // PIONEERS3D_TYPES_WAYPOINT_HPP
