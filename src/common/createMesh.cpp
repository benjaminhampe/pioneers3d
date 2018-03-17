#include "createMesh.hpp"

#include <irrlicht.h>
#include <assert.h>

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

	irr::core::aabbox3df bbox = mesh->getBoundingBox();

	bbox.addInternalBox( buffer->getBoundingBox() );

	mesh->setBoundingBox( bbox );
}
