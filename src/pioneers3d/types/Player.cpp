#include <pioneers3d/types/Player.hpp>
#include <pioneers3d/types/Game.hpp>

namespace pioneers3d {

std::string
Player_t::toString() const
{
    std::stringstream s;
    s << "name: " << Name << "; "
      << "";
    return s.str();
}

void
clearPlayers( Game_t* game )
{
   assert( game );
   game->Players.clear();
}

void
addStandardPlayer( Game_t* game, int id, std::string const & name, uint32_t color )
{
   assert( game );
   Player_t player;
   player.Id = id;
   player.Name = name;
   player.Color = color;
   player.Avatar = Game_getTexture( game, eTexture( uint32_t(eTexture::PLAYER_ICON) + id ) );
   player.Bank.clear();
   game->Players.emplace_back( std::move( player ) );
}

void
createStandardPlayers( Game_t* game )
{
    assert( game );
    addStandardPlayer( game, 1, "Benni", 0xFF30ED30 );
    addStandardPlayer( game, 2, "Robot 1", 0xFFFF0000 );
    // addStandardPlayer( game, 3, "Robot 2", 0xFFFFFF00 );
    // addStandardPlayer( game, 4, "Robot 3", 0xFF0000FF );
}

int32_t
getPlayerCount( Game_t* game )
{
    if ( !game ) return 0;
    return int32_t( game->Players.size() );
}

// get a player by index
Player_t*
getPlayer( Game_t* game, int32_t i )
{
   assert( game );
   if ( i < 0 || i >= getPlayerCount( game ) )
   {
      return nullptr;
   }
   return &game->Players[ i ];
}

// get current player
Player_t*
getPlayer( Game_t* game )
{
   assert( game );
   return getPlayer( game, game->Player );
}


/*
uint32_t Player_getActionMask( Game_t* game, int player )
{
    if ( !game )
    {
        return 0x00000000;
    }
    if ( player >= game->Players.size() )
    {
        return 0x00000000;
    }
    return game->Players[ player].ActionMask;
}

uint32_t Player_setActionMask( Game_t* game, int player, uint32_t actionMask )
{
    if ( !game )
    {
        return 0x00000000;
    }
    if ( player >= game->Players.size() )
    {
        return 0x00000000;
    }
    game->Players[ player].ActionMask = actionMask;
}
*/

void Player_addRoad( Game_t* game, Waypoint_t* w )
{
    if ( !game ) return;
    if ( !w ) return;
    Player_t * player = getPlayer( game );
    if ( !player ) return;

    game->PlaceObject->setPosition( toIRR( w->Pos ) );
    game->PlaceObject->setRotation( irr::core::vector3df( 0, w->Angle, 0 ) );

    w->Owner = player;
    w->OwnerNode = game->PlaceObject;
    w->Points = 0;

    player->NumRoads++;
    player->Waypoints.emplace_back( w );

    game->PlaceObject = nullptr;

    Board_hideWaypointsR( game );

    if ( game->Round >= 3 )
    {
        //player->Bank.buyRoad();
    }
}

void Player_addSettlement( Game_t* game, Waypoint_t* w )
{
    if ( !game ) return;
    if ( !w ) return;
    Player_t * player = getPlayer( game );
    if ( !player ) return;
    w->Owner = player;
    w->OwnerNode = game->PlaceObject;
    w->OwnerNode->setPosition( toIRR( w->Pos ) );
    w->Points = 1;

    player->NumSettlements++;
    player->Waypoints.emplace_back( w );

    game->PlaceObject = nullptr;

    Board_hideWaypointsS( game );

    if ( game->Round >= 3 )
    {
        //player->Bank.buyRoad();
    }
}

void Player_addCity( Game_t* game, Waypoint_t* w )
{
    //Board_hideWaypointsR( game, false );
}


} // end namespace pioneers3d
