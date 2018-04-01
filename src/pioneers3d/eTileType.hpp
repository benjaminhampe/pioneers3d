/// (c) 2017 - 2018 Benjamin Hampe <benjaminhampe@gmx.de>
/// All rights reserved, except the following natural persons:
/// Only free for Persian princesses that have a github account
/// and upgrade their PC (personal flying carpet) with a Raspberry Pi,
/// or people that speak AND live the words of Jesus Christ.

#ifndef PIONEERS3D_E_TILE_TYPES_HPP
#define PIONEERS3D_E_TILE_TYPES_HPP

#include <stdint.h>
#include <sstream>

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
    HAFEN_3zu1,
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
        case eTileType::HAFEN_3zu1: return "HAFEN_3zu1";
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
    else if ( tileName == "HAFEN_3zu1")   { tileType = eTileType::HAFEN_3zu1; }
    else if ( tileName == "HAFEN_HOLZ")     { tileType = eTileType::HAFEN_HOLZ; }
    else if ( tileName == "HAFEN_LEHM")     { tileType = eTileType::HAFEN_LEHM; }
    else if ( tileName == "HAFEN_WEIZEN")   { tileType = eTileType::HAFEN_WEIZEN; }
    else if ( tileName == "HAFEN_ERZ")      { tileType = eTileType::HAFEN_ERZ; }
    else if ( tileName == "HAFEN_WOLLE")    { tileType = eTileType::HAFEN_WOLLE; }
    return tileType;
}



const char* const s_xmlStandardTiles = {
R"(
<!-- Zeile -3: (4-tiles) -->
<tile type="HAFEN_LEHM" x="-2" y="-3" dice="0" a="3" />
<tile type="WASSER" 	x="-1" y="-3" dice="0" a="3" />
<tile type="HAFEN_3zu1" x="0" y="-3" dice="0" a="3" />
<tile type="WASSER" 	x="1" y="-3" dice="0" a="2" />

<!-- Zeile -2: (5-tiles) -->
<tile type="WASSER" 	 x="-2" y="-2" dice="0" a="4" />
<tile type="LAND_WEIZEN" x="-1" y="-2" dice="3" a="0" />
<tile type="LAND_WEIZEN" x="0" y="-2" dice="6" a="0" />
<tile type="LAND_ERZ" 	 x="1" y="-2" dice="11" a="0" />
<tile type="HAFEN_WEIZEN" x="2" y="-2" dice="0" a="1" />

<!-- Zeile -1: (6-tiles) -->
<tile type="HAFEN_3zu1" x="-3" y="-1" dice="0" a="3" />
<tile type="LAND_HOLZ" 	x="-2" y="-1" dice="3" a="0" />
<tile type="LAND_ERZ" 	x="-1" y="-1" dice="5" a="0" />
<tile type="LAND_LEHM" 	x="0" y="-1" dice="10" a="0" />
<tile type="LAND_HOLZ" 	x="1" y="-1" dice="11" a="0" />
<tile type="WASSER" 	x="2" y="-1" dice="0" a="2" />

<!-- Zeile 0: (7-tiles) -->
<tile type="WASSER" x="-3" y="0" dice="0" a="4" />
<tile type="LAND_WOLLE" x="-2" y="0" dice="9" a="0" />
<tile type="LAND_LEHM" x="-1" y="0" dice="8" a="0" />
<tile type="LAND_WUESTE" x="0" y="0" dice="0" a="0" />
<tile type="LAND_ERZ" x="1" y="0" dice="8" a="0" />
<tile type="LAND_WOLLE" x="2" y="0" dice="10" a="0" />
<tile type="HAFEN_3zu1" x="3" y="0" dice="0" a="1" />

<!-- Zeile +1: (6-tiles) -->
<tile type="HAFEN_HOLZ" x="-3" y="1" dice="0" a="4" />
<tile type="LAND_LEHM"  x="-2" y="1" dice="2" a="0" />
<tile type="LAND_HOLZ"  x="-1" y="1" dice="5" a="0" />
<tile type="LAND_WOLLE" x="0" y="1" dice="12" a="0" />
<tile type="LAND_WOLLE" x="1" y="1" dice="4" a="0" />
<tile type="WASSER" 	x="2" y="1" dice="0" a="1" />

<!-- Zeile 2: (5-tiles) -->
<tile type="LAND_WASSER" x="-2" y="2" dice="0" a="5" />
<tile type="LAND_WEIZEN" x="-1" y="2" dice="4" a="0" />
<tile type="LAND_HOLZ" 	 x="0" y="2" dice="6" a="0" />
<tile type="LAND_WEIZEN" x="1" y="2" dice="9" a="0" />
<tile type="HAFEN_3zu1"  x="2" y="2" dice="0" a="1" />

<!-- Zeile 3: (4-tiles) -->
<tile type="HAFEN_ERZ" 	x="-2" y="3" dice="0" a="5" />
<tile type="WASSER" 	x="-1" y="3" dice="0" a="0" />
<tile type="HAFEN_3zu1" x="0" y="3" dice="0" a="0" />
<tile type="WASSER" 	x="1" y="3" dice="0" a="0" />
)"
};

} // end namespace pioneers3d

#endif // PIONEERS3D_TYPES_HPP
