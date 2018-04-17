#ifndef UI_GAME_HPP
#define UI_GAME_HPP

#include <pioneers3d/Types.hpp>

irr::gui::IGUIButton*
    createImageButton(
        irr::gui::IGUIEnvironment* env,
        irr::gui::IGUIElement* parent,
        irr::core::recti const & pos,
        std::string name,
        irr::video::ITexture* tex );

namespace pioneers3d {

class eWindow
{
public:
    enum Enum : uint32_t
    {
        UNKNOWN = 0,
        MAINMENU = 1,
        DICE = 1<<1,
        BANK = 1<<2,
        ACTION = 1<<3,
        PLAYER = 1<<4,
        CHAT = 1<<8,
        ALL = MAINMENU | DICE | BANK | ACTION | PLAYER | CHAT
    };

    eWindow( uint32_t flags ) : Flags( flags ) {}

    // eWindow( Enum flags ) : Flags( flags ) {}

    operator uint32_t() const { return Flags; }

    uint32_t Flags;
};

void setWindowVisible( Game_t * game, eWindow window, bool visible );

void ActionUI_create( Game_t * game, irr::core::recti const & pos );
void ActionUI_update( Game_t * game );

void PlayerUI_create( Game_t * game, irr::core::recti const & pos );
void PlayerUI_update( Game_t * game );

void DiceUI_create( Game_t * game, irr::core::recti const & pos );

void GameUI_createChat( Game_t * game, irr::core::recti const & pos );

/*
void
CardUI_create(  irr::gui::IGUIEnvironment* env,
                irr::gui::IGUIElement* parent,
                irr::core::recti const & pos,
                GUI_Card_t & out,
                std::string name = "Unknown",
                irr::video::ITexture* tex = nullptr,
                std::string value = "" );
*/

void GameUI_createCamera( Game_t * game, irr::core::recti const & pos );

void BankUI_create( Game_t * game, irr::core::recti const & pos );

void MainMenuUI_create( Game_t * game );


void HelpWindowUI_create( Game_t * game );


} // end namespace pioneers3d

#endif // UI_ACTION_HPP
