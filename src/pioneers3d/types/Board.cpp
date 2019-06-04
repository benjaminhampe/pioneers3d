#include <pioneers3d/types/Board.hpp>
#include <pioneers3d/types/Game.hpp>
#include <iostream>

std::ostream &
operator<< ( std::ostream & o, pioneers3d::Tile_t const & t )
{
    o << "type: " << t.Type.toString() << "; "
      << "i: "<< t.BoardIndex.x << "; "
      << "j: "<< t.BoardIndex.y << "; "
      << "x: "<< t.Pos.x << "; "
      << "y: "<< t.Pos.y << "; "
      << "z: "<< t.Pos.z << "; "
      << "dice: "<< t.DiceValue << "; "
      << "ang60: "<< t.Angle60 << "; "
      << "waypoints: "<< t.Waypoints.size() << "; "
      << "";
    return o;
}


std::ostream &
operator<< ( std::ostream & o, pioneers3d::Board_t const & b )
{
    o << "board-name(" << b.Name << "), "
      << "board-type("<< b.Type << "), "
      << "tiles("<< b.Tiles.size() << "), "
      << "waypoints("<< b.Waypoints.size() << ")";
    return o;
}


namespace pioneers3d {

Tile_t::Tile_t()
   : Board( nullptr )
   , Type( TileType::WASSER )
   , BoardIndex()
   , Pos()
   , Size()
   , DiceValue( 0 )
   , Angle60( 0 ) // in range [0...5]
   , Waypoints{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr }  // Corners of the graph
   , Tiles{ nullptr, nullptr, nullptr } // Neighbours
   //, Roads;      // (Full) Edges of the graph
   , Triangles()
   , Node( nullptr )
   , TriangleSelector( nullptr )
{

}

Tile_t::~Tile_t()
{
   // if (Node) Node->drop();
}


int32_t
Tile_t::getPlayerPoints( int playerIndex ) const
{
   int32_t victoryPoints = 0;

   for ( size_t i = 0; i < Waypoints.size(); ++i )
   {
      Waypoint_t const * const w = Waypoints[ i ];
      if ( w && w->Player == playerIndex )
      {
         victoryPoints += w->VictoryPoints;
      }
   }

   return victoryPoints;
}


const char* const s_xmlStandardTiles = {
R"(
<!-- Zeile -3: (4-tiles) -->
<tile type="HAFEN_LEHM" x="-2" y="-3" dice="0" a="3" />
<tile type="WASSER" 	x="-1" y="-3" dice="0" a="3" />
<tile type="HAFEN_3zu1" x="0" y="-3" dice="0" a="3" />
<tile type="WASSER" 	x="1" y="-3" dice="0" a="2" />

<!-- Zeile -2: (5-tiles) -->
<tile type="WASSER" 	 x="-2" y="-2" dice="0" a="4" />
<tile type="LAND_WEIZEN" x="-1" y="-2" dice="3" a="0" />
<tile type="LAND_WEIZEN" x="0" y="-2" dice="6" a="0" />
<tile type="LAND_ERZ" 	 x="1" y="-2" dice="11" a="0" />
<tile type="HAFEN_WEIZEN" x="2" y="-2" dice="0" a="1" />

<!-- Zeile -1: (6-tiles) -->
<tile type="HAFEN_3zu1" x="-3" y="-1" dice="0" a="3" />
<tile type="LAND_HOLZ" 	x="-2" y="-1" dice="3" a="0" />
<tile type="LAND_ERZ" 	x="-1" y="-1" dice="5" a="0" />
<tile type="LAND_LEHM" 	x="0" y="-1" dice="10" a="0" />
<tile type="LAND_HOLZ" 	x="1" y="-1" dice="11" a="0" />
<tile type="WASSER" 	x="2" y="-1" dice="0" a="2" />

<!-- Zeile 0: (7-tiles) -->
<tile type="WASSER" x="-3" y="0" dice="0" a="4" />
<tile type="LAND_WOLLE" x="-2" y="0" dice="9" a="0" />
<tile type="LAND_LEHM" x="-1" y="0" dice="8" a="0" />
<tile type="LAND_WUESTE" x="0" y="0" dice="0" a="0" />
<tile type="LAND_ERZ" x="1" y="0" dice="8" a="0" />
<tile type="LAND_WOLLE" x="2" y="0" dice="10" a="0" />
<tile type="HAFEN_3zu1" x="3" y="0" dice="0" a="1" />

<!-- Zeile +1: (6-tiles) -->
<tile type="HAFEN_HOLZ" x="-3" y="1" dice="0" a="4" />
<tile type="LAND_LEHM"  x="-2" y="1" dice="2" a="0" />
<tile type="LAND_HOLZ"  x="-1" y="1" dice="5" a="0" />
<tile type="LAND_WOLLE" x="0" y="1" dice="12" a="0" />
<tile type="LAND_WOLLE" x="1" y="1" dice="4" a="0" />
<tile type="WASSER" 	x="2" y="1" dice="0" a="1" />

<!-- Zeile 2: (5-tiles) -->
<tile type="LAND_WASSER" x="-2" y="2" dice="0" a="5" />
<tile type="LAND_WEIZEN" x="-1" y="2" dice="4" a="0" />
<tile type="LAND_HOLZ" 	 x="0" y="2" dice="6" a="0" />
<tile type="LAND_WEIZEN" x="1" y="2" dice="9" a="0" />
<tile type="HAFEN_3zu1"  x="2" y="2" dice="0" a="1" />

<!-- Zeile 3: (4-tiles) -->
<tile type="HAFEN_ERZ" 	x="-2" y="3" dice="0" a="5" />
<tile type="WASSER" 	x="-1" y="3" dice="0" a="0" />
<tile type="HAFEN_3zu1" x="0" y="3" dice="0" a="0" />
<tile type="WASSER" 	x="1" y="3" dice="0" a="0" />
)"
};


Board_t::Board_t()
{

}

Board_t::~Board_t()
{

}

Board_t* Board_get( Game_t * game )
{
   assert( game );
   return &game->Board;
}

void Board_create( Game_t * game )
{
    assert( game );
    Board_createStandardTiles( game );
    Board_createWaypoints( game, 10.0f, 5.00f, 13, false );
    Board_createWaypoints( game, 7.5f, 3.33f, 13, true );
}

void Board_createStandardTiles( Game_t * game )
{
    assert( game );

    // <!-- Zeile -3: (4-tiles) -->
    Board_addTile( game, TileType::HAFEN_LEHM, -2, -3, 0, 3);
    Board_addTile( game, TileType::WASSER, -1, -3, 0, 3);
    Board_addTile( game, TileType::HAFEN_3zu1, 0, -3, 0, 3);
    Board_addTile( game, TileType::WASSER, 1, -3, 0, 2);

    // <!-- Zeile -2: (5-tiles) -->
    Board_addTile( game, TileType::WASSER, -2, -2, 0, 4);
    Board_addTile( game, TileType::LAND_WEIZEN, -1, -2, 3, 0);
    Board_addTile( game, TileType::LAND_WEIZEN, 0, -2, 6, 0);
    Board_addTile( game, TileType::LAND_ERZ, 1, -2, 11, 0);
    Board_addTile( game, TileType::HAFEN_WEIZEN, 2, -2, 0, 1);

    // <!-- Zeile -1: (6-tiles) -->
    Board_addTile( game, TileType::HAFEN_3zu1, -3, -1, 0, 3);
    Board_addTile( game, TileType::LAND_HOLZ, -2, -1, 3, 0);
    Board_addTile( game, TileType::LAND_ERZ, -1, -1, 5, 0);
    Board_addTile( game, TileType::LAND_LEHM, 0, -1, 10, 0);
    Board_addTile( game, TileType::LAND_HOLZ, 1, -1, 11, 0);
    Board_addTile( game, TileType::WASSER, 2, -1, 0, 2);

    // <!-- Zeile 0: (7-tiles) -->
    Board_addTile( game, TileType::WASSER, -3, 0, 0, 4);
    Board_addTile( game, TileType::LAND_WOLLE, -2, 0, 9, 0);
    Board_addTile( game, TileType::LAND_LEHM, -1, 0, 8, 0);
    Board_addTile( game, TileType::LAND_WUESTE, 0, 0, 0, 0);
    Board_addTile( game, TileType::LAND_ERZ, 1, 0, 8, 0);
    Board_addTile( game, TileType::LAND_WOLLE, 2, 0, 10, 0);
    Board_addTile( game, TileType::HAFEN_3zu1, 3, 0, 0, 1);

    // <!-- Zeile +1: (6-tiles) -->
    Board_addTile( game, TileType::HAFEN_HOLZ, -3, 1, 0, 4);
    Board_addTile( game, TileType::LAND_LEHM, -2, 1, 2, 0);
    Board_addTile( game, TileType::LAND_HOLZ, -1, 1, 5, 0);
    Board_addTile( game, TileType::LAND_WOLLE, 0, 1, 12, 0);
    Board_addTile( game, TileType::LAND_WOLLE, 1, 1, 4, 0);
    Board_addTile( game, TileType::WASSER, 2, 1, 0, 1);

    // <!-- Zeile 2: (5-tiles) -->
    Board_addTile( game, TileType::WASSER, -2, 2, 0, 5);
    Board_addTile( game, TileType::LAND_WEIZEN, -1, 2, 4, 0);
    Board_addTile( game, TileType::LAND_HOLZ, 0, 2, 6, 0);
    Board_addTile( game, TileType::LAND_WEIZEN, 1, 2, 9, 0);
    Board_addTile( game, TileType::HAFEN_3zu1, 2, 2, 0, 1);

    // <!-- Zeile 3: (4-tiles) -->
    Board_addTile( game, TileType::HAFEN_ERZ, -2, 3, 0, 5);
    Board_addTile( game, TileType::WASSER, -1, 3, 0, 0);
    Board_addTile( game, TileType::HAFEN_WOLLE, 0, 3, 0, 0);
    Board_addTile( game, TileType::WASSER, 1, 3, 0, 0);
}

void
Board_addTile( Game_t * game, TileType tileType, int i, int j, int diceValue, int angle60 )
{
    assert( game );

    //irr::video::IVideoDriver* driver = game->Device->getVideoDriver();
    irr::scene::ISceneManager* smgr = game->Device->getSceneManager();

    float32_t const w = game->Board.TileSize.x;
    float32_t const h = game->Board.TileSize.z;

    Tile_t tile;
    tile.Type = tileType;
    tile.Size = game->Board.TileSize;
    tile.BoardIndex = glm::ivec2( i, j );
    tile.Pos = glm::vec3( w * i + w * 0.5f * ( safeMod( j, 2 ) == 1 ), 0.0f, 3.0f/4.0f * h * j );
    tile.DiceValue = diceValue;
    tile.Angle60 = angle60;

    // create scene
    AutoSceneNode* node = new AutoSceneNode( smgr, smgr->getRootSceneNode(), -1 );
    tile.Node = node;
    node->setPosition( toIRR(tile.Pos) );

    // ground hexagon
    AutoMeshBuffer* hexagon = createHexagon( w, h );
    hexagon->MeshBuffer.Material.setTexture( 0, Game_getTileTexture( game, tileType ) );
    node->add( hexagon, true );

    // our own custom collision detection using 4 triangles for each hexagon
    getHexagonTriangles( tile.Triangles, glm::vec2( tile.Size.x, tile.Size.z), tile.Pos );

    // Create triangle-selector for hexagon collision detection ( only )
    //irr::scene::ITriangleSelector* selector = smgr->createTriangleSelector( node->getMesh(), node );
    //node->setTriangleSelector( selector );
    //game->TileSelector->addTriangleSelector( selector );
    //tile.TriangleSelector = selector;
    //selector->drop();

    // chip cylinder for land tiles
    if ( tileType.isLand() || tileType.isHafen() )
    {
        irr::video::ITexture* tex = Game_getChipTexture( game, tileType, diceValue );

        AutoMeshBuffer* hull = createCylinderHull( glm::vec3(0.0f, 2.5f, 0.0f), 10.0f, 5.0f, 0xFFFFFFFF, 16, 1 );
        hull->MeshBuffer.Material.setTexture( 0, tex );
        node->add( hull, true );

        AutoMeshBuffer* top = createCircleXZ( glm::vec3( 0.0f, 5.0f, 0.0f ), 10.0f, 16 );
        top->MeshBuffer.Material.setTexture( 0, tex );
        node->add( top, true );

        // + 2 roads for hafen tiles
        if ( tileType.isHafen() )
        {
            AutoMeshBuffer* hull = createCylinderHull( glm::vec3(0.0f, 2.5f, 0.0f), 10.0f, 5.0f, 0xFFFFFFFF, 16, 1 );
            hull->setTexture( 0, tex );
            node->add( hull, true );

            AutoMeshBuffer* top = createCircleXZ( glm::vec3( 0.0f, 5.0f, 0.0f ), 10.0f, 16 );
            top->setTexture( 0, tex );
            node->add( top, true );

            int k = tile.Angle60;
            node->add( createRotatedBox( getHexagonPoint( w, h, k )*0.5f, glm::vec3(1,1,20), glm::vec3(0,k*60,0), 0xFFFFFFFF ), true );
            node->add( createRotatedBox( getHexagonPoint( w, h, k+1 )*0.5f, glm::vec3(1,1,20), glm::vec3(0,(k+1)*60,0), 0xFFFFFFFF ), true );
        }
    }

    std::cout << __FUNCTION__ << " :: Tile[" << game->Board.Tiles.size() << "] " << tile << "\n";

    game->Board.Tiles.push_back( std::move( tile ) );
}

void Board_createWaypoints( Game_t * game, float32_t radius, float32_t height, uint32_t tesselation, bool isRoad )
{
    assert ( game );

    for ( size_t i = 0; i < game->Board.Tiles.size(); ++i )
    {
        Tile_t const & tile = game->Board.Tiles[ i ];

         if ( tile.Type.isWasser() ||
              tile.Type == TileType::LAND_WUESTE )
         {
            continue;
         }

        for ( int32_t k = 1; k <= 6; ++k )
        {
             glm::vec3 pos;
             float32_t phi = 0.0f;

             if ( isRoad )
             {
                 pos = tile.getEdgeCenter( k );
                 phi = tile.getEdgeAngle( k );
             }
             else
             {
                 pos = tile.getCorner( k );
             }

             Board_addWaypoint( game, radius, height, tesselation, pos, phi, isRoad );
        }
    }

    std::cout << __FUNCTION__ << "() :: added ("<< game->Board.Waypoints.size() << ") waypoints of type (" << ( isRoad ? "R" : "S" )<< ").\n";
}


void Board_addWaypoint( Game_t * game, float32_t r,float32_t h, uint32_t tesselation, glm::vec3 pos, float32_t angle, bool isRoad )
{
//    std::cout << __FUNCTION__ << "() :: Add waypoint at pos("<< pos << ").\n";

    assert ( game );
    assert ( game->Device );
    irr::scene::ISceneManager* smgr = game->Device->getSceneManager();

    Board_t* board = Board_get( game );
    assert ( board );

    Waypoint_t* found = board->findWaypoint( pos );
    if ( found )
    {
//      std::cout << __FUNCTION__ << "() :: Waypoint already exist at pos("<< pos << ").\n";
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
    node->setPosition( toIRR(pos) );

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
    way.Angle = angle;

    std::vector< Tile_t* > waypointTiles = board->findTiles( pos );

    for ( size_t i = 0; i < waypointTiles.size(); ++i )
    {
      Tile_t * tile = waypointTiles[ i ];
      way.addTile( tile );
    }

    // Create triangle-selector for cylinder collision detection
    //irr::scene::ITriangleSelector* selector = smgr->createTriangleSelector( node->getMesh(), node );
    //node->setTriangleSelector( selector );
    //game->WaypointSelector->addTriangleSelector( selector );
    //selector->drop();

//    std::cout << __FUNCTION__ << " :: " << way << "\n";

    game->Board.Waypoints.emplace_back( std::move( way ) );
}

Tile_t* Board_isMouseOverTile( Game_t * game )
{
    assert( game );
    assert( game->Device );

    irr::IrrlichtDevice* device = game->Device;
    irr::scene::ISceneManager* smgr = device->getSceneManager();
    irr::core::position2di mousePos = device->getCursorControl()->getPosition();
    irr::core::line3df screenRay = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates( mousePos, smgr->getActiveCamera() );

    irr::core::vector3df hitPosition;

    for ( uint32_t i = 0; i < game->Board.Tiles.size(); ++i )
    {
        Tile_t const & tile = game->Board.Tiles[ i ];

        for ( uint32_t j = 0; j < tile.Triangles.size(); ++j )
        {
            irr::core::triangle3df const & tri = tile.Triangles[ j ];
            if ( tri.getIntersectionWithLine( screenRay.start, screenRay.getVector(), hitPosition ) )
            {
                return (Tile_t*)(&tile);
            }
        }
    }
    return nullptr;
}

Waypoint_t* Board_isMouseOverWaypoint( Game_t * game, bool isRoad )
{
    assert( game );
    assert( game->Device );

    irr::IrrlichtDevice* device = game->Device;
    irr::scene::ISceneManager* smgr = device->getSceneManager();
    irr::core::position2di const mousePos = device->getCursorControl()->getPosition();
    irr::core::line3df const screenRay = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates( mousePos, smgr->getActiveCamera() );

    irr::core::vector3df hitPosition;

    // loop all waypoints stored in game
    for ( uint32_t i = 0; i < game->Board.Waypoints.size(); ++i )
    {
        Waypoint_t const & w = game->Board.Waypoints[ i ];

        // use AutoMeshBufferUtils
        if ( (w.IsRoad == isRoad) &&
             (w.Node) &&
             (w.Node->getIntersectionWithLine( screenRay, hitPosition )) )
        {
            return (Waypoint_t*)(&w);
        }
    }
    return nullptr;
}

void Board_setVisible_Waypoints( Game_t* game, bool visible )
{
    forEachWaypoint( game, [visible] (Waypoint_t*w)
                    {
                        if (w->Node)
                            w->Node->setVisible( visible );
                    } );
//    if (!game) return;

//    for ( size_t i = 0; i < game->Waypoints.size(); ++i )
//    {
//        irr::scene::ISceneNode* node = game->Waypoints[ i ].Node;
//        if ( node )
//        {
//            node->setVisible( visible );
//        }
//    }
}


void Board_setVisible_WaypointsR( Game_t* game, bool visible )
{
    forEachWaypointR( game, [visible] (Waypoint_t*w)
                    {
                        if (w->Node)
                            w->Node->setVisible( visible );
                    } );

//    if (!game) return;

//    for ( size_t i = 0; i < game->Waypoints.size(); ++i )
//    {
//        if ( game->Waypoints[ i ].IsRoad )
//        {
//            irr::scene::ISceneNode* node = game->Waypoints[ i ].Node;
//            if ( node )
//            {
//                node->setVisible( visible );
//            }
//        }
//    }
}

void Board_setVisible_WaypointsS( Game_t* game, bool visible )
{
    forEachWaypointS( game, [visible] (Waypoint_t*w)
                    {
                        if (w->Node)
                            w->Node->setVisible( visible );
                    } );

//    if (!game) return;

//    for ( size_t i = 0; i < game->Waypoints.size(); ++i )
//    {
//        if ( !game->Waypoints[ i ].IsRoad )
//        {
//            irr::scene::ISceneNode* node = game->Waypoints[ i ].Node;
//            if ( node )
//            {
//                node->setVisible( visible );
//            }
//        }
//    }
}
/*

std::vector< Tile_t* >
Board_collectTilesByPosition( Game_t * game, glm::vec3 pos )
{
    for ( uint32_t i = 0; i < game->Tiles.size(); ++i )
    {
        Tile_t * tile = game->Tiles[ i ];

        if ( tile )
        {
        for ( uint32_t i = 0; i < game->Tiles.size(); ++i )
        {
            Tile_getCorner( tile, 0 )tile->)
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

*/


} // end namespace pioneers3d
