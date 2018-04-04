#ifndef GUI_CONSTANTS_HPP
#define GUI_CONSTANTS_HPP

#include <common/Types.hpp>

struct GUI_MainMenu_t
{
    irr::gui::IGUIWindow* Window = nullptr;
    irr::gui::IGUIButton* Start = nullptr;
    irr::gui::IGUIButton* Options = nullptr;
    irr::gui::IGUIButton* Exit = nullptr;
};

struct GUI_Card_t
{
    irr::gui::IGUIStaticText* Name = nullptr;
    irr::gui::IGUIImage* Image = nullptr;
    irr::gui::IGUIStaticText* Value = nullptr;
};

struct GUI_CardBank_t
{
    irr::gui::IGUIWindow* Window = nullptr;
    GUI_Card_t Holz;
    GUI_Card_t Lehm;
    GUI_Card_t Weizen;
    GUI_Card_t Wolle;
    GUI_Card_t Erz;
};

struct GUI_PlayerAction_t
{
    irr::gui::IGUIWindow* Window = nullptr;
    irr::gui::IGUIButton* Dice = nullptr;
    irr::gui::IGUIButton* Bank = nullptr;
    irr::gui::IGUIButton* Trade = nullptr;
    irr::gui::IGUIButton* BuyCard = nullptr;
    irr::gui::IGUIButton* BuyRoad = nullptr;
    irr::gui::IGUIButton* BuySett = nullptr;
    irr::gui::IGUIButton* BuyCity = nullptr;
    irr::gui::IGUIButton* EndRound = nullptr;
};

struct GUI_PlayerInfo_t
{
    irr::gui::IGUIWindow* Window = nullptr;
    irr::gui::IGUIStaticText* LogBox = nullptr;
    GUI_CardBank_t Cards;
    GUI_Card_t Roads;
    GUI_Card_t Settlements;
    GUI_Card_t Cities;
    GUI_Card_t EventCards;
    GUI_Card_t KnightCards;
    GUI_Card_t PointCards;
};

struct GUI_ChatBox_t
{
    irr::gui::IGUIWindow* Window = nullptr;
    irr::gui::IGUIEditBox* Input = nullptr;
    irr::gui::IGUIButton* Send = nullptr;
    irr::gui::IGUIStaticText* LogBox = nullptr;
};

struct GameUI_t
{
    GUI_MainMenu_t      MainMenu;
    GUI_PlayerAction_t  PlayerAction;
    GUI_PlayerInfo_t    PlayerInfo;
    GUI_ChatBox_t       ChatBox;
};


#endif // GUI_CONSTANTS_HPP
