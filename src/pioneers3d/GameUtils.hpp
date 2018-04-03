#ifndef GAMEUTILS_HPP
#define GAMEUTILS_HPP

#include <pioneers3d/Types.hpp>
#include <pioneers3d/EventReceiver.hpp>

namespace pioneers3d {

irr::video::ITexture* GameBuilder_createRessourceCardTexture( Game_t* game, eTileType tileType, std::string const & fileName );

irr::video::ITexture* Game_getTexture( Game_t* game, eTexture type );
irr::video::ITexture* Game_getChipTexture( Game_t* game, eTileType tileType, int diceValue );
irr::video::ITexture* Game_getTileTexture( Game_t* game, eTileType tileType );


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

#endif // GAMEUTILS_HPP
