#ifndef P3DDATA_GAMEDATA_HPP
#define P3DDATA_GAMEDATA_HPP

#include <pioneers3d/data/TextureType.hpp>
#include <pioneers3d/data/BoardData.hpp>
#include <pioneers3d/data/PlayerData.hpp>

namespace pioneers3d
{

class GameData
{
public:
    GameData( irr::IrrlichtDevice * device );

    ~GameData();

private:
    irr::IrrlichtDevice * m_Device;

    irr::video::ITexture * m_Textures[ TextureType::COUNT ];

    BoardData * m_Board;

    std::vector< PlayerData* > m_Players;
};

} // end namespace pioneers3d

#endif // P3DDATA_GAMEDATA_HPP
