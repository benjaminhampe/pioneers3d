#include "UI_Chat.hpp"

namespace pioneers3d {

void GameUI_createChat( Game_t * game, irr::core::recti const & pos )
{
    irr::gui::IGUIEnvironment* env = game->Device->getGUIEnvironment();
    irr::gui::IGUIWindow* win = env->addWindow( pos, false, L"Chat & Logs:", env->getRootGUIElement() );
    irr::core::recti r_client = win->getClientRect();
    int x = r_client.UpperLeftCorner.X;
    int y = r_client.UpperLeftCorner.Y;
    int w = r_client.getWidth();
    int h = r_client.getHeight();
    int b = 5;
    game->UI.Chat.Window = win;
    game->UI.Chat.Input = env->addEditBox( L"Chat box", mkRect( x+b, y+b, w - 64 - 3*b, 32 ), true, win, -1 );
    game->UI.Chat.Send = env->addButton( mkRect( x+ w - 64 - 2*b, y+b, 64, 32 ), win, -1, L"Bank", L"Bank" );
    game->UI.Chat.LogBox = env->addListBox( mkRect( x+b, y+32+2*b, w-2*b, h-32-3*b ), win, -1, true );
}

} // end namespace pioneers3d
