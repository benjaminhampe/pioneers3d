#ifndef TILE_HPP
#define TILE_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

int32_t safeMod( int32_t a, int32_t b );

void Game_clearTiles( Game_t* game );
void Game_addTile( Game_t* game, eTileType tileType, int i, int j, int diceValue, int angle60 );
void Game_createStandardTiles( Game_t* game );

inline glm::vec3 Tile_getPosition( Tile_t * tile )
{
    if ( !tile ) return glm::vec3( 0,0,0 );
    return tile->Pos;
}

inline glm::vec3 Tile_getCorner( Tile_t * tile, int i, float32_t tileWidth, float32_t tileheight )
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

inline glm::vec3 Tile_getEdgeCenter( Tile_t * tile, int i, float32_t tileWidth, float32_t tileheight )
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


//std::vector< Tile_t* > Game_getTiles( Game_t * game, glm::vec3 pos )
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

} // end namespace pioneers3d


#endif // TILE_HPP
