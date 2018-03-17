#include "TileData.hpp"

namespace pioneers3d {

	/// create default board
	// x = 0.5*(|j|%2)*dx + i*dx
	// z = j*0.75*dz

Tile::Tile()
{
	std::cout << __FUNCTION__ << "()" << std::endl;

}

Tile::~Tile()
{
	std::cout << "~" << __FUNCTION__ << "()" << std::endl;

}

} // end namespace pioneers3d
