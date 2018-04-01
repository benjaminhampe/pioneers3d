#ifndef PIONEERS3D_GEOMETRY_CREATE_HEXAGON_MESHBUFFER_XZ_HPP
#define PIONEERS3D_GEOMETRY_CREATE_HEXAGON_MESHBUFFER_XZ_HPP

#include <common/AutoMeshBuffer.hpp>

// Hexagon ( ver_2018 ):
//
//                 D        triangles: ABF, BCE, BEF, CDE
//                 /\
//              C /  \ E    M (x=0,y=0,z=0,u=0.5,v=0.5)
//               |----|     F( 0.5, 0, -.25, 1, 0.25 )
//               |  M |     E( 0.5, 0, 0.25, 1, 0.75 )
//               |----|     D( 0.0, 0, 0.50, 0.5, 1 )
//              B \  / F    C( -.5, 0, 0.25, 0, 0.75 )
//                 \/       B( -.5, 0, -.25, 0, 0.25 )
//                  A       A( 0, 0, -.5, .5, 0 )
//

glm::vec3
getHexagonPoint( float w, float h, int i );

AutoMeshBuffer*
createHexagon( float w, float h );

AutoMeshBuffer*
createHafenXZ( float w, float h, int i );

#endif // PIONEERS3D_GEOMETRY_CREATE_HEXAGON_MESHBUFFER_XZ_HPP
