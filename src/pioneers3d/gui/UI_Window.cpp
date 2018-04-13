#include "UI_Window.hpp"

namespace pioneers3d {

GUI_Window_t*
GameUI_addWindow( Game_t * game, std::string const & title,
    irr::core::recti const & pos, irr::gui::IGUIEnvironment* env, irr::gui::IGUIElement* parent, int id )
{
    GUI_Window_t* win = new GUI_Window_t( env, parent, id, pos );
    win->setText( irr::core::stringw( title.c_str() ).c_str() );
    win->setDrawTitlebar( true );
    game->UI.Windows.emplace_back( win );
    return win;
}

} // end namespace pioneers3d


