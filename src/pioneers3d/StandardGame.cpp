#include <pioneers3d/StandardGame.hpp>
#include <pioneers3d/types/CylinderCamera.hpp>
#include <pioneers3d/types/Texture.hpp>

namespace pioneers3d {

EventReceiver::EventReceiver( Game_t* game )
    : irrExt::BaseEventReceiver( game->Device )
    , m_Game( game )
{
    std::cout << __FUNCTION__ << "()\n";
}

EventReceiver::~EventReceiver()
{
    std::cout << __FUNCTION__ << "()\n";
}

bool
EventReceiver::OnEvent( const irr::SEvent& event )
{
    if ( event.EventType == irr::EET_KEY_INPUT_EVENT )
    {
        irr::SEvent::SKeyInput const & keyEvent = event.KeyInput;
#ifdef USE_IRRLICHT
        if ( keyEvent.Key == irr::KEY_ESCAPE && !keyEvent.PressedDown )
#else
        if ( keyEvent.Key == irr::IRR_KEY_ESCAPE && !keyEvent.PressedDown )
#endif
        {
            if ( m_Game->State == GameState::NOT_RUNNING || m_Game->State == GameState::IDLE )
            {
                m_Game->UI.Menu.Window->setVisible( !m_Game->UI.Menu.Window->isVisible() );
                Game_setCameraInput( m_Game, !m_Game->UI.Menu.Window->isVisible() );
            }
            else
            {
                if ( m_Game->State == GameState::PLACE_OBJECT )
                {
                    Action_Abort( m_Game );
                }
            }
            return true;
        }
    }


    if ( event.EventType == irr::EET_MOUSE_INPUT_EVENT )
    {
        irr::SEvent::SMouseInput const & mouseEvent = event.MouseInput;

        if ( mouseEvent.Event == irr::EMIE_MOUSE_MOVED )
        {
            if ( m_Game->State == GameState::PLACE_OBJECT &&
                 m_Game->PlaceObject &&
                 m_Game->PlaceObjectType == ePlaceObjectType::ROAD &&
                 m_Game->SelectedWaypointR )
            {
                m_Game->PlaceObject->setRotation( irr::core::vector3df( 0, m_Game->SelectedWaypointR->Angle, 0 ) );
            }
        }

        if ( mouseEvent.Event == irr::EMIE_LMOUSE_LEFT_UP )
        {
            if ( m_Game->State == GameState::PLACE_OBJECT )
            {
                if ( m_Game->PlaceObjectType == ePlaceObjectType::ROBBER )
                {
//                    Waypoint_t * waypoint = m_Game->SelectedWaypointRoad;
//                    if ( waypoint )
//                    {
//                        m_Game->PlaceSceneNode->setPosition( toVec3df( waypoint->Pos ) );
//                        waypoint->Owner = getPlayer( m_Game, m_Game->Player );

//                        m_Game->State = GameState::IDLE;
//                    }
                }

                if ( m_Game->PlaceObjectType == ePlaceObjectType::ROAD )
                {
                    Waypoint_t * w = m_Game->SelectedWaypointR;
                    if ( w )
                    {
                        Player_addRoad( m_Game, w );
                        m_Game->State = GameState::IDLE;
                    }

                }

                if ( m_Game->PlaceObjectType == ePlaceObjectType::SETTLEMENT )
                {
                    Waypoint_t * w = m_Game->SelectedWaypointS;
                    if ( w )
                    {
                        Player_addSettlement( m_Game, w );
                        m_Game->State = GameState::IDLE;
                    }
                }
            }
        }
    }

    if ( m_Game->Camera &&
         m_Game->Camera->OnEvent( event ) )
    {
        return true;
    }

    if ( event.EventType == irr::EET_GUI_EVENT )
    {
        irr::SEvent::SGUIEvent const & guiEvent = event.GUIEvent;
        irr::gui::IGUIElement* caller = guiEvent.Caller;
        //irr::gui::IGUIEnvironment* env = m_Device->getGUIEnvironment();

        if ( guiEvent.EventType == irr::gui::EGET_BUTTON_CLICKED )
        {
            if ( caller && m_Game )
            {
                if ( caller == m_Game->UI.Menu.Exit )
                {
                    if ( m_Game->Device )
                    {
                        irr::scene::ICameraSceneNode* camera = m_Game->Device->getSceneManager()->getActiveCamera();
                        if ( camera )
                        {
                            camera->setInputReceiverEnabled( false );
                        }

                        m_Device->closeDevice();
                        m_Device->drop();
                        m_Device = nullptr;

                        Game_destroy( m_Game );
                    }
                    return true;
                }

                if ( caller == m_Game->UI.Menu.Start )
                {
                    Game_start( m_Game );
                    return true;
                }
            }
        }
    }

    if ( UI_onEvent( m_Game, event ) )
    {
        return true;
    }

    return irrExt::BaseEventReceiver::OnEvent( event );
}

void
Game_clear( Game_t* game )
{
    Board_clear( game );
    clearPlayers( game );
}

void
Game_destroy( Game_t* game )
{
    Chat_destroy( game );
    Game_clearFonts( game );
}

void
Game_createStandard( Game_t* game, int argc, char** argv )
{
    std::cout << "// ==========================================================\n";
    std::cout << __FUNCTION__ << "()\n";
    std::cout << "// ==========================================================\n";
    glm::ivec3 const desktopSize = getDesktopSize();
    std::cout << "DesktopSize.x = " << desktopSize.x << " px\n";
    std::cout << "DesktopSize.y = " << desktopSize.y << " px\n";
    std::cout << "DesktopSize.z = " << desktopSize.z << " bits\n";

    srand( (unsigned int)time( nullptr ) );

    irr::SIrrlichtCreationParameters cfg;
    cfg.DriverType = irr::video::EDT_OPENGL;
    cfg.WindowSize.Width = 1280; //1440; //desktopSize.x;
    cfg.WindowSize.Height = 800; //900; //desktopSize.y;
    cfg.AntiAlias = irr::video::EAAM_QUALITY;
    cfg.Bits = 32;
    cfg.Doublebuffer = false;
    cfg.Vsync = false;
    cfg.EventReceiver = nullptr;
    cfg.Fullscreen = false;
    cfg.ZBufferBits = 24;
    cfg.Stencilbuffer = true;
    irr::IrrlichtDevice* device = irr::createDeviceEx( cfg );
    assert( device );
//    std::cout << "// ==========================================================\n";
//    std::cout << toXMLElement( cfg );
//    std::cout << "// ==========================================================\n";
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

    game->ExeFile = argv[0];
    game->ExeDir = argv[0];
    game->Device = device;
    game->MediaDir = "../../media/";
    game->ClearColor = irr::video::SColor( 255, 225, 225, 255 );
    game->Type = GameType::STANDARD;
    game->State = GameState::IDLE;
    game->Board.TileSize = glm::vec3( 100.0f, 20.0f, 100.0f );
    game->Board.TileCount = glm::ivec2( 7, 7 );
    //game->TileSelector = smgr->createMetaTriangleSelector();
    //game->WaypointSelector = smgr->createMetaTriangleSelector();
    game->Receiver = new EventReceiver( game );
    game->Camera = new CylinderCamera( game->Device->getSceneManager(), game->Device->getSceneManager()->getRootSceneNode() );

    std::cout << "ExeFile = " << game->ExeFile << "\n";
    std::cout << "ExeDir = " << game->ExeDir << "\n";
    std::cout << "MediaDir = " << game->MediaDir << "\n";
    std::cout << "ClearColor = " << game->ClearColor << "\n";
    std::cout << "Type = " << uint32_t( game->Type ) << "\n";
    std::cout << "State = " << uint32_t( game->State ) << "\n";
    std::cout << "Board.TileSize = " << game->Board.TileSize << "\n";
    std::cout << "Board.TileCount = " << game->Board.TileCount << "\n";

    //GameBuilder_createRessourceCardTexture( game, eTileType::HOLZ, "card_holz.jpg" );
    //GameBuilder_createRessourceCardTexture( game, eTileType::LEHM, "card_lehm.jpg" );
    //GameBuilder_createRessourceCardTexture( game, eTileType::WEIZEN, "card_weizen.jpg" );
    //GameBuilder_createRessourceCardTexture( game, eTileType::WOLLE, "card_wolle.jpg" );
    //GameBuilder_createRessourceCardTexture( game, eTileType::ERZ, "card_erz.jpg" );

    Game_createFonts( game );
    Chat_create( game );
    Board_create( game );
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
    Board_printWaypoints( game );
    //printTextures( device->getVideoDriver() );
    std::cout << __FUNCTION__ << " [End] :: Debug\n";

    Game_start( game );
}


void
Game_start( Game_t * game )
{
    setWindowVisible( game, eWindow::ALL, false );
    setWindowVisible( game, eWindow::INIT_DICE, true );
    Board_hideWaypointsR( game );
    Board_hideWaypointsS( game );

    game->Round = 0;
    game->Player = 0;
    for ( uint32_t i = 0; i < getPlayerCount( game ); ++i )
    {
        Player_setAction( game, i, eAction::DICE );
    }

    UI_update( game );
    game->State = GameState::IDLE;
}


/// Start main loop:
int
Game_exec( Game_t * game )
{
    assert( game );
   assert( game->Device );

   // locals
   irr::IrrlichtDevice* device = game->Device;
    irr::video::IVideoDriver* driver = device->getVideoDriver();
    irr::scene::ISceneManager* smgr = device->getSceneManager();
    irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    irr::core::dimension2du screenSize = driver->getScreenSize();

   // locals
    uint64_t startTime = device->getTimer()->getRealTime();
    uint64_t currTime = device->getTimer()->getRealTime();
    uint64_t lastScreenUpdateTime = device->getTimer()->getRealTime();
    uint64_t lastWindowTitleUpdateTime = device->getTimer()->getRealTime();
    uint64_t updateScreenMs = 10;
    uint64_t updateWindowTitleMs = 1000 / 10;

   // main loop:
    while (device && device->run())
    {
        currTime = device->getTimer()->getRealTime();

        if ( game->State == GameState::PLACE_OBJECT )
        {
            if ( game->EnableCollisionDetectionForWaypoints )
            {
                game->SelectedWaypointR = Board_isMouseOverWaypointR( game );
                game->SelectedWaypointS = Board_isMouseOverWaypointS( game );
            }

            if ( game->EnableCollisionDetectionForTiles )
            {
                game->SelectedTile = Board_isMouseOverTile( game );
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
                        std::stringstream s; s << "GameState = " << game->State;
                        Font_draw( Game_getFont( game, eFontType::FPS_COUNTER ), s.str(), 10,10+y, 0xFFFFDF00 );
                        y += lineHeight;
                    }
                    if ( game->State == GameState::PLACE_OBJECT )
                    {
                        std::stringstream s; s << "ePlaceObjectType = " << game->PlaceObjectType;
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
                std::cout << "[Waypoint_R] " << game->SelectedWaypointR->toString() << "\n";
                }
                if ( game->SelectedWaypointS )
                {
                std::cout << "[Waypoint_S] " << game->SelectedWaypointS->toString() << "\n";
                }
                if ( game->SelectedTile )
                {
                std::cout << "[Tile] " << game->SelectedTile->toString() << "\n";
                }

                lastWindowTitleUpdateTime = currTime;

                std::stringstream s;
                s << "Pioneers3D ";
                s << "- FPS(" << driver->getFPS() << ")";
                s << ", WIN(" << screenSize << ")";

                irr::scene::ICameraSceneNode* camera = smgr->getActiveCamera();
                if ( camera )
                {
                    s << ", CAM-POS(" << camera->getAbsolutePosition() << ")";
                    s << ", CAM-EYE(" << camera->getTarget() << ")";
                    s << ", CAM-ROT(" << camera->getRotation() << ")";
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

Game_t::Game_t( irr::IrrlichtDevice* device )
    : Device( device)
    , ClearColor( 255, 225, 225, 255 )
    , Type( eGameType::STANDARD )
    , State( GameState::GAME_INIT_BOARD )
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
