#ifndef DE_ALPHASONIC_AUTO_MESH_BUFFER_HPP
#define DE_ALPHASONIC_AUTO_MESH_BUFFER_HPP

#include <common/Types.hpp>
#include <irrBackend.hpp>

inline void
enumerateMeshBuffer( irr::scene::SMeshBuffer & p )
{
    std::cout << "VertexCount = " << p.Vertices.size() << "\n";
    for ( uint32_t i = 0; i < p.Vertices.size(); ++i )
    {
        std::cout << "Vertex[" << i << "]" << toString( p.Vertices[ i ] ) << "\n";
    }

    std::cout << "IndexCount = " << p.Indices.size() << "\n";

    for ( uint32_t i = 0; i < p.Indices.size(); ++i )
    {
        std::cout << "Index[" << i << "]" << p.Indices[ i ] << "\n";
    }

    std::cout << "Material = " << p.Vertices.size() << "\n";
    std::cout << "BoundingBox = " << p.Vertices.size() << "\n";
}

class AutoMeshBuffer : public irr::IReferenceCounted
{
public:
    irr::scene::E_PRIMITIVE_TYPE PrimitiveType;	// We need this to enable auto rendering
    irr::video::E_VERTEX_TYPE VertexType;		// We need this to enable auto rendering
    irr::video::E_INDEX_TYPE IndexType;			// We need this to enable auto rendering
    irr::scene::SMeshBuffer MeshBuffer;			// The traditional irrlicht meshbuffer ( aka non-auto, aka broken )

public:
    AutoMeshBuffer() : PrimitiveType( irr::scene::EPT_POINTS ) // This works for every mesh type ( aka fallback )
                     , VertexType( irr::video::EVT_STANDARD )	// Standard Vertex: FVF_POSITION | FVF_NORMAL | FVF_COLOR32 | FVF_TEXCOORD0
                     , IndexType( irr::video::EIT_16BIT )		// Standard up to 65535 Vertices
    {
        MeshBuffer.Material.MaterialType = irr::video::EMT_SOLID;
        MeshBuffer.Material.Lighting = false;
        MeshBuffer.Material.FogEnable = false;
    }

    AutoMeshBuffer( irr::scene::E_PRIMITIVE_TYPE primType,
                    irr::video::E_VERTEX_TYPE vertexType = irr::video::EVT_STANDARD,
                    irr::video::E_INDEX_TYPE indexType = irr::video::EIT_16BIT )
        : PrimitiveType( primType )
        , VertexType( vertexType )
        , IndexType( indexType )
    {
        MeshBuffer.Material.MaterialType = irr::video::EMT_SOLID;
        MeshBuffer.Material.Lighting = false;
        MeshBuffer.Material.FogEnable = false;
    }

    virtual ~AutoMeshBuffer() {}

    static uint32_t
    getPrimitiveCount( irr::scene::E_PRIMITIVE_TYPE primitiveType, uint32_t indexCount )
    {
        switch( primitiveType )
        {
            case irr::scene::EPT_POINTS: return indexCount;
            case irr::scene::EPT_LINES: return indexCount / 2;
            case irr::scene::EPT_LINE_LOOP: return indexCount - 1;
            case irr::scene::EPT_TRIANGLES: return indexCount / 3;
            case irr::scene::EPT_POLYGON: return indexCount;
            case irr::scene::EPT_QUADS: return indexCount / 4;
            default: return 0;
        }
        return 0;
    }

    uint32_t getPrimitiveCount() const
    {
        return getPrimitiveCount( PrimitiveType, MeshBuffer.getIndexCount() );
    }

    void render( irr::video::IVideoDriver* driver )
    {
        driver->setMaterial( MeshBuffer.Material );

        driver->drawVertexPrimitiveList(
            MeshBuffer.getVertices(),
            MeshBuffer.getVertexCount(),
            MeshBuffer.getIndices(),
            this->getPrimitiveCount(),
            VertexType,
            PrimitiveType,
            IndexType
        );
    }

    // material

    void setTexture( uint32_t stage, irr::video::ITexture* tex )
    {
        MeshBuffer.Material.setTexture( stage, tex );
    }

    void setWireframe( bool enable )
    {
        MeshBuffer.Material.Wireframe = enable;
    }

    bool hasTransparentVertexColor() const
    {
        for ( uint32_t i = 0; i < MeshBuffer.Vertices.size(); ++i )
        {
            if ( MeshBuffer.Vertices[ i ].Color.getAlpha() < 255 )
            {
                return true;
            }
        }
        return false;
    }

    void setDefaultMaterialType()
    {
        MeshBuffer.Material.MaterialType = irr::video::EMT_SOLID;

        if ( hasTransparentVertexColor() )
        {
            MeshBuffer.Material.MaterialType = irr::video::EMT_TRANSPARENT_VERTEX_ALPHA;
        }
    }

    void setDefaultMaterialType( irr::video::SColor const & color )
    {
        MeshBuffer.Material.MaterialType = irr::video::EMT_SOLID;

        if ( color.getAlpha() < 255 )
        {
            MeshBuffer.Material.MaterialType = irr::video::EMT_TRANSPARENT_VERTEX_ALPHA;
        }
    }

/// IMeshBuffer interface:
///
    //! returns an axis aligned bounding box
    irr::core::aabbox3d<irr::f32> const & getBoundingBox() const
    {
        return MeshBuffer.BoundingBox;
    }

    //! set user axis aligned bounding box
    void setBoundingBox( irr::core::aabbox3df const & box )
    {
        MeshBuffer.BoundingBox = box;
    }

    //! Get material of this meshbuffer
    /** \return Material of this buffer */
    irr::video::SMaterial const & getMaterial() const
    {
        return MeshBuffer.Material;
    }

    //! Get material of this meshbuffer
    /** \return Material of this buffer */
    irr::video::SMaterial & getMaterial()
    {
        return MeshBuffer.Material;
    }

};

inline void
addVertex( AutoMeshBuffer & buffer, glm::vec3 p, glm::vec3 n, uint32_t color, glm::vec2 uv, bool flipV = true )
{
    buffer.MeshBuffer.Vertices.push_back( irr::video::S3DVertex( p.x, p.y, p.z, n.x, n.y, n.z, irr::video::SColor( color ), uv.x, (flipV) ? 1.0f - uv.y : uv.y ) );
    buffer.MeshBuffer.BoundingBox.addInternalPoint( p.x, p.y, p.z );
}

inline void
addTriangle( AutoMeshBuffer & buffer, glm::vec3 A, glm::vec3 B, glm::vec3 C, uint32_t color, glm::vec2 uvA, glm::vec2 uvB, glm::vec2 uvC, bool flipV = true )
{
    uint32_t const v0 = buffer.MeshBuffer.Vertices.size();
    glm::vec3 const n = glm::normalize( glm::cross( B-A, C-A ) );

    addVertex( buffer, A, n, color, uvA, flipV );
    addVertex( buffer, B, n, color, uvB, flipV );
    addVertex( buffer, C, n, color, uvC, flipV );

    buffer.MeshBuffer.Indices.push_back( v0 + 0 );
    buffer.MeshBuffer.Indices.push_back( v0 + 1 );
    buffer.MeshBuffer.Indices.push_back( v0 + 2 );
}

inline void
addTriangle( AutoMeshBuffer & buffer, glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 n, uint32_t color, glm::vec2 uvA, glm::vec2 uvB, glm::vec2 uvC, bool flipV = true )
{
    uint32_t const v0 = buffer.MeshBuffer.Vertices.size();

    addVertex( buffer, A, n, color, uvA, flipV );
    addVertex( buffer, B, n, color, uvB, flipV );
    addVertex( buffer, C, n, color, uvC, flipV );

    buffer.MeshBuffer.Indices.push_back( v0 + 0 );
    buffer.MeshBuffer.Indices.push_back( v0 + 1 );
    buffer.MeshBuffer.Indices.push_back( v0 + 2 );
}

inline glm::vec3
getNormal( glm::vec3 A, glm::vec3 B, glm::vec3 C )
{
    return glm::normalize( glm::cross( B-A, C-A ) );
}


inline void
addQuad( AutoMeshBuffer & buffer, glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 D, uint32_t color, bool flipV = true )
{
    uint32_t const v0 = buffer.MeshBuffer.Vertices.size();

    glm::vec3 const n1 = getNormal( A, B, C );
    glm::vec3 const n2 = getNormal( A, C, D );
    glm::vec2 const uvA( 0.0f, 0.0f );
    glm::vec2 const uvB( 0.0f, 1.0f );
    glm::vec2 const uvC( 1.0f, 1.0f );
    glm::vec2 const uvD( 1.0f, 0.0f );

    addVertex( buffer, A, n1, color, uvA, flipV );
    addVertex( buffer, B, n2, color, uvB, flipV );
    addVertex( buffer, C, n1, color, uvC, flipV );
    addVertex( buffer, A, n2, color, uvA, flipV );
    addVertex( buffer, C, n2, color, uvC, flipV );
    addVertex( buffer, D, n1, color, uvD, flipV );

    buffer.MeshBuffer.Indices.push_back( v0 + 0 );
    buffer.MeshBuffer.Indices.push_back( v0 + 1 );
    buffer.MeshBuffer.Indices.push_back( v0 + 2 );
    buffer.MeshBuffer.Indices.push_back( v0 + 3 );
    buffer.MeshBuffer.Indices.push_back( v0 + 4 );
    buffer.MeshBuffer.Indices.push_back( v0 + 5 );
}

//  F  G
// /E /H
// B--C
// |/ |
// A--D

/// @brief Create a box with one repeating texture over all 6 planes
inline void
addBox( AutoMeshBuffer & p, glm::vec3 const & pos, glm::vec3 const & size, uint32_t color )
{
    float const dx = 0.5f*size.x;
    float const dy = 0.5f*size.y;
    float const dz = 0.5f*size.z;
    glm::vec3 const A = pos + glm::vec3(-dx,-dy,-dz);
    glm::vec3 const B = pos + glm::vec3(-dx, dy,-dz);
    glm::vec3 const C = pos + glm::vec3( dx, dy,-dz);
    glm::vec3 const D = pos + glm::vec3( dx,-dy,-dz);
    glm::vec3 const E = pos + glm::vec3(-dx,-dy, dz);
    glm::vec3 const F = pos + glm::vec3(-dx, dy, dz);
    glm::vec3 const G = pos + glm::vec3( dx, dy, dz);
    glm::vec3 const H = pos + glm::vec3( dx,-dy, dz);

    // p.MeshBuffer.BoundingBox = irr::core::aabbox3df(-dx,-dy,-dz, dx,dy,dz);

    addQuad( p, E, F, B, A, color ); // n(-1, 0, 0);    // Neg X = EFBA
    addQuad( p, E, A, D, H, color ); // n( 0,-1, 0);    // Neg Y = EADH
    addQuad( p, A, B, C, D, color ); // n( 0, 0, -1);   // Neg Z = ABCD
    addQuad( p, D, C, G, H, color ); // n( 1, 0, 0);    // Pos X = DCGH
    addQuad( p, B, F, G, C, color ); // n( 0, 1, 0);    // Pos Y = BFGC
    addQuad( p, H, G, F, E, color ); // n( 0, 0, 1);    // Pos Z = HGFE
}

/// @brief Create a box with one repeating texture over all 6 planes
inline void
addBoxPlane( AutoMeshBuffer & p, int i, glm::vec3 const & pos, glm::vec3 const & size, uint32_t color )
{
    float const dx = 0.5f*size.x;
    float const dy = 0.5f*size.y;
    float const dz = 0.5f*size.z;
    glm::vec3 const A = pos + glm::vec3(-dx,-dy,-dz);
    glm::vec3 const B = pos + glm::vec3(-dx, dy,-dz);
    glm::vec3 const C = pos + glm::vec3( dx, dy,-dz);
    glm::vec3 const D = pos + glm::vec3( dx,-dy,-dz);
    glm::vec3 const E = pos + glm::vec3(-dx,-dy, dz);
    glm::vec3 const F = pos + glm::vec3(-dx, dy, dz);
    glm::vec3 const G = pos + glm::vec3( dx, dy, dz);
    glm::vec3 const H = pos + glm::vec3( dx,-dy, dz);

         if ( i == 0 ) addQuad( p, E, F, B, A, color ); // n(-1, 0, 0); // Neg X = EFBA
    else if ( i == 1 ) addQuad( p, E, A, D, H, color ); // n( 0,-1, 0); // Neg Y = EADH
    else if ( i == 2 ) addQuad( p, A, B, C, D, color ); // n( 0, 0,-1); // Neg Z = ABCD
    else if ( i == 3 ) addQuad( p, D, C, G, H, color ); // n( 1, 0, 0); // Pos X = DCGH
    else if ( i == 4 ) addQuad( p, B, F, G, C, color ); // n( 0, 1, 0); // Pos Y = BFGC
    else if ( i == 5 ) addQuad( p, H, G, F, E, color ); // n( 0, 0, 1); // Pos Z = HGFE
}

/// @brief Create a box
inline void
addBoxWithoutTop( AutoMeshBuffer & p, glm::vec3 const & pos, glm::vec3 const & size, uint32_t color )
{
    float const dx = 0.5f*size.x;
    float const dy = 0.5f*size.y;
    float const dz = 0.5f*size.z;
    glm::vec3 const A = pos + glm::vec3(-dx,-dy,-dz);
    glm::vec3 const B = pos + glm::vec3(-dx, dy,-dz);
    glm::vec3 const C = pos + glm::vec3( dx, dy,-dz);
    glm::vec3 const D = pos + glm::vec3( dx,-dy,-dz);
    glm::vec3 const E = pos + glm::vec3(-dx,-dy, dz);
    glm::vec3 const F = pos + glm::vec3(-dx, dy, dz);
    glm::vec3 const G = pos + glm::vec3( dx, dy, dz);
    glm::vec3 const H = pos + glm::vec3( dx,-dy, dz);

    addQuad( p, E, F, B, A, color ); // n(-1, 0, 0);    // Neg X = EFBA
    addQuad( p, E, A, D, H, color ); // n( 0,-1, 0);    // Neg Y = EADH
    addQuad( p, A, B, C, D, color ); // n( 0, 0, -1);   // Neg Z = ABCD
    addQuad( p, D, C, G, H, color ); // n( 1, 0, 0);    // Pos X = DCGH
    //addQuad( p, B, F, G, C, color ); // n( 0, 1, 0);    // Pos Y = BFGC
    addQuad( p, H, G, F, E, color ); // n( 0, 0, 1);    // Pos Z = HGFE
}

/// @brief Create a box
inline void
addBoxWithoutTopAndBottom( AutoMeshBuffer & p, glm::vec3 const & pos, glm::vec3 const & size, uint32_t color )
{
    float const dx = 0.5f*size.x;
    float const dy = 0.5f*size.y;
    float const dz = 0.5f*size.z;
    glm::vec3 const A = pos + glm::vec3(-dx,-dy,-dz);
    glm::vec3 const B = pos + glm::vec3(-dx, dy,-dz);
    glm::vec3 const C = pos + glm::vec3( dx, dy,-dz);
    glm::vec3 const D = pos + glm::vec3( dx,-dy,-dz);
    glm::vec3 const E = pos + glm::vec3(-dx,-dy, dz);
    glm::vec3 const F = pos + glm::vec3(-dx, dy, dz);
    glm::vec3 const G = pos + glm::vec3( dx, dy, dz);
    glm::vec3 const H = pos + glm::vec3( dx,-dy, dz);

    addQuad( p, E, F, B, A, color ); // n(-1, 0, 0);    // Neg X = EFBA
    //addQuad( p, E, A, D, H, color ); // n( 0,-1, 0);    // Neg Y = EADH
    addQuad( p, A, B, C, D, color ); // n( 0, 0, -1);   // Neg Z = ABCD
    addQuad( p, D, C, G, H, color ); // n( 1, 0, 0);    // Pos X = DCGH
    //addQuad( p, B, F, G, C, color ); // n( 0, 1, 0);    // Pos Y = BFGC
    addQuad( p, H, G, F, E, color ); // n( 0, 0, 1);    // Pos Z = HGFE
}


#endif // DE_ALPHASONIC_AUTO_MESH_BUFFER_HPP
