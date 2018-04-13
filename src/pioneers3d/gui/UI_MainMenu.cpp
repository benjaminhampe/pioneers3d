#include "UI_MainMenu.hpp"
#include <pioneers3d/gui/UI_Window.hpp>

namespace pioneers3d {

void
MainMenuUI_create( Game_t * game )
{
    std::cout << __FUNCTION__ << "()\n";

    irr::IrrlichtDevice* device = game->Device;
    irr::video::IVideoDriver* driver = device->getVideoDriver();
    //irr::scene::ISceneManager* smgr = device->getSceneManager();
    irr::core::dimension2du screen = driver->getScreenSize();
    irr::gui::IGUIEnvironment* env = device->getGUIEnvironment();
    if ( !env )
    {
        std::cout << __FUNCTION__ << " [Error] :: Invalid pointer to IGUIEnvironment\n";
        return;
    }
    irr::core::recti r_win( screen.Width/2 - 200, 50, screen.Width/2 + 200, 450 );

    GUI_Window_t* win = GameUI_addWindow( game, "GAME MENU", r_win, env, env->getRootGUIElement() );

    irr::core::recti r_client = win->getClientRect();
    int bW = 200;
    int bH = 100;
    int x1 = (r_client.getWidth() - bW) / 2;
    int x2 = (r_client.getWidth() + bW) / 2;
    int y = 50;
    game->UI.Menu.Window = win;
    game->UI.Menu.Start = env->addButton( irr::core::recti( x1, y, x2, y+bH ), win, -1, L"Start Game", L"Starts a new game..." ); y += bH + 25;
    game->UI.Menu.Options = env->addButton( irr::core::recti( x1, y, x2, y+bH ), win, -1, L"Options", L"Enter game settings..." ); y += bH + 25;
    game->UI.Menu.Exit = env->addButton( irr::core::recti( x1, y, x2, y+bH ), win, -1, L"Exit Game", L"Exit game and program..." ); y += bH + 25;
}


} // end namespace pioneers3d
