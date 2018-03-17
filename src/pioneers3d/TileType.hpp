#ifndef PIONEERS3D_TILE_TYPE_HPP
#define PIONEERS3D_TILE_TYPE_HPP

#include <stdint.h>

namespace pioneers3d {

enum class eTileType : uint32_t
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
};

} // end namespace pioneers3d

#endif // PIONEERS3D_TILETYPE_HPP
