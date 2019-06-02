#include <pioneers3d/types/Waypoint.hpp>
#include <pioneers3d/types/Game.hpp>

namespace pioneers3d {

std::string
Waypoint_t::toString() const
{
    std::stringstream s;
    s << "isRoad: " << IsRoad << "; "
      << "owner: "<< (void*)Owner << "; "
      << "points: "<< Points << "; "
      << "pos: "<< Pos << "; "
//      << "dice: "<< tile->DiceValue << "; "
//      << "ang60: "<< tile->TexAngle60 << "; "
//      << "waypoints: "<< tile->Waypoints.size() << "; "
      << "";
    return s.str();
}

} // end namespace pioneers3d
