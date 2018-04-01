#include "GameUtils.hpp"

namespace pioneers3d {

eTexture
Game_getTextureTypeForTile( eTileType tileType )
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

    return texType;
}

eTexture
Game_getTextureTypeForHafenChip( eTileType tileType )
{
    eTexture texType = eTexture::UNKNOWN;
    switch( tileType )
    {
        case eTileType::WASSER: texType = eTexture::WASSER; break;
        case eTileType::HAFEN_3zu1: texType = eTexture::UNKNOWN; break;
        case eTileType::HAFEN_HOLZ: texType = eTexture::CARD_HOLZ; break;
        case eTileType::HAFEN_LEHM: texType = eTexture::CARD_LEHM; break;
        case eTileType::HAFEN_WEIZEN: texType = eTexture::CARD_WEIZEN; break;
        case eTileType::HAFEN_WOLLE: texType = eTexture::CARD_WOLLE; break;
        case eTileType::HAFEN_ERZ: texType = eTexture::CARD_ERZ; break;
        default: break;
    }
    return texType;
}

eTexture
Game_getTextureTypeForLandChip( int diceValue )
{
    eTexture texType = eTexture::UNKNOWN;
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

    return texType;
}
bool
Game_isHafen( eTileType tileType )
{
    bool hafen = false;
    switch( tileType )
    {
        case eTileType::HAFEN_3zu1: hafen=true; break;
        case eTileType::HAFEN_HOLZ: hafen=true; break;
        case eTileType::HAFEN_LEHM: hafen=true; break;
        case eTileType::HAFEN_WEIZEN: hafen=true; break;
        case eTileType::HAFEN_WOLLE: hafen=true; break;
        case eTileType::HAFEN_ERZ: hafen=true; break;
        default: break;
    }

    return hafen;
}



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

        case eTexture::CARD_HOLZ: tmp = "card_holz.jpg"; break;
        case eTexture::CARD_LEHM: tmp = "card_lehm.png"; break;
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
