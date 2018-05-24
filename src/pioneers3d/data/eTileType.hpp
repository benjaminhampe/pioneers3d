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

class eTileType
{
public:
    enum EType : uint32_t
    {
        UNKNOWN = 0,
        WASSER = 1,  // TileType
        LAND = 1<<1, // TileType
        //NONE = 1<<2, // RessourceType
        HAFEN = 1<<3, // RessourceType
        HOLZ = 1<<4, // RessourceType
        LEHM = 1<<5, // RessourceType
        WEIZEN = 1<<6, // RessourceType
        WOLLE = 1<<7, // RessourceType
        ERZ = 1<<8, // RessourceType
        RESSOURCE_MASK = HOLZ | LEHM | WEIZEN | WOLLE | ERZ,
        RESSOURCE_COUNT = 5,
        LAND_WUESTE = LAND,
        LAND_HOLZ = LAND | HOLZ,
        LAND_LEHM = LAND | LEHM,
        LAND_WEIZEN = LAND | WEIZEN,
        LAND_WOLLE = LAND | WOLLE,
        LAND_ERZ = LAND | ERZ,
        HAFEN_3zu1 = HAFEN,
        HAFEN_HOLZ = HAFEN | HOLZ,
        HAFEN_LEHM = HAFEN | LEHM,
        HAFEN_WEIZEN = HAFEN | WEIZEN,
        HAFEN_WOLLE = HAFEN | WOLLE,
        HAFEN_ERZ = HAFEN | ERZ,
        FORCE32BIT = 0x7FFFFFFF
    };
    static eTileType holz() { return eTileType::HOLZ; }
    static eTileType lehm() { return eTileType::LEHM; }
    static eTileType weizen() { return eTileType::WEIZEN; }
    static eTileType wolle() { return eTileType::WOLLE; }
    static eTileType erz() { return eTileType::ERZ; }

    eTileType() : m_TileType( UNKNOWN ) {}
    eTileType( EType type ) : m_TileType( type ) {}
    eTileType( uint32_t type ) : m_TileType( type ) {}
    bool isUnknown() const { return m_TileType == UNKNOWN; }
    bool isWasser() const { return contains( WASSER ); }
    bool isLand() const { return contains( LAND ); }
    bool isRessource() const { return contains( RESSOURCE_MASK ); }
    bool isHafen() const { return contains( HAFEN ); }

    bool contains( uint32_t flags ) const
    {
        return (m_TileType & flags) != 0;
    }

    void set( uint32_t flags ) { m_TileType = flags; }
    uint32_t get() const { return m_TileType; }
    operator uint32_t () const { return m_TileType; }

//    bool isRessource( eTileType tileType ) const
//    {
//        return ((m_TileType & RESSOURCE_MASK) & tileType) != 0;
//    }

    uint32_t getRessourceColor() const
    {
             if ( contains( HOLZ ) ) return 0xFF00C000;
        else if ( contains( LEHM ) ) return 0xFF0000FF;
        else if ( contains( WEIZEN ) ) return 0xFFFFFF00;
        else if ( contains( WOLLE ) ) return 0xFF60FF60;
        else if ( contains( ERZ ) ) return 0xFFFF0000;
        else return 0xFFFF00FF;
    }

    std::string getRessourceString() const
    {
             if ( contains( HOLZ ) ) return "holz";
        else if ( contains( LEHM ) ) return "lehm";
        else if ( contains( WEIZEN ) ) return "weizen";
        else if ( contains( WOLLE ) ) return "wolle";
        else if ( contains( ERZ ) ) return "erz";
        else return "";
    }

    std::string
    toString() const
    {
        if ( m_TileType == UNKNOWN ) return "UNKNOWN";
        if ( m_TileType == WASSER ) return "WASSER";

        std::stringstream s;

        if ( isLand() )
        {
            s << "LAND";
                 if ( contains( HOLZ ) ) s << "_HOLZ";
            else if ( contains( LEHM ) ) s << "_LEHM";
            else if ( contains( WEIZEN ) ) s << "_WEIZEN";
            else if ( contains( WOLLE ) ) s << "_WOLLE";
            else if ( contains( ERZ ) ) s << "_ERZ";
            else s << "_WUESTE";
        }
        else if ( isHafen() )
        {
            s << "HAFEN";
                 if ( contains( HOLZ ) ) s << "_HOLZ";
            else if ( contains( LEHM ) ) s << "_LEHM";
            else if ( contains( WEIZEN ) ) s << "_WEIZEN";
            else if ( contains( WOLLE ) ) s << "_WOLLE";
            else if ( contains( ERZ ) ) s << "_ERZ";
            else s << "_3zu1";
        }

        return s.str();
    }

    static eTileType
    fromString( std::string const & txt )
    {
        uint32_t tileType = eTileType::UNKNOWN;
             if ( txt == "WASSER" )        { tileType = eTileType::WASSER; }
        else if ( txt == "LAND" )          { tileType = eTileType::LAND; }
        else if ( txt == "LAND_HOLZ" )     { tileType = eTileType::LAND_HOLZ; }
        else if ( txt == "LAND_LEHM" )     { tileType = eTileType::LAND_LEHM; }
        else if ( txt == "LAND_WEIZEN" )   { tileType = eTileType::LAND_WEIZEN; }
        else if ( txt == "LAND_ERZ" )      { tileType = eTileType::LAND_ERZ; }
        else if ( txt == "LAND_WOLLE")     { tileType = eTileType::LAND_WOLLE; }
        else if ( txt == "HAFEN_3zu1")     { tileType = eTileType::HAFEN_3zu1; }
        else if ( txt == "HAFEN_HOLZ")     { tileType = eTileType::HAFEN_HOLZ; }
        else if ( txt == "HAFEN_LEHM")     { tileType = eTileType::HAFEN_LEHM; }
        else if ( txt == "HAFEN_WEIZEN")   { tileType = eTileType::HAFEN_WEIZEN; }
        else if ( txt == "HAFEN_WOLLE")    { tileType = eTileType::HAFEN_WOLLE; }
        else if ( txt == "HAFEN_ERZ")      { tileType = eTileType::HAFEN_ERZ; }

        return tileType;
    }

    uint32_t m_TileType;
};






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
