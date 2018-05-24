#include <pioneers3d/data/Types.hpp>
//#include <pioneers3d/data/Texture.hpp>

namespace pioneers3d {

int32_t safeMod( int32_t a, int32_t b )
{
    if ( a == 0 && b == 0)
    {
        return 0;
    }

    return std::abs( a ) % std::abs( b );
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

void getHexagonTriangles( std::vector< irr::core::triangle3df > & container, glm::vec2 const & tile_size, glm::vec3 const & tile_pos )
{
    irr::core::vector3df const P(        tile_pos.x, tile_pos.y, tile_pos.z );
    irr::core::vector3df const A( 0.00f*tile_size.x, 0.0f, -.50f*tile_size.y );
    irr::core::vector3df const B( -.50f*tile_size.x, 0.0f, -.25f*tile_size.y );
    irr::core::vector3df const C( -.50f*tile_size.x, 0.0f, 0.25f*tile_size.y );
    irr::core::vector3df const D( 0.00f*tile_size.x, 0.0f, 0.50f*tile_size.y );
    irr::core::vector3df const E( 0.50f*tile_size.x, 0.0f, 0.25f*tile_size.y );
    irr::core::vector3df const F( 0.50f*tile_size.x, 0.0f, -.25f*tile_size.y );

    auto addTriangle = [ &container, P ] ( irr::core::vector3df const & a, irr::core::vector3df const & b, irr::core::vector3df const & c )
    {
        container.emplace_back( irr::core::triangle3df( P + a, P + b, P + c ) );
    };

    addTriangle( A,B,F ); // ABF
    addTriangle( B,C,E ); // BCE
    addTriangle( B,E,F ); // BEF
    addTriangle( C,D,E ); // CDE
}


glm::vec3 getHexagonCorner( int i, glm::vec2 const & tile_size, glm::vec3 const & tile_pos )
{
    while ( i < 0 ) i += 6;
    while ( i >= 6 ) i -= 6;

    switch ( i )
    {
        case 0: return tile_pos + glm::vec3( 0.00f*tile_size.x, 0.0f, -.50f*tile_size.y ); // A
        case 1: return tile_pos + glm::vec3( -.50f*tile_size.x, 0.0f, -.25f*tile_size.y ); // B
        case 2: return tile_pos + glm::vec3( -.50f*tile_size.x, 0.0f, 0.25f*tile_size.y ); // C
        case 3: return tile_pos + glm::vec3( 0.00f*tile_size.x, 0.0f, 0.50f*tile_size.y ); // D
        case 4: return tile_pos + glm::vec3( 0.50f*tile_size.x, 0.0f, 0.25f*tile_size.y ); // E
        case 5: return tile_pos + glm::vec3( 0.50f*tile_size.x, 0.0f, -.25f*tile_size.y ); // F
        default: assert( false ); // not allowed to happen
    }
}

glm::vec3 getHexagonEdgeCenter( int i, glm::vec2 const & tile_size, glm::vec3 const & tile_pos )
{
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
    glm::vec3 const A = getHexagonCorner( a, tile_size, tile_pos );
    glm::vec3 const B = getHexagonCorner( b, tile_size, tile_pos );
    return A + (B-A)*0.5f; // Center of egde (a,b)
}

float32_t getHexagonEdgeAngle( int i, glm::vec2 const & tile_size )
{
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

    glm::vec3 const A = getHexagonCorner( a, tile_size );
    glm::vec3 const B = getHexagonCorner( b, tile_size );
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

std::string
Tile_t::toString() const
{
    std::stringstream s;
    s << "type: " << Type.toString() << "; "
      << "i: "<< BoardIndex.x << "; "
      << "j: "<< BoardIndex.y << "; "
      << "x: "<< Pos.x << "; "
      << "y: "<< Pos.y << "; "
      << "z: "<< Pos.z << "; "
      << "dice: "<< DiceValue << "; "
      << "ang60: "<< Angle60 << "; "
      << "waypoints: "<< Waypoints.size() << "; "
      << "";
    return s.str();
}

std::string
Waypoint_t::toString() const
{
    std::stringstream s;
    s << "isRoad: " << IsRoad << "; "
      << "owner: "<< (void*)Owner << "; "
      << "points: "<< Points << "; "
      << "x: "<< Pos.x << "; "
      << "y: "<< Pos.x << "; "
      << "z: "<< Pos.x << "; "
//      << "dice: "<< tile->DiceValue << "; "
//      << "ang60: "<< tile->TexAngle60 << "; "
//      << "waypoints: "<< tile->Waypoints.size() << "; "
      << "";
    return s.str();
}

/*
std::string
Board_t::toString() const
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

*/

std::string
Player_t::toString() const
{
    std::stringstream s;
    s << "name: " << Name << "; "
      << "";
    return s.str();
}


} // end namespace pioneers3d
