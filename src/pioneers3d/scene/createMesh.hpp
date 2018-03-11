#ifndef P3D_GEOMETRY_CREATE_MESH_HPP
#define P3D_GEOMETRY_CREATE_MESH_HPP

#include <irrlicht.h>

namespace pioneers3d {

irr::scene::SMesh*
createMesh();

void
addToMesh(
    irr::scene::SMesh* mesh,
    irr::scene::SMeshBuffer* buffer );

} // end namespace pioneers3d

#endif // P3D_GEOMETRY_CREATE_MESH_HPP
