#include "Board.hpp"

#include <pioneers3d/Tile.hpp>
#include <pioneers3d/Waypoint.hpp>

/// create default board
// x = 0.5*(|j|%2)*dx + i*dx
// z = j*0.75*dz

namespace pioneers3d {

Board_t::Board_t( irr::IrrlichtDevice* device )
    : Device( device )
    , TileSize( 10.f, 4.f, 10.f )
{
    std::cout << __FUNCTION__ << "()\n";
    assert( Device );
}

Board_t::~Board_t()
{
    std::cout << __FUNCTION__ << "()\n";
    clear();
}

void
Board_t::clear()
{
   clearTiles();
   clearWaypoints();
}

void
Board_t::clearTiles()
{
    for ( int i = 0; i < Tiles.size(); ++i )
    {
        Tile_t * tile = Tiles[ i ];
        if ( tile )
        {
            delete tile;
        }
    }

    Tiles.clear();
}

void
Board_t::clearWaypoints()
{
    for ( int i = 0; i < Waypoints.size(); ++i )
    {
        Waypoint_t * w = Waypoints[ i ];
        if ( w )
        {
            delete w;
        }
    }

    Waypoints.clear();
}

std::string
Board_t::toXML() const
{
    std::stringstream s;
    s << "<board"
      << HTML_ATTRIBUTE( "tile-count", std::to_string( Tiles.size() ) )
      << HTML_ATTRIBUTE( "tile-size-x", std::to_string( TileSize.x ) )
      << HTML_ATTRIBUTE( "tile-size-y", std::to_string( TileSize.y ) )
      << HTML_ATTRIBUTE( "tile-size-z", std::to_string( TileSize.z ) )
      << ">\n";

    for ( int i = 0; i < Tiles.size(); ++i )
    {
        Tile_t * tile = Tiles[ i ];
        if ( tile )
        {
            s << "\t" << tile->toXML() << "\n";
        }
    }

    s << "</board>\n";
    return s.str();
}

Tile_t*
Board_t::getTile( int i, int j ) const
{
    for ( int i = 0; i < Tiles.size(); ++i )
    {
        Tile_t* tile = Tiles[i];
        if (tile && tile->BoardIndex == boardIndex)
        {
            return tile;
        }
    }

    return nullptr;
}

glm::vec3 const &
Board_t::getTileSize() const
{
    return TileSize;
}

glm::vec3
Board_t::getTilePosition3D( int i, int j ) const
{
    float const w = TileSize.x;
    float const h = TileSize.z;
    float const x = (0.50f * w) * (abs( j ) % 2) + w * i;
    float const z = (0.75f * h) * j;
    return glm::vec3( x, 0.0f, z );
}

irr::video::ITexture*
Board_t::getTileTexture( eTileType tileType, int32_t angle60 )
{
    assert( Device );

    irr::video::IVideoDriver* driver = Device->getVideoDriver();

    std::stringstream fileName;
    fileName << "../../media/" << Textures[ eTileType::WASSER ];
    irr::video::ITexture * tex = driver->getTexture( fileName.str().c_str() );

    if ( !tex )
    {
        std::cout << "Cannot create texture.\n";
    }

    std::cout << __FUNCTION__ << "(" << fileName.str() << ")\n";

    return tex;
}

void
Board_t::addTile(  eTileType tileType, int32_t i, int32_t j, int32_t dice, int32_t angle60 )
{
    Tile_t * tile = getTile( i,j );

    if ( !tile )
    {
        Tiles.push_back( new Tile_t( this, tileType, i, j, dice, angle60 ) );
    }
    else
    {
        tile->Board = this;
        tile->set( tileType, i, j, dice, angle60 );
    }
}

void
Board_t::createStandardBoard()
{
    clear();

    /// create default board
    // x = 0.5*(|j|%2)*dx + i*dx
    // z = j*0.75*dz
    for ( int i = -4; i < 5; ++i )
    {
        for ( int j = -4; j < 5; ++j )
        {
            Tiles.push_back( new Tile_t( i, j, eTileType::WASSER, 0, 0 ) );
        }
    }


}

/*
void
Board_t::createRhombusBoard()
{
    /// create default board
    // x = 0.5*(|j|%2)*dx + i*dx
    // z = j*0.75*dz
    for ( int i = -4; i < 5; ++i )
    {
        for ( int j = -4; j < 5; ++j )
        {
            Tiles.emplace_back( Tile_t( i, j, eTileType::WASSER, 0, 0 ) );
        }
    }
}
*/

void
Board_t::load( std::string const & fileName )
{

}

void
Board_t::save( std::string const & fileName )
{

}

} // end namespace pioneers3d

/*
    QImage _img[E_SIEDLER_TEX_COUNT];
    _img[E_SIEDLER_TEX_WASSER] = createImage_Wasser( _texW, _texH );
    _img[E_SIEDLER_TEX_HOLZ] = createImage_Holz( _texW, _texH );
    _img[E_SIEDLER_TEX_LEHM] = createImage_Lehm( _texW, _texH );
    _img[E_SIEDLER_TEX_WEIZEN] = createImage_Weizen( _texW, _texH );
    _img[E_SIEDLER_TEX_WOLLE] = createImage_Wolle( _texW, _texH );
    _img[E_SIEDLER_TEX_ERZ] = createImage_Erz( _texW, _texH );
    _img[E_SIEDLER_TEX_AUGEN_2] = createImage_Augen(2,0);
    _img[E_SIEDLER_TEX_AUGEN_3] = createImage_Augen(3,0);
    _img[E_SIEDLER_TEX_AUGEN_4] = createImage_Augen(4,2);
    _img[E_SIEDLER_TEX_AUGEN_5] = createImage_Augen(5,3);
    _img[E_SIEDLER_TEX_AUGEN_6] = createImage_Augen(6,4);
    _img[E_SIEDLER_TEX_AUGEN_7] = createImage_Augen(7,5);
    _img[E_SIEDLER_TEX_AUGEN_8] = createImage_Augen(8,4);
    _img[E_SIEDLER_TEX_AUGEN_9] = createImage_Augen(9,3);
    _img[E_SIEDLER_TEX_AUGEN_10] = createImage_Augen(10,2);
    _img[E_SIEDLER_TEX_AUGEN_11] = createImage_Augen(11,0);
    _img[E_SIEDLER_TEX_AUGEN_12] = createImage_Augen(12,0);

    // save("data");

    QDir().mkpath( baseDir );

    for ( int i = 0; i < E_SIEDLER_TEX_COUNT; ++i )
    {
        QString fileName = baseDir;
        fileName.append( "/" );
        fileName.append( E_SIEDLER_TEX_FILENAMES[i] );

        if (!_img[i].save( fileName ))
        {
            std::cout << "Cannot save image (" << fileName.toStdString() << ")" << std::endl;
        }
    }

    // load("data");

    for ( int i = 0; i < E_SIEDLER_TEX_COUNT; ++i )
    {
        QString fileName = baseDir;
        fileName.append( "/" );
        fileName.append( E_SIEDLER_TEX_FILENAMES[i] );

        _tex[i] = loadTexture( _driver, fileName );

        if (!_tex[i])
        {
            std::cout << "Cannot load texture (" << fileName.toStdString() << ")" << std::endl;
        }
    }
*/
