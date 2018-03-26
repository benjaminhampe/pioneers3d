#include "Waypoint.hpp"

#include <pioneers3d/Tile.hpp>
#include <pioneers3d/Player.hpp>

namespace pioneers3d {

Waypoint_t::Waypoint_t()
    : IsEnabled( true ) // false = Robber is on tile
    , CanHaveOwner( true )
    , Owner( nullptr )
    , VictoryPoints( 0 )
{
    std::cout << __FUNCTION__ << "()\n";

}

Waypoint_t::~Waypoint_t()
{
    std::cout << __FUNCTION__ << "()\n";
}

} // end namespace pioneers3d
