#ifndef PIONEERS_COMMON_TILE_TYPE_HPP
#define PIONEERS_COMMON_TILE_TYPE_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

// int32_t safeMod( int32_t a, int32_t b );
// void getHexagonTriangles( std::vector< irr::core::triangle3df > & container, float32_t w, float32_t h, glm::vec3 pos );

inline int32_t safeMod( int32_t a, int32_t b )
{
    if ( a == 0 && b == 0)
    {
        return 0;
    }

    return std::abs( a ) % std::abs( b );
}

inline void getHexagonTriangles( std::vector< irr::core::triangle3df > & container, float32_t w, float32_t h, glm::vec3 pos )
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

class Player_t;
class Waypoint_t;

class Tile_t
{
public:
    // Tile_t() {}
	//~Tile_t() { if (Node) Node->drop(); }
	
	std::string
	toString() const;

public:	
    eTileType 					Type = eTileType::WASSER;
    glm::ivec2 					BoardIndex;
    glm::vec3                   Pos;
    glm::vec3                   Size;
    int32_t 					DiceValue = 0;
    int32_t 					Angle60 = 0;
    std::vector< RoadPoint_t* > RoadPoints;
    std::vector< Waypoint_t* >  Waypoints;
    std::vector< irr::core::triangle3df > Triangles;
    AutoSceneNode*              Node = nullptr;
    irr::scene::ITriangleSelector* TriangleSelector = nullptr;
};



std::string Tile_toString( Tile_t const & tile );

Tile_t*     findTileUnderMouse( Game_t * game );

void        createStandardTiles( Game_t* game );
void        clearTiles( Game_t* game );
void        addTile( Game_t* game, eTileType tileType, int i, int j, int diceValue, int angle60 );

glm::vec3   getTilePosition( Tile_t * tile );
glm::vec3   getTileCorner( Tile_t * tile, int i, float32_t tileWidth, float32_t tileheight );
glm::vec3   getTileEdgeCenter( Tile_t * tile, int i, float32_t tileWidth, float32_t tileheight );
float32_t   getTileEdgeAngle( Tile_t * tile, int i, float32_t tileWidth, float32_t tileheight );

//std::vector< Tile_t* > Tiles_collectByPosition( Game_t * game, glm::vec3 pos )

} // end namespace pioneers3d

#endif // GAME_TYPES_TILE_HPP
