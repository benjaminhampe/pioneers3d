#ifndef DE_ALPHASONIC_AUTO_SCENE_NODE_HPP
#define DE_ALPHASONIC_AUTO_SCENE_NODE_HPP

#include <common/AutoMeshBuffer.hpp>

class AutoSceneNode : public irr::scene::ISceneNode
{
public:
    AutoSceneNode( irr::scene::ISceneManager* smgr, irr::scene::ISceneNode* parent, int id = -1 )
        : irr::scene::ISceneNode( parent, smgr, id )
    {
        std::cout << __FUNCTION__ << "()" << std::endl;
        //setAutomaticCulling( irr::scene::EAC_OFF );
    }

    virtual ~AutoSceneNode()
    {
        std::cout << "~" << __FUNCTION__ << "()" << std::endl;

        clear();
    }

    void clear()
    {
        for ( uint32_t i = 0; i < getMeshBufferCount(); ++i )
        {
            AutoMeshBuffer* p = m_MeshBuffer[ i ];
            if ( p )
            {
                p->drop();
            }
        }

        m_MeshBuffer.clear();
    }

    void addMeshBuffer( AutoMeshBuffer * mb )
    {
        m_MeshBuffer.emplace_back( mb );
    }

    void addMeshBuffer(
            irr::scene::SMeshBuffer && mb,
            irr::scene::E_PRIMITIVE_TYPE primType = irr::scene::EPT_TRIANGLES,
            irr::video::E_VERTEX_TYPE vertexType = irr::video::EVT_STANDARD,
            irr::video::E_INDEX_TYPE indexType = irr::video::EIT_16BIT )
    {
        m_MeshBuffer.emplace_back( new AutoMeshBuffer( std::move( mb ), primType, vertexType, indexType ) );
    }

    irr::u32
    getMeshBufferCount() const
    {
        return static_cast< irr::u32 >( m_MeshBuffer.size() );
    }

    AutoMeshBuffer*
    getAutoMeshBuffer( irr::u32 i )
    {
        assert( getMeshBufferCount() > i );
        return m_MeshBuffer[ i ];
    }

    irr::scene::SMeshBuffer*
    getMeshBuffer( irr::u32 i )
    {
        assert( getMeshBufferCount() > i );
        assert( m_MeshBuffer[ i ] );
        return &(m_MeshBuffer[ i ]->MeshBuffer);
    }

    irr::u32
    getMaterialCount() const override
    {
        return static_cast< irr::u32 >( m_MeshBuffer.size() );
    }

    irr::video::SMaterial&
    getMaterial( irr::u32 i ) override
    {
        assert( getMaterialCount() > i );
        assert( m_MeshBuffer[ i ] );
        return m_MeshBuffer[ i ]->MeshBuffer.Material;
    }

    irr::core::aabbox3d<irr::f32> const &
    getBoundingBox() const override
    {
        return m_BoundingBox;
    }

    void
    render() override
    {
        irr::video::IVideoDriver* driver = SceneManager->getVideoDriver();

        assert( driver );

        for ( size_t i = 0; i < m_MeshBuffer.size(); ++i )
        {
            AutoMeshBuffer* p = m_MeshBuffer[ i ];
            if ( p )
            {
                p->render( driver );
            }
        }
    }

protected:
    irr::core::aabbox3d<irr::f32> m_BoundingBox;
    std::vector< AutoMeshBuffer* > m_MeshBuffer;
};

#endif // DE_ALPHASONIC_AUTO_RENDER_SCENE_NODE_HPP
