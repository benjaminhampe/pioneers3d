#ifndef PIONEERS3D_GAME_HPP
#define PIONEERS3D_GAME_HPP

#include <pioneers3d/GameUtils.hpp>
#include <pioneers3d/EventReceiver.hpp>

namespace pioneers3d {

inline int32_t safeMod( int32_t a, int32_t b )
{
    if ( a == 0 && b == 0)
    {
        return 0;
    }

    return std::abs( a ) % std::abs( b );
}

inline std::string
Game_t_toXML( Game_t* game )
{
    std::stringstream s;
    s   << "<game "
        << XML_ATTRIBUTE( "type", game->Type.toString() )
        << ">\n"
        << "\n"
        << "</game>";
    return s.str();
}

inline
void
Game_createStandard( Game_t* game, irr::IrrlichtDevice* device )
{
    std::cout << __FUNCTION__ << "()" << std::endl;

    assert( device );

    srand( (unsigned int)time(NULL) );

    device->setResizable( true );
    device->setWindowCaption( L"Pioneers3D (c) 2018 by Benjamin Hampe <benjaminhampe@gmx.de>" );

    game->Device = device;
    game->MediaDir = "../../media/";
    game->ClearColor = irr::video::SColor( 255, 225, 225, 255 );
    game->Type = eGameType::STANDARD;
    game->State = eGameState::GAME_INIT_BOARD;
    game->Receiver = new BaseEventReceiver( device );

    // createStandardBoard()
    game->TileSize = glm::vec3( 100.0f, 20.0f, 100.0f );
    game->TileCount = glm::ivec2( 7, 7 );

    irr::video::IVideoDriver* driver = device->getVideoDriver();
    irr::scene::ISceneManager* smgr = game->Device->getSceneManager();

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
        hexagon->MeshBuffer.Material.setTexture( 0, Game_getTexture( game, Game_getTextureTypeForTile( tileType ) ) );
        node->addMeshBuffer( hexagon, true );

        // chip cylinder for land tiles
        eTexture diceTexId = Game_getTextureTypeForLandChip( tile.DiceValue );
        if ( diceTexId != eTexture::UNKNOWN )
        {
            irr::video::ITexture* tex = Game_getTexture( game, diceTexId );

            AutoMeshBuffer* hull = createCylinderHull( glm::vec3(0.0f, 2.5f, 0.0f), 10.0f, 5.0f, 0xFFFFFFFF, 16, 1 );
            hull->MeshBuffer.Material.setTexture( 0, tex );
            node->addMeshBuffer( hull, true );

            AutoMeshBuffer* top = createCircleXZ( glm::vec3( 0.0f, 5.0f, 0.0f ), 10.0f, 16 );
            top->MeshBuffer.Material.setTexture( 0, tex );
            node->addMeshBuffer( top, true );
        }

        // chip cylinder + 2 roads for hafen tiles
        if ( Game_isHafen( tileType ) )
        {
            irr::video::ITexture* tex = Game_getTexture( game, Game_getTextureTypeForHafenChip( tileType ) );

            AutoMeshBuffer* hull = createCylinderHull( glm::vec3(0.0f, 2.5f, 0.0f), 10.0f, 5.0f, 0xFFFFFFFF, 16, 1 );
            hull->MeshBuffer.Material.setTexture( 0, tex );
            node->addMeshBuffer( hull, true );

            AutoMeshBuffer* top = createCircleXZ( glm::vec3( 0.0f, 5.0f, 0.0f ), 10.0f, 16 );
            top->MeshBuffer.Material.setTexture( 0, tex );
            node->addMeshBuffer( top, true );

/// @brief Create a box with one repeating texture over all 6 planes
            glm::vec3 M = tile.Pos;
            glm::vec3 A = getHexagonPoint( w, h, 0 );
            glm::vec3 B = getHexagonPoint( w, h, 1 );

            int k = tile.TexAngle60;
            node->addMeshBuffer( createRotatedBox( getHexagonPoint( w, h, k )*0.5f, glm::vec3(1,1,20), glm::vec3(0,k*60,0), 0xFFFFFFFF ), true );
            node->addMeshBuffer( createRotatedBox( getHexagonPoint( w, h, k+1 )*0.5f, glm::vec3(1,1,20), glm::vec3(0,(k+1)*60,0), 0xFFFFFFFF ), true );
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

    irr::core::dimension2du screenSize = driver->getScreenSize();
    irr::gui::IGUIEnvironment* guienv = game->Device->getGUIEnvironment();
    if ( !guienv )
    {
        std::cout << __FUNCTION__ << " :: ERROR: Invalid pointer to IGUIEnvironment\n";
    }
    else
    {
        irr::gui::IGUIWindow* win0 = guienv->addWindow( irr::core::recti( 100, 10, screenSize.Width - 200, 10 + 100 ), false, L"Game Settings", guienv->getRootGUIElement() );
        irr::gui::IGUIButton* btnStart = guienv->addButton( irr::core::recti( 10, 10, 100, 80 ), win0, -1, L"Start Game", L"Starts a new game..." );
        irr::gui::IGUIButton* btnEdit = guienv->addButton( irr::core::recti( 10, 10, 100, 80 ), win0, -1, L"Options", L"Enter game settings..." );
        irr::gui::IGUIButton* btnExit = guienv->addButton( irr::core::recti( 10, 10, 100, 80 ), win0, -1, L"Exit Game", L"Exit game and program..." );
    }

}

/// Start main loop:
inline int
Game_main( Game_t * game )
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

inline void
Game_load( std::string const & fileName )
{

}

inline void
Game_save( std::string const & fileName )
{

}

} // end namespace pioneers3d

#endif // PIONEERS3D_GAME_HPP
