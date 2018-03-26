#ifndef DE_ALPHASONIC_CREATE_CIRCLE_MESHBUFFER_HPP
#define DE_ALPHASONIC_CREATE_CIRCLE_MESHBUFFER_HPP

#include <irrlicht.h>

irr::scene::SMeshBuffer*
createCircleMeshBufferXY( float r, int segments, float x, float y, float z );

irr::scene::SMeshBuffer*
createCircleMeshBufferXZ( float r, int segments, float x, float y, float z );

#endif // DE_ALPHASONIC_CREATE_CIRCLE_MESHBUFFER_HPP
