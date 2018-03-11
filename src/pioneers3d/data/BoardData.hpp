#ifndef P3DDATA_BOARD_HPP
#define P3DDATA_BOARD_HPP

#include <pioneers3d/data/TextureType.hpp>
#include <pioneers3d/data/TileData.hpp>
#include <vector>

namespace pioneers3d
{

// ============================================================================
class BoardData
// ============================================================================
{
public:

    BoardData();

    ~BoardData();

private:
    std::vector< TileData > m_Tiles;

};

} // end namespace pioneers3d


#endif // P3DDATA_BOARD_HPP
