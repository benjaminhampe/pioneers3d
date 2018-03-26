/// (c) 2017 - 2018 Benjamin Hampe <benjaminhampe@gmx.de>
/// All rights reserved, except the following natural persons:
/// Only free for Persian princesses that have a github account
/// and upgrade their PC (personal flying carpet) with a Raspberry Pi,
/// or people that speak AND live the words of Jesus Christ.

#ifndef PIONEERS3D_COMMON_TYPES_HPP
#define PIONEERS3D_COMMON_TYPES_HPP

#include <common/Types.hpp>
#include <common/StringUtils.hpp>
#include <common/ImageUtils.hpp>
#include <common/AutoMeshBuffer.hpp>
#include <common/AutoSceneNode.hpp>
#include <common/TextureManager.hpp>
#include <common/Camera.hpp>
#include <common/createDevice.hpp>
#include <common/createCircle.hpp>
#include <common/createCylinder.hpp>
#include <common/createHexagon.hpp>
#include <common/createBox.hpp>
#include <common/createRect.hpp>
#include <common/createRoundRect.hpp>

namespace pioneers3d {

enum class eTileType : uint32_t
{
    UNKNOWN = 0,
    WASSER,
    LAND_WUESTE,
    LAND_HOLZ,
    LAND_LEHM,
    LAND_WEIZEN,
    LAND_ERZ,
    LAND_WOLLE,
    HAFEN_3_ZU_1,
    HAFEN_HOLZ,
    HAFEN_LEHM,
    HAFEN_WEIZEN,
    HAFEN_ERZ,
    HAFEN_WOLLE,
    COUNT,
};

inline std::string
eTileTypeToString( eTileType const & tileType )
{
    switch( tileType )
    {
        case eTileType::WASSER: return "WASSER";
        case eTileType::LAND_WUESTE: return "LAND_WUESTE";
        case eTileType::LAND_HOLZ: return "LAND_HOLZ";
        case eTileType::LAND_LEHM: return "LAND_LEHM";
        case eTileType::LAND_WEIZEN: return "LAND_WEIZEN";
        case eTileType::LAND_ERZ: return "LAND_ERZ";
        case eTileType::LAND_WOLLE: return "LAND_WOLLE";
        case eTileType::HAFEN_3_ZU_1: return "HAFEN_3_ZU_1";
        case eTileType::HAFEN_HOLZ: return "HAFEN_HOLZ";
        case eTileType::HAFEN_LEHM: return "HAFEN_LEHM";
        case eTileType::HAFEN_WEIZEN: return "HAFEN_WEIZEN";
        case eTileType::HAFEN_ERZ: return "HAFEN_ERZ";
        case eTileType::HAFEN_WOLLE: return "HAFEN_WOLLE";
        default: return "UNKNOWN";
    }
    return "MISSION IMPOSSIBLE FINISHED";
}

inline eTileType
eTileTypeFromString( std::string const & tileName )
{
    eTileType tileType = eTileType::UNKNOWN;
         if ( tileName == "WASSER" )        { tileType = eTileType::WASSER; }
    else if ( tileName == "LAND_WUESTE" )   { tileType = eTileType::LAND_WUESTE; }
    else if ( tileName == "LAND_HOLZ" )     { tileType = eTileType::LAND_HOLZ; }
    else if ( tileName == "LAND_LEHM" )     { tileType = eTileType::LAND_LEHM; }
    else if ( tileName == "LAND_WEIZEN" )   { tileType = eTileType::LAND_WEIZEN; }
    else if ( tileName == "LAND_ERZ" )      { tileType = eTileType::LAND_ERZ; }
    else if ( tileName == "LAND_WOLLE")     { tileType = eTileType::LAND_WOLLE; }
    else if ( tileName == "HAFEN_3_ZU_1")   { tileType = eTileType::HAFEN_3_ZU_1; }
    else if ( tileName == "HAFEN_HOLZ")     { tileType = eTileType::HAFEN_HOLZ; }
    else if ( tileName == "HAFEN_LEHM")     { tileType = eTileType::HAFEN_LEHM; }
    else if ( tileName == "HAFEN_WEIZEN")   { tileType = eTileType::HAFEN_WEIZEN; }
    else if ( tileName == "HAFEN_ERZ")      { tileType = eTileType::HAFEN_ERZ; }
    else if ( tileName == "HAFEN_WOLLE")    { tileType = eTileType::HAFEN_WOLLE; }
    return tileType;
}


/*
enum class eTexture : uint32_t
{
    UNKNOWN = 0,
    ROBBER_BG, PLAYER_1_BG, PLAYER_2_BG, PLAYER_3_BG, PLAYER_4_BG,
    TILE_BG, TILE_WASSER, TILE_HOLZ, TILE_LEHM,	TILE_WEIZEN, TILE_WOLLE, TILE_ERZ,
    HAFEN_BG, HAFEN_4zu1, HAFEN_LEHM, HAFEN_HOLZ, HAFEN_WEIZEN, HAFEN_ERZ, HAFEN_WOLLE,
    CARD_BG, CARD_KNIGHT, CARD_VICTORY_POINT, CARD_TRADE_POINT, CARD_INVENTION, CARD_FREE_BANK,
    DICE_BG, DICE_1, DICE_2, DICE_3, DICE_4, DICE_5, DICE_6,
    CHIP_BG, CHIP_2, CHIP_3, CHIP_4, CHIP_5, CHIP_6, CHIP_7, CHIP_8, CHIP_9, CHIP_10, CHIP_11, CHIP_12,
    PLAN_BG, PLAN_STANDARD,
    BANK_BG, BANK_HOLZ, BANK_LEHM, BANK_WEIZEN, BANK_WOLLE, BANK_ERZ,
    COUNT
};

const char* const eTexture[] =
{
    "TEX_WASSER.png",
    "TEX_HOLZ.png",
    "TEX_LEHM.png",
    "TEX_WEIZEN.png",
    "TEX_WOLLE.png",
    "TEX_ERZ.png",
    "TEX_AUGEN_02.png",
    "TEX_AUGEN_03.png",
    "TEX_AUGEN_04.png",
    "TEX_AUGEN_05.png",
    "TEX_AUGEN_06.png",
    "TEX_AUGEN_07.png",
    "TEX_AUGEN_08.png",
    "TEX_AUGEN_09.png",
    "TEX_AUGEN_10.png",
    "TEX_AUGEN_11.png",
    "TEX_AUGEN_12.png"
};
*/

class eGameType
{
public:
    enum EType : uint32_t
    {
        UNKNOWN = 0,
        STANDARD = 1,
        FISHER = 2,
        PIRATES = 4,
        THIEFS = 8,
        CARDS = 16,
        CHEATS = 128,
        ALL = STANDARD | FISHER | PIRATES | THIEFS | CARDS
    };

    eGameType() : m_Value( STANDARD )
    {}

    eGameType( EType type ) : m_Value( type )
    {}

    eGameType( uint32_t type ) : m_Value( static_cast< EType >( type ) )
    {}

    operator EType() const { return m_Value; }

    bool
    hasAddon( EType type ) const { return m_Value & type; }

    EType
    value() const { return m_Value; }

    void
    setValue( EType value ) { m_Value = value; }

    eGameType&
    operator|=( EType type )
    {
        m_Value = static_cast< EType >( uint32_t( m_Value ) | uint32_t( type ) );
        return *this;
    }

    eGameType&
    operator|=( eGameType const & type )
    {
        m_Value = static_cast< EType >( uint32_t( m_Value ) | uint32_t( type.value() ) );
        return *this;
    }

    /// @brief Parses the entire string for all values in enum eGameType.
    /// The results are OR'ed together and returned as one value containing bitflags.
    static eGameType
    parseString( std::string const & src )
    {
        eGameType gameType;
        if ( src.find( "STANDARD" ) != std::string::npos ) { gameType |= eGameType::STANDARD; }
        if ( src.find( "FISHER" ) != std::string::npos )   { gameType |= eGameType::FISHER; }
        if ( src.find( "PIRATES" ) != std::string::npos )  { gameType |= eGameType::PIRATES; }
        if ( src.find( "THIEFS" ) != std::string::npos )   { gameType |= eGameType::THIEFS; }
        if ( src.find( "CARDS" ) != std::string::npos )    { gameType |= eGameType::CARDS; }
        return gameType;
    }

    /// @brief Converts enum eGameType to a string as flags OR'ed together.
    std::string
    toString() const
    {
        std::stringstream s;
        int k=0;
        if ( m_Value & STANDARD ) { if (k>0) { s << '|'; } s << "STANDARD"; ++k; }
        if ( m_Value & FISHER ) { if (k>0) { s << '|'; } s << "FISHER"; ++k; }
        if ( m_Value & PIRATES ) { if (k>0) { s << '|'; } s << "PIRATES"; ++k; }
        if ( m_Value & THIEFS ) { if (k>0) { s << '|'; } s << "THIEFS"; ++k; }
        if ( m_Value & CARDS ) { if (k>0) { s << '|'; } s << "CARDS"; ++k; }

        std::cout << __FUNCTION__ << "() -> returns " << s.str() << "\n";

        return s.str();
    }

    std::string
    toXML() const
    {
        std::stringstream s;
        s << "<eGameType>" << toString() << "</eGameType>\n";
        return s.str();
    }

    EType m_Value;
};

enum class eGameState : uint32_t
{
    IDLE = 0,
    GAME_MENU,
    GAME_INIT_PLAYER,
    GAME_INIT_BOARD,
    GAME_DICE,
    GAME_PLACE_ROBBER,
    GAME_PLACE_FIRST_ROAD,
    GAME_PLACE_FIRST_SETTLEMENT,
    GAME_PLACE_SECOND_ROAD,
    GAME_PLACE_SECOND_SETTLEMENT,
    GAME_LOOP,
    GAME_END,
    PLAYER_1,
    PLAYER_2,
    PLAYER_3,
    PLAYER_4,
    COUNT
};

} // end namespace pioneers3d

#endif // PIONEERS3D_TYPES_HPP
