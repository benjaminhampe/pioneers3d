#ifndef UI_WINDOW_HPP
#define UI_WINDOW_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

GUI_Window_t*
GameUI_addWindow(
    Game_t * game,
    std::string const & title,
    irr::core::recti const & pos,
    irr::gui::IGUIEnvironment* env,
    irr::gui::IGUIElement* parent,
    int id = -1 );

} // end namespace pioneers3d


#endif // UI_WINDOW_HPP
