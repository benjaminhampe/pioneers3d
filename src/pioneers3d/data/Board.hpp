#ifndef PIONEERS3D_BOARD_HPP
#define PIONEERS3D_BOARD_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d
{

// ============================================================================
class TileType
// ============================================================================
{
public:
	enum ETileType
	{
		WASSER = 0,
		HOLZ,
		LEHM,
		WEIZEN,
		ERZ,
		WOLLE,
		HAFEN_3_ZU_1,
		HAFEN_HOLZ,
		HAFEN_LEHM,
		HAFEN_WEIZEN,
		HAFEN_ERZ,
		HAFEN_WOLLE,
		COUNT,
		FORCE_32BIT = 65536
	};
};

// ============================================================================
struct Tile
// ============================================================================
{
	Tile();
	~Tile();
};

// ============================================================================
class Board
// ============================================================================
{
public:
	Board();
	~Board();
private:
	std::vector< Tile > m_Tiles;

};

} // end namespace pioneers3d

#endif // P3DDATA_BOARD_HPP
