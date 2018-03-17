#include <pioneers3d/data/Board.hpp>

#include <iostream>

namespace pioneers3d {

Tile::Tile()
{

}

Tile::~Tile()
{

}

Board::Board()
{
	std::cout << __FUNCTION__ << "()" << std::endl;

#if 0
	/// create default board
	// x = 0.5*(|j|%2)*dx + i*dx
	// z = j*0.75*dz

	for ( int i = -4; i < 5; ++i )
	{
		for ( int j = -4; j < 5; ++j )
		{
			m_Tiles.emplace_back( std::move( TileData( i, j ) ) );
		}
	}
#endif
}

Board::~Board()
{
	std::cout << "~" << __FUNCTION__ << "()" << std::endl;
}

} // end namespace pioneers3d
