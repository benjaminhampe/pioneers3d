#include <pioneers3d/Types.hpp>

namespace pioneers3d {


std::string Bank_t::toString() const
{
    std::stringstream s;
    s << "Bank_t:\n";
    return s.str();
}

std::string Player_t::toString() const
{
    std::stringstream s;
    s << "Player_t:\n";
    return s.str();
}


} // end namespace pioneers3d
