#ifndef PIONEERS3D_PLAYER_DATA_HPP
#define PIONEERS3D_PLAYER_DATA_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

class Player_t
{
public:
    Player_t( int id, std::string const & name );
    ~Player_t();

    std::string
    toXML() const;

public:
    int Id;                 // Player id
    std::string Name;       // Player name
    bool IsActive;			// sagt aus ob Player in der Runde aktiviert ist.
    uint32_t Color;			// Player color
    int Type;				// Player type //0=Human, 1=CPU, 2=HumanTCP/IP, 3=HumanLAN

    short Dice1;			// Würfelwert
    short Dice2;			// Würfelwert

    int nErz;				// Anzahl Erz
    int nHolz;				// Anzahl Holz
    int nLehm;				// Anzahl Lehm
    int nWeizen;			// Anzahl Weizen
    int nWolle;				// Anzahl Wolle
    //int nCards;           // Anzahl Rohstoffkarten

    int nVictoryPoints;		// Anzahl Siegpunkte
    int nRoads;             // Anzahl Strassen
    int nSettlements;       // Anzahl Siedlungen
    int nCities;            // Anzahl Städte
    int nKnightCards;		// Anzahl Ritterkarten
    int nVictoryCards;      // Anzahl Siegpunktkarten
    int nEventCards;        // Anzahl Ereigniskarten

    bool HasBonusArmy;      // Rittermacht
    bool HasBonusTrade;     // Laengste Handelsroute

    bool hasHafen3zu1;		// Has Player Hafen-3zu1
    bool hasHafenErz;		// Has Player Hafen-Erz
    bool hasHafenHolz;		// Has Player Hafen-Holz
    bool hasHafenLehm;		// Has Player Hafen-Lehm
    bool hasHafenWeizen;	// Has Player Hafen-Weizen
    bool hasHafenWolle;		// Has Player Hafen-Wolle

//	int IconId;				// Icon des Players 64x64
//	int IconBorder;         // Rahmen des Playericons 64x64
//	int icon_strasse;		// Icon Strasse
//	int icon_siedlung;		// Icon Siedlung
//	int icon_stadt;			// Icon Stadt
//	int tex_holz;			// Textur für Strassen, Siedlungen und Städte

};


} // end namespace pioneers3d

#endif // PIONEERS3D_PLAYER_DATA_HPP
