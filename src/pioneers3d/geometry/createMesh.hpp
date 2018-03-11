#ifndef P3D_GEOMETRY_CREATE_MESH_HPP
#define P3D_GEOMETRY_CREATE_MESH_HPP

namespace irr {
namespace scene {

	class SMesh;
	class SMeshBuffer;

} // end namespace scene
} // end namespace irr

irr::scene::SMesh* 
createMesh();

void 
addToMesh( 
	irr::scene::SMesh* mesh, 
	irr::scene::SMeshBuffer* buffer );

#endif // P3D_GEOMETRY_CREATE_MESH_HPP
