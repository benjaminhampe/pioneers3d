#include <pioneers3d/Game_Player.hpp>
#include <pioneers3d/Game_Texture.hpp>
#include <pioneers3d/Game_Bank.hpp>
#include <pioneers3d/Game_Waypoint.hpp>

namespace pioneers3d {

uint32_t Player_getNumRoads( Game_t* game )
{
    if ( !game ) return 0;
    Player_t * player = getPlayer( game );
    if ( !player ) return 0;
    return player->NumRoads;
}

uint32_t Player_getNumSettlements( Game_t* game )
{
    if ( !game ) return 0;
    Player_t * player = getPlayer( game );
    if ( !player ) return 0;
    return player->NumSettlements;
}

uint32_t Player_getNumCities( Game_t* game )
{
    if ( !game ) return 0;
    Player_t * player = getPlayer( game );
    if ( !player ) return 0;
    return player->NumCities;
}

uint32_t Player_getNumRessource( Game_t* game, eTileType resType )
{
    if ( !game ) return 0;
    Player_t * player = getPlayer( game );
    if ( !player ) return 0;
    return player->Bank.getRessource( resType );
}

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

    Waypoints_R_setVisible( game, false );

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

    Waypoints_S_setVisible( game, false );

    if ( game->Round >= 3 )
    {
        //player->Bank.buyRoad();
    }
}

void Player_addCity( Game_t* game, Waypoint_t* w )
{
    Waypoints_S_setVisible( game, false );
}

uint32_t
getPlayerCount( Game_t* game )
{
    if ( !game ) return 0;
    return game->Players.size();
}

bool
isPlayer( Game_t* game, uint32_t playerIndex )
{
    if ( !game ) return false;
    if ( playerIndex >= getPlayerCount( game ) ) return false;
    return true;
}

Player_t*
getPlayer( Game_t* game, uint32_t playerIndex )
{
    if ( !isPlayer( game, playerIndex ) ) return nullptr;
    return &game->Players[ playerIndex ];
}

uint32_t
Player_getColor( Game_t* game, uint32_t playerIndex )
{
    Player_t* player = getPlayer( game, playerIndex );
    if ( !player ) { return 0xFFFFFFFF; }
    return player->Color;
}

std::string
Player_getName( Game_t* game, uint32_t playerIndex )
{
    Player_t* player = getPlayer( game, playerIndex );
    if ( !player ) { return "Unnamed"; }
    return player->Name;
}

eAction
Player_getAction( Game_t* game, uint32_t playerIndex )
{
    Player_t* player = getPlayer( game, playerIndex );
    if ( !player ) { return eAction::UNKNOWN; }
    return player->Action;
}

void
Player_setAction( Game_t* game, uint32_t playerIndex, eAction action )
{
    Player_t* player = getPlayer( game, playerIndex );
    if ( !player ) { return; }
    player->Action = action;
}

bool
Player_isActionEnabled( Game_t* game, uint32_t playerIndex, eAction action )
{
    Player_t* player = getPlayer( game, playerIndex );
    if ( !player ) { return false; }
    return ( player->Action.m_Action & uint32_t( action ) ) != 0;
}

void
Player_setActionEnabled( Game_t* game, uint32_t playerIndex, eAction action, bool enable )
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
togglePlayerAction( Game_t* game, uint32_t playerIndex, eAction action )
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
    assert( game );
    game->Players.clear();
}

void
createStandardPlayers( Game_t* game )
{
    assert( game );

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
    //addPlayer( 3, "Robot 2", 0xFFFFFF00 );
    //addPlayer( 4, "Robot 3", 0xFF0000FF );
}

} // end namespace pioneers3d
