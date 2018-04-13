#ifndef GAME_BANK_HPP
#define GAME_BANK_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

void Bank_clear( Bank_t & bank );

void Bank_addRessource( Bank_t & bank, eTileType tileType );

int Bank_getRessourceCount( Bank_t const & bank );

bool Bank_canRobberSteal( Bank_t const & bank );

std::string Bank_toString( Bank_t const & bank );

} // end namespace pioneers3d

#endif // GAME_BANK_HPP
