#ifndef GAME_FONT_HPP
#define GAME_FONT_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

void Game_clearFonts( Game_t* game );
void Game_createFonts( Game_t* game );
void Game_addFont( Game_t* game, eFontType type, std::string fileName, int32_t pxSize, bool aa = true, bool transparent = true );
irr::gui::IGUIFont* Game_getFont( Game_t* game, eFontType type );

} // end namespace pioneers3d

#endif // GAME_FONT_HPP
