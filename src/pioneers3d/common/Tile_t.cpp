#include "Tile_t.hpp"

#include "TextureManager.hpp"

namespace pioneers3d {

// Tile_t::Tile_t()
// {

// }
// Tile_t::~Tile_t()
// {

// }

std::string
Tile::toString() const
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

/*
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
*/
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
