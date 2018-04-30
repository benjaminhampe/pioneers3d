#ifndef GAME_BANK_HPP
#define GAME_BANK_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

struct Bank_t
{
    int32_t Holz = 0;			// Anzahl Holz
    int32_t Lehm = 0;			// Anzahl Lehm
    int32_t Weizen = 0;			// Anzahl Weizen
    int32_t Wolle = 0;			// Anzahl Wolle
    int32_t Erz = 0;			// Anzahl Erz
    std::string Name = "Bank";

    void clear()
    {
        Holz = Lehm = Weizen = Wolle = Erz = 0;
    }

    int32_t getTotal() const
    {
        return Holz + Lehm + Weizen + Wolle + Erz;
    }

    bool canRobberSteal() const
    {
        return getTotal() >= 7;
    }

    std::string toString() const
    {
        std::stringstream s;
        s << "Bank: "<< Name << "; "
        << "Holz:" << Holz << "; "
        << "Lehm:" << Lehm << "; "
        << "Weizen:" << Weizen << "; "
        << "Wolle:" << Wolle << "; "
        << "Erz:" << Erz << "; "
        << ";";
        return s.str();
    }

    int32_t get( eTileType type ) const
    {
        int32_t n = 0;
        if ( type.contains( eTileType::HOLZ ) ) n += Holz;
        if ( type.contains( eTileType::LEHM ) ) n += Lehm;
        if ( type.contains( eTileType::WEIZEN ) ) n += Weizen;
        if ( type.contains( eTileType::WOLLE ) ) n += Wolle;
        if ( type.contains( eTileType::ERZ ) ) n += Erz;
        return n;
    }

    void set( eTileType type, int32_t value )
    {
        if ( type.contains( eTileType::HOLZ ) ) Holz=value;
        if ( type.contains( eTileType::LEHM ) ) Lehm=value;
        if ( type.contains( eTileType::WEIZEN ) ) Weizen=value;
        if ( type.contains( eTileType::WOLLE ) ) Wolle=value;
        if ( type.contains( eTileType::ERZ ) ) Erz=value;
    }

    void add( eTileType type, int32_t value )
    {
        if ( type.contains( eTileType::HOLZ ) ) Holz+=value;
        if ( type.contains( eTileType::LEHM ) ) Lehm+=value;
        if ( type.contains( eTileType::WEIZEN ) ) Weizen+=value;
        if ( type.contains( eTileType::WOLLE ) ) Wolle+=value;
        if ( type.contains( eTileType::ERZ ) ) Erz+=value;
    }
};

/*
void    Bank_clear( Bank_t & bank );
void    Bank_addRessource( Bank_t & bank, eTileType tileType );
int     Bank_getRessourceCount( Bank_t const & bank );
bool    Bank_canRobberSteal( Bank_t const & bank );
std::string Bank_toString( Bank_t const & bank );
*/

} // end namespace pioneers3d

#endif // GAME_BANK_HPP
