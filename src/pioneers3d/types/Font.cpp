#include <pioneers3d/types/Font.hpp>
#include <pioneers3d/types/Game.hpp>
#include <irrExt/CGUITTFont.hpp>

namespace pioneers3d {


void
Game_addFont( Game_t* game, eFontType type, std::string fileName, int32_t pxSize, bool aa, bool transparent )
{
    Font_t font;
    font.Font = Font_create( game->Device->getGUIEnvironment(), game->MediaDir + fileName, pxSize, aa, transparent );
    font.Type = type;
    font.Size = pxSize;
    game->Fonts.emplace_back( std::move( font ) );
}

irr::gui::IGUIFont*
Game_getFont( Game_t* game, eFontType type )
{
    //PRINT_FUNCTION_NAME
    for ( size_t i = 0; i < game->Fonts.size(); ++i )
    {
        Font_t const & font = game->Fonts[ i ];
        if ( font.Type == type )
        {
            return font.Font;
        }
    }
    return nullptr;
}

void
Game_createFonts( Game_t* game )
{
    game->Fonts.clear();
    Game_addFont( game, eFontType::DEFAULT, "fonts/DejaVuSansMono.ttf", 12, true, true );
    Game_addFont( game, eFontType::CHAT, "fonts/Garton.ttf", 24, true, false );
    Game_addFont( game, eFontType::FPS_COUNTER, "fonts/DejaVuSansMono.ttf", 32, true, true );
    Game_addFont( game, eFontType::H1, "fonts/caribbean.otf", 32, true, true );
    Game_addFont( game, eFontType::AWESOME, "fonts/FontAwesome.ttf", 64, true, true );
}

void
Game_clearFonts( Game_t* game )
{
    for ( size_t i = 0; i < game->Fonts.size(); ++i )
    {
        Font_t & font = game->Fonts[ i ];
        if ( font.Font )
        {
            font.Font->drop();
        }
    }
    game->Fonts.clear();
}



irr::core::dimension2du
Font_getPixelSize( irr::gui::IGUIFont* font, std::string txt )
{
    if ( !font ) { return irr::core::dimension2du(0,0); }
    irr::core::stringw const text( txt.c_str() );
    return font->getDimension( text.c_str() );
}

irr::gui::CGUITTFont*
Font_create(
        irr::gui::IGUIEnvironment* env,
        std::string fileName,
        int32_t pxSize,
        bool aa,
        bool transparent )
{
    return irr::gui::CGUITTFont::create( env, irr::core::stringw( fileName.c_str() ).c_str(), pxSize, aa, transparent );
}

void
Font_draw(
    irr::gui::IGUIFont* font,
    std::string txt,
    int32_t x,
    int32_t y,
    uint32_t color )
{
    if ( !font ) { return; }
    irr::core::stringw text( txt.c_str() );
    irr::core::dimension2du size = font->getDimension( text.c_str() );
    font->draw( text, mkRect( x, y, size.Width, size.Height ), color, false, false, 0 );
}

void
Font_draw(
    irr::gui::IGUIFont* font,
    std::string txt,
    irr::core::recti const & pos,
    uint32_t color )
{
    if ( !font )
    {
        std::cout << __FUNCTION__ << " :: Invalid pointer to Font\n";
        return;
    }

    irr::core::stringw tmp( txt.c_str() );
    irr::core::dimension2du txtSize = font->getDimension( tmp.c_str() );

    if ( txtSize.Width < 1 || txtSize.Height < 1 )
    {
        std::cout << __FUNCTION__ << " :: Invalid Font Size(" << txtSize << ")\n";
        return;
    }
    int w = pos.getWidth();
    int h = pos.getHeight();
    //int x = pos.UpperLeftCorner.X + ( w - txtSize.Width ) / 2;
    //int y = pos.UpperLeftCorner.Y + ( h - txtSize.Height ) / 2;

    int x = pos.UpperLeftCorner.X;
    int y = pos.UpperLeftCorner.Y;
    font->draw( tmp, mkRect( x-1, y-1, txtSize.Width+2, txtSize.Height+2 ), color, false, false, 0 );
}

void Font_drawBig( irr::gui::IGUIFont* font, std::string txt, int32_t x, int32_t y, uint32_t color )
{
    Font_draw( font, txt, x-1, y-1, color );
    Font_draw( font, txt, x,   y-1, color );
    Font_draw( font, txt, x+1, y-1, color );
    Font_draw( font, txt, x-1, y,   color );
    Font_draw( font, txt, x,   y,   color );
    Font_draw( font, txt, x+1, y,   color );
    Font_draw( font, txt, x-1, y+1, color );
    Font_draw( font, txt, x,   y+1, color );
    Font_draw( font, txt, x+1, y+1, color );
}

void Font_drawShadow( irr::gui::IGUIFont* font, std::string txt, int32_t x, int32_t y, uint32_t color )
{
    if (!font) return;
    uint32_t shadowColor = 0xFF202020;
    uint32_t highlightColor = 0xFFFFFFFF;
    Font_draw( font, txt, x,   y-1, shadowColor );
    Font_draw( font, txt, x+1, y-1, shadowColor );
    Font_draw( font, txt, x,   y+1, highlightColor );
    Font_draw( font, txt, x+1, y+1, highlightColor );
    Font_draw( font, txt, x,   y,   color );
    Font_draw( font, txt, x+1, y,   color );

//    Font_draw( font, item.Text, tx-1, ty, color );
//    Font_draw( font, item.Text, tx+2, ty, bgColor );
//    Font_draw( font, item.Text, tx-1, ty+1, bgColor );
//    Font_draw( font, item.Text, tx,   ty+1, item.Color );
//    Font_draw( font, item.Text, tx+1, ty+1, item.Color );
//    Font_draw( font, item.Text, tx+2, ty+1, bgColor );
//    Font_draw( font, item.Text, tx, ty+2, bgColor );
//    Font_draw( font, item.Text, tx+1, ty+2, bgColor );


}


void Text_draw( Text_t * p, int32_t x, int32_t y )
{
    if ( !p ) { return; }
    irr::core::dimension2du const txtSize = Font_getPixelSize( p->Font, p->Text );
    Font_draw( p->Font, p->Text, mkRect( x, y, txtSize.Width, txtSize.Height ), p->Color );
}

void Text_draw( Text_t * p, irr::core::recti const & pos )
{
    if ( !p ) { return; }
    irr::core::dimension2du txtSize = Font_getPixelSize( p->Font, p->Text );
    int32_t w = txtSize.Width;
    int32_t h = txtSize.Height;
    int32_t posW = pos.getWidth();
    int32_t posH = pos.getHeight();
    int32_t x = pos.UpperLeftCorner.X + (posW - w)/2;
    int32_t y = pos.UpperLeftCorner.Y + (posH - h)/2;
    Font_draw( p->Font, p->Text, mkRect( x, y, w, h ), p->Color );
}

} // end namespace pioneers3d
