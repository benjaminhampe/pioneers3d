#include "createMeshBuffer.hpp"

#include <irrlicht.h>

irr::scene::SMeshBuffer* 
createMeshBuffer()
{
    irr::scene::SMeshBuffer * meshBuffer = new irr::scene::SMeshBuffer();
    meshBuffer->Material.Lighting = false;
    meshBuffer->Material.FogEnable = false;
    meshBuffer->Material.Wireframe = false;
    meshBuffer->Material.MaterialType = irr::video::EMT_SOLID;

    return meshBuffer;
}