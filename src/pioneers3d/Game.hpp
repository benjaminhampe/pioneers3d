#ifndef PIONEERS3D_GAME_HPP
#define PIONEERS3D_GAME_HPP

#include <pioneers3d/Types.hpp>
#include <pioneers3d/EventReceiver.hpp>

namespace pioneers3d {

std::string
Game_toXML( Game_t* game );

void
Game_clear( Game_t* game );

void
Game_createStandard( Game_t* game );

int
Game_exec( Game_t * game );

void
Game_load( std::string const & fileName );

void
Game_save( std::string const & fileName );

} // end namespace pioneers3d

#endif // PIONEERS3D_GAME_HPP
