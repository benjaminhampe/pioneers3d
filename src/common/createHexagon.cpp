#include "createHexagon.hpp"

irr::scene::SMeshBuffer*
createHexagonMeshBufferXZ( float w, float h, float x, float y, float z )
{
    irr::scene::SMeshBuffer* p = new irr::scene::SMeshBuffer();

    // Vertices:
    irr::video::SColor const white = 0xFFFFFFFF;
    p->Vertices.reallocate(6);
    p->Vertices.set_used(0);
    p->Vertices.push_back( irr::video::S3DVertex( -.50f*w + x, y, 0.25f*h + z, 0,1,0, white, 0.00f,0.75f ) ); // A
    p->Vertices.push_back( irr::video::S3DVertex( 0.00f*w + x, y, 0.50f*h + z, 0,1,0, white, 0.50f,1.00f ) ); // B
    p->Vertices.push_back( irr::video::S3DVertex( 0.50f*w + x, y, 0.25f*h + z, 0,1,0, white, 1.00f,0.75f ) ); // C
    p->Vertices.push_back( irr::video::S3DVertex( 0.50f*w + x, y, -.25f*h + z, 0,1,0, white, 1.00f,0.25f ) ); // D
    p->Vertices.push_back( irr::video::S3DVertex( 0.00f*w + x, y, -.50f*h + z, 0,1,0, white, 0.50f,0.00f ) ); // E
    p->Vertices.push_back( irr::video::S3DVertex( -.50f*w + x, y, -.25f*h + z, 0,1,0, white, 0.00f,0.25f ) ); // F
    
	// BoundingBox:
    p->recalculateBoundingBox();
    
	// Indices:
	auto addTriangle = [ &p ] ( uint16_t a, uint16_t b, uint16_t c )
	{
		p->Indices.push_back( a );
		p->Indices.push_back( b );
		p->Indices.push_back( c );		
	};
	
    p->Indices.reallocate( 12 );
    p->Indices.set_used( 0 );
    addTriangle( 0,1,2 ); // ABC
	addTriangle( 0,2,3 ); // ACD
	addTriangle( 0,3,5 ); // ADF
	addTriangle( 5,3,4 ); // FDE
	
    return p;
}
