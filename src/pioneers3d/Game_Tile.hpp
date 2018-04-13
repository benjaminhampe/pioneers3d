#ifndef TILE_HPP
#define TILE_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

int32_t safeMod( int32_t a, int32_t b );

void Tiles_createStandard( Game_t* game );
void Tiles_clear( Game_t* game );
void Tile_add( Game_t* game, eTileType tileType, int i, int j, int diceValue, int angle60 );

glm::vec3 Tile_getPosition( Tile_t * tile );
glm::vec3 Tile_getCorner( Tile_t * tile, int i, float32_t tileWidth, float32_t tileheight );
glm::vec3 Tile_getEdgeCenter( Tile_t * tile, int i, float32_t tileWidth, float32_t tileheight );

//std::vector< Tile_t* > Tiles_collectByPosition( Game_t * game, glm::vec3 pos )

} // end namespace pioneers3d


#endif // TILE_HPP
