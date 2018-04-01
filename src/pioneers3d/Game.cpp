#include "Game.hpp"

namespace pioneers3d {

} // end namespace pioneers3d


#if 0
void
setBaseDir( std::string const & basePath )
{
    BasePath = basePath;

    // replaceChar( BasePath, '\\', '/' );

    auto endsWidth = [] ( std::string const & txt, char endChar ) -> bool
    {
        if ( txt.empty() )
        {
            return false;
        }

        if ( txt.at( txt.size()-1 ) == endChar )
        {
            return true;
        }

        return false;
    };

    if ( !endsWidth( BasePath, '/' ) )
    {
        BasePath += '/';
    }

    std::cout << __FUNCTION__ << " :: basePath(" << basePath << ") -> BasePath(" << BasePath << ")\n";
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

void
Board_clear( Board_t * board )
{
    std::cout << __FUNCTION__ << "()\n";

    if ( !board ) return;

    // clear Tiles:
    for ( int i = 0; i < board->Tiles.size(); ++i )
    {
        Tile_t * tile = board->Tiles[ i ];
        if ( tile )
        {
            delete tile;
        }
    }

    board->Tiles.clear();

    // clear Waypoints:
    for ( int i = 0; i < board->Waypoints.size(); ++i )
    {
        Waypoint_t * w = board->Waypoints[ i ];
        if ( w )
        {
            delete w;
        }
    }

    board->Waypoints.clear();
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

Game_t::Game_t( irr::IrrlichtDevice* device )
    : Device( device)
    , ClearColor( 255, 225, 225, 255 )
    , Type( eGameType::STANDARD )
    , State( eGameState::GAME_INIT_BOARD )
{
    /// logging
    std::cout << __FUNCTION__ << "()" << std::endl;

    /// device
    assert( Device );
    Device->setEventReceiver( this );

    /// randomize
    srand( (unsigned int)time(NULL) );
}

Game_t::~Game_t()
{
    std::cout << __FUNCTION__ << "()" << std::endl;
}

bool
Game_t::OnEvent( const irr::SEvent& event )
{
    if ( event.EventType == irr::EET_KEY_INPUT_EVENT )
    {
        irr::SEvent::SKeyInput const & keyEvent = event.KeyInput;

        if ( keyEvent.Key == irr::KEY_ESCAPE )
        {
            if ( Device )
            {
                Device->closeDevice();
            }
            return true;
        }
    }
    return false;
}

void
Game_t::createStandardGame()
{
    BasePath = "../../media/";

    Board.createStandardBoard();

    /// players
    Players.clear();
    Players.push_back( Player_t( 0, "Benni" ) );
    Players.push_back( Player_t( 1, "Robot 1" ) );
    Players.push_back( Player_t( 2, "Robot 2" ) );
    Players.push_back( Player_t( 3, "Robot 3" ) );


    irr::video::IVideoDriver* driver = Device->getVideoDriver();
    assert( driver );
    irr::scene::ISceneManager* smgr = Device->getSceneManager();
    assert( smgr );
    irr::scene::ICameraSceneNode* camera = Camera::createFPSCamera( smgr, smgr->getRootSceneNode() );
    assert( camera );

    /// logging content
    std::cout << toXML() << "\n";
}

/// Start main loop:
int
Game_t::exec()
{
    assert( Device );

    uint64_t startTime = Device->getTimer()->getRealTime();
    uint64_t currentTime = Device->getTimer()->getRealTime();

    while (Device && Device->run())
    {
        irr::video::IVideoDriver* driver = Device->getVideoDriver();
        if (driver)
        {
            driver->beginScene( true, true, ClearColor );

            irr::scene::ISceneManager* smgr = Device->getSceneManager();
            if ( smgr )
            {
                smgr->drawAll();
            }

            driver->endScene();

            std::wstringstream s; s << "Pioneers3D ";
            s << "- FPS(" << driver->getFPS() << ")";

            Device->setWindowCaption( s.str().c_str() );
        }
    }

    Device->drop();
    return 0;
}

std::string
Game_t::toXML() const
{
    std::stringstream s;
    s   << "<game "
        << HTML_ATTRIBUTE( "type", Type.toString() )
        << ">\n"
        << Board.toXML() << "\n"
        << "</game>";
    return s.str();
}

void
Game_t::load( std::string const & fileName )
{

}

void
Game_t::save( std::string const & fileName )
{

}

#endif
