#include "Game_Waypoints.hpp"

#include <pioneers3d/Game_Textures.hpp>
#include <pioneers3d/Game_Tiles.hpp>

#include <pioneers3d/Game_Logger.hpp>

namespace pioneers3d {

void Game_printWaypoints( Game_t * game )
{
    if (!game) return;
    GAME_LOG_ERROR( de::alphasonic::sprintf( "Waypoint.size() = %d", game->Waypoints.size() ) );

    for ( size_t i = 0; i < game->Waypoints.size(); ++i )
    {
        Waypoint_t * w = &game->Waypoints[ i ];
        if ( w )
        {
            GAME_LOG_ERROR( de::alphasonic::sprintf( "Waypoint[%d].Pos = (%s)", i, toString(w->Pos).c_str() ) );
        }
    }
}
void Game_clearWaypoints( Game_t* game )
{
    if (!game) return;
//    for ( size_t i = 0; i < game->Waypoints.size(); ++i )
//    {
//        Waypoint_t * w = game->Waypoints[ i ];
//        if ( w )
//        {
//            delete w;
//        }
//    }
    game->Waypoints.clear();
}


Waypoint_t* Waypoint_findByPosition( Game_t * game, glm::vec3 pos )
{
    if ( !game ) return nullptr;

    for ( uint32_t i = 0; i < game->Waypoints.size(); ++i )
    {
        Waypoint_t * w = &game->Waypoints[ i ];
        if ( equals( w->Pos, pos ) )
        {
            GAME_LOG_ERROR( de::alphasonic::sprintf( "Found waypoint[%d] at pos(%s)", i, toString(pos).c_str() ) )
            return w;
        }
    }

    return nullptr;
}

void Game_createWaypoints( Game_t * game )
{
    if ( !game ) { GAME_LOG_ERROR("Invalid pointer to Game") return; }
    if ( !game->Device ) { GAME_LOG_ERROR("Invalid pointer to IrrlichtDevice") return; }
    irr::scene::ISceneManager* smgr = game->Device->getSceneManager();
    if ( !smgr ) { GAME_LOG_ERROR("Invalid pointer to ISceneManager") return; }
    game->Waypoints.clear();

    auto addWaypoint = [game,smgr] ( glm::vec3 pos ) -> void
    {
        assert ( game );

        Waypoint_t* found = Waypoint_findByPosition( game, pos );
        if ( found )
            return;

        //Waypoint_t* found = Game_findWaypoint( game, pos );
        //if ( !found )
        //return;
        irr::video::ITexture* tex = Game_getTexture( game, eTexture::CHIP_S );

        AutoSceneNode* node = new AutoSceneNode( smgr, smgr->getRootSceneNode(), -1 );
        node->setPosition( pos );

        AutoMeshBuffer* hull = createCylinderHull( glm::vec3(0.0f, 2.5f, 0.0f), 10.0f, 5.0f, 0xFFFFFFFF, 16, 1 );
        hull->MeshBuffer.Material.setTexture( 0, tex );
        node->add( hull, true );

        AutoMeshBuffer* top = createCircleXZ( glm::vec3( 0.0f, 5.0f, 0.0f ), 10.0f, 16 );
        top->MeshBuffer.Material.setTexture( 0, tex );
        node->add( top, true );

        Waypoint_t way;
        way.Pos = pos;
        way.Node = node;
        game->Waypoints.push_back( way );
    };

    for ( uint32_t i = 0; i < game->Tiles.size(); ++i )
    {
        Tile_t * tile = &game->Tiles[ i ];

        for ( uint32_t k = 0; k < 6; ++k )
        {
            glm::vec3 const pos = Tile_getCorner( tile, k, game->TileSize.x, game->TileSize.z );

            if ( tile->Type != eTileType::WASSER && tile->Type != eTileType::LAND_WUESTE )
            {
                addWaypoint( pos );
            }
        }
    }

    GAME_LOG_ERROR( de::alphasonic::sprintf( "added (%d) waypoints", game->Waypoints.size() ) )
}

} // end namespace pioneers3d
