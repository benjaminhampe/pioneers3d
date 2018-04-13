#include "Game_Waypoint.hpp"

#include <pioneers3d/Game_Texture.hpp>
#include <pioneers3d/Game_Tile.hpp>

#include <pioneers3d/Game_Logger.hpp>

namespace pioneers3d {

void Waypoints_print( Game_t * game )
{
    if (!game) return;

    uint32_t n = game->Waypoints.size();

    std::cout << "Waypoints.size() = " << n << "\n";

//    for ( size_t i = 0; i < n; ++i )
//    {
//        Waypoint_t * w = &game->Waypoints[ i ];
//        if ( w )
//        {
//            std::cout << "Waypoint["<<i<<"]", i, toString(w->Pos).c_str() ) );
//        }
//    }
}
void Waypoints_clear( Game_t* game )
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
            //std::cout << __FUNCTION__ << " [Found] :: Waypoint(" << i << ") at pos(" << toString(pos) << ")\n";
            return w;
        }
    }

    return nullptr;
}

void Waypoint_add( Game_t * game, float32_t r,float32_t h, uint32_t tesselation, glm::vec3 pos, bool isRoad )
{
    assert ( game );
    assert ( game->Device );
    irr::scene::ISceneManager* smgr = game->Device->getSceneManager();

    Waypoint_t* found = Waypoint_findByPosition( game, pos );
    if ( found )
    {
        // std::cout << __FUNCTION__ << "(" << r << "," << h << "," << toString(pos) << ")\n";
        return;
    }

    irr::video::ITexture* tex = nullptr;
    irr::video::SColor color = 0xFFFFFFFF;
    if ( isRoad )
    {
        tex = Game_getTexture( game, eTexture::CHIP_W ); // W - Waypoint - A simple waypoint for roads
        color = 0xFFFFFF00;
    }
    else
    {
        tex = Game_getTexture( game, eTexture::CHIP_S ); // S - Settlement point - A waypoint that can have buildings.
        color = 0xFFFF0000;
    }

    AutoSceneNode* node = new AutoSceneNode( smgr, smgr->getRootSceneNode(), -1 );
    node->setPosition( pos );

    AutoMeshBuffer* hull = createCylinderHull( glm::vec3(0.0f, 0.5f*h, 0.0f), r, h, color.color, tesselation, 1 );
    //hull->MeshBuffer.Material.setTexture( 0, tex );
    node->add( hull, true );

    AutoMeshBuffer* top = createCircleXZ( glm::vec3( 0.0f, h, 0.0f ), r, tesselation );
    top->MeshBuffer.Material.setTexture( 0, tex );
    node->add( top, true );

    Waypoint_t way;
    way.IsRoad = isRoad;
    way.Pos = pos;
    way.Node = node;
    game->Waypoints.push_back( way );

    std::cout << __FUNCTION__ << ((isRoad) ? "R" : "S") << "(" << r << "," << h << "," << toString(pos) << ")\n";
}

void Waypoints_create( Game_t * game, float32_t radius, float32_t height, uint32_t tesselation, bool isRoad )
{
    assert ( game );

    for ( uint32_t i = 0; i < game->Tiles.size(); ++i )
    {
        Tile_t * tile = &game->Tiles[ i ];

        for ( uint32_t k = 1; k <= 6; ++k )
        {
            if ( !tile->Type.isWasser() && tile->Type != eTileType::LAND_WUESTE )
            {
                float32_t w = game->TileSize.x;
                float32_t h = game->TileSize.z;

                glm::vec3 pos;
                if ( isRoad )
                {
                    pos = Tile_getEdgeCenter( tile, k, w, h );
                }
                else
                {
                    pos = Tile_getCorner( tile, k, w, h );
                }

                Waypoint_add( game, radius, height, tesselation, pos, isRoad );
            }
        }
    }

    std::cout << __FUNCTION__ << "() :: added ("<< game->Waypoints.size() << ") waypoints of type (" << ( isRoad ? "R" : "S" )<< ").\n";
}

} // end namespace pioneers3d
