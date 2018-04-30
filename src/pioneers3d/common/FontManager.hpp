#ifndef GAME_FONT_HPP
#define GAME_FONT_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

// ---------------------------------------------------------------------------------------
enum class eFontType : uint32_t
{
    DEFAULT = 0,
    CHAT_BG,
    CHAT,
    AWESOME,
    FPS_COUNTER,
    H1,
    H2,
    H3,
    SMALL,
};
// ---------------------------------------------------------------------------------------
struct Font_t
{
    eFontType Type;
    std::string FileName;
    int32_t Size;
    int32_t Style;
    irr::gui::CGUITTFont* Font;
};

typedef std::vector< Font_t > Fonts_t;

void Game_clearFonts( Game_t* game );
void Game_createFonts( Game_t* game );
void Game_addFont( Game_t* game, eFontType type, std::string fileName, int32_t pxSize, bool aa = true, bool transparent = true );
irr::gui::IGUIFont* Game_getFont( Game_t* game, eFontType type );

} // end namespace pioneers3d

#endif // GAME_FONT_HPP
