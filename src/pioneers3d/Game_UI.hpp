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
        //CHAT = 1<<8,
        INIT_DICE = ACTION | DICE,
        INIT_PLACE = ACTION | PLAYER,
        ALL = MAINMENU | DICE | BANK | ACTION | PLAYER
    };

    eWindow( uint32_t flags ) : Flags( flags ) {}

    // eWindow( Enum flags ) : Flags( flags ) {}

    operator uint32_t() const { return Flags; }

    uint32_t Flags;
};

void setWindowVisible( Game_t * game, eWindow window, bool visible );
void UI_create( Game_t * game );
void UI_update( Game_t * game );
void UI_createActionWindow( Game_t * game, irr::core::recti const & pos );
void UI_updateActionWindow( Game_t * game );
void UI_createPlayerWindow( Game_t * game, irr::core::recti const & pos );
void UI_updatePlayerWindow( Game_t * game );
void UI_createDiceWindow( Game_t * game, irr::core::recti const & pos );
void UI_createChatWindow( Game_t * game, irr::core::recti const & pos );
void UI_createBankWindow( Game_t * game, irr::core::recti const & pos );
void UI_createStartWindow( Game_t * game, irr::core::recti const & pos );
void UI_createHelpWindow( Game_t * game );
void UI_createCameraEditorWindow( Game_t * game, irr::core::recti const & pos );

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

} // end namespace pioneers3d

#endif // UI_ACTION_HPP
