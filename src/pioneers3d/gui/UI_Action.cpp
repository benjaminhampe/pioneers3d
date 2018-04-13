#include "UI_Action.hpp"
#include <pioneers3d/Game_Texture.hpp>
#include <pioneers3d/gui/UI_Window.hpp>
#include <pioneers3d/gui/UI_Card.hpp>

namespace pioneers3d {

void
ActionUI_update( Game_t * game )
{

}

void
ActionUI_create( Game_t * game, irr::core::recti const & pos )
{
    irr::IrrlichtDevice* device = game->Device;
    irr::gui::IGUIEnvironment* env = device->getGUIEnvironment();
    GUI_Window_t* win = GameUI_addWindow( game, "Action Menu", pos, env, env->getRootGUIElement() );
    irr::core::recti rc = win->getClientRect();
    int x = rc.UpperLeftCorner.X;
    int y = rc.UpperLeftCorner.Y;
    game->UI.Action.Window = win;

    auto addButton = [game,env,&x,y,win] ( irr::gui::IGUIButton* & button, std::string name, eTexture tex ) -> void
    {
        button = env->addButton( mkRect( x+2, y+2, 80, 80 ), win, -1, L"", irr::core::stringw( name.c_str() ).c_str() );
        button->setImage( Game_getTexture( game, tex ) );
        x += 85;
    };

    addButton( game->UI.Action.EndRound, "End Round", eTexture::ACTION_ENDTURN );
    addButton( game->UI.Action.Dice, "Dice", eTexture::ACTION_DICE );
    addButton( game->UI.Action.Bank, "Bank", eTexture::ACTION_BANK );
    addButton( game->UI.Action.Trade, "Trade", eTexture::ACTION_TRADE );
    addButton( game->UI.Action.PlayCard, "Play City", eTexture::CARD_EVENT );
    addButton( game->UI.Action.BuyCard, "Buy Event Card", eTexture::ACTION_BUY_EVENT_CARD );
    addButton( game->UI.Action.BuyRoad, "Buy Road", eTexture::ACTION_BUY_ROAD );
    addButton( game->UI.Action.BuySett, "Buy Settlement", eTexture::ACTION_BUY_SETTLEMENT );
    addButton( game->UI.Action.BuyCity, "Buy City", eTexture::ACTION_BUY_CITY );
    addButton( game->UI.Action.PlaceRobber, "Place Robber", eTexture::ACTION_PLACE_ROBBER );
    addButton( game->UI.Action.PlaceRoad, "Place Road", eTexture::ACTION_BUY_ROAD );
    addButton( game->UI.Action.PlaceSett, "Place Settlement", eTexture::ACTION_BUY_SETTLEMENT );
    addButton( game->UI.Action.PlaceCity, "Place City", eTexture::ACTION_BUY_CITY );
}


} // end namespace pioneers3d
