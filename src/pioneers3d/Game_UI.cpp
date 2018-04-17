#include "Game_UI.hpp"
#include <pioneers3d/Game_Font.hpp>
#include <pioneers3d/Game_Texture.hpp>
#include <pioneers3d/Game_Player.hpp>

irr::gui::IGUIButton*
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


namespace pioneers3d {

void
setWindowVisible( Game_t * game, eWindow window, bool visible )
{
    if ( window & eWindow::MAINMENU ) { game->UI.Menu.Window->setVisible( visible); }
    if ( window & eWindow::ACTION ) { game->UI.Action.Window->setVisible( visible); }
    if ( window & eWindow::BANK ) { game->UI.Bank.Window->setVisible( visible); }
    if ( window & eWindow::DICE ) { game->UI.Dice.Window->setVisible( visible); }
    if ( window & eWindow::PLAYER ) { game->UI.Player.Window->setVisible( visible); }
    if ( window & eWindow::CHAT ) { game->UI.Chat.Window->setVisible( visible); }
}

BaseWindow*
addWindow( Game_t * game, std::string const & title,
    irr::core::recti const & pos, irr::gui::IGUIEnvironment* env, irr::gui::IGUIElement* parent, int id = -1 )
{
    BaseWindow* win = createBaseWindow( title, pos, env, parent, id );
    game->UI.Windows.emplace_back( win );
    return win;
}

void BankUI_create( Game_t * game, irr::core::recti const & pos )
{
    std::cout << __FUNCTION__ << "(" << toString( pos ) << ")\n";
    irr::gui::IGUIEnvironment* env = game->Device->getGUIEnvironment();
    BaseWindow* win = addWindow( game, "Bank", pos, env, env->getRootGUIElement() );
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


void GameUI_createCamera( Game_t * game, irr::core::recti const & pos )
{

}

void
DiceUI_create( Game_t * game, irr::core::recti const & pos )
{
    std::cout << __FUNCTION__ << "(" << toString( pos ) << ")\n";
    irr::gui::IGUIEnvironment* env = game->Device->getGUIEnvironment();
    BaseWindow* win = addWindow( game, "D I C E", pos, env, env->getRootGUIElement() );
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

void
ActionUI_create( Game_t * game, irr::core::recti const & pos )
{
    irr::IrrlichtDevice* device = game->Device;
    irr::gui::IGUIEnvironment* env = device->getGUIEnvironment();
    BaseWindow* win = addWindow( game, "Action Menu", pos, env, env->getRootGUIElement() );
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

void
ActionUI_update( Game_t * game )
{
    int32_t currPlayer = getCurrentPlayer( game );

    Player_t* player = getPlayer( game, currPlayer );

    auto setButton = [game] ( irr::gui::IGUIButton* & button, bool visibleAndEnabled ) -> void
    {
        button->setVisible( visibleAndEnabled );
        button->setEnabled( visibleAndEnabled );
    };

    setButton( game->UI.Action.EndRound, player->Action.contains( eAction::ENDTURN ) );
    setButton( game->UI.Action.Dice, player->Action.contains( eAction::DICE ) );
    setButton( game->UI.Action.Bank, player->Action.contains( eAction::BANK ) );
    setButton( game->UI.Action.Trade, player->Action.contains( eAction::TRADE ) );
    setButton( game->UI.Action.PlayCard, player->Action.contains( eAction::PLAY_EVENT_CARD ) );
    setButton( game->UI.Action.BuyCard, player->Action.contains( eAction::BUY_EVENT_CARD ) );
    setButton( game->UI.Action.BuyRoad, player->Action.contains( eAction::BUY_ROAD ) );
    setButton( game->UI.Action.BuySett, player->Action.contains( eAction::BUY_SETTLEMENT ) );
    setButton( game->UI.Action.BuyCity, player->Action.contains( eAction::BUY_CITY ) );
    setButton( game->UI.Action.PlaceRobber, player->Action.contains( eAction::PLACE_ROBBER ) );
    setButton( game->UI.Action.PlaceRoad, player->Action.contains( eAction::PLACE_ROAD ) );
    setButton( game->UI.Action.PlaceSett, player->Action.contains( eAction::PLACE_SETTLEMENT ) );
    setButton( game->UI.Action.PlaceCity, player->Action.contains( eAction::PLACE_CITY ) );
}

void
PlayerUI_update( Game_t * game )
{

}

void
PlayerUI_create( Game_t * game, irr::core::recti const & pos )
{
    std::cout << __FUNCTION__ << "(" << toString( pos ) << ")\n";

    irr::gui::IGUIEnvironment* env = game->Device->getGUIEnvironment();
    BaseWindow* win = addWindow( game, "Player", pos, env, env->getRootGUIElement() );
    irr::core::recti r_client = win->getClientRect();
    irr::gui::IGUIFont* font = Font_create( env, game->MediaDir + "fonts/DejaVuSansMono.ttf", 12, true, true );
    int x = r_client.UpperLeftCorner.X;
    int y = r_client.UpperLeftCorner.Y;
    int dx = 64;
    int dy = 128;
    int b = 5;
    game->UI.Player.Window = win;
    createGUIImage( env, win, mkRect(x+b,   y+b,96,96), Game_getPlayerTexture( game, 1 ) );
    createGUIImage( env, win, mkRect(x+b,   y+b+96+b,32,32), Game_getTexture( game, eTexture::STAT_ROAD ) );
    createGUIImage( env, win, mkRect(x+b+32,y+b+96+b,32,32), Game_getTexture( game, eTexture::STAT_SETTLEMENT ) );
    createGUIImage( env, win, mkRect(x+b+64,y+b+96+b,32,32), Game_getTexture( game, eTexture::STAT_CITY ) );
    x += 96 + b;

    auto addCard = [game,env,win,font,&x,y,dx,dy,b] ( GUI_Card_t* & card, std::string name, std::string value, eTexture tex, uint32_t color )
    {
        card = new GUI_Card_t( env, win, -1, mkRect(x,y,dx,dy) );
        card->setTexture( Game_getTexture( game, tex ) );
        Text_t t_title( name, color, font );
        Text_t t_value( value, 0xFFFFFFFF, font );
        card->setTitle( std::move( t_title ) );
        card->setValue( std::move( t_value ) );
        x += dx + b;
    };

    addCard( game->UI.Player.Holz, "Holz", "0", eTexture::CARD_HOLZ,      eTileType::holz().getRessourceColor() );
    addCard( game->UI.Player.Lehm, "Lehm", "0", eTexture::CARD_LEHM,      eTileType::lehm().getRessourceColor() );
    addCard( game->UI.Player.Weizen, "Weizen", "0", eTexture::CARD_WEIZEN, eTileType::weizen().getRessourceColor() );
    addCard( game->UI.Player.Wolle, "Wolle", "0", eTexture::CARD_WOLLE,   eTileType::wolle().getRessourceColor() );
    addCard( game->UI.Player.Erz, "Erz", "0", eTexture::CARD_ERZ,         eTileType::erz().getRessourceColor() );

//    addCard( game->UI.Player.Roads, "Roads", "0", eTexture::STAT_ROAD,  0xFFCCCCCC );
//    addCard( game->UI.Player.Settlements, "Settlements", "0", eTexture::STAT_SETTLEMENT, 0xFFDDDDDD );
//    addCard( game->UI.Player.Cities, "Cities", "0", eTexture::STAT_CITY, 0xFFEEEEEE );
    addCard( game->UI.Player.EventCards, "Event Cards", "0", eTexture::CARD_EVENT, 0xFFFFFFFF );
    addCard( game->UI.Player.KnightCards, "Knight Cards", "0", eTexture::CARD_KNIGHT, 0xFFFFFFFF );
    addCard( game->UI.Player.PointCards, "Point Cards", "0", eTexture::CARD_POINT, 0xFFFFFFFF );
    addCard( game->UI.Player.BonusRoad, "Bonus", "Longest Road", eTexture::CARD_BONUS_ROAD, 0xFFFFFFFF );
    addCard( game->UI.Player.BonusArmy, "Bonus", "Biggest Army", eTexture::CARD_BONUS_ARMY, 0xFFFFFFFF );
}

void GameUI_createChat( Game_t * game, irr::core::recti const & pos )
{
    irr::gui::IGUIEnvironment* env = game->Device->getGUIEnvironment();
    BaseWindow* win = addWindow( game, "Chat & Logs:", pos, env, env->getRootGUIElement() );
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

    BaseWindow* win = addWindow( game, "GAME MENU", r_win, env, env->getRootGUIElement() );

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


void
HelpWindowUI_create( Game_t * game )
{

}


} // end namespace pioneers3d