#ifndef PIONEERS3D_TILE_DATA_HPP
#define PIONEERS3D_TILE_DATA_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

class Board_t;
class Waypoint_t;

class Tile_t
{
public:
    Tile_t( Board_t* board,
            eTileType tileType,
            int32_t i, int32_t j,
            int32_t dice,
            int32_t angle60 = 0 );

    ~Tile_t();

    void set( eTileType tileType,
            int32_t i, int32_t j,
            int32_t dice,
            int32_t angle60 = 0 );

    std::string
    getTexName() const;

    std::string
    toXML() const;

    void
    setType( eTileType tileType );

public:
    Board_t* 					Board;
    glm::ivec2 					BoardIndex;
    eTileType 					TileType = eTileType::WASSER;
    int32_t 					DiceValue = 0;
    irr::video::ITexture* 		Tex;
    int32_t 					TexAngle60 = 0;
    std::vector< Waypoint_t* >  Waypoints;
};

} // end namespace pioneers3d

#endif // PIONEERS3D_TILE_DATA_HPP
