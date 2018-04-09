#include "EventReceiver.hpp"

#include "Game_Camera.hpp"
#include <pioneers3d/Game_Textures.hpp>

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
        irr::gui::IGUIEnvironment* env = m_Device->getGUIEnvironment();

        if ( guiEvent.EventType == irr::gui::EGET_BUTTON_CLICKED )
        {
            if ( caller && m_Game )
            {
                if ( caller == m_Game->UI.MainMenu.Exit )
                {
                    if ( m_Device )
                    {
                        irr::scene::ICameraSceneNode* camera = m_Device->getSceneManager()->getActiveCamera();
                        if ( camera )
                        {
                            camera->setInputReceiverEnabled( false );
                        }
                        m_Device->closeDevice();
                        m_Device = nullptr;
                    }
                    return true;
                }
                if ( caller == m_Game->UI.MainMenu.Start )
                {
                    m_Game->UI.MainMenu.Window->setVisible( false );
                    m_Game->State = eGameState::GAME_START;
                    return true;
                }
                if ( caller == m_Game->UI.PlayerAction.Dice )
                {
                    m_Game->Dice.A = rand() % 6 + 1;
                    m_Game->Dice.B = rand() % 6 + 1;
                    m_Game->UI.Dice.A->setImage( Dice_getTexture( m_Game, m_Game->Dice.A ) );
                    m_Game->UI.Dice.B->setImage( Dice_getTexture( m_Game, m_Game->Dice.B ) );
                    return true;
                }
                if ( caller == m_Game->UI.PlayerAction.EndRound )
                {

                    return true;
                }
                if ( caller == m_Game->UI.PlayerAction.BuyRoad )
                {

                    return true;
                }
                if ( caller == m_Game->UI.PlayerAction.BuySett )
                {

                    return true;
                }
                if ( caller == m_Game->UI.PlayerAction.BuyCity )
                {

                    return true;
                }
                if ( caller == m_Game->UI.PlayerAction.Trade )
                {

                    return true;
                }
                if ( caller == m_Game->UI.PlayerAction.Bank )
                {

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
