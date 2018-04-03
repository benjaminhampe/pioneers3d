#include "EventReceiver.hpp"

#include "GameUtils.hpp"


namespace pioneers3d {

EventReceiver::EventReceiver( Game_t* game )
    : BaseEventReceiver( game->Device )
    , m_Game(game)
{
    std::cout << __FUNCTION__ << "()\n";
}

EventReceiver::~EventReceiver()
{
    std::cout << __FUNCTION__ << "()\n";
}

bool
EventReceiver::OnEvent( const irr::SEvent& event )
{
    if ( event.EventType == irr::EET_GUI_EVENT )
    {
        irr::SEvent::SGUIEvent const & guiEvent = event.GUIEvent;
        irr::gui::IGUIElement* caller = guiEvent.Caller;

//        assert( caller );
//        if ( !caller )
//        {
//            return false;
//        }

        if ( guiEvent.EventType == irr::gui::EGET_BUTTON_CLICKED )
        {
            if ( caller && m_Game )
            {
                if ( caller == m_Game->UI.MainMenu.Exit )
                {
                    m_Device->closeDevice();
                    return true;
                }
                if ( caller == m_Game->UI.MainMenu.Start )
                {
                    m_Game->UI.MainMenu.Window->setVisible( false );
                    return true;
                }
            }
        }
    }

    if ( event.EventType == irr::EET_KEY_INPUT_EVENT )
    {
        irr::SEvent::SKeyInput const & keyEvent = event.KeyInput;

        if ( keyEvent.Key == irr::KEY_ESCAPE && !keyEvent.PressedDown )
        {
            m_Game->UI.MainMenu.Window->setVisible( !m_Game->UI.MainMenu.Window->isVisible() );
            Game_setCameraInput( m_Game, !m_Game->UI.MainMenu.Window->isVisible() );
            return true;
        }
    }
    return BaseEventReceiver::OnEvent( event );
}


} // end namespace pioneers3d
