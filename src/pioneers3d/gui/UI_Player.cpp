#include "UI_Player.hpp"

#include <pioneers3d/Game_Textures.hpp>
#include <pioneers3d/gui/UI_Card.hpp>

namespace pioneers3d {

void GameUI_updatePlayerAction( Game_t * game )
{

}

void
GameUI_createPlayerInfo( Game_t * game, irr::core::recti const & pos )
{
    std::cout << __FUNCTION__ << "(" << toString( pos ) << ")\n";
    //irr::IrrlichtDevice* device = game->Device;
    //irr::video::IVideoDriver* driver = device->getVideoDriver();
    //irr::core::dimension2du screen = driver->getScreenSize();
    irr::gui::IGUIEnvironment* env = game->Device->getGUIEnvironment();
    irr::gui::IGUIWindow* win = env->addWindow( pos, false, L"PlayerInfo", env->getRootGUIElement() );
    irr::core::recti r_client = win->getClientRect();

    game->UI.PlayerInfo.Window = win;

    // Game_createBank( game, win, game->UI.PlayerInfo.Cards, irr::core::recti( 10, 10, 500, 200 ) );
    //int w = r_client.getWidth();
    //int h = r_client.getHeight();
    int x = r_client.UpperLeftCorner.X;
    int y = r_client.UpperLeftCorner.Y;
    int dx = 64;
    int dy = 128;
    int b = 10;
    createGUIImage( env, win, mkRect(x+b,y+32,64,64), Game_getPlayerTexture( game, 1 ) ); x += dx + b;

    auto addCard = [game,env,win,&x,y,dx,dy,b] ( GUI_Card_t & card, std::string name, std::string value, eTexture tex )
    {
        GUI_Card_create( env, win, mkRect(x,y,dx,dy), card, name, Game_getTexture( game, tex), value );
        x += dx + b;
    };

    addCard( game->UI.PlayerInfo.Holz, "Holz", "1", eTexture::PLAYER_HOLZ );
    addCard( game->UI.PlayerInfo.Lehm, "Lehm", "0", eTexture::PLAYER_LEHM );
    addCard( game->UI.PlayerInfo.Weizen, "Weizen", "0", eTexture::PLAYER_WEIZEN );
    addCard( game->UI.PlayerInfo.Wolle, "Wolle", "0", eTexture::PLAYER_WOLLE );
    addCard( game->UI.PlayerInfo.Erz, "Erz", "0", eTexture::PLAYER_ERZ );

    addCard( game->UI.PlayerInfo.Roads, "Roads", "0", eTexture::PLAYER_ROAD );
    addCard( game->UI.PlayerInfo.Settlements, "Settlements", "0", eTexture::PLAYER_SETTLEMENT );
    addCard( game->UI.PlayerInfo.Cities, "Cities", "0", eTexture::PLAYER_CITY );

    addCard( game->UI.PlayerInfo.EventCards, "Event Cards", "0", eTexture::PLAYER_EVENT_CARD );
    addCard( game->UI.PlayerInfo.KnightCards, "Knight Cards", "0", eTexture::PLAYER_KNIGHT_CARD );
    addCard( game->UI.PlayerInfo.PointCards, "Point Cards", "0", eTexture::PLAYER_POINT_CARD );

    addCard( game->UI.PlayerInfo.BonusLongestRoad, "Bonus", "Longest Road", eTexture::PLAYER_BONUS_LONGEST_ROAD );
    addCard( game->UI.PlayerInfo.BonusLongestRoad, "Bonus", "Biggest Army", eTexture::PLAYER_BONUS_BIGGEST_ARMY );
}

void
GameUI_createPlayerAction( Game_t * game, irr::core::recti const & pos )
{
    irr::IrrlichtDevice* device = game->Device;
    irr::gui::IGUIEnvironment* env = device->getGUIEnvironment();
    irr::gui::IGUIWindow* win = env->addWindow( pos, false, L"Player Action Menu | Player (0) Benni", env->getRootGUIElement() );
    irr::core::recti rc = win->getClientRect();
    int x = rc.UpperLeftCorner.X;
    int y = rc.UpperLeftCorner.Y;
    game->UI.PlayerAction.Window = win;

    auto addButton = [game,env,&x,y,win] ( irr::gui::IGUIButton* & button, std::string name, eTexture tex ) -> void
    {
        button = env->addButton( mkRect( x+10, y+5, 100, 80 ), win, -1, irr::core::stringw( name.c_str() ).c_str(), irr::core::stringw( name.c_str() ).c_str() );
        button->setImage( Game_getTexture( game, tex ) );
        x += 110;
    };

    addButton( game->UI.PlayerAction.Dice, "Dice", eTexture::PLAYER_ACTION_DICE );
    addButton( game->UI.PlayerAction.Bank, "Bank", eTexture::PLAYER_ACTION_BANK );
    addButton( game->UI.PlayerAction.Trade, "Trade", eTexture::PLAYER_ACTION_TRADE );
    addButton( game->UI.PlayerAction.BuyCard, "Buy Event Card", eTexture::PLAYER_ACTION_BUY_EVENT_CARD );
    addButton( game->UI.PlayerAction.BuyRoad, "Buy Road", eTexture::PLAYER_ACTION_BUY_ROAD );
    addButton( game->UI.PlayerAction.BuySett, "Buy Settlement", eTexture::PLAYER_ACTION_BUY_SETTLEMENT );
    addButton( game->UI.PlayerAction.BuyCity, "Buy City", eTexture::PLAYER_ACTION_BUY_CITY );
    addButton( game->UI.PlayerAction.EndRound, "End Round", eTexture::PLAYER_ACTION_ENDTURN );
}


} // end namespace pioneers3d


#if 0
void
Game_createCardInfo( Game_t * game, irr::gui::IGUIElement* parent,
                        GUI_Card_t & out, const char* name, eTexture tex, int value, irr::core::recti const & pos )
{
    std::cout << __FUNCTION__ << "(" << name << "," << toString( pos ) << ")\n";

    irr::gui::IGUIEnvironment* env = game->Device->getGUIEnvironment();

    int x = pos.UpperLeftCorner.X;
    int y = pos.UpperLeftCorner.Y;
    int w = pos.getWidth();
    int h = pos.getHeight();

    out.Name = env->addStaticText( irr::core::stringw( name ).c_str(), mkRect(x,y,w,10), true, false, parent, -1, false );
    out.Image = createGUIImage( env, parent, Game_getTexture( game, tex ), mkRect( x, y+10, w, h-20 ) );

    std::wstringstream s; s << value;
    out.Value = guienv->addStaticText( s.str().c_str(), mkRect( x, h-10, w, 10 ), true, false, parent, -1, false );
}

void
Game_createBank( Game_t * game, irr::gui::IGUIElement* parent,
                    GUI_CardBank_t & out, irr::core::recti const & pos )
{
    std::cout << __FUNCTION__ << "()\n";
    irr::IrrlichtDevice* device = game->Device;
    irr::gui::IGUIEnvironment* env = device->getGUIEnvironment();
    irr::gui::IGUIWindow* win = env->addWindow( pos, false, L"Bank", parent );
    irr::core::recti rc = win->getClientRect();
    int w = rc.getWidth();
    int h = rc.getHeight();
    out.Window = win;
    int b = 5;
    int x = rc.UpperLeftCorner.X + b;
    int y = rc.UpperLeftCorner.Y + b;
    int dx = w/6;
    int dy = h-2*b;

    inline void
createGUICard(  GUI_Card_t & out,
                irr::gui::IGUIEnvironment* env,
                irr::gui::IGUIElement* parent,
                irr::core::recti const & pos,
                const char* name = "Unknown Card",
                irr::video::ITexture* tex = nullptr,
                int value = 0 )

    createGUICard( GUI_Card_t & out, win, out.Holz, "Holz", eTexture::CARD_HOLZ, 1, mkRect(x,y,dx,dy) ); x += dx + b;
    Game_createCardInfo( game, win, out.Lehm, "Lehm", eTexture::CARD_LEHM, 2, mkRect(x,y,dx,dy) ); x += dx + b;
    Game_createCardInfo( game, win, out.Weizen, "Weizen", eTexture::CARD_WEIZEN, 3, mkRect(x,y,dx,dy) ); x += dx + b;
    Game_createCardInfo( game, win, out.Wolle, "Wolle", eTexture::CARD_WOLLE, 4, mkRect(x,y,dx,dy) ); x += dx + b;
    Game_createCardInfo( game, win, out.Erz, "Erz", eTexture::CARD_ERZ, 5, mkRect(x,y,dx,dy) ); x += dx + b;
}
#endif

