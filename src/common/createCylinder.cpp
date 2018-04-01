#include "createCylinder.hpp"

/// @brief Create a cylinder hull meshbuffer.

AutoMeshBuffer*
createCylinderHull(
    glm::vec3 pos,
    float radius,
    float height,
    uint32_t color,
    uint32_t tessCircle,
    uint32_t tessHull)
{
    AutoMeshBuffer* p = new AutoMeshBuffer();

    assert( p );

    p->PrimitiveType = irr::scene::EPT_TRIANGLES;

    // common vars and constants
    float const y0 = 0.5f*height;				// top
    float const y1 = -0.5f*height;			// bottom
    float const sx = 1.f / (float)tessCircle;   // value step for circle
    float const sy = 1.f / (float)tessHull;		// value step for hull

    // bbox
    p->MeshBuffer.BoundingBox.reset( irr::core::aabbox3df(-radius,y1,-radius, radius,y0,radius) );

    // points

    SinCosTablef sincosTable( tessCircle );

    std::vector< glm::vec3 > vertexData;

    for (uint32_t y=0; y<=tessHull; y++)
    {
        for (uint32_t x=0; x<=tessCircle; x++)
        {
            float const s = sincosTable[x].s;
            float const c = sincosTable[x].c;
            vertexData.emplace_back( pos + glm::vec3( radius*s, y1 + height*sy*y, radius*c ) );
        }
    }

    // vertices

    uint32_t const pitch = tessCircle + 1; // vertices per row to skip

    for (uint32_t j = 0; j < tessHull; ++j )
    {
        for (uint32_t i = 0; i < tessCircle; ++i )
        {
            uint32_t const iA = i + j*pitch;
            uint32_t const iB = i + (j+1)*pitch;
            uint32_t const iC = (i+1) + (j+1)*pitch;
            uint32_t const iD = (i+1) + j*pitch;

            glm::vec3 const & D = vertexData[ iA ];
            glm::vec3 const & C = vertexData[ iB ];
            glm::vec3 const & B = vertexData[ iC ];
            glm::vec3 const & A = vertexData[ iD ];

            addQuad( *p, A, B, C, D, color );
        }
    }

    return p;
}

#if 0
// berechnet alle Punkte für eine Zylindermantelflaeche
// Die Flaeche besteht aus tessCircle * tessHull Segmenten
// Jedes Segment besteht aus 2 Dreiecken ABC und ACD
// Die Punkte ABCD werden wie folgt berechnet.

irr::scene::SMesh*
    createCylinderMesh(
        float radius,
        float height,
        uint32_t tessCircle,
        uint32_t tessHull,
        bool closeTop,
        bool closeBottom,
        bool bOneMaterial,
        irr::video::SColor const & color,
        irr::video::SColor const & topColor,
        irr::video::SColor const & bottomColor) const
{
    SMesh* mesh = new SMesh();
    if (!mesh)
        return 0;

    // common vars and constants
    const float y0 = 0.5f*height;				// top
    const float y1 = -0.5f*height;			// bottom
    const float sx = 1.f / (float)tessCircle;	// angle step for circle
    const float sy = 1.f / (float)tessHull;		// value step for hull
    core::CSinTablef sinTable(tessCircle);	// sin-table
    core::CCosTablef cosTable(tessCircle);	// cos-table

    // bbox
    mesh->BoundingBox.reset( core::aabbox3df(-radius,y1,-radius, radius,y0,radius) );

    //! hull
    SMeshBuffer* buffer = new SMeshBuffer();
    if (buffer)
    {
        // bbox
        buffer->BoundingBox.reset( core::aabbox3df(-radius,y1,-radius,radius,y0,radius) );

        // material
        if (color.getAlpha()<255)
            buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
        else
            buffer->Material.MaterialType = video::EMT_SOLID;

        // memory
        buffer->Vertices.reallocate( (tessCircle+1)*(tessHull+1) );
        buffer->Indices.reallocate( 6*tessCircle*tessHull );
        buffer->Vertices.set_used( 0 );
        buffer->Indices.set_used( 0 );

        // vertices
        for (uint32_t y=0; y<=tessHull; y++)
        {
            for (uint32_t x=0; x<=tessCircle; x++)
            {
                const float& s = sinTable[x];
                const float& c = cosTable[x];

                buffer->Vertices.push_back(
                    video::S3DVertex( radius*s, y1 + height*sy*y, radius*c, s,0,c, color, 1.0f-sx*x, 1.0f-sy*y ) );
            }
        }

        // indices
        const uint32_t pitch = tessCircle + 1; // vertices per row to skip

        for (uint32_t y=0; y<tessHull; y++)
        {
            for (uint32_t x=0; x<tessCircle; x++)
            {
                const uint32_t ix=x+1;
                const uint32_t iy=y+1;
                const uint32_t iA = x + y*pitch;
                const uint32_t iB = x + iy*pitch;
                const uint32_t iC = ix + iy*pitch;
                const uint32_t iD = ix + y*pitch;
                buffer->Indices.push_back(iA);
                buffer->Indices.push_back(iC);
                buffer->Indices.push_back(iB);
                buffer->Indices.push_back(iA);
                buffer->Indices.push_back(iD);
                buffer->Indices.push_back(iC);
            }
        }

        // add to mesh
        mesh->addMeshBuffer(buffer);
//		core::aabbox3df bbox = mesh->getBoundingBox();
//		bbox.addInternalBox( buffer->getBoundingBox() );
//		mesh->setBoundingBox( bbox );
        buffer->drop();
        buffer = 0;
    }

    //! top circle - cannot share vertices with hull, due to texturing and lighting
    if (closeTop)
    {
        buffer = new SMeshBuffer();
        if (buffer)
        {
            // bbox
            buffer->BoundingBox.reset( core::aabbox3df(-radius,y0,-radius,radius,y0,radius) );

            // material
            if (topColor.getAlpha()<255)
                buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
            else
                buffer->Material.MaterialType = video::EMT_SOLID;

            // memory
            buffer->Vertices.reallocate( tessCircle+1 );
            buffer->Vertices.set_used( 0 );
            buffer->Indices.reallocate( 3*tessCircle );
            buffer->Indices.set_used( 0 );

            // center vertex
            buffer->Vertices.push_back( video::S3DVertex(0,y0,0, 0,1,0,topColor,0.5f,0.5f) );

            // vertices + indices
            for (uint32_t i=0; i<tessCircle; i++)
            {
                const float x = radius * sinTable[i];
                const float z = radius * cosTable[i];
                const float u = 0.5f+0.5f*sinTable[i];
                const float v = 0.5f-0.5f*cosTable[i];
                buffer->Vertices.push_back( video::S3DVertex(x,y0,z,0,1,0,topColor,u,v) );

                buffer->Indices.push_back(0);	// push always center vertex
                uint32_t j=i+2;
                if (j>=tessCircle+1)
                    j=1;
                buffer->Indices.push_back(i+1);
                buffer->Indices.push_back(j);
            }

            // add to mesh
            mesh->addMeshBuffer(buffer);
    //		core::aabbox3df bbox = mesh->getBoundingBox();
    //		bbox.addInternalBox( buffer->getBoundingBox() );
    //		mesh->setBoundingBox( bbox );
            buffer->drop();
            buffer = 0;
        }
    }

    //! bottom circle - cannot share vertices with hull, due to texturing and lighting
    if (closeBottom)
    {
        buffer = new SMeshBuffer();
        if (buffer)
        {
            // bbox
            buffer->BoundingBox.reset( core::aabbox3df(-radius,y1,-radius,radius,y1,radius) );

            // material
            if (topColor.getAlpha()<255)
                buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
            else
                buffer->Material.MaterialType = video::EMT_SOLID;

            // memory
            buffer->Vertices.reallocate( tessCircle+1 );
            buffer->Vertices.set_used( 0 );
            buffer->Indices.reallocate( 3*tessCircle );
            buffer->Indices.set_used( 0 );

            // center vertex
            buffer->Vertices.push_back( video::S3DVertex(0,y1,0, 0,-1,0,bottomColor,0.5f,0.5f) );

            // vertices + indices
            for (uint32_t i=0; i<tessCircle; i++)
            {
                const float x = radius * sinTable[i];
                const float z = radius * cosTable[i];
                const float u = 0.5f+0.5f*sinTable[i];
                const float v = 0.5f+0.5f*cosTable[i];
                buffer->Vertices.push_back( video::S3DVertex(x,y1,z,0,-1,0,bottomColor,u,v) );

                buffer->Indices.push_back(0);	// push always center vertex
                uint32_t j=i+2;
                if (j>=tessCircle+1)
                    j=1;
                buffer->Indices.push_back(j);
                buffer->Indices.push_back(i+1);
            }

            // add to mesh
            mesh->addMeshBuffer(buffer);
    //		core::aabbox3df bbox = mesh->getBoundingBox();
    //		bbox.addInternalBox( buffer->getBoundingBox() );
    //		mesh->setBoundingBox( bbox );
            buffer->drop();
            buffer = 0;
        }
    }
    // return mesh
    mesh->setHardwareMappingHint(EHM_STATIC);
    return mesh;
}

#endif
