#include <pioneers3d/types/Game.hpp>

namespace pioneers3d {

glm::ivec2
Game_getScreenSize( Game_t * game )
{
   if ( !game || !game->Device || !game->Device->getVideoDriver() ) return glm::ivec2(0,0);
   irr::core::dimension2du const uScreenSize = game->Device->getVideoDriver()->getScreenSize();
   return glm::ivec2( int32_t( uScreenSize.Width ), int32_t( uScreenSize.Height ) );
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
Game_createStandard( Game_t* game, irr::IrrlichtDevice* device, int argc, char** argv )
{
    srand( (unsigned int)time( nullptr ) );

    std::cout << "// ==========================================================\n";
    std::cout << __FUNCTION__ << "()\n";
    std::cout << "// ==========================================================\n";

    assert( device );
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
    game->Receiver = new GameEventReceiver( game );
    game->Camera = new CylinderCamera( game->Device->getSceneManager(), game->Device->getSceneManager()->getRootSceneNode() );

    std::cout << "ExeFile = " << game->ExeFile << "\n";
    std::cout << "ExeDir = " << game->ExeDir << "\n";
    std::cout << "MediaDir = " << game->MediaDir << "\n";
    std::cout << "ClearColor = " << game->ClearColor << "\n";
    std::cout << "Type = " << uint32_t( game->Type ) << "\n";
    std::cout << "State = " << uint32_t( game->State ) << "\n";
    std::cout << "Board = " << game->Board << "\n";

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

    std::cout << __FUNCTION__ << "\n[Begin]\n" << game->Board << "\n[End]\n";

    Game_start( game );
}


void
Game_start( Game_t * game )
{
    UI_setWindowVisible( game, eWindow::ALL, false );
    UI_setWindowVisible( game, eWindow::INIT_DICE, true );
    Board_hideWaypointsR( game );
    Board_hideWaypointsS( game );

    game->Round = 0;
    game->Player = 0;
    for ( int32_t i = 0; i < Player_getCount( game ); ++i )
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
                  // std::cout << "[Waypoint_R] " << *game->SelectedWaypointR << "\n";
                }
                if ( game->SelectedWaypointS )
                {
                  // std::cout << "[Waypoint_S] " << *game->SelectedWaypointS << "\n";
                }
                if ( game->SelectedTile )
                {
                  // std::cout << "[Tile] " << *game->SelectedTile << "\n";
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
