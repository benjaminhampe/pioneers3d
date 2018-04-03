#include "GameUtils.hpp"

namespace pioneers3d {

inline uint32_t getScreenWidth( irr::video::IVideoDriver* driver )
{
    if ( !driver ) return 0;
    return driver->getScreenSize().Width;
}

inline uint32_t getScreenHeight( irr::video::IVideoDriver* driver )
{
    if ( !driver ) return 0;
    return driver->getScreenSize().Height;
}

inline glm::ivec2 getScreenSize( irr::video::IVideoDriver* driver )
{
    if ( !driver ) return glm::ivec2(0,0);
    return glm::ivec2( driver->getScreenSize().Width, driver->getScreenSize().Height );
}

inline void saveTexture( irr::video::IVideoDriver* driver, irr::video::ITexture* tex, std::string const & fileName )
{
    if ( !driver ) return;
    irr::video::IImage* img = driver->createImage( tex, irr::core::position2di(0,0), tex->getOriginalSize() );
    if ( img )
    {
        driver->writeImageToFile( img, fileName.c_str() );
        img->drop();
    }
}


irr::video::ITexture*
GameBuilder_getRessourceCardTexture( Game_t* game, eTileType tileType, bool fg )
{
    eTexture texType = eTexture::UNKNOWN;
    if ( fg )
    {
             if ( tileType.has( eTileType::HOLZ) ) { texType = eTexture::CHIP_HOLZ; }
        else if ( tileType.has( eTileType::LEHM) ) { texType = eTexture::CHIP_LEHM; }
        else if ( tileType.has( eTileType::WEIZEN) ) { texType = eTexture::CHIP_WEIZEN; }
        else if ( tileType.has( eTileType::WOLLE) ) { texType = eTexture::CHIP_WOLLE; }
        else if ( tileType.has( eTileType::ERZ) ) { texType = eTexture::CHIP_ERZ; }
    }
    else
    {
             if ( tileType.has( eTileType::HOLZ) ) { texType = eTexture::LAND_HOLZ; }
        else if ( tileType.has( eTileType::LEHM) ) { texType = eTexture::LAND_LEHM; }
        else if ( tileType.has( eTileType::WEIZEN) ) { texType = eTexture::LAND_WEIZEN; }
        else if ( tileType.has( eTileType::WOLLE) ) { texType = eTexture::LAND_WOLLE; }
        else if ( tileType.has( eTileType::ERZ) ) { texType = eTexture::LAND_ERZ; }
    }

    return Game_getTexture( game, texType );
}

irr::video::ITexture*
GameBuilder_createRessourceCardTexture( Game_t* game, eTileType tileType, std::string const & fileName )
{
    assert( game );
    assert( game->Device );

    irr::IrrlichtDevice* device = game->Device;
    irr::video::IVideoDriver* driver = device->getVideoDriver();
    irr::scene::ISceneManager* smgr = device->getSceneManager();
    smgr->clear();

    AutoSceneNode* node = new AutoSceneNode( smgr, smgr->getRootSceneNode(), -1 );
    node->setPosition( glm::vec3( 0,0,0) );
    node->add( createRoundRect( glm::vec3(0,0,    0), glm::vec2(600,1000), glm::vec2(40,40), 9, tileType.getRessourceColor() ), true );
    node->add( createRoundRect( glm::vec3(0,0,-0.05f), glm::vec2(580,980), glm::vec2(40,40), 9, 0xFFFFFFFF ), true );
    AutoMeshBuffer* bg0 = createRoundRect( glm::vec3(0,0,-0.15f), glm::vec2(540,940), glm::vec2(40,40), 9, 0xFFFFFFFF );
    bg0->setTexture( 0, GameBuilder_getRessourceCardTexture( game, tileType, false ) );
    node->add( bg0, true );
    node->add( createCircle( glm::vec3(0,0,-0.2f), 190.f, 36, tileType.getRessourceColor() ), true );
    AutoMeshBuffer* bg1 = createCircle( glm::vec3(0,0,-0.25f), 180.f, 36, 0xFFFFFFFF );
    bg1->setTexture( 0, GameBuilder_getRessourceCardTexture( game, tileType, true ) );
    node->add( bg1, true );

    irr::video::ITexture* tex = driver->getTexture( "offscreen_0" );
    if ( !tex )
    {
        tex = driver->addRenderTargetTexture( irr::core::dimension2du(1024,1024), "offscreen_0", irr::video::ECF_A8R8G8B8 );
    }

    driver->setRenderTarget( tex, true, true, 0xFFFFFFFF );
    //driver->beginScene( true, true, 0xFFFFFFFF ); // 0x00000000 );

    irr::core::matrix4 m_WorldMatrix; m_WorldMatrix.makeIdentity();
    irr::core::matrix4 m_ViewMatrix; m_ViewMatrix.makeIdentity();
    irr::core::matrix4 m_ProjMatrix; m_ProjMatrix.buildProjectionMatrixOrthoLH( tex->getSize().Width, tex->getSize().Height, 1.0f, 10000.0f );
    driver->setTransform( irr::video::ETS_WORLD, m_WorldMatrix );
    driver->setTransform( irr::video::ETS_VIEW, m_ViewMatrix );
    driver->setTransform( irr::video::ETS_PROJECTION, m_ProjMatrix );
    node->render();
    //driver->endScene();
    driver->setRenderTarget( 0 );
    node->drop();
    smgr->clear();

    // std::stringstream s; s << "card_"<< tileType.getRessourceString() << ".jpg";

    irr::core::dimension2du texSize = tex->getOriginalSize();
    irr::video::IImage* img = driver->createImage( tex, irr::core::position2di(200,0), irr::core::dimension2du( texSize.Width-400, texSize.Height ) );
    if ( img )
    {
        driver->writeImageToFile( img, (game->MediaDir + fileName).c_str() );
        img->drop();
    }


    //rtt0->drop();
}


irr::video::ITexture*
Game_getTileTexture( Game_t* game, eTileType tileType )
{
    eTexture texType = eTexture::UNKNOWN;
    switch( tileType )
    {
        case eTileType::WASSER: texType = eTexture::WASSER; break;
        case eTileType::LAND_WUESTE: texType = eTexture::LAND_WUESTE; break;
        case eTileType::LAND_HOLZ: texType = eTexture::LAND_HOLZ; break;
        case eTileType::LAND_LEHM: texType = eTexture::LAND_LEHM; break;
        case eTileType::LAND_WEIZEN: texType = eTexture::LAND_WEIZEN; break;
        case eTileType::LAND_WOLLE: texType = eTexture::LAND_WOLLE; break;
        case eTileType::LAND_ERZ: texType = eTexture::LAND_ERZ; break;
        case eTileType::HAFEN_3zu1: texType = eTexture::HAFEN_3zu1; break;
        case eTileType::HAFEN_HOLZ: texType = eTexture::HAFEN_HOLZ; break;
        case eTileType::HAFEN_LEHM: texType = eTexture::HAFEN_LEHM; break;
        case eTileType::HAFEN_WEIZEN: texType = eTexture::HAFEN_WEIZEN; break;
        case eTileType::HAFEN_WOLLE: texType = eTexture::HAFEN_WOLLE; break;
        case eTileType::HAFEN_ERZ: texType = eTexture::HAFEN_ERZ; break;
        default: break;
    }

    return Game_getTexture( game, texType );
}


irr::video::ITexture*
Game_getChipTexture( Game_t* game, eTileType tileType, int diceValue )
{
    eTexture texType = eTexture::UNKNOWN;
    if ( tileType.isHafen() )
    {
        switch( tileType )
        {
            //case eTileType::HAFEN_3zu1: texType = eTexture::UNKNOWN; break;
            case eTileType::HAFEN_HOLZ: texType = eTexture::CHIP_HOLZ; break;
            case eTileType::HAFEN_LEHM: texType = eTexture::CHIP_LEHM; break;
            case eTileType::HAFEN_WEIZEN: texType = eTexture::CHIP_WEIZEN; break;
            case eTileType::HAFEN_WOLLE: texType = eTexture::CHIP_WOLLE; break;
            case eTileType::HAFEN_ERZ: texType = eTexture::CHIP_ERZ; break;
            default: break;
        }
    }
    else if ( tileType.isLand() )
    {
        switch( diceValue )
        {
            case 2: texType = eTexture::CHIP_2; break;
            case 3: texType = eTexture::CHIP_3; break;
            case 4: texType = eTexture::CHIP_4; break;
            case 5: texType = eTexture::CHIP_5; break;
            case 6: texType = eTexture::CHIP_6; break;
            //case 7: texType = eTexture::CHIP_7; break;
            case 8: texType = eTexture::CHIP_8; break;
            case 9: texType = eTexture::CHIP_9; break;
            case 10: texType = eTexture::CHIP_10; break;
            case 11: texType = eTexture::CHIP_11; break;
            case 12: texType = eTexture::CHIP_12; break;
            default: break;
        }
    }

    return Game_getTexture( game, texType );
}

/*
irr::video::ITexture*
Game_getCardTexture( Game_t* game, eTileType tileType )
{
    eTexture texType = eTexture::UNKNOWN;
    switch( tileType )
    {
        //case eTileType::WASSER: texType = eTexture::WASSER; break;
        //case eTileType::LAND_WUESTE: texType = eTexture::UNKNOWN; break;
        case eTileType::LAND_HOLZ: texType = eTexture::CARD_HOLZ; break;
        case eTileType::LAND_LEHM: texType = eTexture::CARD_LEHM; break;
        case eTileType::LAND_WEIZEN: texType = eTexture::CARD_WEIZEN; break;
        case eTileType::LAND_WOLLE: texType = eTexture::CARD_WOLLE; break;
        case eTileType::LAND_ERZ: texType = eTexture::CARD_ERZ; break;
        //case eTileType::HAFEN_3zu1: texType = eTexture::UNKNOWN; break;
        case eTileType::HAFEN_HOLZ: texType = eTexture::CARD_HOLZ; break;
        case eTileType::HAFEN_LEHM: texType = eTexture::CARD_LEHM; break;
        case eTileType::HAFEN_WEIZEN: texType = eTexture::CARD_WEIZEN; break;
        case eTileType::HAFEN_WOLLE: texType = eTexture::CARD_WOLLE; break;
        case eTileType::HAFEN_ERZ: texType = eTexture::CARD_ERZ; break;
        default: break;
    }

    return Game_getTexture( game, texType );
}
*/


void Game_clearTiles( Game_t* game )
{
    if (!game) return;
//    for ( size_t i = 0; i < game->Tiles.size(); ++i )
//    {
//        Tile_t * tile = game->Tiles[ i ];
//        if ( tile )
//        {
//            delete tile;
//        }
//    }
    game->Tiles.clear();
}

void Game_clearWaypoints( Game_t* game )
{
    if (!game) return;
//    for ( size_t i = 0; i < game->Waypoints.size(); ++i )
//    {
//        Waypoint_t * w = game->Waypoints[ i ];
//        if ( w )
//        {
//            delete w;
//        }
//    }
    game->Waypoints.clear();
}

void
Game_clear( Game_t* game )
{
    Game_clearWaypoints( game );
    Game_clearTiles( game );
}

irr::video::ITexture*
Game_getTexture( Game_t* game, eTexture type )
{
    irr::video::IVideoDriver * driver = game->Device->getVideoDriver();
    std::string const & mediaDir = game->MediaDir;

    if ( !driver )
    {
        return nullptr;
    }

    std::string tmp;

    switch( type )
    {
        case eTexture::UNKNOWN: tmp = "unknown.jpg"; break;
        case eTexture::SKYBOX_TOP: tmp = "skybox/ct/top.jpg"; break;
        case eTexture::SKYBOX_BOTTOM: tmp = "skybox/ct/bottom.jpg"; break;
        case eTexture::SKYBOX_LEFT: tmp = "skybox/ct/left.jpg"; break;
        case eTexture::SKYBOX_RIGHT: tmp = "skybox/ct/right.jpg"; break;
        case eTexture::SKYBOX_FRONT: tmp = "skybox/ct/front.jpg"; break;
        case eTexture::SKYBOX_BACK: tmp = "skybox/ct/back.jpg"; break;
        case eTexture::WASSER: tmp = "wasser.png"; break;
        case eTexture::LAND_WUESTE: tmp = "land_wueste.jpg"; break;
        case eTexture::LAND_HOLZ: tmp = "land_holz.png"; break;
        case eTexture::LAND_LEHM: tmp = "land_lehm.png"; break;
        case eTexture::LAND_WEIZEN: tmp = "land_weizen.jpg"; break;
        case eTexture::LAND_WOLLE: tmp = "land_wolle.jpg"; break;
        case eTexture::LAND_ERZ: tmp = "land_erz.jpg"; break;
        case eTexture::HAFEN_3zu1: tmp = "wasser.png"; break;
        case eTexture::HAFEN_HOLZ: tmp = "wasser.png"; break;
        case eTexture::HAFEN_LEHM: tmp = "wasser.png"; break;
        case eTexture::HAFEN_WEIZEN: tmp = "wasser.png"; break;
        case eTexture::HAFEN_WOLLE: tmp = "wasser.png"; break;
        case eTexture::HAFEN_ERZ: tmp = "wasser.png"; break;

        case eTexture::CHIP_HOLZ: tmp = "chip_holz.jpg"; break;
        case eTexture::CHIP_LEHM: tmp = "chip_lehm.png"; break;
        case eTexture::CHIP_WEIZEN: tmp = "chip_weizen.jpg"; break;
        case eTexture::CHIP_WOLLE: tmp = "chip_wolle.jpg"; break;
        case eTexture::CHIP_ERZ: tmp = "chip_erz.jpg"; break;

        case eTexture::CARD_HOLZ: tmp = "card_holz.jpg"; break;
        case eTexture::CARD_LEHM: tmp = "card_lehm.jpg"; break;
        case eTexture::CARD_WEIZEN: tmp = "card_weizen.jpg"; break;
        case eTexture::CARD_WOLLE: tmp = "card_wolle.jpg"; break;
        case eTexture::CARD_ERZ: tmp = "card_erz.jpg"; break;

        case eTexture::ROBBER: tmp = "unknown.png"; break;
        case eTexture::ROAD: tmp = "wasser.png"; break;

        case eTexture::DICE_1: tmp = "dice1.png"; break;
        case eTexture::DICE_2: tmp = "dice2.png"; break;
        case eTexture::DICE_3: tmp = "dice3.png"; break;
        case eTexture::DICE_4: tmp = "dice4.png"; break;
        case eTexture::DICE_5: tmp = "dice5.png"; break;
        case eTexture::DICE_6: tmp = "dice6.png"; break;

        case eTexture::CHIP_2: tmp = "chip02.png"; break;
        case eTexture::CHIP_3: tmp = "chip03.png"; break;
        case eTexture::CHIP_4: tmp = "chip04.png"; break;
        case eTexture::CHIP_5: tmp = "chip05.png"; break;
        case eTexture::CHIP_6: tmp = "chip06.png"; break;
        case eTexture::CHIP_8: tmp = "chip08.png"; break;
        case eTexture::CHIP_9: tmp = "chip09.png"; break;
        case eTexture::CHIP_10: tmp = "chip10.png"; break;
        case eTexture::CHIP_11: tmp = "chip11.png"; break;
        case eTexture::CHIP_12: tmp = "chip12.png"; break;

        // ICON_PLAYER_1,
        // ICON_PLAYER_2,
        // ICON_PLAYER_3,
        // ICON_PLAYER_4,
        // CARD_UNKNOWN,
        // CARD_HOLZ,
        // CARD_LEHM,
        // CARD_WEIZEN,
        // CARD_WOLLE,
        // CARD_ERZ,
        // EVTCARD_UNKNOWN,
        // EVTCARD_KNIGHT,
        // EVTCARD_VICTORY_POINT,
        // EVTCARD_INVENTION,
        // EVTCARD_FREE_BANK,
        // BONUS_UNKNOWN,
        // BONUS_LONGEST_ROAD,
        // BONUS_BIGGEST_ARMY,
        // BUY_EVENT_CARD,
        // PLAN_BG,
        // PLAN_STANDARD,
        // COUNT
        default: break;
    }

    if ( tmp.empty() )
    {
        return nullptr;
    }

    std::string fileName = mediaDir + tmp;

    // irr::video::ITexture* tex = Game_loadTextureFromFile( driver, fileName );

    driver->setTextureCreationFlag( irr::video::ETCF_ALWAYS_32_BIT, true );
    //driver->setTextureCreationFlag( irr::video::ETCF_CREATE_MIP_MAPS, false );

    irr::video::ITexture* tex = driver->getTexture( fileName.c_str() );

    if ( !tex )
    {
        std::cout << __FUNCTION__ << "(" << fileName << ") - Error.\n";
    }
    else
    {
        std::cout << __FUNCTION__ << "(" << fileName << ") - OK.\n";
    }

    return tex;

}


bool
Game_isCameraInput( Game_t * game )
{
    irr::IrrlichtDevice* device = game->Device;
    irr::scene::ICameraSceneNode* camera = device->getSceneManager()->getActiveCamera();
    if ( camera )
    {
        return camera->isInputReceiverEnabled();
    }
    else
    {
        return false;
    }
}

void
Game_toggleCameraInput( Game_t * game )
{
    irr::IrrlichtDevice* device = game->Device;
    irr::scene::ICameraSceneNode* camera = device->getSceneManager()->getActiveCamera();
    if ( camera )
    {
        camera->setInputReceiverEnabled( !camera->isInputReceiverEnabled() );
    }
}

void
Game_setCameraInput( Game_t * game, bool enable )
{
    irr::scene::ICameraSceneNode* camera = game->Device->getSceneManager()->getActiveCamera();
    if ( camera )
    {
        camera->setInputReceiverEnabled( enable );
    }
}


void
Game_createCardInfo( Game_t * game, irr::gui::IGUIElement* parent,
                        GUI_Card_t & out, const char* name, eTexture tex, int value, irr::core::recti const & pos )
{
    int x = pos.UpperLeftCorner.X;
    int y = pos.UpperLeftCorner.Y;
    int w = pos.getWidth();
    int h = pos.getHeight();
    std::cout << __FUNCTION__ << "(" << name << ")\n";
    irr::gui::IGUIEnvironment* guienv = game->Device->getGUIEnvironment();
    out.Name = guienv->addStaticText( irr::core::stringw( name ).c_str(), mkRect(x,y,w,10), true, false, parent, -1, false );
    out.Image = guienv->addImage( mkRect( x, y+10, w, h-20 ), parent, -1, L"CardImage", true );
    out.Image->setScaleImage( true );
    out.Image->setImage( Game_getTexture( game, tex ) );

    std::wstringstream s;
    s << value;
    out.Value = guienv->addStaticText( s.str().c_str(), mkRect( x, h-10, w, 10 ), true, false, parent, -1, false );
}

void
Game_createBank( Game_t * game, irr::gui::IGUIElement* parent,
                    GUI_CardBank_t & out, irr::core::recti const & pos )
{
    std::cout << __FUNCTION__ << "()\n";
    irr::IrrlichtDevice* device = game->Device;
    irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    irr::gui::IGUIWindow* win = guienv->addWindow( pos, false, L"Bank", parent );
    irr::core::recti rc = win->getClientRect();
    int w = rc.getWidth();
    int h = rc.getHeight();
    out.Window = win;
    int b = 5;
    int x = rc.UpperLeftCorner.X + b;
    int y = rc.UpperLeftCorner.Y + b;
    int dx = w/6;
    int dy = h-2*b;
    Game_createCardInfo( game, win, out.Holz, "Holz", eTexture::CARD_HOLZ, 1, mkRect(x,y,dx,dy) ); x += dx + b;
    Game_createCardInfo( game, win, out.Lehm, "Lehm", eTexture::CARD_LEHM, 2, mkRect(x,y,dx,dy) ); x += dx + b;
    Game_createCardInfo( game, win, out.Weizen, "Weizen", eTexture::CARD_WEIZEN, 3, mkRect(x,y,dx,dy) ); x += dx + b;
    Game_createCardInfo( game, win, out.Wolle, "Wolle", eTexture::CARD_WOLLE, 4, mkRect(x,y,dx,dy) ); x += dx + b;
    Game_createCardInfo( game, win, out.Erz, "Erz", eTexture::CARD_ERZ, 5, mkRect(x,y,dx,dy) ); x += dx + b;
}

void
GameUI_createPlayerInfo( Game_t * game, int player )
{
    std::cout << __FUNCTION__ << "(" << player << ")\n";
    irr::IrrlichtDevice* device = game->Device;
    irr::video::IVideoDriver* driver = device->getVideoDriver();
    irr::core::dimension2du screen = driver->getScreenSize();
    irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    irr::gui::IGUIWindow* win = guienv->addWindow( irr::core::recti( 10, 10, 600, 300 ), false, L"PlayerInfo", guienv->getRootGUIElement() );
    irr::core::recti clientRect = win->getClientRect();

    game->UI.PlayerInfo.Window = win;

    Game_createBank( game, win, game->UI.PlayerInfo.Cards, irr::core::recti( 10, 10, 500, 200 ) );

}

void
GameUI_createChatBox( Game_t * game, irr::core::recti const & pos )
{
    irr::IrrlichtDevice* device = game->Device;
    irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    irr::gui::IGUIElement* parent = guienv->getRootGUIElement();
    irr::gui::IGUIWindow* win = guienv->addWindow( pos, false, L"ChatBox:", parent );
    irr::core::recti rc = win->getClientRect();
    int x = rc.UpperLeftCorner.X;
    int y = rc.UpperLeftCorner.Y;
    int w = rc.getWidth();
    int h = rc.getHeight();
    int b = 5;
    game->UI.ChatBox.Window = win;
    game->UI.ChatBox.Input = guienv->addEditBox( L"Chat box", mkRect( x+b, y+b, w - 64 - 3*b, 32 ), true, win, -1 ); x += 110;
    game->UI.ChatBox.Send = guienv->addButton( mkRect( x+ w - 64 - 2*b, y+b, 64, 32 ), win, -1, L"Bank", L"Bank" ); x += 110;
    game->UI.ChatBox.LogBox = guienv->addStaticText( L"PLAYER (0) Benni: Log message", mkRect( x+b, y+32+2*b, w-2*b, h-32-3*b ), true, false, win, -1, false ); x += 110;
}

void
GameUI_createPlayerAction( Game_t * game, irr::core::recti const & pos )
{
    irr::IrrlichtDevice* device = game->Device;
    irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    irr::gui::IGUIElement* parent = guienv->getRootGUIElement();
    irr::gui::IGUIWindow* win = guienv->addWindow( pos, false, L"Player Action Menu | Player (0) Benni", parent );
    irr::core::recti rc = win->getClientRect();
    int x = rc.UpperLeftCorner.X;
    int y = rc.UpperLeftCorner.Y;
    game->UI.PlayerAction.Window = win;
    game->UI.PlayerAction.Dice = guienv->addButton( mkRect( x+10, y+5, 100, 80 ), win, -1, L"Dice", L"Dice" ); x += 110;
    game->UI.PlayerAction.Bank = guienv->addButton( mkRect( x+10, y+5, 100, 80 ), win, -1, L"Bank", L"Bank" ); x += 110;
    game->UI.PlayerAction.Trade = guienv->addButton( mkRect( x+10, y+5, 100, 80 ), win, -1, L"Trade", L"Trade" ); x += 110;
    game->UI.PlayerAction.BuyCard = guienv->addButton( mkRect( x+10, y+5, 100, 80 ), win, -1, L"Buy Card", L"Buy an event card" ); x += 110;
    game->UI.PlayerAction.BuyRoad = guienv->addButton( mkRect( x+10, y+5, 100, 80 ), win, -1, L"Buy Road", L"Buy a road" ); x += 110;
    game->UI.PlayerAction.BuySett = guienv->addButton( mkRect( x+10, y+5, 100, 80 ), win, -1, L"Buy Settlement", L"Buy a settlement" ); x += 110;
    game->UI.PlayerAction.BuyCity = guienv->addButton( mkRect( x+10, y+5, 100, 80 ), win, -1, L"Buy City", L"Buy a city" ); x += 110;
    game->UI.PlayerAction.EndRound = guienv->addButton( mkRect( x+10, y+5, 100, 80 ), win, -1, L"End Round", L"End round" ); x += 110;
}

void
GameUI_createMainMenuWindow( Game_t * game )
{
    std::cout << __FUNCTION__ << "()\n";

    irr::IrrlichtDevice* device = game->Device;
    irr::video::IVideoDriver* driver = device->getVideoDriver();
    //irr::scene::ISceneManager* smgr = device->getSceneManager();
    irr::core::dimension2du screen = driver->getScreenSize();
    irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    if ( !guienv )
    {
        std::cout << __FUNCTION__ << " :: ERROR: Invalid pointer to IGUIEnvironment\n";
        return;
    }

    irr::gui::IGUIWindow* win = guienv->addWindow( irr::core::recti( screen.Width/2 - 200, 50, screen.Width/2 + 200, 450 ), false, L"Game Settings", guienv->getRootGUIElement() );
    irr::core::recti clientRect = win->getClientRect();
    int bW = 200;
    int bH = 100;
    int x1 = (clientRect.getWidth() - bW) / 2;
    int x2 = (clientRect.getWidth() + bW) / 2;
    int y = 50;
    game->UI.MainMenu.Window = win;
    game->UI.MainMenu.Start = guienv->addButton( irr::core::recti( x1, y, x2, y+bH ), win, -1, L"Start Game", L"Starts a new game..." ); y += bH + 25;
    game->UI.MainMenu.Options = guienv->addButton( irr::core::recti( x1, y, x2, y+bH ), win, -1, L"Options", L"Enter game settings..." ); y += bH + 25;
    game->UI.MainMenu.Exit = guienv->addButton( irr::core::recti( x1, y, x2, y+bH ), win, -1, L"Exit Game", L"Exit game and program..." ); y += bH + 25;
}

} // end namespace pioneers3d


/*
const char* const s_xmlStandardTiles = {
R"(
<!-- Zeile -3: (4-tiles) -->
<tile type="HAFEN_LEHM" x="-2" y="-3" dice="0" a="3" />
<tile type="WASSER" 	x="-1" y="-3" dice="0" a="3" />
<tile type="HAFEN_3zu1" x="0" y="-3" dice="0" a="3" />
<tile type="WASSER" 	x="1" y="-3" dice="0" a="2" />

<!-- Zeile -2: (5-tiles) -->
<tile type="WASSER" 	 x="-2" y="-2" dice="0" a="4" />
<tile type="LAND_WEIZEN" x="-1" y="-2" dice="3" a="0" />
<tile type="LAND_WEIZEN" x="0" y="-2" dice="6" a="0" />
<tile type="LAND_ERZ" 	 x="1" y="-2" dice="11" a="0" />
<tile type="HAFEN_WEIZEN" x="2" y="-2" dice="0" a="1" />

<!-- Zeile -1: (6-tiles) -->
<tile type="HAFEN_3zu1" x="-3" y="-1" dice="0" a="3" />
<tile type="LAND_HOLZ" 	x="-2" y="-1" dice="3" a="0" />
<tile type="LAND_ERZ" 	x="-1" y="-1" dice="5" a="0" />
<tile type="LAND_LEHM" 	x="0" y="-1" dice="10" a="0" />
<tile type="LAND_HOLZ" 	x="1" y="-1" dice="11" a="0" />
<tile type="WASSER" 	x="2" y="-1" dice="0" a="2" />

<!-- Zeile 0: (7-tiles) -->
<tile type="WASSER" x="-3" y="0" dice="0" a="4" />
<tile type="LAND_WOLLE" x="-2" y="0" dice="9" a="0" />
<tile type="LAND_LEHM" x="-1" y="0" dice="8" a="0" />
<tile type="LAND_WUESTE" x="0" y="0" dice="0" a="0" />
<tile type="LAND_ERZ" x="1" y="0" dice="8" a="0" />
<tile type="LAND_WOLLE" x="2" y="0" dice="10" a="0" />
<tile type="HAFEN_3zu1" x="3" y="0" dice="0" a="1" />

<!-- Zeile +1: (6-tiles) -->
<tile type="HAFEN_HOLZ" x="-3" y="1" dice="0" a="4" />
<tile type="LAND_LEHM"  x="-2" y="1" dice="2" a="0" />
<tile type="LAND_HOLZ"  x="-1" y="1" dice="5" a="0" />
<tile type="LAND_WOLLE" x="0" y="1" dice="12" a="0" />
<tile type="LAND_WOLLE" x="1" y="1" dice="4" a="0" />
<tile type="WASSER" 	x="2" y="1" dice="0" a="1" />

<!-- Zeile 2: (5-tiles) -->
<tile type="LAND_WASSER" x="-2" y="2" dice="0" a="5" />
<tile type="LAND_WEIZEN" x="-1" y="2" dice="4" a="0" />
<tile type="LAND_HOLZ" 	 x="0" y="2" dice="6" a="0" />
<tile type="LAND_WEIZEN" x="1" y="2" dice="9" a="0" />
<tile type="HAFEN_3zu1"  x="2" y="2" dice="0" a="1" />

<!-- Zeile 3: (4-tiles) -->
<tile type="HAFEN_ERZ" 	x="-2" y="3" dice="0" a="5" />
<tile type="WASSER" 	x="-1" y="3" dice="0" a="0" />
<tile type="HAFEN_3zu1" x="0" y="3" dice="0" a="0" />
<tile type="WASSER" 	x="1" y="3" dice="0" a="0" />
)"
};
*/
