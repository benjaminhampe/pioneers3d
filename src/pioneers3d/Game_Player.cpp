#include "Game_Player.hpp"

#include <pioneers3d/Game_Texture.hpp>
#include <pioneers3d/Game_Bank.hpp>

#define PRINT_FUNCTION_NAME { std::cout << __FUNCTION__ << ":" << __LINE__ << "()\n"; }

namespace pioneers3d {

uint32_t
Player_getColor( Game_t* game, int32_t playerIndex )
{
    PRINT_FUNCTION_NAME
    if ( !Player_isValidIndex( game, playerIndex ) ) { return 0x00000000; }
//    switch( playerIndex )
//    {
//        case 1: return 0x00000000;
//    }
    return game->Players[ playerIndex ].Color;
}

int32_t
Player_getCount( Game_t* game )
{
    PRINT_FUNCTION_NAME
    if ( !game ) return 0;
    return game->Players.size();
}

bool
Player_isValidIndex( Game_t* game, int32_t playerIndex )
{
    PRINT_FUNCTION_NAME
    if ( !game ) return false;
    if ( playerIndex >= int32_t(game->Players.size()) ) return false;
    return true;
}

int32_t
Player_getCurrentIndex( Game_t* game )
{
    PRINT_FUNCTION_NAME
    if (!game) return -1;
    return game->Player;
}

Player_t*
Player_getCurrentData( Game_t* game )
{
    PRINT_FUNCTION_NAME
    int32_t playerIndex = Player_getCurrentIndex( game );
    if ( Player_isValidIndex( game, playerIndex ) )
    {
        return &game->Players[ playerIndex ];
    }
    return nullptr;
}

Player_t*
Player_getData( Game_t* game, int32_t playerIndex )
{
    PRINT_FUNCTION_NAME
    if ( Player_isValidIndex( game, playerIndex ) )
    {
        return &game->Players[ playerIndex ];
    }
    return nullptr;
}

void
Players_clear( Game_t* game )
{
    PRINT_FUNCTION_NAME
    game->Players.clear();
}

void
Players_create( Game_t* game )
{
    PRINT_FUNCTION_NAME
    // create 4 standard players

    auto addPlayer = [ game ] ( int id, std::string const & name ) -> void
    {
        Player_t player;
        player.Id = id;
        player.Name = name;
        player.Avatar = Game_getTexture( game, eTexture( uint32_t(eTexture::PLAYER_ICON) + id ) );
        Bank_clear( player.Bank );
        game->Players.emplace_back( std::move( player ) );
    };

    addPlayer( 1, "Benni" );
    addPlayer( 2, "Robot 1" );
    addPlayer( 3, "Robot 2" );
    addPlayer( 4, "Robot 3" );
}

} // end namespace pioneers3d
