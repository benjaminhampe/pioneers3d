#ifndef GAMEUTILS_HPP
#define GAMEUTILS_HPP

#include <pioneers3d/Types.hpp>
#include <pioneers3d/EventReceiver.hpp>

namespace pioneers3d {

eTexture Game_getTextureTypeForTile( eTileType tileType );
eTexture Game_getTextureTypeForHafenChip( eTileType tileType );
eTexture Game_getTextureTypeForLandChip( int diceValue );
bool Game_isHafen( eTileType tileType ) ;
void Game_clearTiles( Game_t* game );
void Game_clearWaypoints( Game_t* game );
void Game_clear( Game_t* game );

irr::video::ITexture* Game_getTexture( Game_t* game, eTexture type );

} // end namespace pioneers3d

#endif // GAMEUTILS_HPP
