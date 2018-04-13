#include "UI_Dice.hpp"
#include <pioneers3d/Game_Texture.hpp>
#include <pioneers3d/gui/UI_Window.hpp>

namespace pioneers3d {

inline irr::gui::IGUIButton*
createImageButton(
    irr::gui::IGUIEnvironment* env,
    irr::gui::IGUIElement* parent,
    irr::core::recti const & pos,
    std::string name,
    irr::video::ITexture* tex  )
{
    std::cout << __FUNCTION__ << "(" << toString( pos ) << ")\n";
    assert( env );
    if ( !parent ) parent = env->getRootGUIElement();

    irr::gui::IGUIButton* button = env->addButton( pos, parent, -1, L"", irr::core::stringw( name.c_str() ).c_str() );
    button->setImage( tex );
    //button->setScaleImage( true );
    return button;
}

void
DiceUI_create( Game_t * game, irr::core::recti const & pos )
{
    std::cout << __FUNCTION__ << "(" << toString( pos ) << ")\n";
    irr::gui::IGUIEnvironment* env = game->Device->getGUIEnvironment();
    GUI_Window_t* win = GameUI_addWindow( game, "D I C E", pos, env, env->getRootGUIElement() );
    irr::core::recti r_client = win->getClientRect();
    int w = r_client.getWidth();
    int h = r_client.getHeight();
    int x = r_client.UpperLeftCorner.X;
    int y = r_client.UpperLeftCorner.Y;
    int b = 10;
    int dx = (w-3*b)/2;
    int dy = h-2*b;
    game->UI.Dice.Window = win;
    game->UI.Dice.A = createImageButton( env, win, mkRect(x+b,y+b,dx,dy), "Dice 1", Game_getDiceTexture( game, 1+(rand()%6) ) );
    game->UI.Dice.B = createImageButton( env, win, mkRect(x+w-1-b-dx,y+b,dx,dy), "Dice 2", Game_getDiceTexture( game, 1+(rand()%6) ) );
}

} // end namespace pioneers3d
