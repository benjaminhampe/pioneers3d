#ifndef P3D_DATA_PLAYERDATA_HPP
#define P3D_DATA_PLAYERDATA_HPP

#include <pioneers3d/data/TileType.hpp>

namespace pioneers3d
{

class PlayerData
{
public:
    PlayerData( int playerId, std::string const & playerName = "" );

    ~PlayerData();

private:
    int m_PlayerId;
    std::string m_PlayerName;

};

} // end namespace pioneers3d

#endif // P3D_DATA_PLAYERDATA_HPP
