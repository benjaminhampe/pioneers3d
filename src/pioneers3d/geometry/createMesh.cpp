#include "createMesh.hpp"

#include <irrlicht.h>

irr::scene::SMesh* 
createMesh()
{
    irr::scene::SMesh * mesh = new irr::scene::SMesh();
    return mesh;
}

void 
addToMesh( irr::scene::SMesh* mesh, irr::scene::SMeshBuffer* buffer )
{
    assert( mesh );
	
	assert( buffer );
	
	mesh->addMeshBuffer( buffer );
	
	mesh->setBoundingBox( mesh->getBoundingBox().addInternalBox( buffer->getBoundingBox() ) );
}