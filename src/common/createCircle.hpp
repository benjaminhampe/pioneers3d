#ifndef DE_ALPHASONIC_CREATE_CIRCLE_MESHBUFFER_HPP
#define DE_ALPHASONIC_CREATE_CIRCLE_MESHBUFFER_HPP

#include <common/AutoMeshBuffer.hpp>

AutoMeshBuffer*
createCircle( glm::vec3 const & pos, float r, uint32_t segments = 36, uint32_t color = 0xFFFFFFFF );

AutoMeshBuffer*
createCircleXZ( glm::vec3 const & pos, float r, uint32_t segments );

#endif // DE_ALPHASONIC_CREATE_CIRCLE_MESHBUFFER_HPP
