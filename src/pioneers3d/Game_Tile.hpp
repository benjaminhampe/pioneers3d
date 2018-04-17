#ifndef TILE_HPP
#define TILE_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

Tile_t * findTileUnderMouse( Game_t * game );

int32_t safeMod( int32_t a, int32_t b );

void createStandardTiles( Game_t* game );
void clearTiles( Game_t* game );
void addTile( Game_t* game, eTileType tileType, int i, int j, int diceValue, int angle60 );

glm::vec3 getTilePosition( Tile_t * tile );
glm::vec3 getTileCorner( Tile_t * tile, int i, float32_t tileWidth, float32_t tileheight );
glm::vec3 getTileEdgeCenter( Tile_t * tile, int i, float32_t tileWidth, float32_t tileheight );

std::string Tile_toString( Tile_t * tile );

//std::vector< Tile_t* > Tiles_collectByPosition( Game_t * game, glm::vec3 pos )

} // end namespace pioneers3d


#endif // TILE_HPP
