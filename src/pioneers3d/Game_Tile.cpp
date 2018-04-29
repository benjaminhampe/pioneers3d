#include "Game_Tile.hpp"

#include "Game_Texture.hpp"

namespace pioneers3d {

std::string
Tile_toString( Tile_t const & tile )
{
    std::stringstream s;
    s << "type: " << tile.Type.toString() << "; "
      << "i: "<< tile.BoardIndex.x << "; "
      << "j: "<< tile.BoardIndex.y << "; "
      << "x: "<< tile.Pos.x << "; "
      << "y: "<< tile.Pos.y << "; "
      << "z: "<< tile.Pos.z << "; "
      << "dice: "<< tile.DiceValue << "; "
      << "ang60: "<< tile.Angle60 << "; "
      << "waypoints: "<< tile.Waypoints.size() << "; "
      << "";
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

    for ( uint32_t i = 0; i < game->Tiles.size(); ++i )
    {
        Tile_t const & tile = game->Tiles[ i ];

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


void getHexagonTriangles( std::vector< irr::core::triangle3df > & container, float32_t w, float32_t h, glm::vec3 pos )
{
    irr::core::vector3df const P( pos.x, pos.y, pos.z );
    irr::core::vector3df const A( 0.00f*w, 0.0f, -.50f*h );
    irr::core::vector3df const B( -.50f*w, 0.0f, -.25f*h );
    irr::core::vector3df const C( -.50f*w, 0.0f, 0.25f*h );
    irr::core::vector3df const D( 0.00f*w, 0.0f, 0.50f*h );
    irr::core::vector3df const E( 0.50f*w, 0.0f, 0.25f*h );
    irr::core::vector3df const F( 0.50f*w, 0.0f, -.25f*h );

    auto addTriangle = [ &container, P ] ( irr::core::vector3df const & a, irr::core::vector3df const & b, irr::core::vector3df const & c )
    {
        container.emplace_back( irr::core::triangle3df( P + a, P + b, P + c ) );
    };

    addTriangle( A,B,F ); // ABF
    addTriangle( B,C,E ); // BCE
    addTriangle( B,E,F ); // BEF
    addTriangle( C,D,E ); // CDE
}


void addTile( Game_t* game, eTileType tileType, int i, int j, int diceValue, int angle60 )
{
    //irr::video::IVideoDriver* driver = game->Device->getVideoDriver();
    irr::scene::ISceneManager* smgr = game->Device->getSceneManager();

    float32_t const w = game->TileSize.x;
    float32_t const h = game->TileSize.z;

    Tile_t tile;
    tile.Type = tileType;
    tile.Size = game->TileSize;
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
    getHexagonTriangles( tile.Triangles, tile.Size.x, tile.Size.z, tile.Pos );

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
    game->Tiles.push_back( std::move( tile ) );
}

glm::vec3
getTilePosition( Tile_t * tile )
{
    if ( !tile ) return glm::vec3( 0,0,0 );
    return tile->Pos;
}

/// Hexagon ( ver_2018 ):
///
///                 D        triangles: ABF, BCE, BEF, CDE
///                 /\
///              C /  \ E    M (x=0,y=0,z=0,u=0.5,v=0.5)
///               |----|     F( 0.5, 0, -.25, 1, 0.25 )
///               |  M |     E( 0.5, 0, 0.25, 1, 0.75 )
///               |----|     D( 0.0, 0, 0.50, 0.5, 1 )
///              B \  / F    C( -.5, 0, 0.25, 0, 0.75 )
///                 \/       B( -.5, 0, -.25, 0, 0.25 )
///                  A       A( 0, 0, -.5, .5, 0 )
///

glm::vec3
getTileCorner( Tile_t * tile, int i, float32_t tileWidth, float32_t tileheight )
{
    assert( tile );
    while ( i < 0 ) i += 6;
    while ( i >= 6 ) i -= 6;
    switch ( i )
    {
        case 0: return tile->Pos + glm::vec3( 0.00f*tileWidth, 0.0f, -.50f*tileheight ); // A
        case 1: return tile->Pos + glm::vec3( -.50f*tileWidth, 0.0f, -.25f*tileheight ); // B
        case 2: return tile->Pos + glm::vec3( -.50f*tileWidth, 0.0f, 0.25f*tileheight ); // C
        case 3: return tile->Pos + glm::vec3( 0.00f*tileWidth, 0.0f, 0.50f*tileheight ); // D
        case 4: return tile->Pos + glm::vec3( 0.50f*tileWidth, 0.0f, 0.25f*tileheight ); // E
        case 5: return tile->Pos + glm::vec3( 0.50f*tileWidth, 0.0f, -.25f*tileheight ); // F
        default: assert( false ); // not allowed to happen
    }
}

glm::vec3
getTileEdgeCenter( Tile_t * tile, int i, float32_t tileWidth, float32_t tileheight )
{
    assert( tile );
    int32_t a, b;
    while ( i < 0 ) i += 6;
    while ( i >= 6 ) i -= 6;
    switch ( i )
    {
        case 0: a = 0, b = 1; break;
        case 1: a = 1; b = 2; break; // B-C
        case 2: a = 2; b = 3; break; // C-D
        case 3: a = 3; b = 4; break; // D-E
        case 4: a = 4; b = 5; break; // E-F
        case 5: a = 5; b = 0; break; // F-A
        default: assert( false ); // not allowed to happen
    }
    glm::vec3 const A = getTileCorner( tile, a, tileWidth, tileheight );
    glm::vec3 const B = getTileCorner( tile, b, tileWidth, tileheight );
    return A + (B-A)*0.5f; // Center of egde (a,b)
}

float32_t
getTileEdgeAngle( Tile_t * tile, int i, float32_t tileWidth, float32_t tileheight )
{
    assert( tile );
    int32_t a, b;
    while ( i < 0 ) i += 6;
    while ( i >= 6 ) i -= 6;
    switch ( i )
    {
        case 0: a = 0; b = 1; break; // A-B
        case 1: a = 1; b = 2; break; // B-C
        case 2: a = 2; b = 3; break; // C-D
        case 3: a = 3; b = 4; break; // D-E
        case 4: a = 4; b = 5; break; // E-F
        case 5: a = 0; b = 5; break; // F-A
        default: assert( false ); // not allowed to happen
    }

    glm::vec3 const A = getTileCorner( tile, a, tileWidth, tileheight );
    glm::vec3 const B = getTileCorner( tile, b, tileWidth, tileheight );
    glm::vec3 eAB( B.x-A.x, 0.0f, B.z-A.z); // projected onto xz plane
    glm::vec3 eX(1,0,0); // we want angle between +x axis
    // dot(a,b) = |a||b|cos(a,b);
    // cos(a,b) = dot(a,b) / |a||b|;
    // angle(a,b) = acos( dot(a,b) / |a||b| );
    float32_t angle = irr::core::RADTODEG * acos( glm::dot(eAB,eX) / glm::length(eAB) );
    while ( angle < 0.0f ) angle += 360.0f;
    while ( angle >= 360.0f ) angle -= 360.0f;

    std::cout << __FUNCTION__ << "(" << i << ") -> a60(" << angle << ")\n";

    return angle;
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
