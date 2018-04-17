#include "Game_EventReceiver.hpp"

#include <pioneers3d/Game_Logger.hpp>
#include <pioneers3d/Game_Font.hpp>
#include <pioneers3d/Game_Camera.hpp>
#include <pioneers3d/Game_Texture.hpp>
#include <pioneers3d/Game_Action.hpp>
#include <pioneers3d/Game_Action.hpp>
#include <pioneers3d/Game.hpp>

namespace pioneers3d {

EventReceiver::EventReceiver( Game_t* game )
    : BaseEventReceiver( game->Device )
    , m_Game( game )
    , m_Camera( game->Device->getSceneManager(), game->Device->getSceneManager()->getRootSceneNode() )
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
    if ( event.EventType == irr::EET_KEY_INPUT_EVENT )
    {
        irr::SEvent::SKeyInput const & keyEvent = event.KeyInput;

        if ( keyEvent.Key == irr::KEY_ESCAPE && !keyEvent.PressedDown )
        {
            m_Game->UI.Menu.Window->setVisible( !m_Game->UI.Menu.Window->isVisible() );
            Game_setCameraInput( m_Game, !m_Game->UI.Menu.Window->isVisible() );
            return true;
        }
    }

    if ( m_Camera.OnEvent( event ) )
    {
        return true;
    }

    if ( event.EventType == irr::EET_GUI_EVENT )
    {
        irr::SEvent::SGUIEvent const & guiEvent = event.GUIEvent;
        irr::gui::IGUIElement* caller = guiEvent.Caller;
        irr::gui::IGUIEnvironment* env = m_Device->getGUIEnvironment();

        if ( guiEvent.EventType == irr::gui::EGET_BUTTON_CLICKED )
        {
            if ( caller && m_Game )
            {
                if ( caller == m_Game->UI.Menu.Exit )
                {
                    if ( m_Device )
                    {
                        irr::scene::ICameraSceneNode* camera = m_Device->getSceneManager()->getActiveCamera();
                        if ( camera )
                        {
                            camera->setInputReceiverEnabled( false );
                        }

                        m_Device->closeDevice();
                        m_Device->drop();
                        m_Device = nullptr;

                        Game_destroy( m_Game );
                    }
                    return true;
                }
                if ( caller == m_Game->UI.Menu.Start )
                {
                    Game_start( m_Game );
                    return true;
                }
                if ( caller == m_Game->UI.Action.Dice )
                {
                    Action_Dice( m_Game );
                    return true;
                }
                if ( caller == m_Game->UI.Action.EndRound )
                {
                    Action_EndTurn( m_Game );
                    return true;
                }
                if ( caller == m_Game->UI.Action.BuyCard )
                {
                    Action_BuyEventCard( m_Game );
                    return true;
                }
                if ( caller == m_Game->UI.Action.BuyRoad )
                {
                    Action_BuyRoad( m_Game );
                    return true;
                }
                if ( caller == m_Game->UI.Action.BuySett )
                {
                    Action_BuySettlement( m_Game );
                    return true;
                }
                if ( caller == m_Game->UI.Action.BuyCity )
                {
                    Action_BuyCity( m_Game );
                    return true;
                }
                if ( caller == m_Game->UI.Action.Trade )
                {
                    Action_Trade( m_Game );
                    return true;
                }
                if ( caller == m_Game->UI.Action.Bank )
                {
                    Action_Bank( m_Game );
                    return true;
                }
            }
        }
    }

    return BaseEventReceiver::OnEvent( event );
}


} // end namespace pioneers3d
