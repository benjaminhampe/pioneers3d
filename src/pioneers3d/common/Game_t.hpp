#ifndef PIONEERS3D_COMMON_TYPES_GAME_HPP
#define PIONEERS3D_COMMON_TYPES_GAME_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

struct Game_t
{
    std::string             MediaDir;
    irr::IrrlichtDevice*    Device = nullptr;
    irr::IEventReceiver*    Receiver = nullptr;
    irr::video::SColor      ClearColor;
    std::string             FontFileName;
    Fonts_t                 Fonts;

    void*                   Chat;

    eGameType 				Type;
    eGameState 				State;
    uint32_t                Round = 0;
    Dice_t                  Dice;

    Bank_t                  Bank;

	Board_t					Board;
	
    std::vector< Player_t > Players;
    uint32_t 				Player = 0;

    Raueber_t               Raeuber;
    ePlaceObjectType        PlaceObjectType = ePlaceObjectType::ROBBER;
    AutoSceneNode*          PlaceObject = nullptr;

    GameUI_t                UI;
};

} // end namespace pioneers3d

#endif // PIONEERS3D_COMMON_TYPES_GAME_T_HPP
