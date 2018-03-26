#ifndef PIONEERS3D_BOARD_DATA_HPP
#define PIONEERS3D_BOARD_DATA_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

class Tile_t;
class Waypoint_t;

class Board_t
{
public:
    Board_t( irr::IrrlichtDevice* device );
    ~Board_t();

    void clear();
    void clearTiles();
    void clearWaypoints();

    std::string
    toXML() const;

    void
    readXML( irr::io::IXMLReaderUTF8 * xml)
    {
        if ( std::string("board") != xml->getNodeName() )
        {
            return;
        }

        xml->read();

        if ( std::string("tile") != xml->get() )
        {
            return;
        }
    }

    Tile_t*
    getTile( int i, int j ) const;

    glm::vec3 const &
    getTileSize() const;

    glm::vec3
    getTilePosition3D( int i, int j ) const;

    void
    addTile( eTileType tileType, int32_t i, int32_t j, int32_t dice, int32_t angle60 = 0 );

    irr::video::ITexture*
    getTileTexture( eTileType tileType, int32_t angle60 = 0);

    void
    createStandardBoard();

    void
    createWaypoints();

    void
    load( std::string const & fileName );

    void
    save( std::string const & fileName );

private:
    irr::IrrlichtDevice* Device;
    glm::vec3 TileSize;
    std::map< eTileType, std::string > Textures;
    std::vector< Tile_t* > Tiles;
    std::vector< Waypoint_t* > Waypoints;
};

} // end namespace pioneers3d

#endif // PIONEERS3D_BOARD_DATA_HPP
