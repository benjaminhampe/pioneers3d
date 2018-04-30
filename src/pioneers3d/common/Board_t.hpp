#ifndef PIONEERS_COMMON_BOARD_TYPE_HPP
#define PIONEERS_COMMON_BOARD_TYPE_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

class Player_t;
class Waypoint_t;
class Tile_t;
class Game_t;

class Board_t
{
public:
	Board_t( Game_t * game );
	~Board_t();
	
	std::string
	toString() const;
	
	void 
	clear();
	
	Tile_t *
	findTileUnderMouse() const;

	void 
	createStandard();
	
	void 
	addTile( eTileType tileType, int i, int j, int diceValue, int angle60 );
	
public:
	Game_t * 				Game;
    std::string             Name;
    glm::ivec2              TileCount;
    glm::vec3               TileSize;
    std::vector< Tile_t >   Tiles;
    std::vector< Waypoint_t > Waypoints;
	
    Tile_t*                 SelectedTile = nullptr;
    bool                    EnableCollisionDetectionForTiles = true;

    Waypoint_t*             SelectedWaypointR = nullptr;
    Waypoint_t*             SelectedWaypointS = nullptr;
    bool                    EnableCollisionDetectionForWaypoints = true;
};

} // end namespace pioneers3d

#endif // PIONEERS_COMMON_BOARD_TYPE_HPP
