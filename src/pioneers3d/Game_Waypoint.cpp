#include "Game_Waypoint.hpp"

#include <pioneers3d/Game_Texture.hpp>
#include <pioneers3d/Game_Tile.hpp>

#include <pioneers3d/Game_Logger.hpp>

namespace pioneers3d {

void setWaypointsVisible( Game_t* game, bool visible )
{
    if (!game) return;

    size_t const n = game->Waypoints.size();

    std::cout << __FUNCTION__ << "(" << n << "," << visible << ")\n";

    for ( size_t i = 0; i < n; ++i )
    {
        irr::scene::ISceneNode* node = game->Waypoints[ i ].Node;
        if ( node )
        {
            node->setVisible( visible );
        }
    }
}

void setWaypointsVisible( Game_t* game, bool visible, bool isRoad )
{
    if (!game) return;

    size_t const n = game->Waypoints.size();

    std::cout << __FUNCTION__ << "(" << n << "," << visible << "," << isRoad << ")\n";

    for ( size_t i = 0; i < n; ++i )
    {
        if ( game->Waypoints[ i ].IsRoad == isRoad )
        {
            irr::scene::ISceneNode* node = game->Waypoints[ i ].Node;
            if ( node )
            {
                node->setVisible( visible );
            }
        }
    }
}

void printWaypoints( Game_t * game )
{
    if (!game) return;

    uint32_t n = game->Waypoints.size();

    std::cout << "Waypoints.size() = " << n << "\n";

    for ( size_t i = 0; i < n; ++i )
    {
        Waypoint_t * w = &game->Waypoints[ i ];
        if ( w )
        {
            std::cout << "Waypoint[" << i << "] " << toString( w->Pos) << "\n";
        }
    }
}

void clearWaypoints( Game_t* game )
{
    if (!game) return;
    for ( size_t i = 0; i < game->Waypoints.size(); ++i )
    {
        Waypoint_t & w = game->Waypoints[ i ];
        if ( w.Node )
        {
            w.Node->drop();
            w.Node = nullptr;
        }
    }
    game->Waypoints.clear();
}

Waypoint_t* findWaypoint( Game_t * game, glm::vec3 pos )
{
    if ( !game ) return nullptr;

    for ( uint32_t i = 0; i < game->Waypoints.size(); ++i )
    {
        Waypoint_t & w = game->Waypoints[ i ];
        if ( equals( w.Pos, pos ) )
        {
            //std::cout << __FUNCTION__ << " [Found] :: Waypoint(" << i << ") at pos(" << toString(pos) << ")\n";
            return &w;
        }
    }

    return nullptr;
}

void addWaypoint( Game_t * game, float32_t r,float32_t h, uint32_t tesselation, glm::vec3 pos, bool isRoad )
{
    assert ( game );
    assert ( game->Device );
    irr::scene::ISceneManager* smgr = game->Device->getSceneManager();

    Waypoint_t* found = findWaypoint( game, pos );
    if ( found )
    {
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

    // Create triangle-selector for cylinder collision detection
    irr::scene::ITriangleSelector* selector = smgr->createTriangleSelector( node->getMesh(), node );
    node->setTriangleSelector( selector );
    game->WaypointSelector->addTriangleSelector( selector );
    selector->drop();

    std::cout << __FUNCTION__ << ((isRoad) ? "R" : "S") << "(" << r << "," << h << "," << toString(pos) << ")\n";

    game->Waypoints.emplace_back( std::move( way ) );
}

void createWaypoints( Game_t * game, float32_t radius, float32_t height, uint32_t tesselation, bool isRoad )
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
                    pos = getTileEdgeCenter( tile, k, w, h );
                }
                else
                {
                    pos = getTileCorner( tile, k, w, h );
                }

                addWaypoint( game, radius, height, tesselation, pos, isRoad );
            }
        }
    }

    std::cout << __FUNCTION__ << "() :: added ("<< game->Waypoints.size() << ") waypoints of type (" << ( isRoad ? "R" : "S" )<< ").\n";
}

} // end namespace pioneers3d
