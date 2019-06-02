#include <pioneers3d/types/Texture.hpp>
#include <pioneers3d/types/Game.hpp>

namespace pioneers3d {

irr::video::ITexture*
Game_getTexture( Game_t * game, eTexture type )
{
    if ( !game )
    {
        std::cout << __FUNCTION__ << " [Error] :: Invalid pointer to Game\n";
        return nullptr;
    }
    if ( !game->Device )
    {
        std::cout << __FUNCTION__ << " [Error] :: Invalid pointer to IrrlichtDevice\n";
        return nullptr;
    }

    std::string const & mediaDir = game->MediaDir;
    irr::video::IVideoDriver * driver = game->Device->getVideoDriver();
    if ( !driver )
    {
        std::cout << __FUNCTION__ << " [Error] :: Invalid pointer to IVideoDriver\n";
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

        case eTexture::DICE_1: tmp = "dice/dice1.png"; break;
        case eTexture::DICE_2: tmp = "dice/dice2.png"; break;
        case eTexture::DICE_3: tmp = "dice/dice3.png"; break;
        case eTexture::DICE_4: tmp = "dice/dice4.png"; break;
        case eTexture::DICE_5: tmp = "dice/dice5.png"; break;
        case eTexture::DICE_6: tmp = "dice/dice6.png"; break;

        case eTexture::CHIP_W: tmp = "chips/waypoint_w.png"; break;
        case eTexture::CHIP_S: tmp = "chips/waypoint_s.png"; break;
        case eTexture::CHIP_HOLZ: tmp = "chips/chip_holz.jpg"; break;
        case eTexture::CHIP_LEHM: tmp = "chips/chip_lehm.png"; break;
        case eTexture::CHIP_WEIZEN: tmp = "chips/chip_weizen.jpg"; break;
        case eTexture::CHIP_WOLLE: tmp = "chips/chip_wolle.jpg"; break;
        case eTexture::CHIP_ERZ: tmp = "chips/chip_erz.jpg"; break;
        case eTexture::CHIP_2: tmp = "chips/chip02.png"; break;
        case eTexture::CHIP_3: tmp = "chips/chip03.png"; break;
        case eTexture::CHIP_4: tmp = "chips/chip04.png"; break;
        case eTexture::CHIP_5: tmp = "chips/chip05.png"; break;
        case eTexture::CHIP_6: tmp = "chips/chip06.png"; break;
        case eTexture::CHIP_8: tmp = "chips/chip08.png"; break;
        case eTexture::CHIP_9: tmp = "chips/chip09.png"; break;
        case eTexture::CHIP_10: tmp = "chips/chip10.png"; break;
        case eTexture::CHIP_11: tmp = "chips/chip11.png"; break;
        case eTexture::CHIP_12: tmp = "chips/chip12.png"; break;

        case eTexture::TILE_WASSER: tmp = "tiles/wasser.png"; break;
        case eTexture::TILE_WUESTE: tmp = "tiles/wueste.jpg"; break;
        case eTexture::TILE_HOLZ: tmp = "tiles/land_holz.png"; break;
        case eTexture::TILE_LEHM: tmp = "tiles/land_lehm.png"; break;
        case eTexture::TILE_WEIZEN: tmp = "tiles/land_weizen.jpg"; break;
        case eTexture::TILE_WOLLE: tmp = "tiles/land_wolle.jpg"; break;
        case eTexture::TILE_ERZ: tmp = "tiles/land_erz.jpg"; break;

        // Composed textures
        case eTexture::CARD_HOLZ:       tmp = "cards/card_holz.jpg"; break;
        case eTexture::CARD_LEHM:       tmp = "cards/card_lehm.jpg"; break;
        case eTexture::CARD_WEIZEN:     tmp = "cards/card_weizen.jpg"; break;
        case eTexture::CARD_WOLLE:      tmp = "cards/card_wolle.jpg"; break;
        case eTexture::CARD_ERZ:        tmp = "cards/card_erz.jpg"; break;
        case eTexture::CARD_EVENT:      tmp = "cards/card_event.png"; break;
        case eTexture::CARD_KNIGHT:     tmp = "cards/card_knight.png"; break;
        case eTexture::CARD_POINT:      tmp = "cards/card_point.png"; break;
        case eTexture::CARD_BONUS:      tmp = "cards/card_bonus.png"; break;
        case eTexture::CARD_BONUS_ARMY: tmp = "cards/card_bonus_army.png"; break;
        case eTexture::CARD_BONUS_ROAD: tmp = "cards/card_bonus_road.png"; break;
        case eTexture::STAT_ROAD:       tmp = "cards/stat_roads.png"; break;
        case eTexture::STAT_SETTLEMENT: tmp = "cards/stat_settlements.png"; break;
        case eTexture::STAT_CITY:       tmp = "cards/stat_cities.png"; break;

        case eTexture::ACTION_DICE:             tmp = "action/dice.png"; break;
        case eTexture::ACTION_PLACE_ROBBER:     tmp = "action/place_robber.png"; break;
        case eTexture::ACTION_ENDTURN:          tmp = "action/endturn.png"; break;
        case eTexture::ACTION_TRADE:            tmp = "action/trade.png"; break;
        case eTexture::ACTION_BANK:             tmp = "action/bank.png"; break;
        case eTexture::ACTION_PLAY_EVENT_CARD:  tmp = "action/play_event_card.png"; break;
        case eTexture::ACTION_BUY_EVENT_CARD:   tmp = "action/buy_event_card.png"; break;
        case eTexture::ACTION_BUY_ROAD:         tmp = "action/buy_road.png"; break;
        case eTexture::ACTION_BUY_SETTLEMENT:   tmp = "action/buy_settlement.png"; break;
        case eTexture::ACTION_BUY_CITY:         tmp = "action/buy_city.png"; break;

        case eTexture::TEX_ROBBER:          tmp = "raeuber/raeuber_tex.jpg"; break;
        case eTexture::TEX_ROAD: tmp = "tex_road.jpg"; break;

        case eTexture::PLAYER_ICON: tmp = "player/unknown.png"; break;
        case eTexture::PLAYER_ICON_1: tmp = "player_avatars/genghis.png"; break;
        case eTexture::PLAYER_ICON_2: tmp = "player_avatars/gandhi.png"; break;
        case eTexture::PLAYER_ICON_3: tmp = "player_avatars/catherine.png"; break;
        case eTexture::PLAYER_ICON_4: tmp = "player_avatars/hatshepsut.png"; break;
        default: break;
    }

    if ( tmp.empty() )
    {
        std::cout << __FUNCTION__ << " [Error] :: Empty filename\n";
        return nullptr;
    }

    std::string const fileName = mediaDir + tmp;

    driver->setTextureCreationFlag( irr::video::ETCF_ALWAYS_32_BIT, true );
    //driver->setTextureCreationFlag( irr::video::ETCF_CREATE_MIP_MAPS, false );

    irr::video::ITexture* tex = driver->getTexture( fileName.c_str() );

    if ( !tex )
    {
        std::cout << __FUNCTION__ << " [Error] :: Cannot get texture (" << fileName << ")\n";
        return nullptr;
    }

    return tex;

}

irr::video::ITexture*
Game_getDiceTexture( Game_t* game, int diceValue )
{
    switch( diceValue )
    {
        case 1: return Game_getTexture( game, eTexture::DICE_1 );
        case 2: return Game_getTexture( game, eTexture::DICE_2 );
        case 3: return Game_getTexture( game, eTexture::DICE_3 );
        case 4: return Game_getTexture( game, eTexture::DICE_4 );
        case 5: return Game_getTexture( game, eTexture::DICE_5 );
        case 6: return Game_getTexture( game, eTexture::DICE_6 );
        default: return Game_getTexture( game, eTexture::UNKNOWN );
    }
}

irr::video::ITexture*
Game_getPlayerTexture( Game_t* game, int player )
{
    switch( player )
    {
        case 1: return Game_getTexture( game, eTexture::PLAYER_ICON_1 );
        case 2: return Game_getTexture( game, eTexture::PLAYER_ICON_2 );
        case 3: return Game_getTexture( game, eTexture::PLAYER_ICON_3 );
        case 4: return Game_getTexture( game, eTexture::PLAYER_ICON_4 );
        default: return Game_getTexture( game, eTexture::PLAYER_ICON );
    }
}

irr::video::ITexture*
Game_getTileTexture( Game_t* game, TileType tileType )
{
    eTexture texType = eTexture::TILE_WASSER;
    switch( tileType )
    {
        case TileType::LAND_WUESTE: texType = eTexture::TILE_WUESTE; break;
        case TileType::LAND_HOLZ: texType = eTexture::TILE_HOLZ; break;
        case TileType::LAND_LEHM: texType = eTexture::TILE_LEHM; break;
        case TileType::LAND_WEIZEN: texType = eTexture::TILE_WEIZEN; break;
        case TileType::LAND_WOLLE: texType = eTexture::TILE_WOLLE; break;
        case TileType::LAND_ERZ: texType = eTexture::TILE_ERZ; break;
        default: break;
    }

    return Game_getTexture( game, texType );
}

irr::video::ITexture*
Game_getCardTexture( Game_t* game, TileType tileType )
{
    eTexture texType = eTexture::UNKNOWN;
    if ( tileType.contains( TileType::HOLZ ) ) texType = eTexture::CARD_HOLZ;
    if ( tileType.contains( TileType::LEHM ) ) texType = eTexture::CARD_LEHM;
    if ( tileType.contains( TileType::WEIZEN ) ) texType = eTexture::CARD_WEIZEN;
    if ( tileType.contains( TileType::WOLLE ) ) texType = eTexture::CARD_WOLLE;
    if ( tileType.contains( TileType::ERZ ) ) texType = eTexture::CARD_ERZ;

    return Game_getTexture( game, texType );
}

irr::video::ITexture*
Game_getChipTexture( Game_t* game, TileType tileType, int diceValue )
{
    eTexture texType = eTexture::UNKNOWN;
    if ( tileType.isHafen() )
    {
        switch( tileType )
        {
            //case TileType::HAFEN_3zu1: texType = eTexture::UNKNOWN; break;
            case TileType::HAFEN_HOLZ: texType = eTexture::CHIP_HOLZ; break;
            case TileType::HAFEN_LEHM: texType = eTexture::CHIP_LEHM; break;
            case TileType::HAFEN_WEIZEN: texType = eTexture::CHIP_WEIZEN; break;
            case TileType::HAFEN_WOLLE: texType = eTexture::CHIP_WOLLE; break;
            case TileType::HAFEN_ERZ: texType = eTexture::CHIP_ERZ; break;
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

irr::video::ITexture*
GameBuilder_getRessourceCardTexture( Game_t* game, TileType tt, bool fg )
{
    eTexture texType = eTexture::UNKNOWN;
    if ( fg )
    {
             if (tt.contains( TileType::HOLZ) ) { texType = eTexture::CHIP_HOLZ; }
        else if (tt.contains( TileType::LEHM) ) { texType = eTexture::CHIP_LEHM; }
        else if (tt.contains( TileType::WEIZEN) ) { texType = eTexture::CHIP_WEIZEN; }
        else if (tt.contains( TileType::WOLLE) ) { texType = eTexture::CHIP_WOLLE; }
        else if (tt.contains( TileType::ERZ) ) { texType = eTexture::CHIP_ERZ; }
    }
    else
    {
             if (tt.contains( TileType::HOLZ) ) { texType = eTexture::TILE_HOLZ; }
        else if (tt.contains( TileType::LEHM) ) { texType = eTexture::TILE_LEHM; }
        else if (tt.contains( TileType::WEIZEN) ) { texType = eTexture::TILE_WEIZEN; }
        else if (tt.contains( TileType::WOLLE) ) { texType = eTexture::TILE_WOLLE; }
        else if (tt.contains( TileType::ERZ) ) { texType = eTexture::TILE_ERZ; }
    }

    return Game_getTexture( game, texType );
}

irr::video::ITexture*
GameBuilder_createRessourceCardTexture( Game_t* game, TileType tileType, std::string const & fileName )
{
    assert( game );
    assert( game->Device );

    irr::IrrlichtDevice* device = game->Device;
    irr::video::IVideoDriver* driver = device->getVideoDriver();
    irr::scene::ISceneManager* smgr = device->getSceneManager();
    smgr->clear();

    AutoSceneNode* node = new AutoSceneNode( smgr, smgr->getRootSceneNode(), -1 );
    node->setPosition( irr::core::vector3df(0,0,0) );
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

    return tex;
}

} // end namespace pioneers3d
