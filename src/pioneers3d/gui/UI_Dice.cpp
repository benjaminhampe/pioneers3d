#include "UI_Dice.hpp"

#include <pioneers3d/Game_Textures.hpp>

namespace pioneers3d {


inline irr::gui::IGUIButton*
GameUI_createImageButton(
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

void GameUI_createDice( Game_t * game, irr::core::recti const & pos )
{
    std::cout << __FUNCTION__ << "(" << toString( pos ) << ")\n";
    //irr::IrrlichtDevice* device = game->Device;
    //irr::video::IVideoDriver* driver = device->getVideoDriver();
    //irr::core::dimension2du screen = driver->getScreenSize();
    irr::gui::IGUIEnvironment* env = game->Device->getGUIEnvironment();
    irr::gui::IGUIWindow* win = env->addWindow( pos, false, L"D.I.C.E.S.", env->getRootGUIElement() );
    irr::core::recti r_client = win->getClientRect();


    // Game_createBank( game, win, game->UI.PlayerInfo.Cards, irr::core::recti( 10, 10, 500, 200 ) );
    int w = r_client.getWidth();
    int h = r_client.getHeight();
    int x = r_client.UpperLeftCorner.X;
    int y = r_client.UpperLeftCorner.Y;
    int b = 10;
    int dx = (w-3*b)/2;
    int dy = h-2*b;
    game->UI.Dice.Window = win;
    game->UI.Dice.A = GameUI_createImageButton( env, win, mkRect(x+b,y+b,dx,dy), "Dice 1", Game_getDiceTexture( game, 1+(rand()%6) ) );
    game->UI.Dice.B = GameUI_createImageButton( env, win, mkRect(x+w-1-b-dx,y+b,dx,dy), "Dice 2", Game_getDiceTexture( game, 1+(rand()%6) ) );
}

} // end namespace pioneers3d
