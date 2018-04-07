#include "UI_Game.hpp"
#include <pioneers3d/Game_Logger.hpp>
#include <pioneers3d/gui/UI_Card.hpp>
#include <pioneers3d/gui/UI_Bank.hpp>
#include <pioneers3d/gui/UI_Trade.hpp>
#include <pioneers3d/gui/UI_Dice.hpp>
#include <pioneers3d/gui/UI_Player.hpp>
#include <pioneers3d/gui/UI_Chat.hpp>
#include <pioneers3d/gui/UI_Camera.hpp>

namespace pioneers3d {

void GameUI_create( Game_t * game )
{
    //ALPHASONIC_CREATE_INLINE_LOGGER(__FUNCTION__)

    if ( !game )
    {
        std::cout << __FUNCTION__ << " :: Invalid pointer to Game\n";
        return;
    }
    if ( !game->Device )
    {
        std::cout << __FUNCTION__ << " :: Invalid pointer to IrrlichtDevice\n";
        return;
    }

    irr::video::IVideoDriver* driver = game->Device->getVideoDriver();
    irr::gui::IGUIEnvironment* guienv = game->Device->getGUIEnvironment();
    if ( !guienv )
    {
        std::cout << __FUNCTION__ << " :: Invalid pointer to IGUIEnvironment\n";
        return;
    }

    irr::core::dimension2du const screen = driver->getScreenSize();

    GameUI_createChat( game, mkRect( screen.Width/2+100, screen.Height/4, screen.Width/2 - 150, screen.Height/2 ) );
    GameLogger::singleton().setLogBox( game->UI.Chat.LogBox );
    GAME_LOG_ERROR("Hello World")

    GameUI_createMainMenuWindow( game );
    GameUI_createPlayerAction( game, mkRect( 100, 10, screen.Width - 200, 120 ) );
    GameUI_createPlayerInfo( game, mkRect( 10, screen.Height - 210, screen.Width - 100, 200 ) );
    GameUI_createDice( game, mkRect( screen.Width - 300, 10, 250, 200 ) );
}


void
GameUI_createMainMenuWindow( Game_t * game )
{
    std::cout << __FUNCTION__ << "()\n";

    irr::IrrlichtDevice* device = game->Device;
    irr::video::IVideoDriver* driver = device->getVideoDriver();
    //irr::scene::ISceneManager* smgr = device->getSceneManager();
    irr::core::dimension2du screen = driver->getScreenSize();
    irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    if ( !guienv )
    {
        std::cout << __FUNCTION__ << " :: ERROR: Invalid pointer to IGUIEnvironment\n";
        return;
    }

    irr::gui::IGUIWindow* win = guienv->addWindow( irr::core::recti( screen.Width/2 - 200, 50, screen.Width/2 + 200, 450 ), false, L"Game Settings", guienv->getRootGUIElement() );
    irr::core::recti clientRect = win->getClientRect();
    int bW = 200;
    int bH = 100;
    int x1 = (clientRect.getWidth() - bW) / 2;
    int x2 = (clientRect.getWidth() + bW) / 2;
    int y = 50;
    game->UI.MainMenu.Window = win;
    game->UI.MainMenu.Start = guienv->addButton( irr::core::recti( x1, y, x2, y+bH ), win, -1, L"Start Game", L"Starts a new game..." ); y += bH + 25;
    game->UI.MainMenu.Options = guienv->addButton( irr::core::recti( x1, y, x2, y+bH ), win, -1, L"Options", L"Enter game settings..." ); y += bH + 25;
    game->UI.MainMenu.Exit = guienv->addButton( irr::core::recti( x1, y, x2, y+bH ), win, -1, L"Exit Game", L"Exit game and program..." ); y += bH + 25;
}


} // end namespace pioneers3d
