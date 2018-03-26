#ifndef PIONEERS3D_GEOMETRY_CREATE_HEXAGON_MESHBUFFER_XZ_HPP
#define PIONEERS3D_GEOMETRY_CREATE_HEXAGON_MESHBUFFER_XZ_HPP

#include <common/Types.hpp>

///
/// ( 3D ) Hexagon MeshBuffer XZ plane
///
//
// M (x=0,y=0,z=0,u=0.5,v=0.5)
// A( -.5, 0, 0.25, 0, 0.75 )
// B( 0.0, 0, 0.50, 0.5, 1 )
// C( 0.5, 0, 0.25, 1, 0.75 )
// D( 0.5, 0, -.25, 1, 0.25 )
// E( 0.0, 0, -.50, 0.5, 0 )
// F( -.5, 0, -.25, 0, 0.25 )
//
//                 B
//                 /\
//              A /  \ C
//               |----|
//               |  M |
//               |----|
//              F \  / D
//                 \/
//                  E
//
// as Top: ABC, ACD, ADF, FDE
// as Bottom: CBA, DCA, FDA, EDF
//

irr::scene::SMeshBuffer*
createHexagonMeshBufferXZ( float w, float h, float x, float y, float z );

#endif // PIONEERS3D_GEOMETRY_CREATE_HEXAGON_MESHBUFFER_XZ_HPP
