// ---------------------------------------------------------------------------------------
#ifndef PIONEERS3D_UI_TYPES_INGAME_HPP
#define PIONEERS3D_UI_TYPES_INGAME_HPP

#include <pioneers3d/common/types.hpp>

namespace pioneers3d 
{

struct GUI_Menu_t
{
    BaseWindow* Window = nullptr;
    irr::gui::IGUIButton* Start = nullptr;
    irr::gui::IGUIButton* Options = nullptr;
    irr::gui::IGUIButton* Exit = nullptr;
};

class GUI_Card_t : public irr::gui::IGUIElement
{
public:
    GUI_Card_t( irr::gui::IGUIEnvironment* env,
            irr::gui::IGUIElement* parent,
            int id,
            irr::core::recti const & pos );

    virtual ~GUI_Card_t();

    virtual void draw() override;

    void setTitle( Text_t&& title ) { m_Title = std::move( title ); }
    void setValue( Text_t&& value ) { m_Value = std::move( value ); }
    void setTexture( irr::video::ITexture* tex ) { m_Tex = tex; }
public:
    Text_t m_Title;
    Text_t m_Value;
    irr::video::ITexture* m_Tex;
};

struct GUI_Bank_t
{
    BaseWindow * Window = nullptr;
    GUI_Card_t * Holz = nullptr;
    GUI_Card_t * Lehm = nullptr;
    GUI_Card_t * Weizen = nullptr;
    GUI_Card_t * Wolle = nullptr;
    GUI_Card_t * Erz = nullptr;
};

struct GUI_Action_t
{
    BaseWindow* Window = nullptr;
    irr::gui::IGUIButton* Dice = nullptr;
    irr::gui::IGUIButton* Bank = nullptr;
    irr::gui::IGUIButton* Trade = nullptr;
    irr::gui::IGUIButton* PlayCard = nullptr;
    irr::gui::IGUIButton* BuyCard = nullptr;
    irr::gui::IGUIButton* BuyRoad = nullptr;
    irr::gui::IGUIButton* BuySett = nullptr;
    irr::gui::IGUIButton* BuyCity = nullptr;
    irr::gui::IGUIButton* PlaceRobber = nullptr;
    irr::gui::IGUIButton* PlaceRoad = nullptr;
    irr::gui::IGUIButton* PlaceSett = nullptr;
    irr::gui::IGUIButton* PlaceCity = nullptr;
    irr::gui::IGUIButton* EndRound = nullptr;
};

struct GUI_Player_t
{
    BaseWindow* Window = nullptr;
    irr::gui::IGUIStaticText* Name = nullptr;
    irr::gui::IGUIImage* Avatar = nullptr;
    GUI_Card_t * Roads = nullptr;
    GUI_Card_t * Settlements = nullptr;
    GUI_Card_t * Cities = nullptr;
    // Bank for ressource cards
    GUI_Card_t * Holz = nullptr;
    GUI_Card_t * Lehm = nullptr;
    GUI_Card_t * Weizen = nullptr;
    GUI_Card_t * Wolle = nullptr;
    GUI_Card_t * Erz = nullptr;
    // Bonus and Addons
    GUI_Card_t * EventCards = nullptr;
    GUI_Card_t * KnightCards = nullptr;
    GUI_Card_t * PointCards = nullptr;
    GUI_Card_t * BonusRoad = nullptr;
    GUI_Card_t * BonusArmy = nullptr;
    // A lotbox
    irr::gui::IGUIStaticText* LogBox = nullptr;
};
struct GUI_ChatBox_t
{
    BaseWindow* Window = nullptr;
    irr::gui::IGUIEditBox* Input = nullptr;
    irr::gui::IGUIButton* Send = nullptr;
    irr::gui::IGUIListBox* LogBox = nullptr;
};
struct GUI_Dice_t
{
    BaseWindow* Window = nullptr;
    irr::gui::IGUIButton* A = nullptr;
    irr::gui::IGUIButton* B = nullptr;
};
struct GameUI_t
{
    GUI_Menu_t          Menu;
    GUI_Bank_t          Bank;
    GUI_Action_t        Action;
    GUI_Player_t        Player;
    GUI_ChatBox_t       Chat;
    GUI_Dice_t          Dice;
    std::vector< irr::gui::IGUIWindow* > Windows;
};

} // end namespace pioneers3d

#endif // PIONEERS3D_TYPES_HPP
