#include "Game_Players.hpp"

#include <pioneers3d/Game_Textures.hpp>

namespace pioneers3d {

void Game_clearPlayers( Game_t* game )
{
    game->Players.clear();
}

void Game_createPlayers( Game_t* game )
{
    // create 4 standard players
    game->Players.clear();

    auto addPlayer = [ game ] ( int id, std::string const & name ) -> void
    {
        Player_t player;
        player.Id = id;
        player.Name = name;
        player.Avatar = Game_getTexture( game, eTexture( uint32_t(eTexture::PLAYER_ICON) + id ) );
        game->Players.emplace_back( std::move( player ) );
    };

    addPlayer( 1, "Benni" );
    addPlayer( 2, "Robot 1" );
    addPlayer( 3, "Robot 2" );
    addPlayer( 4, "Robot 3" );
}

} // end namespace pioneers3d
