/// (c) 2017 - 20190 Benjamin Hampe <benjaminhampe@gmx.de>

#ifndef PIONEERS3D_TYPES_FONT_HPP
#define PIONEERS3D_TYPES_FONT_HPP

#include <pioneers3d/types/Common.hpp>

namespace pioneers3d {

class Game_t;

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

irr::gui::IGUIFont* Game_getFont( Game_t* game, eFontType type );
void Game_clearFonts( Game_t* game );
void Game_createFonts( Game_t* game );
void Game_addFont( Game_t* game, eFontType type, std::string fileName, int32_t pxSize, bool aa = true, bool transparent = true );

struct Font_t
{
    eFontType Type;
    std::string FileName;
    int32_t Size;
    int32_t Style;
    irr::gui::CGUITTFont* Font;
};

typedef std::vector< Font_t > Fonts_t;

irr::core::dimension2du
Font_getPixelSize( irr::gui::IGUIFont* font, std::string txt );

// #ifdef USE_LIB_FREETYPE2
irr::gui::CGUITTFont*
Font_create(
        irr::gui::IGUIEnvironment* env,
        std::string fileName,
        int32_t pxSize,
        bool aa,
        bool transparent = true );
// #endif

void
Font_draw(
        irr::gui::IGUIFont* font,
        std::string txt,
        int32_t x,
        int32_t y,
        uint32_t color );

void
Font_draw(
        irr::gui::IGUIFont* font,
        std::string txt,
        irr::core::recti const & pos,
        uint32_t color );

struct Text_t
{
    std::string Text;
    uint32_t Color;
    irr::gui::IGUIFont * Font;
    Text_t() : Text( "X" ), Color( 0xFFFFFFFF ), Font( nullptr ) {}
    Text_t( std::string txt, uint32_t color, irr::gui::IGUIFont* font ) : Text( txt ), Color( color ), Font( font ) {}
    bool canDraw() const
    {
        if ( !Font ) return false;
        if ( Text.empty() ) return false;
        return true;
    }
};

void Text_draw( Text_t * txt, int32_t x, int32_t y );
void Text_draw( Text_t * txt, irr::core::recti const & pos );

} // end namespace pioneers3d

#endif // PIONEERS3D_TYPES_FONT_HPP
