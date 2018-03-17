#ifndef PIONEERS3D_SCENE_BOARDSCENENODE_HPP
#define PIONEERS3D_SCENE_BOARDSCENENODE_HPP

#include <pioneers3d/data/BoardData.hpp>
#include <pioneers3d/scene/createHexagonMeshBufferXZ.hpp>
#include <irrlicht.h>
#include <assert.h>

namespace pioneers3d {

// ============================================================================
class BoardSceneNode : public irr::scene::ISceneNode
// ============================================================================
{
public:
    BoardSceneNode( irr::scene::ISceneManager* smgr, irr::scene::ISceneNode* parent, int id = -1 );

    virtual ~BoardSceneNode();

    void render() override
    {
        if ( !m_Mesh ) return;

        irr::video::IVideoDriver* driver = SceneManager->getVideoDriver();

        for ( irr::u32 i = 0; i < m_Mesh->getMeshBufferCount(); ++i )
        {
            irr::scene::IMeshBuffer* b = m_Mesh->getMeshBuffer( i );

            assert( b );

            driver->drawVertexPrimitiveList(
                        b->getVertices(),
                        b->getVertexCount(),
                        b->getIndices(),
                        b->getIndexCount() / 3,
                        irr::video::EVT_STANDARD,
                        irr::scene::EPT_TRIANGLES,
                        irr::video::EIT_16BIT );
        }
    }

    irr::u32 getMaterialCount() const override
    {
        return m_Mesh->getMeshBufferCount();
    }

    irr::video::SMaterial& getMaterial(irr::u32 num) override
    {
        return m_Mesh->getMeshBuffer(num)->getMaterial();
    }

    irr::core::aabbox3d<irr::f32> const & getBoundingBox() const override
    {
        return m_Mesh->getBoundingBox();
    }

protected:
    irr::video::ITexture*
    getTileTexture( TileType::ETileType const & tileType )
    {
        return nullptr;
    }


    irr::scene::SMeshBuffer*
    createTileMeshBuffer( TileType::ETileType const & tileType, int i, int j )
    {
        float const x = (0.50f * m_TileSizeX) * ( std::abs(j) % 2 ) + m_TileSizeX * i;
        float const y = 0.0f; // m_TileSizeY * sqrtf( (float)( i*i + j*j ) );
        float const z = (0.75f * m_TileSizeZ) * j;

        irr::scene::SMeshBuffer * meshBuffer = createHexagonMeshBufferXZ( m_TileSizeX, m_TileSizeZ, x, y, z );

        meshBuffer->Material.setTexture( 0, getTileTexture( tileType ) );

        return meshBuffer;
    }


//    /// INTERFACE: IMeshSceneNode
//    virtual void setMesh( irr::scene::IMesh* mesh ) { _mesh = (irr::scene::SMesh*)mesh; }
//    virtual irr::scene::IMesh* getMesh() { return _mesh; }
//    virtual irr::scene::IShadowVolumeSceneNode* addShadowVolumeSceneNode( const irr::scene::IMesh* shadowMesh=0, irr::s32 id=-1, bool zfailmethod=true, irr::f32 infinity=1000.0f) { return nullptr; }
//    virtual void setReadOnlyMaterials( bool readonly ) {}
//    virtual bool isReadOnlyMaterials() const { return false; }

protected:
    irr::scene::SMesh * m_Mesh = nullptr;

    BoardData * m_Data = nullptr;

    float m_TileSizeX = 10.0f;
    float m_TileSizeY = 4.0f;
    float m_TileSizeZ = 10.0f;
    TileType::ETileType m_DefaultTileType = TileType::WASSER;

    //getTexture("wasser.png")

};

} // end namespace pioneers3d

#endif // PIONEERS3D_SCENE_BOARDSCENENODE_HPP
