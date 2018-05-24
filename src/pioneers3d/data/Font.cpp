#include "Font.hpp"

#define PRINT_FUNCTION_NAME { std::cout << __FUNCTION__ << ":" << __LINE__ << "()" << std::endl; }

namespace pioneers3d {

void
Game_addFont( Game_t* game, eFontType type, std::string fileName, int32_t pxSize, bool aa, bool transparent )
{
    PRINT_FUNCTION_NAME
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
    PRINT_FUNCTION_NAME
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
    PRINT_FUNCTION_NAME
    for ( size_t i = 0; i < game->Fonts.size(); ++i )
    {
        Font_t & font = game->Fonts[ i ];
        if ( font.Font )
        {
            font.Font->drop();
            //font.Font = nullptr;
        }
    }
    game->Fonts.clear();
}


} // end namespace pioneers3d
