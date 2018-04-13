#include "UI_Bank.hpp"

#include <pioneers3d/Game_Font.hpp>
#include <pioneers3d/Game_Texture.hpp>
#include <pioneers3d/gui/UI_Card.hpp>
#include <pioneers3d/gui/UI_Window.hpp>
namespace pioneers3d {

irr::gui::IGUIButton*
createImageButton( irr::gui::IGUIEnvironment* env, irr::gui::IGUIElement* parent,
    irr::core::recti const & pos, std::string name, irr::video::ITexture* tex  )
{
    std::cout << __FUNCTION__ << "(" << toString( pos ) << ")\n";
    assert( env );
    if ( !parent ) parent = env->getRootGUIElement();

    irr::gui::IGUIButton* button = env->addButton( pos, parent, -1, L"", irr::core::stringw( name.c_str() ).c_str() );
    button->setImage( tex );
    //button->setScaleImage( true );
    return button;
}


void BankUI_create( Game_t * game, irr::core::recti const & pos )
{
    std::cout << __FUNCTION__ << "(" << toString( pos ) << ")\n";
    irr::gui::IGUIEnvironment* env = game->Device->getGUIEnvironment();
    GUI_Window_t* win = GameUI_addWindow( game, "Bank", pos, env, env->getRootGUIElement() );
    irr::core::recti r_client = win->getClientRect();
    game->UI.Bank.Window = win;
    int x = r_client.UpperLeftCorner.X;
    int y = r_client.UpperLeftCorner.Y;
    int dx = 64;
    int dy = 128;
    int b = 0;

    irr::gui::IGUIFont* font = Game_getFont( game, eFontType::DEFAULT );

    auto addCard = [game,env,win,font,&x,y,dx,dy,b] ( GUI_Card_t* & card, std::string name, std::string value, eTileType tt )
    {
        card = new GUI_Card_t( env, win, -1, mkRect(x,y,dx,dy) );
        card->setTexture( Game_getCardTexture( game, tt ) );
        Text_t t_title( name, tt.getRessourceColor(), font );
        Text_t t_value( value, 0xFFFFFFFF, font );
        card->setTitle( std::move( t_title ) );
        card->setValue( std::move( t_value ) );
        x += dx + b;
    };

    addCard( game->UI.Bank.Holz, "Holz", "0", eTileType::HOLZ );
    addCard( game->UI.Bank.Lehm, "Lehm", "0", eTileType::LEHM );
    addCard( game->UI.Bank.Weizen, "Weizen", "0", eTileType::WEIZEN );
    addCard( game->UI.Bank.Wolle, "Wolle", "0", eTileType::WOLLE );
    addCard( game->UI.Bank.Erz, "Erz", "0", eTileType::ERZ );
}


} // end namespace pioneers3d


