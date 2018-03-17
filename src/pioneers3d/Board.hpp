#ifndef PIONEERS3D_DATA_BOARD_HPP
#define PIONEERS3D_DATA_BOARD_HPP

#include <pioneers3d/TileData.hpp>

namespace pioneers3d {

class BoardData
{
public:
	BoardData();
	~BoardData();
private:
	std::vector< TileData > m_Tiles;

};

} // end namespace pioneers3d

#endif // P3DDATA_BOARD_HPP
