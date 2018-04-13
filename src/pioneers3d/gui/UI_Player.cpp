#include "UI_Player.hpp"

#include <pioneers3d/Game_Texture.hpp>
#include <pioneers3d/Game_Player.hpp>
#include <pioneers3d/gui/UI_Card.hpp>
#include <pioneers3d/gui/UI_Window.hpp>

namespace pioneers3d {

void
PlayerUI_update( Game_t * game )
{

}

void
PlayerUI_create( Game_t * game, irr::core::recti const & pos )
{
    std::cout << __FUNCTION__ << "(" << toString( pos ) << ")\n";

    irr::gui::IGUIEnvironment* env = game->Device->getGUIEnvironment();
    GUI_Window_t* win = GameUI_addWindow( game, "Player", pos, env, env->getRootGUIElement() );
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

