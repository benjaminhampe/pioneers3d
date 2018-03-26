#include "Tile.hpp"

#include <pioneers3d/Waypoint.hpp>
#include <pioneers3d/Board.hpp>

namespace pioneers3d {

Tile_t::Tile_t( Board_t * board,
                int32_t i, int32_t j,
                eTileType tileType,
                int32_t dice,
                int32_t angle60 )
    : Board( board )
    , BoardIndex( i, j )
    , TileType( tileType )
    , DiceValue( dice )
    , Tex( nullptr )
    , TexAngle60( angle60 )
{
    std::cout << __FUNCTION__ << "("<< i << "," << j << ")\n";
    if ( Board )
    {
        Tex = Board->getTileTexture( TileType, TexAngle60 );
    }
}

Tile_t::~Tile_t()
{
    std::cout << __FUNCTION__ << "()\n";
}

std::string
Tile_t::getTexName() const
{
    if ( !Tex )
    {
        return "nullptr";
    }

    if ( Tex->getName().getPath().size() < 1)
    {
        return "invalid";
    }

    return Tex->getName().getPath().c_str();
}

void
Tile_t::set( eTileType tileType, int32_t i, int32_t j, int32_t dice, int32_t angle60 )
{
    TileType = tileType;
    BoardIndex.x = i;
    BoardIndex.y = j;
    DiceValue = dice;
    TexAngle60 = angle60;
    if ( Board )
    {
        Tex = Board->getTileTexture( TileType, TexAngle60 );
    }
}


std::string
Tile_t::toXML() const
{
    std::stringstream s;
    s   << "<tile"
        << HTML_ATTRIBUTE( "type", eTileTypeToString( TileType ) )
        << HTML_ATTRIBUTE( "x", std::to_string( BoardIndex.x ) )
        << HTML_ATTRIBUTE( "y", std::to_string( BoardIndex.y ) )
        << HTML_ATTRIBUTE( "dice", std::to_string( DiceValue ) )
        << HTML_ATTRIBUTE( "tex", getTexName() )
        << HTML_ATTRIBUTE( "angle", std::to_string( TexAngle60 ) )
        << " />";
    return s.str();
}

} // end namespace pioneers3d
