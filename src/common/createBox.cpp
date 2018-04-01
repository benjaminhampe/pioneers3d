#include "createBox.hpp"

/// @brief Create a box with one repeating texture over all 6 planes
AutoMeshBuffer *
createRotatedBox( glm::vec3 const & pos, glm::vec3 const & size, glm::vec3 const & rot, uint32_t color )
{
    AutoMeshBuffer * p = new AutoMeshBuffer( irr::scene::EPT_TRIANGLES );

    // material
//    if (color.getAlpha()<255)
//        buffer->Material.MaterialType = irr::video::EMT_TRANSPARENT_VERTEX_ALPHA;
//    else
//        buffer->Material.MaterialType = irr::video::EMT_SOLID;

    float const dx = 0.5f*size.x;
    float const dy = 0.5f*size.y;
    float const dz = 0.5f*size.z;

    glm::mat4 m0;
    m0 = glm::rotate( m0, rot.x * irr::core::DEGTORAD, glm::vec3( 1,0,0 ) );
    m0 = glm::rotate( m0, rot.y * irr::core::DEGTORAD, glm::vec3( 0,1,0 ) );
    m0 = glm::rotate( m0, rot.z * irr::core::DEGTORAD, glm::vec3( 0,0,1 ) );
    glm::mat3 mat(m0);
    glm::vec3 const A = pos + mat * glm::vec3(-dx,-dy,-dz);
    glm::vec3 const B = pos + mat * glm::vec3(-dx, dy,-dz);
    glm::vec3 const C = pos + mat * glm::vec3( dx, dy,-dz);
    glm::vec3 const D = pos + mat * glm::vec3( dx,-dy,-dz);
    glm::vec3 const E = pos + mat * glm::vec3(-dx,-dy, dz);
    glm::vec3 const F = pos + mat * glm::vec3(-dx, dy, dz);
    glm::vec3 const G = pos + mat * glm::vec3( dx, dy, dz);
    glm::vec3 const H = pos + mat * glm::vec3( dx,-dy, dz);

    addQuad( *p, E, F, B, A, color ); // n(-1, 0, 0);    // Neg X = EFBA
    addQuad( *p, E, A, D, H, color ); // n( 0,-1, 0);    // Neg Y = EADH
    addQuad( *p, A, B, C, D, color ); // n( 0, 0, -1);   // Neg Z = ABCD
    addQuad( *p, D, C, G, H, color ); // n( 1, 0, 0);    // Pos X = DCGH
    addQuad( *p, B, F, G, C, color ); // n( 0, 1, 0);    // Pos Y = BFGC
    addQuad( *p, H, G, F, E, color ); // n( 0, 0, 1);    // Pos Z = HGFE

    return p;
}


/// @brief Create a box mesh with 6 mesh-buffers and 6 textures
irr::scene::SMesh*
createBoxMesh( 	irr::core::vector3df const& size, // 3d-size
                irr::video::SColor const & color, // vertexcolor
                uint32_t matCount ) // material count == meshbuffer count
{
    //! common vars
    float const dx = 0.5f*size.X;
    float const dy = 0.5f*size.Y;
    float const dz = 0.5f*size.Z;
    irr::core::vector3df const A(-dx,-dy,-dz);
    irr::core::vector3df const B(-dx, dy,-dz);
    irr::core::vector3df const C( dx, dy,-dz);
    irr::core::vector3df const D( dx,-dy,-dz);
    irr::core::vector3df const E(-dx,-dy, dz);
    irr::core::vector3df const F(-dx, dy, dz);
    irr::core::vector3df const G( dx, dy, dz);
    irr::core::vector3df const H( dx,-dy, dz);
    irr::core::vector2df const uv1( 0, 1 );
    irr::core::vector2df const uv2( 0, 0 );
    irr::core::vector2df const uv3( 1, 0 );
    irr::core::vector2df const uv4( 1, 1 );

    //! six materials ( six possible textures, like flipped skybox for crates, cargoboxes, dice, etc... )
    if (matCount==6)
    {
        irr::scene::SMesh* mesh = new irr::scene::SMesh();
        if (!mesh)
            return 0;

        mesh->setBoundingBox( irr::core::aabbox3df(-dx,-dy,-dz, dx,dy,dz) );

        for ( int i = 0; i < 6; ++i )
        {
            irr::scene::SMeshBuffer* buffer = new irr::scene::SMeshBuffer();
            if (buffer)
            {
                // material
                if (color.getAlpha()<255)
                    buffer->Material.MaterialType = irr::video::EMT_TRANSPARENT_VERTEX_ALPHA;
                else
                    buffer->Material.MaterialType = irr::video::EMT_SOLID;

                // memory
                buffer->Vertices.reallocate(4);
                buffer->Vertices.set_used(0);
                buffer->Indices.reallocate(6);
                buffer->Indices.set_used(0);

                // choose quad
                if (i==0)
                {
                    // QUAD [1] neg dx
                    irr::core::vector3df const n(-1, 0, 0);
                    buffer->Vertices.push_back( irr::video::S3DVertex( E, n, color, uv1) ); // C
                    buffer->Vertices.push_back( irr::video::S3DVertex( F, n, color, uv2) ); // F
                    buffer->Vertices.push_back( irr::video::S3DVertex( B, n, color, uv3) ); // B
                    buffer->Vertices.push_back( irr::video::S3DVertex( A, n, color, uv4) ); // A
                    // buffer->Material.setTexture( 0, negX);
                }
                else if (i==1)
                {
                    // QUAD [2] neg dy
                    irr::core::vector3df const n(0, -1, 0);
                    buffer->Vertices.push_back( irr::video::S3DVertex( E, n, color, uv1) ); // C
                    buffer->Vertices.push_back( irr::video::S3DVertex( A, n, color, uv2) ); // A
                    buffer->Vertices.push_back( irr::video::S3DVertex( D, n, color, uv3) ); // B
                    buffer->Vertices.push_back( irr::video::S3DVertex( H, n, color, uv4) ); // D
                    // buffer->Material.setTexture( 0, negY);
                }
                else if (i==2)
                {
                    // QUAD [3] neg dz
                    irr::core::vector3df const n(-1, 0, 0);
                    buffer->Vertices.push_back( irr::video::S3DVertex( A, n, color, uv1) ); // A
                    buffer->Vertices.push_back( irr::video::S3DVertex( B, n, color, uv2) ); // B
                    buffer->Vertices.push_back( irr::video::S3DVertex( C, n, color, uv3) ); // C
                    buffer->Vertices.push_back( irr::video::S3DVertex( D, n, color, uv4) ); // D
                    // buffer->Material.setTexture( 0, negZ);
                }
                else if (i==3)
                {
                    // QUAD [4] pos dx
                    irr::core::vector3df const n(1, 0, 0);
                    buffer->Vertices.push_back( irr::video::S3DVertex( D, n, color, uv1) ); // D
                    buffer->Vertices.push_back( irr::video::S3DVertex( C, n, color, uv2) ); // C
                    buffer->Vertices.push_back( irr::video::S3DVertex( G, n, color, uv3) ); // G
                    buffer->Vertices.push_back( irr::video::S3DVertex( H, n, color, uv4) ); // H
                    // buffer->Material.setTexture( 0, posX);
                }
                else if (i==4)
                {
                    // QUAD [5] pos dy
                    irr::core::vector3df const n(0, 1, 0);
                    buffer->Vertices.push_back( irr::video::S3DVertex( B, n, color, uv1) ); // B
                    buffer->Vertices.push_back( irr::video::S3DVertex( F, n, color, uv2) ); // F
                    buffer->Vertices.push_back( irr::video::S3DVertex( G, n, color, uv3) ); // G
                    buffer->Vertices.push_back( irr::video::S3DVertex( C, n, color, uv4) ); // C
                    // buffer->Material.setTexture( 0, posY);
                }
                else if (i==5)
                {
                    // QUAD [6] pos dz
                    irr::core::vector3df const n(0, 0, 1);
                    buffer->Vertices.push_back( irr::video::S3DVertex( H, n, color, uv1) ); // E
                    buffer->Vertices.push_back( irr::video::S3DVertex( G, n, color, uv2) ); // F
                    buffer->Vertices.push_back( irr::video::S3DVertex( F, n, color, uv3) ); // G
                    buffer->Vertices.push_back( irr::video::S3DVertex( E, n, color, uv4) ); // H
                    // buffer->Material.setTexture( 0, posZ);
                }

                // bbox
                buffer->recalculateBoundingBox();

                // indices
                buffer->Indices.push_back( 0 );
                buffer->Indices.push_back( 1 );
                buffer->Indices.push_back( 2 );
                buffer->Indices.push_back( 0 );
                buffer->Indices.push_back( 2 );
                buffer->Indices.push_back( 3 );

                // add to mesh
                mesh->addMeshBuffer( buffer );
                buffer->drop();
                buffer = 0;
            }
        }

        // return
        mesh->setHardwareMappingHint( irr::scene::EHM_STATIC );
        return mesh;
    }

    //! three materials ( three textures )
    if (matCount>2 && matCount<6)
    {
        irr::scene::SMesh* mesh = new irr::scene::SMesh();
        if (!mesh)
            return 0;

        mesh->setBoundingBox( irr::core::aabbox3df(-dx,-dy,-dz, dx,dy,dz) );

        for (uint32_t i=0; i<3; i++)
        {
            irr::scene::SMeshBuffer* buffer = new irr::scene::SMeshBuffer();
            if (buffer)
            {
                // material
                if (color.getAlpha()<255)
                    buffer->Material.MaterialType = irr::video::EMT_TRANSPARENT_VERTEX_ALPHA;
                else
                    buffer->Material.MaterialType = irr::video::EMT_SOLID;

                // memory
                buffer->Vertices.reallocate(2*4);
                buffer->Vertices.set_used(0);
                buffer->Indices.reallocate(2*6);
                buffer->Indices.set_used(0);

                // choose dx quads
                if (i==0)
                {
                    // QUAD [1] neg dx
                    irr::core::vector3df const n(-1, 0, 0);
                    buffer->Vertices.push_back( irr::video::S3DVertex( E, n, color, uv1) ); // C
                    buffer->Vertices.push_back( irr::video::S3DVertex( F, n, color, uv2) ); // F
                    buffer->Vertices.push_back( irr::video::S3DVertex( B, n, color, uv3) ); // B
                    buffer->Vertices.push_back( irr::video::S3DVertex( A, n, color, uv4) ); // A

                    // QUAD [4] pos dx
                    irr::core::vector3df const m(1, 0, 0);
                    buffer->Vertices.push_back( irr::video::S3DVertex( D, m, color, uv1) ); // D
                    buffer->Vertices.push_back( irr::video::S3DVertex( C, m, color, uv2) ); // C
                    buffer->Vertices.push_back( irr::video::S3DVertex( G, m, color, uv3) ); // G
                    buffer->Vertices.push_back( irr::video::S3DVertex( H, m, color, uv4) ); // H
                    // buffer->Material.setTexture( 0, posX);
                }
                else if (i==1)
                {
                    // QUAD [2] neg dy
                    irr::core::vector3df const n(0, -1, 0);
                    buffer->Vertices.push_back( irr::video::S3DVertex( E, n, color, uv1) ); // C
                    buffer->Vertices.push_back( irr::video::S3DVertex( A, n, color, uv2) ); // A
                    buffer->Vertices.push_back( irr::video::S3DVertex( D, n, color, uv3) ); // B
                    buffer->Vertices.push_back( irr::video::S3DVertex( H, n, color, uv4) ); // D

                    // QUAD [5] pos dy
                    irr::core::vector3df const m(0, 1, 0);
                    buffer->Vertices.push_back( irr::video::S3DVertex( B, m, color, uv1) ); // B
                    buffer->Vertices.push_back( irr::video::S3DVertex( F, m, color, uv2) ); // F
                    buffer->Vertices.push_back( irr::video::S3DVertex( G, m, color, uv3) ); // G
                    buffer->Vertices.push_back( irr::video::S3DVertex( C, m, color, uv4) ); // C
                    // buffer->Material.setTexture( 0, posY);
                }
                else
                {
                    // QUAD [3] neg dz
                    irr::core::vector3df const n(-1, 0, 0);
                    buffer->Vertices.push_back( irr::video::S3DVertex( A, n, color, uv1) ); // A
                    buffer->Vertices.push_back( irr::video::S3DVertex( B, n, color, uv2) ); // B
                    buffer->Vertices.push_back( irr::video::S3DVertex( C, n, color, uv3) ); // C
                    buffer->Vertices.push_back( irr::video::S3DVertex( D, n, color, uv4) ); // D

                    // QUAD [6] pos dz
                    irr::core::vector3df const m(0, 0, 1);
                    buffer->Vertices.push_back( irr::video::S3DVertex( H, m, color, uv1) ); // E
                    buffer->Vertices.push_back( irr::video::S3DVertex( G, m, color, uv2) ); // F
                    buffer->Vertices.push_back( irr::video::S3DVertex( F, m, color, uv3) ); // G
                    buffer->Vertices.push_back( irr::video::S3DVertex( E, m, color, uv4) ); // H
                    // buffer->Material.setTexture( 0, posZ);
                }

                // bbox
                buffer->recalculateBoundingBox();

                // indices
                buffer->Indices.push_back( 0 );
                buffer->Indices.push_back( 1 );
                buffer->Indices.push_back( 2 );
                buffer->Indices.push_back( 0 );
                buffer->Indices.push_back( 2 );
                buffer->Indices.push_back( 3 );
                buffer->Indices.push_back( 0+4 );
                buffer->Indices.push_back( 1+4 );
                buffer->Indices.push_back( 2+4 );
                buffer->Indices.push_back( 0+4 );
                buffer->Indices.push_back( 2+4 );
                buffer->Indices.push_back( 3+4 );

                // add to mesh
                mesh->addMeshBuffer( buffer );
                buffer->drop();
                buffer = 0;
            }
        }

        // return
        mesh->setHardwareMappingHint( irr::scene::EHM_STATIC );
        return mesh;
    }
//	//! one material ( zero or one texture )
//	else
//	{
//		return createCubeMesh( size );
//	}

    return 0;
}
