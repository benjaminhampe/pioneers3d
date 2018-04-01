#ifndef DE_ALPHASONIC_CREATE_CIRCLE_MESHBUFFER_HPP
#define DE_ALPHASONIC_CREATE_CIRCLE_MESHBUFFER_HPP

#include <common/AutoMeshBuffer.hpp>

AutoMeshBuffer*
createCircleXY( float r, int segments, float x, float y, float z );

AutoMeshBuffer*
createCircleXZ( glm::vec3 pos, float r, int segments );

#endif // DE_ALPHASONIC_CREATE_CIRCLE_MESHBUFFER_HPP
