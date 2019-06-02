/// (c) 2017 - 2018 Benjamin Hampe <benjaminhampe@gmx.de>

#ifndef PIONEERS3D_TYPES_GAME_HPP
#define PIONEERS3D_TYPES_GAME_HPP

#include <pioneers3d/types/Common.hpp>
#include <pioneers3d/types/GameType.hpp>
#include <pioneers3d/types/GameState.hpp>
#include <pioneers3d/types/PlaceObjectType.hpp>
#include <pioneers3d/types/Font.hpp>
#include <pioneers3d/types/Texture.hpp>
#include <pioneers3d/types/CylinderCamera.hpp>
#include <pioneers3d/types/Dice.hpp>
#include <pioneers3d/types/Board.hpp>
#include <pioneers3d/types/Player.hpp>
#include <pioneers3d/types/Action.hpp>
#include <pioneers3d/types/Chat.hpp>
#include <pioneers3d/types/UI.hpp>

namespace pioneers3d {

// ---------------------------------------------------------------------------------------

class Game_t
{
public:
   std::string             Name;
   irr::IrrlichtDevice*    Device = nullptr;
   irr::video::IVideoDriver* Driver = nullptr;
   irr::IEventReceiver*    Receiver = nullptr;
   irr::video::SColor      ClearColor;
   std::string             ExeFile;
   std::string             ExeDir;
   std::string             MediaDir;
   std::string             FontFileName;
   Fonts_t                 Fonts;
   void*                   Chat;
   GameType                Type;
   GameState               State;
   uint32_t                Round = 0;
   Dice_t                  Dice;
   std::vector< Player_t > Players;
   uint32_t                Player = 0;
   Board_t                 Board;
   Tile_t*                 SelectedTile = nullptr;
   bool                    EnableCollisionDetectionForTiles = true;
   Waypoint_t*             SelectedWaypointR = nullptr;
   Waypoint_t*             SelectedWaypointS = nullptr;
   bool                    EnableCollisionDetectionForWaypoints = true;
   Raueber_t               Raeuber;
   ePlaceObjectType        PlaceObjectType = ePlaceObjectType::ROBBER;
   AutoSceneNode*          PlaceObject = nullptr;
   CylinderCamera*         Camera;
   GameUI_t                UI;
public:
   Game_t() {}
   ~Game_t() {}
};


} // end namespace pioneers3d

#endif // PIONEERS3D_TYPES_GAME_HPP
