#ifndef DE_ALPHASONIC_CREATE_MESH_HPP
#define DE_ALPHASONIC_CREATE_MESH_HPP

namespace irr {
namespace scene {

	class SMeshBuffer;
	class SMesh;

} // end namespace scene
} // end namespace irr

irr::scene::SMesh*
createMesh();

void
addToMesh(
	irr::scene::SMesh* mesh,
	irr::scene::SMeshBuffer* buffer );

#endif // DE_ALPHASONIC_CREATE_MESH_HPP
