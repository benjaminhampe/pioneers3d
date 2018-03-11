#ifndef P3D_GEOMETRY_CREATE_CIRCLE_MESHBUFFER_XY_HPP
#define P3D_GEOMETRY_CREATE_CIRCLE_MESHBUFFER_XY_HPP

#include <pioneers3d/scene/createMeshBuffer.hpp>

namespace pioneers3d {

irr::scene::SMeshBuffer*
    createCircleMeshBufferXY( float r, int segments, float x, float y, float z );

} // end namespace pioneers3d


#endif // P3D_GEOMETRY_CREATE_CIRCLE_MESHBUFFER_HPP
