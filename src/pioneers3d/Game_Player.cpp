#include "Game_Player.hpp"

#include <pioneers3d/Game_Texture.hpp>
#include <pioneers3d/Game_Bank.hpp>

#define PRINT_FUNCTION_NAME { std::cout << __FUNCTION__ << ":" << __LINE__ << "()\n"; }

namespace pioneers3d {

uint32_t
getPlayerColor( Game_t* game, int32_t playerIndex )
{
//    PRINT_FUNCTION_NAME
    if ( !isPlayer( game, playerIndex ) ) { return 0x00000000; }
    return game->Players[ playerIndex ].Color;
}

std::string
getPlayerName( Game_t* game, int32_t playerIndex )
{
//    PRINT_FUNCTION_NAME
    if ( !isPlayer( game, playerIndex ) ) { return "Unknown Player"; }
    return game->Players[ playerIndex ].Name;
}


int32_t
getPlayerCount( Game_t* game )
{
//    PRINT_FUNCTION_NAME
    if ( !game ) return 0;
    return int32_t( game->Players.size() );
}

bool
isPlayer( Game_t* game, int32_t playerIndex )
{
//    PRINT_FUNCTION_NAME
    assert( game );
    if ( playerIndex < 0 ) return false;
    if ( playerIndex >= int32_t(game->Players.size()) ) return false;
    return true;
}

int32_t
getCurrentPlayer( Game_t* game )
{
//    PRINT_FUNCTION_NAME
    assert( game );
    return game->Player;
}

Player_t*
getPlayer( Game_t* game, int32_t playerIndex )
{
//    PRINT_FUNCTION_NAME
    if ( !game ) return nullptr;
    if ( !isPlayer( game, playerIndex ) ) return nullptr;
    return &game->Players[ playerIndex ];
}

eAction
getPlayerAction( Game_t* game, int32_t playerIndex )
{
    Player_t* player = getPlayer( game, playerIndex );
    if ( !player ) { return eAction::UNKNOWN; }
    return player->Action;
}

void
setPlayerAction( Game_t* game, int32_t playerIndex, eAction action )
{
    Player_t* player = getPlayer( game, playerIndex );
    if ( !player ) { return; }
    player->Action = action;
}

bool
isPlayerActionEnabled( Game_t* game, int32_t playerIndex, eAction action )
{
    Player_t* player = getPlayer( game, playerIndex );
    if ( !player ) { return false; }
    return ( player->Action.m_Action & uint32_t( action ) ) != 0;
}

void
setPlayerActionEnabled( Game_t* game, int32_t playerIndex, eAction action, bool enable )
{
    Player_t* player = getPlayer( game, playerIndex );
    if ( !player ) { return; }
    if ( enable )
    {
        player->Action.m_Action |= uint32_t( action );
    }
    else
    {
        player->Action.m_Action &= ~uint32_t( action );
    }
}

void
togglePlayerAction( Game_t* game, int32_t playerIndex, eAction action )
{
    Player_t* player = getPlayer( game, playerIndex );
    if ( !player ) { return; }
    if ( player->Action.m_Action & uint32_t( action ) )
    {
        player->Action.m_Action &= ~uint32_t( action );
    }
    else
    {
        player->Action.m_Action |= uint32_t( action );
    }
}


void
clearPlayers( Game_t* game )
{
    PRINT_FUNCTION_NAME
    assert( game );
    game->Players.clear();
}

void
createStandardPlayers( Game_t* game )
{
    PRINT_FUNCTION_NAME
    assert( game );
    // create 4 standard players

    auto addPlayer = [ game ] ( int id, std::string const & name, uint32_t color ) -> void
    {
        Player_t player;
        player.Id = id;
        player.Name = name;
        player.Color = color;
        player.Avatar = Game_getTexture( game, eTexture( uint32_t(eTexture::PLAYER_ICON) + id ) );
        Bank_clear( player.Bank );
        game->Players.emplace_back( std::move( player ) );
    };

    addPlayer( 1, "Benni", 0xFF30ED30 );
    addPlayer( 2, "Robot 1", 0xFFFF0000 );
    addPlayer( 3, "Robot 2", 0xFFFFFF00 );
    addPlayer( 4, "Robot 3", 0xFF0000FF );
}

} // end namespace pioneers3d
