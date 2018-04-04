#ifndef GAMEUTILS_HPP
#define GAMEUTILS_HPP

#include <pioneers3d/Types.hpp>
#include <pioneers3d/EventReceiver.hpp>

namespace pioneers3d {

irr::video::ITexture* GameBuilder_createRessourceCardTexture( Game_t* game, eTileType tileType, std::string const & fileName );

irr::video::ITexture* Game_getTexture( Game_t* game, eTexture type );
irr::video::ITexture* Game_getChipTexture( Game_t* game, eTileType tileType, int diceValue );
irr::video::ITexture* Game_getTileTexture( Game_t* game, eTileType tileType );

void Game_createWaypoints( Game_t * game );

bool Game_isHafen( eTileType tileType );
void Game_clearTiles( Game_t* game );
void Game_clearWaypoints( Game_t* game );
void Game_clear( Game_t* game );

bool Game_isCameraInput( Game_t * game );
void Game_toggleCameraInput( Game_t * game );
void Game_setCameraInput( Game_t * game, bool enable );


void GameUI_createMainMenuWindow( Game_t * game );
void GameUI_createPlayerAction( Game_t * game, irr::core::recti const & pos );
void GameUI_createPlayerInfo( Game_t * game, int player );
void GameUI_createChatBox( Game_t * game, irr::core::recti const & pos );

} // end namespace pioneers3d

inline uint32_t
getScreenWidth( irr::video::IVideoDriver* driver )
{
    if ( !driver ) return 0;
    return driver->getScreenSize().Width;
}

inline uint32_t
getScreenHeight( irr::video::IVideoDriver* driver )
{
    if ( !driver ) return 0;
    return driver->getScreenSize().Height;
}

inline glm::ivec2
getScreenSize( irr::video::IVideoDriver* driver )
{
    if ( !driver ) return glm::ivec2(0,0);
    return glm::ivec2( driver->getScreenSize().Width, driver->getScreenSize().Height );
}

inline void
saveTexture( irr::video::IVideoDriver* driver, irr::video::ITexture* tex, std::string const & fileName )
{
    if ( !driver ) return;
    irr::video::IImage* img = driver->createImage( tex, irr::core::position2di(0,0), tex->getOriginalSize() );
    if ( img )
    {
        driver->writeImageToFile( img, fileName.c_str() );
        img->drop();
    }
}

#endif // GAMEUTILS_HPP
