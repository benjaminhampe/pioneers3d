#ifndef UI_CARD_HPP
#define UI_CARD_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

void
GUI_Card_create(  irr::gui::IGUIEnvironment* env,
                irr::gui::IGUIElement* parent,
                irr::core::recti const & pos,
                GUI_Card_t & out,
                std::string name = "Unknown",
                irr::video::ITexture* tex = nullptr,
                std::string value = "" );

} // end namespace pioneers3d



#endif // UI_CARD_HPP
