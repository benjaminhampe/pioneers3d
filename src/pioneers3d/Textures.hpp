#ifndef PIONEERS3D_TEXTURES_HPP
#define PIONEERS3D_TEXTURES_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

enum class eTexture : uint32_t
{
    UNKNOWN = 0,
    TEX = 100,
    TEX_ROBBER,
    TEX_ROAD,
    TEX_TILE_BORDER,
    DICE_BG = 200,
    DICE_1,
    DICE_2,
    DICE_3,
    DICE_4,
    DICE_5,
    DICE_6,
    CHIP_BG = 250,
    CHIP_2,
    CHIP_3,
    CHIP_4,
    CHIP_5,
    CHIP_6,
    CHIP_7,
    CHIP_8,
    CHIP_9,
    CHIP_10,
    CHIP_11,
    CHIP_12,
    TILE_BG = 300,
    TILE_WASSER,
    TILE_LAND_HOLZ,
    TILE_LAND_LEHM,
    TILE_LAND_WEIZEN,
    TILE_LAND_WOLLE,
    TILE_LAND_ERZ,
    TILE_HAFEN_BG,
    TILE_HAFEN_4zu1,
    TILE_HAFEN_LEHM,
    TILE_HAFEN_HOLZ,
    TILE_HAFEN_WEIZEN,
    TILE_HAFEN_ERZ,
    TILE_HAFEN_WOLLE,
    ICON_BG = 400,
    ICON_PLAYER_1,
    ICON_PLAYER_2,
    ICON_PLAYER_3,
    ICON_PLAYER_4,
    RESCARD_BG = 500,
    RESCARD_HOLZ,
    RESCARD_LEHM,
    RESCARD_WEIZEN,
    RESCARD_WOLLE,
    RESCARD_ERZ,
    EVTCARD_BG = 550,
    EVTCARD_KNIGHT,
    EVTCARD_VICTORY_POINT,
    EVTCARD_INVENTION,
    EVTCARD_FREE_BANK,
    BONUS_BG = 600,
    BONUS_LONGEST_ROAD,
    BONUS_BIGGEST_ARMY,
    UI = 700,
    BUY_EVENT_CARD,
    PLAN_BG,
    PLAN_STANDARD,
    COUNT
};

class TextureManager
{
public:
    std::string m_MediaDir;

    std::map< eTexture, irr::video::ITexture* > m_Textures;

    irr::video::IVideoDriver* m_Driver;

public:
    TextureManager( irr::video::IVideoDriver* driver )
    : m_Driver( driver )
    {
        createDefault();
    }

    ~TextureManager()
    {
        clear();
    }

    void clear()
    {

    }

    void addTexture( eTexture type, std::string const & fileName )
    {
        if ( !m_Driver ) return;
        m_Textures[ type ] = m_Driver->getTexture( fileName.c_str() );
    }

    void createDefault()
    {
        addTexture( eTexture::UNKNOWN, "unknown.jpg" );
        addTexture( eTileType::WASSER, "wasser.png" );
        addTexture( eTileType::LAND_WUESTE, "land_wueste.png" );
        addTexture( eTileType::LAND_HOLZ, "land_holz.png" );
        addTexture( eTileType::LAND_LEHM, "land_.png" );
        addTexture( eTileType::LAND_WEIZEN, "wasser.png" );
        addTexture( eTileType::LAND_WOLLE, "wasser.png" );
        addTexture( eTileType::LAND_ERZ, "wasser.png" );
        addTexture( eTileType::HAFEN_3_ZU_1, "wasser.png" );
        addTexture( eTileType::HAFEN_HOLZ, "wasser.png" );
        addTexture( eTileType::HAFEN_LEHM, "wasser.png" );
        addTexture( eTileType::HAFEN_WEIZEN, "wasser.png" );
        addTexture( eTileType::HAFEN_WOLLE, "wasser.png" );
        addTexture( eTileType::HAFEN_ERZ, "wasser.png" );
    }

    irr::video::ITexture* getTexture( eTexture texture )
    {

    }
};


} // end namespace pioneers3d

#endif // PIONEERS3D_TEXTURES_HPP
