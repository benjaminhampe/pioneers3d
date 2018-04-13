#include "UI_Card.hpp"
#include <pioneers3d/Game_Texture.hpp>

namespace pioneers3d {

/*
void
CardUI_create( irr::gui::IGUIEnvironment* env,
                irr::gui::IGUIElement* parent,
                irr::core::recti const & pos,
                GUI_Card_t & out,
                std::string name,
                irr::video::ITexture* tex,
                std::string value )
{
    std::cout << __FUNCTION__ << "(" << name << "," << value << "," << getTexNameA( tex ) << "," << toString( pos ) << ")\n";
    int b = 5;
    int x = pos.UpperLeftCorner.X;
    int y = pos.UpperLeftCorner.Y;
    int w = pos.getWidth();
    int h = pos.getHeight();
    irr::core::recti r_label = mkRect( x, y,          w, 15);
    irr::core::recti r_image = mkRect( x, y+10+b, w, h-2*b-2*15 );
    irr::core::recti r_value = mkRect( x, y+h-10, w, 15 );

    out.Name = env->addStaticText( irr::core::stringw( name.c_str() ).c_str(), r_label, true, false, parent, -1, false );
    out.Name->setDrawBorder( false );
    out.Name->setAlignment( irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER );
    out.Image = createGUIImage( env, parent, r_image, tex );
    out.Value = env->addStaticText( irr::core::stringw( value.c_str() ).c_str(), r_value, true, false, parent, -1, false );
    out.Value->setDrawBorder( false );
    out.Value->setAlignment( irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER );
}
*/

} // end namespace pioneers3d


