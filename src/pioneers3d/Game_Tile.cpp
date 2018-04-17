#include "Game_Tile.hpp"

#include "Game_Texture.hpp"

namespace pioneers3d {

std::string Tile_toString( Tile_t * tile )
{
    std::stringstream s;
    s << "Type: " << tile->Type.toString() << "; "
      << "x: "<< tile->BoardIndex.x << "; "
      << "y: "<< tile->BoardIndex.y;
    return s.str();
}

Tile_t *
findTileUnderMouse( Game_t * game )
{
    if ( !game || !game->Device ) return nullptr;
    irr::IrrlichtDevice* device = game->Device;
    irr::scene::ISceneManager* smgr = device->getSceneManager();
    irr::core::position2di mousePos = device->getCursorControl()->getPosition();
    irr::core::line3df screenRay = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates( mousePos, smgr->getActiveCamera() );
    irr::core::vector3df hitPosition;
    irr::core::triangle3df hitTriangle;
    irr::scene::ISceneNode* hitSceneNode = nullptr;
    if ( smgr->getSceneCollisionManager()->getCollisionPoint( screenRay, game->TileSelector, hitPosition, hitTriangle, hitSceneNode ) )
    {
        //std::cout << "[Hit] " << __FUNCTION__ << " :: " << toString( hitPosition ) << ")\n";
        for ( uint32_t i = 0; i < game->Tiles.size(); ++i )
        {
            Tile_t & tile = game->Tiles[ i ];
            if ( tile.Node && tile.Node == hitSceneNode )
            {
                std::cout << "[Tile] " << __FUNCTION__ << " :: " << Tile_toString( &tile ) << "\n";
                return &tile;
            }
        }

        game->HitSceneNode = hitSceneNode;
        if ( game->HitSceneNode != game->HitSceneNodeLast )
        {
            if (game->HitSceneNodeLast) game->HitSceneNodeLast->setDebugDataVisible( irr::scene::EDS_OFF );
            if (game->HitSceneNode) game->HitSceneNode->setDebugDataVisible( irr::scene::EDS_FULL );
            game->HitSceneNodeLast = game->HitSceneNode;
        }
    }
    else
    {
        //
    }
    return nullptr;
}

void clearTiles( Game_t* game )
{
    if (!game) return;
//    for ( size_t i = 0; i < game->Tiles.size(); ++i )
//    {
//        Tile_t * tile = game->Tiles[ i ];
//        if ( tile )
//        {
//            delete tile;
//        }
//    }
    game->Tiles.clear();
}

//std::vector< Tile_t* > Tiles_collectByPosition( Game_t * game, glm::vec3 pos )
//{
//    for ( uint32_t i = 0; i < game->Tiles.size(); ++i )
//    {
//        Tile_t * tile = game->Tiles[ i ];

//        if ( tile )
//        {
//        for ( uint32_t i = 0; i < game->Tiles.size(); ++i )
//        {
//            Tile_getCorner( tile, 0 )tile->)
//        }

//    }
//}

void createStandardTiles( Game_t* game )
{
    // <!-- Zeile -3: (4-tiles) -->
    addTile( game, eTileType::HAFEN_LEHM, -2, -3, 0, 3);
    addTile( game, eTileType::WASSER, -1, -3, 0, 3);
    addTile( game, eTileType::HAFEN_3zu1, 0, -3, 0, 3);
    addTile( game, eTileType::WASSER, 1, -3, 0, 2);

    // <!-- Zeile -2: (5-tiles) -->
    addTile( game, eTileType::WASSER, -2, -2, 0, 4);
    addTile( game, eTileType::LAND_WEIZEN, -1, -2, 3, 0);
    addTile( game, eTileType::LAND_WEIZEN, 0, -2, 6, 0);
    addTile( game, eTileType::LAND_ERZ, 1, -2, 11, 0);
    addTile( game, eTileType::HAFEN_WEIZEN, 2, -2, 0, 1);

    // <!-- Zeile -1: (6-tiles) -->
    addTile( game, eTileType::HAFEN_3zu1, -3, -1, 0, 3);
    addTile( game, eTileType::LAND_HOLZ, -2, -1, 3, 0);
    addTile( game, eTileType::LAND_ERZ, -1, -1, 5, 0);
    addTile( game, eTileType::LAND_LEHM, 0, -1, 10, 0);
    addTile( game, eTileType::LAND_HOLZ, 1, -1, 11, 0);
    addTile( game, eTileType::WASSER, 2, -1, 0, 2);

    // <!-- Zeile 0: (7-tiles) -->
    addTile( game, eTileType::WASSER, -3, 0, 0, 4);
    addTile( game, eTileType::LAND_WOLLE, -2, 0, 9, 0);
    addTile( game, eTileType::LAND_LEHM, -1, 0, 8, 0);
    addTile( game, eTileType::LAND_WUESTE, 0, 0, 0, 0);
    addTile( game, eTileType::LAND_ERZ, 1, 0, 8, 0);
    addTile( game, eTileType::LAND_WOLLE, 2, 0, 10, 0);
    addTile( game, eTileType::HAFEN_3zu1, 3, 0, 0, 1);

    // <!-- Zeile +1: (6-tiles) -->
    addTile( game, eTileType::HAFEN_HOLZ, -3, 1, 0, 4);
    addTile( game, eTileType::LAND_LEHM, -2, 1, 2, 0);
    addTile( game, eTileType::LAND_HOLZ, -1, 1, 5, 0);
    addTile( game, eTileType::LAND_WOLLE, 0, 1, 12, 0);
    addTile( game, eTileType::LAND_WOLLE, 1, 1, 4, 0);
    addTile( game, eTileType::WASSER, 2, 1, 0, 1);

    // <!-- Zeile 2: (5-tiles) -->
    addTile( game, eTileType::WASSER, -2, 2, 0, 5);
    addTile( game, eTileType::LAND_WEIZEN, -1, 2, 4, 0);
    addTile( game, eTileType::LAND_HOLZ, 0, 2, 6, 0);
    addTile( game, eTileType::LAND_WEIZEN, 1, 2, 9, 0);
    addTile( game, eTileType::HAFEN_3zu1, 2, 2, 0, 1);

    // <!-- Zeile 3: (4-tiles) -->
    addTile( game, eTileType::HAFEN_ERZ, -2, 3, 0, 5);
    addTile( game, eTileType::WASSER, -1, 3, 0, 0);
    addTile( game, eTileType::HAFEN_WOLLE, 0, 3, 0, 0);
    addTile( game, eTileType::WASSER, 1, 3, 0, 0);
}

void addTile( Game_t* game, eTileType tileType, int i, int j, int diceValue, int angle60 )
{
    //irr::video::IVideoDriver* driver = game->Device->getVideoDriver();
    irr::scene::ISceneManager* smgr = game->Device->getSceneManager();

    float32_t const w = game->TileSize.x;
    float32_t const h = game->TileSize.z;

    Tile_t tile;
    tile.Type = tileType;
    tile.BoardIndex = glm::ivec2( i, j );
    tile.Pos = glm::vec3( w * i + w * 0.5f * ( safeMod( j, 2 ) == 1 ), 0.0f, 3.0f/4.0f * h * j );
    tile.DiceValue = diceValue;
    tile.TexAngle60 = angle60;

    // create scene
    AutoSceneNode* node = new AutoSceneNode( smgr, smgr->getRootSceneNode(), -1 );
    tile.Node = node;
    node->setPosition( tile.Pos );

    // ground hexagon
    AutoMeshBuffer* hexagon = createHexagon( w, h );
    hexagon->MeshBuffer.Material.setTexture( 0, Game_getTileTexture( game, tileType ) );
    node->add( hexagon, true );

    // Create triangle-selector for hexagon collision detection ( only )
    irr::scene::ITriangleSelector* selector = smgr->createTriangleSelector( node->getMesh(), node );
    node->setTriangleSelector( selector );
    game->TileSelector->addTriangleSelector( selector );
    tile.TriangleSelector = selector;
    selector->drop();

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

            int k = tile.TexAngle60;
            node->add( createRotatedBox( getHexagonPoint( w, h, k )*0.5f, glm::vec3(1,1,20), glm::vec3(0,k*60,0), 0xFFFFFFFF ), true );
            node->add( createRotatedBox( getHexagonPoint( w, h, k+1 )*0.5f, glm::vec3(1,1,20), glm::vec3(0,(k+1)*60,0), 0xFFFFFFFF ), true );
        }


    }
    game->Tiles.push_back( std::move( tile ) );
}

glm::vec3
getTilePosition( Tile_t * tile )
{
    if ( !tile ) return glm::vec3( 0,0,0 );
    return tile->Pos;
}

glm::vec3
getTileCorner( Tile_t * tile, int i, float32_t tileWidth, float32_t tileheight )
{
    if ( !tile ) return glm::vec3( 0,0,0 );
    switch ( i )
    {
        case 1: return tile->Pos + glm::vec3( 0.00f*tileWidth, 0.0f, -.50f*tileheight ); // A
        case 2: return tile->Pos + glm::vec3( -.50f*tileWidth, 0.0f, -.25f*tileheight ); // B
        case 3: return tile->Pos + glm::vec3( -.50f*tileWidth, 0.0f, 0.25f*tileheight ); // C
        case 4: return tile->Pos + glm::vec3( 0.00f*tileWidth, 0.0f, 0.50f*tileheight ); // D
        case 5: return tile->Pos + glm::vec3( 0.50f*tileWidth, 0.0f, 0.25f*tileheight ); // E
        case 6: return tile->Pos + glm::vec3( 0.50f*tileWidth, 0.0f, -.25f*tileheight ); // F
        default:return tile->Pos; // M
    }
}

glm::vec3
getTileEdgeCenter( Tile_t * tile, int i, float32_t tileWidth, float32_t tileheight )
{
    if ( !tile ) return glm::vec3( 0,0,0 );
    int32_t a = 1, b = 2;
    switch ( i )
    {
        //case 1: a = 1; b = 2; break; // A-B
        case 2: a = 2; b = 3; break; // B-C
        case 3: a = 3; b = 4; break; // C-D
        case 4: a = 4; b = 5; break; // D-E
        case 5: a = 5; b = 6; break; // E-F
        case 6: a = 6; b = 1; break; // F-A
        default: break; // A-B
    }

    glm::vec3 const A = getTileCorner( tile, a, tileWidth, tileheight );
    glm::vec3 const B = getTileCorner( tile, b, tileWidth, tileheight );
    return A + (B-A)*0.5f; // Center of egde (a,b)
}

int32_t safeMod( int32_t a, int32_t b )
{
    if ( a == 0 && b == 0)
    {
        return 0;
    }

    return std::abs( a ) % std::abs( b );
}

} // end namespace pioneers3d




/*
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
*/
