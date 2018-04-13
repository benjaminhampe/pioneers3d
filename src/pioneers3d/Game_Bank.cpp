#include "Game_Bank.hpp"

namespace pioneers3d {

void Bank_clear( Bank_t & bank )
{
    bank.Holz = 0;
    bank.Lehm = 0;
    bank.Weizen = 0;
    bank.Wolle = 0;
    bank.Erz = 0;
}

void Bank_addRessource( Bank_t & bank, eTileType tt )
{
    if ( tt.contains( eTileType::HOLZ ) ) bank.Holz++;
    if ( tt.contains( eTileType::LEHM ) ) bank.Lehm++;
    if ( tt.contains( eTileType::WEIZEN ) ) bank.Weizen++;
    if ( tt.contains( eTileType::WOLLE ) ) bank.Wolle++;
    if ( tt.contains( eTileType::ERZ ) ) bank.Erz++;
}

int Bank_getResourceCount( Bank_t const & bank )
{
    return bank.Holz + bank.Lehm + bank.Weizen + bank.Wolle + bank.Erz;
}

bool Bank_canRobberSteal( Bank_t const & bank )
{
    return Bank_getResourceCount( bank ) >= 7;
}

std::string Bank_toString( Bank_t const & bank )
{
    std::stringstream s;
    s << "Bank["<< bank.Name << "] { "
    << "Holz:" << bank.Holz << "; "
    << "Lehm:" << bank.Lehm << "; "
    << "Weizen:" << bank.Weizen << "; "
    << "Wolle:" << bank.Wolle << "; "
    << "Erz:" << bank.Erz << "; "
    << " }";
    return s.str();
}


} // end namespace pioneers3d
