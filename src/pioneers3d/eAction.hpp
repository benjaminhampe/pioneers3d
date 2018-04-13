#ifndef GAME_EACTION_HPP
#define GAME_EACTION_HPP

#include <stdint.h>
#include <sstream>

namespace pioneers3d {

class eAction
{
public:
    enum EAction : uint32_t
    {
        UNKNOWN         = 0,
        ENDTURN         = 1,
        DICE            = 1<<1,
        BANK            = 1<<2,
        TRADE           = 1<<3,
        BUY_EVENT_CARD  = 1<<4,
        BUY_ROAD        = 1<<5,
        BUY_SETTLEMENT  = 1<<6,
        BUY_CITY        = 1<<7,
        PLAY_EVENT_CARD = 1<<8,
        PLACE_ROAD      = 1<<9,
        PLACE_SETTLEMENT= 1<<10,
        PLACE_CITY      = 1<<11,
        PLACE_ROBBER    = 1<<12,
        LOOSE           = 1<<13,
        WIN             = 1<<14,
        COUNT           = 15,
        DEFAULT_MASK = ENDTURN | DICE | BANK | TRADE | WIN | LOOSE,
        BUY_MASK = BUY_EVENT_CARD | BUY_ROAD | BUY_SETTLEMENT | BUY_CITY,
        PLAY_MASK = PLAY_EVENT_CARD,
        PLACE_MASK = PLACE_ROBBER | PLACE_ROAD | PLACE_SETTLEMENT | PLACE_CITY,
        ACTION_MASK = DEFAULT_MASK | BUY_MASK | PLAY_MASK | PLACE_MASK
    };

    static bool
    isAction( uint32_t action )
    {
        return (action & uint32_t( ACTION_MASK )) != 0;
    }

    static bool
    contains( uint32_t action, uint32_t flags )
    {
        return (action & flags) != 0;
    }

    eAction() : m_Action( UNKNOWN ) {}
    eAction( EAction action ) : m_Action( static_cast< uint32_t >( action ) ) {}
    eAction( uint32_t action ) : m_Action( action ) {}

    operator uint32_t() const { return m_Action; }

    uint32_t getValue() const { return m_Action; }
    void setValue( uint32_t value ) { m_Action = value; }

    bool contains( EAction action ) const
    {
        return contains( m_Action, uint32_t( action ) );
    }

    void setEnabled( EAction action, bool doEnable )
    {
        if ( doEnable )
        {
            m_Action |= uint32_t( action );
        }
        else
        {
            m_Action &= ~uint32_t( action );
        }
    }

    void toggle( EAction action )
    {
        if ( contains( action ) )
        {
            m_Action &= ~uint32_t( action );  // disable
        }
        else
        {
            m_Action |= uint32_t( action );  // enable
        }
    }

    uint32_t m_Action;

};

} // end namespace pioneers3d


#endif // GAME_EACTION_HPP
