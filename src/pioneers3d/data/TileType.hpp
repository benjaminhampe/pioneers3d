#ifndef P3D_DATA_TILETYPE_HPP
#define P3D_DATA_TILETYPE_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

class TileType
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

} // end namespace pioneers3d

#endif // P3D_DATA _TILETYPE_HPP
