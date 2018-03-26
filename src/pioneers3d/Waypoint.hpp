#ifndef PIONEERS3D_WAYPOINT_DATA_HPP
#define PIONEERS3D_WAYPOINT_DATA_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

class Tile_t;
class Player_t;

class Waypoint_t
{
public:
    Waypoint_t();
    ~Waypoint_t();

public:
    bool IsEnabled; // Can generate ressource cards ( no thief/robber )
    bool CanHaveOwner; // Can have an owner
    Player_t* Owner;
    int VictoryPoints;
    std::vector< Tile_t* > Neighbours; // Parents
};

} // end namespace pioneers3d

#endif // PIONEERS3D_WAYPOINT_DATA_HPP
