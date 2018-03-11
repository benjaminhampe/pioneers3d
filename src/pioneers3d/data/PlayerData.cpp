#include "PlayerData.hpp"

namespace pioneers3d
{

PlayerData::PlayerData( int playerId, std::string const & playerName )
    : m_PlayerId( playerId )
    , m_PlayerName( playerName )
{

}

PlayerData::~PlayerData()
{

}

} // end namespace pioneers3d
