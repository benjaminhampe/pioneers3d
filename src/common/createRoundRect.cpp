#include "createRoundRect.hpp"

#include <common/sinCosTable.hpp>

irr::scene::SMeshBuffer*
createRoundRectMeshBuffer(
    glm::vec2 size,
    glm::vec2 radius,
    int tesselation,
    bool bFullyTextured,
    irr::video::SColor const & outerColor,
    irr::video::SColor const & innerColor )
{
    irr::scene::SMeshBuffer* buffer = new irr::scene::SMeshBuffer();
    assert( buffer );

    // tables
    SinCosTablef lookupTable( tesselation + 1 );

    // bbox
    buffer->setBoundingBox(
        irr::core::aabbox3df(-0.5f*size.x, -0.5f*size.y, 0.0f, 0.5f*size.x, 0.5f*size.y, 0.0f) );

    // material
    if (outerColor.getAlpha()<255 || innerColor.getAlpha()<255)
        buffer->Material.MaterialType = irr::video::EMT_TRANSPARENT_VERTEX_ALPHA;
    else
        buffer->Material.MaterialType = irr::video::EMT_SOLID;

    float const fw = 1.0f/(float)size.x;
    float const fh = 1.0f/(float)size.y;
    float const frw = (float)radius.x*fw;
    float const frh = (float)radius.y*fh;
    float const fwrw = (float)(size.x-radius.x)*fw;
    float const fhrh = (float)(size.y-radius.y)*fh;
    float const x = -0.5f*size.x;
    float const y = -0.5f*size.y;

    // vertices = 12 + 4*tesselation
    buffer->Vertices.reallocate(12 + 4*tesselation);
    buffer->Vertices.set_used(0);
    irr::core::vector3df const A ( x+radius.x,       y+radius.y,0 );
    irr::core::vector3df const B ( x+radius.x,       y-radius.y+size.y,0 );
    irr::core::vector3df const C ( x+size.x-radius.x,y-radius.y+size.y,0 );
    irr::core::vector3df const D ( x+size.x-radius.x,y+radius.y,0 );
    irr::core::vector3df const E ( x+radius.x,       y,0 );
    irr::core::vector3df const F ( x+size.x-radius.x,y,0 );
    irr::core::vector3df const G ( x+radius.x,       y+size.y,0 );
    irr::core::vector3df const H ( x+size.x-radius.x,y+size.y,0);
    irr::core::vector3df const I ( x+0,              y+radius.y,0);
    irr::core::vector3df const J ( x+0,              y-radius.y+size.y,0);
    irr::core::vector3df const K ( x+size.x,         y-radius.y+size.y,0);
    irr::core::vector3df const L ( x+size.x,         y+radius.y,0);
    irr::core::vector3df const n ( 0,0,-1);

    // vertices += 12
    buffer->Vertices.push_back( irr::video::S3DVertex( A, n, innerColor, irr::core::vector2df(frw,fhrh)) ); // A=0
    buffer->Vertices.push_back( irr::video::S3DVertex( B, n, innerColor, irr::core::vector2df(frw,frh)) ); 	// B=1
    buffer->Vertices.push_back( irr::video::S3DVertex( C, n, innerColor, irr::core::vector2df(fwrw,frh)) );	// C=2
    buffer->Vertices.push_back( irr::video::S3DVertex( D, n, innerColor, irr::core::vector2df(fwrw,fhrh)) );// D=3
    buffer->Vertices.push_back( irr::video::S3DVertex( E, n, outerColor, irr::core::vector2df(frw,1)) ); 	// E=4
    buffer->Vertices.push_back( irr::video::S3DVertex( F, n, outerColor, irr::core::vector2df(fwrw,1)) ); 	// F=5
    buffer->Vertices.push_back( irr::video::S3DVertex( G, n, outerColor, irr::core::vector2df(frw,0)) ); 	// G=6
    buffer->Vertices.push_back( irr::video::S3DVertex( H, n, outerColor, irr::core::vector2df(fwrw,0)) ); 	// H=7
    buffer->Vertices.push_back( irr::video::S3DVertex( I, n, outerColor, irr::core::vector2df(0,fhrh)) ); 	// I=8
    buffer->Vertices.push_back( irr::video::S3DVertex( J, n, outerColor, irr::core::vector2df(0,frh)) ); 	// J=9
    buffer->Vertices.push_back( irr::video::S3DVertex( K, n, outerColor, irr::core::vector2df(1,frh)) ); 	// K=A
    buffer->Vertices.push_back( irr::video::S3DVertex( L, n, outerColor, irr::core::vector2df(1,fhrh)) ); 	// L=B

    // indices += 30 + 4*3*(tesselation+1)
    buffer->Indices.reallocate(30 + 4*3*(tesselation+1));
    buffer->Indices.set_used(0);

    // indices += 30
    auto addTriangle = [&buffer] ( uint16_t a, uint16_t b, uint16_t c )
    {
        buffer->Indices.push_back( a );
        buffer->Indices.push_back( b );
        buffer->Indices.push_back( c );
    };

    addTriangle( 0, 1, 2 ); 	// ABC = 012
    addTriangle( 0, 2, 3 ); 	// ACD = 023
    addTriangle( 1, 6, 7 );		// BGH = 167
    addTriangle( 1, 7, 2 );		// BHC = 172
    addTriangle( 4, 0, 3 );		// EAD = 403
    addTriangle( 4, 3, 5 );		// EDF = 435
    addTriangle( 8, 9, 1 );		// IJB = 891
    addTriangle( 8, 1, 0 );		// IBA = 810
    addTriangle( 3, 2, 10 );	// DCK = 32A
    addTriangle( 3, 10, 11 );	// DKL = 3AB

    uint32_t const INDEX_A = 0;
    uint32_t const INDEX_B = 1;
    uint32_t const INDEX_C = 2;
    uint32_t const INDEX_D = 3;
    uint32_t const INDEX_E = 4;
    uint32_t const INDEX_F = 5;
    uint32_t const INDEX_G = 6;
    uint32_t const INDEX_H = 7;
    uint32_t const INDEX_I = 8;
    uint32_t const INDEX_J = 9;
    uint32_t const INDEX_K = 10;
    uint32_t const INDEX_L = 11;

    //! topLeft BJG quarter circle
    // vertices += tesselation
    uint32_t k = buffer->Vertices.size();
    for (uint32_t i=0; i<tesselation; i++)
    {
        float x = buffer->Vertices[INDEX_B].Pos.X - radius.x*lookupTable[ i ].c;
        float y = buffer->Vertices[INDEX_B].Pos.Y + radius.y*lookupTable[i].s;
        float z = buffer->Vertices[INDEX_B].Pos.Z;
        float u = (float)radius.x*(1.0f-lookupTable[ i ].c)/(float)size.x;
        float v = (float)radius.y*(1.0f-lookupTable[ i ].s)/(float)size.y;
        buffer->Vertices.push_back( irr::video::S3DVertex( x, y,	z, 0, 0, -1, outerColor, u, v ));
    }
    // indices += 3*(tesselation+1)
    for (uint32_t i=0; i<tesselation+1; i++)
    {
        uint32_t a,b,c;
        if (i==0) 					{ a = INDEX_B; b = INDEX_J; c = k; }
        else if (i==tesselation) 	{ a = INDEX_B; b = k+i-1; c = INDEX_G; }
        else 						{ a = INDEX_B; b = k+i-1; c = k+i; }
        buffer->Indices.push_back(a);
        buffer->Indices.push_back(b);
        buffer->Indices.push_back(c);
    }

    //! topRight CHK quarter circle
    // vertices += tesselation
    k=buffer->Vertices.size();
    for (uint32_t i=0; i<tesselation; i++)
    {
        float x = buffer->Vertices[INDEX_C].Pos.X + radius.x*lookupTable[ i ].c;
        float y = buffer->Vertices[INDEX_C].Pos.Y + radius.y*lookupTable[i].s;
        float z = buffer->Vertices[INDEX_C].Pos.Z;
        float u = 1.0f-(float)radius.x*(1.0f-lookupTable[ i ].c)/(float)size.x;
        float v = (float)radius.y*(1.0f-lookupTable[ i ].s)/(float)size.y;
        buffer->Vertices.push_back( irr::video::S3DVertex( x, y, z, 0, 0, -1, outerColor, u, v ));
    }
    // indices += 3*(tesselation+1)
    for (uint32_t i=0; i<tesselation+1; i++)
    {
        uint32_t a,b,c;
        if (i==0) 					{ a=INDEX_C; b=k; c=INDEX_K; }
        else if (i==tesselation) 	{ a=INDEX_C; b=INDEX_H; c=k+i-1; }
        else 						{ a=INDEX_C; b=k+i; c=k+i-1; }
        buffer->Indices.push_back(a);
        buffer->Indices.push_back(b);
        buffer->Indices.push_back(c);
    }

    //! bottomRight DLF quarter circle
    // vertices += tesselation
    k=buffer->Vertices.size();
    for (uint32_t i=0; i<tesselation; i++)
    {
        float x = buffer->Vertices[INDEX_D].Pos.X + radius.x*lookupTable[ i ].c;
        float y = buffer->Vertices[INDEX_D].Pos.Y - radius.y*lookupTable[i].s;
        float z = buffer->Vertices[INDEX_D].Pos.Z;
        float u = 1.0f-(float)radius.x*(1.0f-lookupTable[ i ].c)/(float)size.x;
        float v = 1.0f-(float)radius.y*(1.0f-lookupTable[ i ].s)/(float)size.y;
        buffer->Vertices.push_back( irr::video::S3DVertex( x, y, z, 0, 0, -1, outerColor, u, v ));
    }
    // indices += 3*(tesselation+1)
    for (uint32_t i=0; i<tesselation+1; i++)
    {
        uint32_t a,b,c;
        if (i==0) 					{ a=INDEX_D; b=INDEX_L; c=k; }
        else if (i==tesselation) 	{ a=INDEX_D; b=k+i-1; c=INDEX_F; }
        else 						{ a=INDEX_D; b=k+i-1; c=k+i; }
        buffer->Indices.push_back(a);
        buffer->Indices.push_back(b);
        buffer->Indices.push_back(c);
    }

    //! bottomLeft AEI quarter circle
    // vertices += tesselation
    k=buffer->Vertices.size();
    for (uint32_t i=0; i<tesselation; i++)
    {
        float x = buffer->Vertices[INDEX_A].Pos.X - radius.x*lookupTable[ i ].c;
        float y = buffer->Vertices[INDEX_A].Pos.Y - radius.y*lookupTable[i].s;
        float z = buffer->Vertices[INDEX_A].Pos.Z;
        float u = (float)radius.x*(1.0f-lookupTable[ i ].c)/(float)size.x;
        float v = 1.0f-(float)radius.y*(1.0f-lookupTable[ i ].s)/(float)size.y;
        buffer->Vertices.push_back( irr::video::S3DVertex( x, y, z, 0, 0, -1, outerColor, u, v ));
    }
    // indices += 3*(tesselation+1)
    for (uint32_t i=0; i<tesselation+1; i++)
    {
        uint32_t a,b,c;
        if (i==0) 					{ a=INDEX_A; b=k; c=INDEX_I; }
        else if (i==tesselation) 	{ a=INDEX_A; b=INDEX_E; c=k+i-1; }
        else 						{ a=INDEX_A; b=k+i; c=k+i-1; }
        buffer->Indices.push_back(a);
        buffer->Indices.push_back(b);
        buffer->Indices.push_back(c);
    }

    return buffer;
}
