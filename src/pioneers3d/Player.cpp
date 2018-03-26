#include "Player.hpp"

namespace pioneers3d {

Player_t::Player_t( int id, std::string const & name )
    : Id( id )
    , Name( name )
{
    std::cout << __FUNCTION__ << "():\n" << toXML() << '\n';
}

Player_t::~Player_t()
{
    std::cout << __FUNCTION__ << "()\n";
}

std::string
Player_t::toXML() const
{
    std::stringstream s;
    s   << "<player "
        << HTML_ATTRIBUTE( "id", std::to_string( Id ) )
        << HTML_ATTRIBUTE( "name", Name )
        << " />";
    return s.str();
}

} // end namespace pioneers3d
