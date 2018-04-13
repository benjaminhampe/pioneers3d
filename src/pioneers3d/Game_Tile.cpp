#include "Game_Tile.hpp"

#include "Game_Texture.hpp"

namespace pioneers3d {

void Tiles_clear( Game_t* game )
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

void Tiles_createStandard( Game_t* game )
{
    auto addTile = [game] ( eTileType tileType, int i, int j, int diceValue, int angle60 ) -> void
    {
        Tile_add( game, tileType, i, j, diceValue, angle60 );
    };

    // <!-- Zeile -3: (4-tiles) -->
    addTile( eTileType::HAFEN_LEHM, -2, -3, 0, 3);
    addTile( eTileType::WASSER, -1, -3, 0, 3);
    addTile( eTileType::HAFEN_3zu1, 0, -3, 0, 3);
    addTile( eTileType::WASSER, 1, -3, 0, 2);

    // <!-- Zeile -2: (5-tiles) -->
    addTile( eTileType::WASSER, -2, -2, 0, 4);
    addTile( eTileType::LAND_WEIZEN, -1, -2, 3, 0);
    addTile( eTileType::LAND_WEIZEN, 0, -2, 6, 0);
    addTile( eTileType::LAND_ERZ, 1, -2, 11, 0);
    addTile( eTileType::HAFEN_WEIZEN, 2, -2, 0, 1);

    // <!-- Zeile -1: (6-tiles) -->
    addTile( eTileType::HAFEN_3zu1, -3, -1, 0, 3);
    addTile( eTileType::LAND_HOLZ, -2, -1, 3, 0);
    addTile( eTileType::LAND_ERZ, -1, -1, 5, 0);
    addTile( eTileType::LAND_LEHM, 0, -1, 10, 0);
    addTile( eTileType::LAND_HOLZ, 1, -1, 11, 0);
    addTile( eTileType::WASSER, 2, -1, 0, 2);

    // <!-- Zeile 0: (7-tiles) -->
    addTile( eTileType::WASSER, -3, 0, 0, 4);
    addTile( eTileType::LAND_WOLLE, -2, 0, 9, 0);
    addTile( eTileType::LAND_LEHM, -1, 0, 8, 0);
    addTile( eTileType::LAND_WUESTE, 0, 0, 0, 0);
    addTile( eTileType::LAND_ERZ, 1, 0, 8, 0);
    addTile( eTileType::LAND_WOLLE, 2, 0, 10, 0);
    addTile( eTileType::HAFEN_3zu1, 3, 0, 0, 1);

    // <!-- Zeile +1: (6-tiles) -->
    addTile( eTileType::HAFEN_HOLZ, -3, 1, 0, 4);
    addTile( eTileType::LAND_LEHM, -2, 1, 2, 0);
    addTile( eTileType::LAND_HOLZ, -1, 1, 5, 0);
    addTile( eTileType::LAND_WOLLE, 0, 1, 12, 0);
    addTile( eTileType::LAND_WOLLE, 1, 1, 4, 0);
    addTile( eTileType::WASSER, 2, 1, 0, 1);

    // <!-- Zeile 2: (5-tiles) -->
    addTile( eTileType::WASSER, -2, 2, 0, 5);
    addTile( eTileType::LAND_WEIZEN, -1, 2, 4, 0);
    addTile( eTileType::LAND_HOLZ, 0, 2, 6, 0);
    addTile( eTileType::LAND_WEIZEN, 1, 2, 9, 0);
    addTile( eTileType::HAFEN_3zu1, 2, 2, 0, 1);

    // <!-- Zeile 3: (4-tiles) -->
    addTile( eTileType::HAFEN_ERZ, -2, 3, 0, 5);
    addTile( eTileType::WASSER, -1, 3, 0, 0);
    addTile( eTileType::HAFEN_WOLLE, 0, 3, 0, 0);
    addTile( eTileType::WASSER, 1, 3, 0, 0);
}

void Tile_add( Game_t* game, eTileType tileType, int i, int j, int diceValue, int angle60 )
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
    game->Tiles.push_back( std::move( tile ) );

    // create scene
    AutoSceneNode* node = new AutoSceneNode( smgr, smgr->getRootSceneNode(), -1 );
    node->setPosition( tile.Pos );

    // ground hexagon
    AutoMeshBuffer* hexagon = createHexagon( w, h );
    hexagon->MeshBuffer.Material.setTexture( 0, Game_getTileTexture( game, tileType ) );
    node->add( hexagon, true );

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
}

glm::vec3
Tile_getPosition( Tile_t * tile )
{
    if ( !tile ) return glm::vec3( 0,0,0 );
    return tile->Pos;
}

glm::vec3
Tile_getCorner( Tile_t * tile, int i, float32_t tileWidth, float32_t tileheight )
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
Tile_getEdgeCenter( Tile_t * tile, int i, float32_t tileWidth, float32_t tileheight )
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

    glm::vec3 const A = Tile_getCorner( tile, a, tileWidth, tileheight );
    glm::vec3 const B = Tile_getCorner( tile, b, tileWidth, tileheight );
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


