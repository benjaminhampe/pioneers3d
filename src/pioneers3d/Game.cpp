#include "Game.hpp"

#include <pioneers3d/Game_Logger.hpp>
#include <pioneers3d/Game_EventReceiver.hpp>
#include <pioneers3d/Game_Font.hpp>
#include <pioneers3d/Game_Texture.hpp>
#include <pioneers3d/Game_Chat.hpp>
#include <pioneers3d/Game_Tile.hpp>
#include <pioneers3d/Game_Waypoint.hpp>
#include <pioneers3d/Game_Player.hpp>
#include <pioneers3d/Game_Camera.hpp>
#include <pioneers3d/Game_Raeuber.hpp>
#include <pioneers3d/Game_UI.hpp>

namespace pioneers3d {

void
Game_clear( Game_t* game )
{
    clearWaypoints( game );
    clearTiles( game );
    clearPlayers( game );
}

void
Game_destroy( Game_t* game )
{
    Chat_destroy( game );
    Game_clearFonts( game );
}

void
Game_createStandard( Game_t* game )
{
    std::cout << "// ==========================================================\n";
    std::cout << __FUNCTION__ << "()\n";
    std::cout << "// ==========================================================\n";
    glm::ivec3 const desktopSize = getDesktopSize();
    std::cout << "DesktopSize.x = " << desktopSize.x << " px\n";
    std::cout << "DesktopSize.y = " << desktopSize.y << " px\n";
    std::cout << "DesktopSize.z = " << desktopSize.z << " bits\n";

    srand( (unsigned int)time(NULL) );

    irr::SIrrlichtCreationParameters cfg;
    cfg.DriverType = irr::video::EDT_OPENGL;
    cfg.WindowSize.Width = 1280; //1440; //desktopSize.x;
    cfg.WindowSize.Height = 800; //900; //desktopSize.y;
    cfg.AntiAlias = irr::video::EAAM_QUALITY;
    cfg.Bits = 32;
    cfg.Doublebuffer = true;
    cfg.Vsync = true;
    cfg.EventReceiver = nullptr;
    cfg.Fullscreen = false;
    cfg.Stencilbuffer = true;
    irr::IrrlichtDevice* device = irr::createDeviceEx( cfg );
    assert( device );
    std::cout << "// ==========================================================\n";
    std::cout << toXMLElement( cfg );
    std::cout << "// ==========================================================\n";
    device->setResizable( true );
    device->setWindowCaption( L"Pioneers3D (c) 2018 by Benjamin Hampe <benjaminhampe@gmx.de>" );
    irr::video::IVideoDriver* driver = device->getVideoDriver();
    irr::scene::ISceneManager* smgr = device->getSceneManager();
    irr::gui::IGUIEnvironment* env = device->getGUIEnvironment();
    //addFont( env, game->MediaDir + "fonts/FontAwesome.ttf", 8, true, true );
//    pioneers3d::Game_t game( device );
//    game.create();
//    game.save( "standard_test1.xml" );
//    game.load( "standard_test1.xml" );
//    game.save( "standard_test2.xml" );

    game->Device = device;
    game->MediaDir = "../../media/";
    game->ClearColor = irr::video::SColor( 255, 225, 225, 255 );
    game->Type = eGameType::STANDARD;
    game->State = eGameState::IDLE;
    game->TileSize = glm::vec3( 100.0f, 20.0f, 100.0f );
    game->TileCount = glm::ivec2( 7, 7 );
    //game->TileSelector = smgr->createMetaTriangleSelector();
    //game->WaypointSelector = smgr->createMetaTriangleSelector();
    game->Receiver = new EventReceiver( game );

    //GameBuilder_createRessourceCardTexture( game, eTileType::HOLZ, "card_holz.jpg" );
    //GameBuilder_createRessourceCardTexture( game, eTileType::LEHM, "card_lehm.jpg" );
    //GameBuilder_createRessourceCardTexture( game, eTileType::WEIZEN, "card_weizen.jpg" );
    //GameBuilder_createRessourceCardTexture( game, eTileType::WOLLE, "card_wolle.jpg" );
    //GameBuilder_createRessourceCardTexture( game, eTileType::ERZ, "card_erz.jpg" );

    Game_createFonts( game );
    Chat_create( game );
    createStandardTiles( game );
    createWaypoints( game, 10.0f, 5.00f, 13, false );
    createWaypoints( game, 7.5f, 3.33f, 13, true );
    Game_createRaeuber( game );
    createStandardPlayers( game );

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

    UI_create( game );

    std::cout << __FUNCTION__ << " [Begin] :: Debug\n";
    printWaypoints( game );
    printTextures( device->getVideoDriver() );
    std::cout << __FUNCTION__ << " [End] :: Debug\n";

    Game_start( game );
}


void
Game_start( Game_t * game )
{
    setWindowVisible( game, eWindow::ALL, false );
    setWindowVisible( game, eWindow::INIT_DICE, true );
    Waypoints_R_setVisible( game, false );
    Waypoints_S_setVisible( game, false );

    game->Round = 0;
    game->Player = 0;
    for ( uint32_t i = 0; i < getPlayerCount( game ); ++i )
    {
        Player_setAction( game, i, eAction::DICE );
    }

    UI_update( game );
    game->State = eGameState::IDLE;
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
    irr::core::dimension2du screenSize = driver->getScreenSize();
    uint64_t startTime = device->getTimer()->getRealTime();
    uint64_t currTime = device->getTimer()->getRealTime();
    uint64_t lastScreenUpdateTime = device->getTimer()->getRealTime();
    uint64_t lastWindowTitleUpdateTime = device->getTimer()->getRealTime();

    uint64_t updateScreenMs = 10;
    uint64_t updateWindowTitleMs = 1000 / 10;

    while (device && device->run())
    {
        currTime = device->getTimer()->getRealTime();

        if ( game->State == eGameState::PLACE_OBJECT )
        {
            if ( game->EnableCollisionDetectionForWaypoints )
            {
                game->SelectedWaypointR = Waypoint_mouseOver( game, true );
                game->SelectedWaypointS = Waypoint_mouseOver( game, false );
            }

            if ( game->EnableCollisionDetectionForTiles )
            {
                game->SelectedTile = findTileUnderMouse( game );
            }

            if ( game->PlaceObject )
            {
                irr::IrrlichtDevice* device = game->Device;
                irr::scene::ISceneManager* smgr = device->getSceneManager();
                irr::core::position2di mousePos = device->getCursorControl()->getPosition();
                irr::core::line3df screenRay = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates( mousePos, smgr->getActiveCamera() );
                irr::core::plane3df xzPlane( irr::core::vector3df(0,0,0), irr::core::vector3df(0,1,0) );
                irr::core::vector3df hitPosition;
                if ( xzPlane.getIntersectionWithLine( screenRay.start, screenRay.getVector(), hitPosition ) )
                {
                    game->PlaceObject->setPosition( hitPosition );
                }

            } // endif PlaceObject
        } // endif PLACE_OBJECT

        if ( device->isWindowActive() )
        {
            if ( currTime - lastScreenUpdateTime >= updateScreenMs )
            {
                lastScreenUpdateTime = currTime;

                if (driver)
                {
                    driver->beginScene( true, true, game->ClearColor );

                    screenSize = driver->getScreenSize();

                    if ( smgr )
                    {
                        smgr->drawAll();
                    }

                    if ( guienv )
                    {
                        guienv->drawAll();
                    }

                    int y = screenSize.Height/2;
                    int lineHeight = 50;

                    {
                        std::stringstream s; s << "FPS(" << std::to_string( driver->getFPS() ) << ")";
                        Font_draw( Game_getFont( game, eFontType::FPS_COUNTER ), s.str(), 10,10+y, 0xFFFFFF00 );
                        y += lineHeight;
                    }
                    {
                        std::stringstream s; s << "Round = " << game->Round;
                        Font_draw( Game_getFont( game, eFontType::FPS_COUNTER ), s.str(), 10,10+y, 0xFF00DF00 );
                        y += lineHeight;
                    }
                    {
                        std::stringstream s; s << "eGameState = " << toString( game->State );
                        Font_draw( Game_getFont( game, eFontType::FPS_COUNTER ), s.str(), 10,10+y, 0xFFFFDF00 );
                        y += lineHeight;
                    }
                    if ( game->State == eGameState::PLACE_OBJECT )
                    {
                        std::stringstream s; s << "ePlaceObjectType = " << toString( game->PlaceObjectType );
                        Font_draw( Game_getFont( game, eFontType::FPS_COUNTER ), s.str(), 10,10+y, 0xFFFFAF00 );
                        y += lineHeight;
                    }
                    {
                        std::stringstream s; s << "Player = " << ( game->Player+1 ) << ", " << Player_getName( game );
                        Font_draw( Game_getFont( game, eFontType::FPS_COUNTER ), s.str(), 10,10+y, 0xFFFF9520 );
                        y += lineHeight;
                    }

                    Chat_draw( game, screenSize.Width - 400, screenSize.Height/2 - 200 );

                    driver->endScene();
                }

            }

            if ( currTime - lastWindowTitleUpdateTime >= updateWindowTitleMs )
            {
                if ( game->SelectedWaypointR )
                {
                std::cout << "[Waypoint_R] " << Waypoint_toString( *game->SelectedWaypointR ) << "\n";
                }
                if ( game->SelectedWaypointS )
                {
                std::cout << "[Waypoint_S] " << Waypoint_toString( *game->SelectedWaypointS ) << "\n";
                }
                if ( game->SelectedTile )
                {
                std::cout << "[Tile] " << Tile_toString( *game->SelectedTile ) << "\n";
                }

                lastWindowTitleUpdateTime = currTime;

                std::stringstream s;
                s << "Pioneers3D ";
                s << "- FPS(" << driver->getFPS() << ")";
                s << ", WIN(" << toString( screenSize ) << ")";

                irr::scene::ICameraSceneNode* camera = smgr->getActiveCamera();
                if ( camera )
                {
                    s << ", CAM-POS(" << toString( camera->getAbsolutePosition() ) << ")";
                    s << ", CAM-EYE(" << toString( camera->getTarget() ) << ")";
                    s << ", CAM-ROT(" << toString( camera->getRotation() ) << ")";
                }

                s << ", POLY(" << device->getVideoDriver()->getPrimitiveCountDrawn() << ")";
                s << ", TEX(" << device->getVideoDriver()->getTextureCount() << ")";

                device->setWindowCaption( irr::core::stringw( s.str().c_str() ).c_str() );
            }
        }
        else
        {
            device->yield();
        }

    }
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
