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
        case 0: return tile->Pos + glm::vec3( 0.00f*tileWidth, 0.0f, -.50f*tileheight ); // A
        case 1: return tile->Pos + glm::vec3( -.50f*tileWidth, 0.0f, -.25f*tileheight ); // B
        case 2: return tile->Pos + glm::vec3( -.50f*tileWidth, 0.0f, 0.25f*tileheight ); // C
        case 3: return tile->Pos + glm::vec3( 0.00f*tileWidth, 0.0f, 0.50f*tileheight ); // D
        case 4: return tile->Pos + glm::vec3( 0.50f*tileWidth, 0.0f, 0.25f*tileheight ); // E
        case 5: return tile->Pos + glm::vec3( 0.50f*tileWidth, 0.0f, -.25f*tileheight ); // F
        default:return tile->Pos; // M
    }
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
