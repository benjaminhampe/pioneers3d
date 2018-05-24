#ifndef PIONEERS3D_GAME_TEXTURE_HPP
#define PIONEERS3D_GAME_TEXTURE_HPP

#include <pioneers3d/data/Types.hpp>

namespace pioneers3d {

irr::video::ITexture* Game_getTexture( Game_t* game, eTexture type );
irr::video::ITexture* Game_getChipTexture( Game_t* game, eTileType tileType, int diceValue );
irr::video::ITexture* Game_getTileTexture( Game_t* game, eTileType tileType );
irr::video::ITexture* Game_getPlayerTexture( Game_t* game, int player );
irr::video::ITexture* Game_getDiceTexture( Game_t* game, int diceValue );
irr::video::ITexture* Game_getCardTexture( Game_t* game, eTileType tileType ); // get composed texture

irr::video::ITexture* GameBuilder_getRessourceCardTexture( Game_t* game, eTileType tileType, bool fg );
irr::video::ITexture* GameBuilder_createRessourceCardTexture( Game_t* game, eTileType tileType, std::string const & fileName );

// inline irr::video::ITexture* Dice_getTexture( Game_t* game, int diceValue ) { return Game_getDiceTexture( game, diceValue ); }

} // end namespace pioneers3d

#endif // PIONEERS3D_GAME_TEXTURE_HPP
