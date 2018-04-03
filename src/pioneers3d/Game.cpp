#include "Game.hpp"

namespace pioneers3d {

int32_t safeMod( int32_t a, int32_t b )
{
    if ( a == 0 && b == 0)
    {
        return 0;
    }

    return std::abs( a ) % std::abs( b );
}

std::string
Game_toXML( Game_t* game )
{
    std::stringstream s;
    s   << "<game "
        << XML_ATTRIBUTE( "type", game->Type.toString() )
        << ">\n"
        << "\n"
        << "</game>";
    return s.str();
}

void
Game_createStandard( Game_t* game, irr::IrrlichtDevice* device )
{
    std::cout << __FUNCTION__ << "()\n";

    assert( device );

    srand( (unsigned int)time(NULL) );

    game->Device = device;
    game->MediaDir = "../../media/";
    game->ClearColor = irr::video::SColor( 255, 225, 225, 255 );

    device->setResizable( true );
    device->setWindowCaption( L"Pioneers3D (c) 2018 by Benjamin Hampe <benjaminhampe@gmx.de>" );

    irr::video::IVideoDriver* driver = device->getVideoDriver();
    irr::scene::ISceneManager* smgr = device->getSceneManager();

    //GameBuilder_createRessourceCardTexture( game, eTileType::HOLZ, "card_holz.jpg" );
    //GameBuilder_createRessourceCardTexture( game, eTileType::LEHM, "card_lehm.jpg" );
    //GameBuilder_createRessourceCardTexture( game, eTileType::WEIZEN, "card_weizen.jpg" );
    //GameBuilder_createRessourceCardTexture( game, eTileType::WOLLE, "card_wolle.jpg" );
    //GameBuilder_createRessourceCardTexture( game, eTileType::ERZ, "card_erz.jpg" );

    game->Type = eGameType::STANDARD;
    game->State = eGameState::GAME_INIT_BOARD;
    game->Receiver = new EventReceiver( game );
    game->TileSize = glm::vec3( 100.0f, 20.0f, 100.0f );
    game->TileCount = glm::ivec2( 7, 7 );

    auto addTile = [ &game, &driver, &smgr ] ( eTileType tileType, int i, int j, int diceValue, int angle60 ) -> void
    {
        float32_t const w = game->TileSize.x;
        float32_t const h = game->TileSize.z;

        Tile_t tile;
        tile.BoardIndex = glm::ivec2( i, j );
        tile.TileType = tileType;
        tile.DiceValue = diceValue;
        tile.TexAngle60 = angle60;
        tile.Pos = glm::vec3( w * i + w * 0.5f * ( safeMod( j, 2 ) == 1 ), 0.0f, 3.0f/4.0f * h * j );
        game->Tiles.push_back( std::move( tile ) );

        // create scene
        AutoSceneNode* node = new AutoSceneNode( smgr, smgr->getRootSceneNode(), -1 );
        node->setPosition( tile.Pos );

        // ground hexagon
        AutoMeshBuffer* hexagon = createHexagon( w, h );
        hexagon->MeshBuffer.Material.setTexture( 0, Game_getTileTexture( game, tileType ) );
        node->add( hexagon, true );

        // chip cylinder for land tiles
        if ( tileType.isLand() || tileType.isHafen() )
        {

            irr::video::ITexture* tex = Game_getChipTexture( game, tileType, diceValue );

            AutoMeshBuffer* hull = createCylinderHull( glm::vec3(0.0f, 2.5f, 0.0f), 10.0f, 5.0f, 0xFFFFFFFF, 16, 1 );
            hull->MeshBuffer.Material.setTexture( 0, tex );
            node->add( hull, true );

            AutoMeshBuffer* top = createCircleXZ( glm::vec3( 0.0f, 5.0f, 0.0f ), 10.0f, 16 );
            top->MeshBuffer.Material.setTexture( 0, tex );
            node->add( top, true );

            // + 2 roads for hafen tiles
            if ( tileType.isHafen() )
            {
                AutoMeshBuffer* hull = createCylinderHull( glm::vec3(0.0f, 2.5f, 0.0f), 10.0f, 5.0f, 0xFFFFFFFF, 16, 1 );
                hull->setTexture( 0, tex );
                node->add( hull, true );

                AutoMeshBuffer* top = createCircleXZ( glm::vec3( 0.0f, 5.0f, 0.0f ), 10.0f, 16 );
                top->setTexture( 0, tex );
                node->add( top, true );

                int k = tile.TexAngle60;
                node->add( createRotatedBox( getHexagonPoint( w, h, k )*0.5f, glm::vec3(1,1,20), glm::vec3(0,k*60,0), 0xFFFFFFFF ), true );
                node->add( createRotatedBox( getHexagonPoint( w, h, k+1 )*0.5f, glm::vec3(1,1,20), glm::vec3(0,(k+1)*60,0), 0xFFFFFFFF ), true );
            }
        }
    };

    // <!-- Zeile -3: (4-tiles) -->
    addTile( eTileType::HAFEN_LEHM, -2, -3, 0, 3);
    addTile( eTileType::WASSER, -1, -3, 0, 3);
    addTile( eTileType::HAFEN_3zu1, 0, -3, 0, 3);
    addTile( eTileType::WASSER, 1, -3, 0, 2);

    // <!-- Zeile -2: (5-tiles) -->
    addTile( eTileType::WASSER, -2, -2, 0, 4);
    addTile( eTileType::LAND_WEIZEN, -1, -2, 3, 0);
    addTile( eTileType::LAND_WEIZEN, 0, -2, 6, 0);
    addTile( eTileType::LAND_ERZ, 1, -2, 11, 0);
    addTile( eTileType::HAFEN_WEIZEN, 2, -2, 0, 1);

    // <!-- Zeile -1: (6-tiles) -->
    addTile( eTileType::HAFEN_3zu1, -3, -1, 0, 3);
    addTile( eTileType::LAND_HOLZ, -2, -1, 3, 0);
    addTile( eTileType::LAND_ERZ, -1, -1, 5, 0);
    addTile( eTileType::LAND_LEHM, 0, -1, 10, 0);
    addTile( eTileType::LAND_HOLZ, 1, -1, 11, 0);
    addTile( eTileType::WASSER, 2, -1, 0, 2);

    // <!-- Zeile 0: (7-tiles) -->
    addTile( eTileType::WASSER, -3, 0, 0, 4);
    addTile( eTileType::LAND_WOLLE, -2, 0, 9, 0);
    addTile( eTileType::LAND_LEHM, -1, 0, 8, 0);
    addTile( eTileType::LAND_WUESTE, 0, 0, 0, 0);
    addTile( eTileType::LAND_ERZ, 1, 0, 8, 0);
    addTile( eTileType::LAND_WOLLE, 2, 0, 10, 0);
    addTile( eTileType::HAFEN_3zu1, 3, 0, 0, 1);

    // <!-- Zeile +1: (6-tiles) -->
    addTile( eTileType::HAFEN_HOLZ, -3, 1, 0, 4);
    addTile( eTileType::LAND_LEHM, -2, 1, 2, 0);
    addTile( eTileType::LAND_HOLZ, -1, 1, 5, 0);
    addTile( eTileType::LAND_WOLLE, 0, 1, 12, 0);
    addTile( eTileType::LAND_WOLLE, 1, 1, 4, 0);
    addTile( eTileType::WASSER, 2, 1, 0, 1);

    // <!-- Zeile 2: (5-tiles) -->
    addTile( eTileType::WASSER, -2, 2, 0, 5);
    addTile( eTileType::LAND_WEIZEN, -1, 2, 4, 0);
    addTile( eTileType::LAND_HOLZ, 0, 2, 6, 0);
    addTile( eTileType::LAND_WEIZEN, 1, 2, 9, 0);
    addTile( eTileType::HAFEN_3zu1, 2, 2, 0, 1);

    // <!-- Zeile 3: (4-tiles) -->
    addTile( eTileType::HAFEN_ERZ, -2, 3, 0, 5);
    addTile( eTileType::WASSER, -1, 3, 0, 0);
    addTile( eTileType::HAFEN_WOLLE, 0, 3, 0, 0);
    addTile( eTileType::WASSER, 1, 3, 0, 0);

    /// createStandard: Players
    game->Players.clear();

    auto addPlayer = [ &game ] ( int id, std::string const & name ) -> void
    {
        Player_t player;
        player.Id = id;
        player.Name = name;
        game->Players.emplace_back( std::move( player ) );
    };

    addPlayer( 0, "Benni" );
    addPlayer( 1, "Robot 1" );
    addPlayer( 2, "Robot 2" );
    addPlayer( 3, "Robot 3" );

/*
    irr::video::IVideoDriver* driver = Device->getVideoDriver();
    assert( driver );
    irr::scene::ISceneManager* smgr = Device->getSceneManager();
    assert( smgr );
    irr::scene::ICameraSceneNode* camera = Camera::createFPSCamera( smgr, smgr->getRootSceneNode() );
    assert( camera );
*/
    {
        irr::SKeyMap keyMap[6];
        keyMap[0].Action = irr::EKA_MOVE_FORWARD;
        keyMap[0].KeyCode = irr::KEY_KEY_W;
        keyMap[1].Action = irr::EKA_MOVE_BACKWARD;
        keyMap[1].KeyCode = irr::KEY_KEY_S;
        keyMap[2].Action = irr::EKA_STRAFE_LEFT;
        keyMap[2].KeyCode = irr::KEY_KEY_A;
        keyMap[3].Action = irr::EKA_STRAFE_RIGHT;
        keyMap[3].KeyCode = irr::KEY_KEY_D;
        keyMap[4].Action = irr::EKA_JUMP_UP;
        keyMap[4].KeyCode = irr::KEY_SPACE;
        keyMap[5].Action = irr::EKA_CROUCH;
        keyMap[5].KeyCode = irr::KEY_KEY_C;
        irr::scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS( smgr->getRootSceneNode(), 65.f,0.5f,-1,keyMap,6,false,1.0f, false, true );
        camera->setNearValue( 1.0f );
        camera->setFarValue( 10000.0f );
        camera->setPosition( irr::core::vector3df(0,300,-300) );
        camera->setTarget( irr::core::vector3df(0,-60,-60) );
    }


    // addSkyBox( AutoSceneNode* )
    {
        irr::video::ITexture* top = Game_getTexture( game, eTexture::SKYBOX_TOP );
        irr::video::ITexture* bottom = Game_getTexture( game, eTexture::SKYBOX_BOTTOM );
        irr::video::ITexture* left = Game_getTexture( game, eTexture::SKYBOX_LEFT );
        irr::video::ITexture* right = Game_getTexture( game, eTexture::SKYBOX_RIGHT );
        irr::video::ITexture* front = Game_getTexture( game, eTexture::SKYBOX_FRONT );
        irr::video::ITexture* back = Game_getTexture( game, eTexture::SKYBOX_BACK );
        //irr::scene::ISceneNode* skyBox =
        smgr->addSkyBoxSceneNode( top, bottom, left, right, front, back, smgr->getRootSceneNode(), -1 );
    }

    irr::gui::IGUIEnvironment* guienv = game->Device->getGUIEnvironment();
    if ( !guienv )
    {
        std::cout << __FUNCTION__ << " :: ERROR: Invalid pointer to IGUIEnvironment\n";
        return;
    }

    irr::core::dimension2du const screen = driver->getScreenSize();

    GameUI_createMainMenuWindow( game );
    GameUI_createPlayerAction( game, mkRect( 100, 10, screen.Width - 200, 120 ) );
    GameUI_createPlayerInfo( game, 0 );
    GameUI_createChatBox( game, mkRect( screen.Width/2+100, screen.Height/4, screen.Width/2 - 150, screen.Height/2 ) );
}

/// Start main loop:
int
Game_exec( Game_t * game )
{
    assert( game );

    irr::IrrlichtDevice* device = game->Device;

    assert( device );

    irr::video::IVideoDriver* driver = device->getVideoDriver();
    irr::scene::ISceneManager* smgr = device->getSceneManager();
    irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

    uint64_t startTime = device->getTimer()->getRealTime();
    uint64_t currTime = device->getTimer()->getRealTime();
    uint64_t lastScreenUpdateTime = device->getTimer()->getRealTime();
    uint64_t lastWindowTitleUpdateTime = device->getTimer()->getRealTime();

    uint64_t updateScreenMs = 10;
    uint64_t updateWindowTitleMs = 1000 / 10;

    while (device && device->run())
    {
        currTime = device->getTimer()->getRealTime();

        if ( device->isWindowActive() )
        {
            if ( currTime - lastScreenUpdateTime >= updateScreenMs )
            {
                lastScreenUpdateTime = currTime;

                if (driver)
                {
                    driver->beginScene( true, true, game->ClearColor );

                    if ( smgr )
                    {
                        smgr->drawAll();
                    }

                    if ( guienv )
                    {
                        guienv->drawAll();
                    }

                    driver->endScene();
                }

            }

            if ( currTime - lastWindowTitleUpdateTime >= updateWindowTitleMs )
            {
                lastWindowTitleUpdateTime = currTime;

                std::stringstream s;
                s << "Pioneers3D ";
                s << "- FPS(" << driver->getFPS() << ")";
                s << ", WIN(" << toString( driver->getScreenSize() ) << ")";

                irr::scene::ICameraSceneNode* camera = smgr->getActiveCamera();
                if ( camera )
                {
                    s << ", CAM-POS(" << toString( camera->getAbsolutePosition() ) << ")";
                    s << ", CAM-EYE(" << toString( camera->getTarget() ) << ")";
                    s << ", CAM-ROT(" << toString( camera->getRotation() ) << ")";
                }

                device->setWindowCaption( irr::core::stringw( s.str().c_str() ).c_str() );
            }
        }
        else
        {
            device->yield();
        }

    }

    device->drop();
    return 0;
}

void
Game_load( std::string const & fileName )
{

}

void
Game_save( std::string const & fileName )
{

}

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
