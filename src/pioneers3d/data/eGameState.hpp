/// (c) 2017 - 2018 Benjamin Hampe <benjaminhampe@gmx.de>
/// All rights reserved, except the following natural persons:
/// Only free for Persian princesses that have a github account
/// and upgrade their PC (personal flying carpet) with a Raspberry Pi,
/// or people that speak AND live the words of Jesus Christ.

#ifndef PIONEERS3D_E_GAME_STATE_HPP
#define PIONEERS3D_E_GAME_STATE_HPP

#include <common/Types.hpp>

namespace pioneers3d {

enum class eGameState : uint32_t
{
    NOT_RUNNING = 0,
    IDLE,
    PLACE_OBJECT, /// @see eGameObject
//    PLACE_ROBBER,
//    PLACE_ROAD,
//    PLACE_SETTLEMENT,
//    PLACE_CITY,
    COUNT
};

// Uses to differentiate between PLACE_OBJECT objects.
enum class ePlaceObjectType : uint32_t
{
    ROBBER = 0,
    ROAD,
    SETTLEMENT,
    CITY,
    COUNT
};

} // end namespace pioneers3d

inline std::string toString( pioneers3d::eGameState egs )
{
    switch( egs )
    {
    case pioneers3d::eGameState::NOT_RUNNING: return "NOT_RUNNING";
    case pioneers3d::eGameState::IDLE: return "IDLE";
    case pioneers3d::eGameState::PLACE_OBJECT: return "PLACE_OBJECT";
    default: return "UNKNOWN";
    }
}

inline std::string toString( pioneers3d::ePlaceObjectType pot )
{
    switch( pot )
    {
    case pioneers3d::ePlaceObjectType::ROBBER: return "ROBBER";
    case pioneers3d::ePlaceObjectType::ROAD: return "ROAD";
    case pioneers3d::ePlaceObjectType::SETTLEMENT: return "SETTLEMENT";
    case pioneers3d::ePlaceObjectType::CITY: return "CITY";
    default: return "UNKNOWN";
    }
}

#endif // PIONEERS3D_E_GAMESTATE_HPP
