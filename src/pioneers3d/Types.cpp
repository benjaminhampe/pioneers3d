#include <pioneers3d/Types.hpp>

namespace pioneers3d {

// =============================================================================================
GUI_Window_t::GUI_Window_t( irr::gui::IGUIEnvironment* env, irr::gui::IGUIElement* parent, int id, irr::core::recti const & pos )
    : irr::gui::BaseWindow( env, parent, id, pos )
{}

GUI_Window_t::~GUI_Window_t()
{}

bool
GUI_Window_t::OnEvent( irr::SEvent const & event )
{
    if ( event.EventType == irr::EET_GUI_EVENT )
    {
        irr::SEvent::SGUIEvent guiEvent = event.GUIEvent;

        if ( guiEvent.Caller == getCloseButton() &&
             guiEvent.EventType == irr::gui::EGET_BUTTON_CLICKED )
        {
            this->setVisible( false );
            return true;
        }

    }

    return irr::gui::BaseWindow::OnEvent( event );
}

// =============================================================================================

GUI_Card_t::GUI_Card_t(
        irr::gui::IGUIEnvironment* env,
        irr::gui::IGUIElement* parent,
        int id,
        irr::core::recti const & pos )
    : irr::gui::IGUIElement( irr::gui::EGUIET_ELEMENT, env, parent, id, pos )
    , m_Tex( nullptr )
{}

GUI_Card_t::~GUI_Card_t()
{}

void
GUI_Card_t::draw()
{
    // std::cout << "GUI_Card_t." << __FUNCTION__ << "(" << m_Title << "," << m_Value << "," << getTexNameA( m_Tex ) << "," << toString( AbsoluteRect ) << ")\n";

    if ( Environment && isVisible() )
    {
        irr::video::IVideoDriver* driver = Environment->getVideoDriver();
        if ( driver )
        {
            int b = 5;
            int x = AbsoluteRect.UpperLeftCorner.X;
            int y = AbsoluteRect.UpperLeftCorner.Y;
            int w = AbsoluteRect.getWidth();
            int h = AbsoluteRect.getHeight();
            int lineHeight = 15;
            irr::core::recti r_name  = mkRect( x+b, y+b, w-2*b, lineHeight);
            irr::core::recti r_image = mkRect( x+b, y+b+lineHeight, w-2*b, h - 3*b - 2*lineHeight );
            irr::core::recti r_value = mkRect( x+b, y+h-b-lineHeight, w-2*b, lineHeight );

            Text_draw( &m_Title, r_name );
            if ( m_Tex )
            {
                driver->draw2DImage( m_Tex, r_image, mkRect(0,0,m_Tex->getOriginalSize()), 0, 0, true );
            }
            Text_draw( &m_Value, r_value );

        }

    }

    irr::gui::IGUIElement::draw();
}

} // end namespace pioneers3d
