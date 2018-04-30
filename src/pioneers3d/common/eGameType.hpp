/// (c) 2017 - 2018 Benjamin Hampe <benjaminhampe@gmx.de>
/// All rights reserved, except the following natural persons:
/// Only free for Persian princesses that have a github account
/// and upgrade their PC (personal flying carpet) with a Raspberry Pi,
/// or people that speak AND live the words of Jesus Christ.

#ifndef PIONEERS3D_E_GAME_TYPE_HPP
#define PIONEERS3D_E_GAME_TYPE_HPP

#include <common/Types.hpp>

namespace pioneers3d {

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

} // end namespace pioneers3d

#endif // PIONEERS3D_TYPES_HPP
