#include "AutoSceneNode.hpp"

// #define ENABLE_AUTOSCENENODE_DEBUG_LOGGING

#ifdef ENABLE_AUTOSCENENODE_DEBUG_LOGGING
    #define AUTOSCENENODE_LOG_SIMPLE { std::cout << __FUNCTION__ << "()\n"; }
#else
    #define AUTOSCENENODE_LOG_SIMPLE
#endif

AutoSceneNode::AutoSceneNode( irr::scene::ISceneManager* smgr, irr::scene::ISceneNode* parent, int id )
    : irr::scene::ISceneNode( parent, smgr, id )
{
    AUTOSCENENODE_LOG_SIMPLE
    //setAutomaticCulling( irr::scene::EAC_OFF );
}

AutoSceneNode::~AutoSceneNode()
{
    AUTOSCENENODE_LOG_SIMPLE
    clear();
}

//! This method is called just before the rendering process of the whole scene.
void
AutoSceneNode::OnRegisterSceneNode()
{
    if (IsVisible)
        SceneManager->registerNodeForRendering(this);

    ISceneNode::OnRegisterSceneNode();
}


void
AutoSceneNode::render()
{
    AUTOSCENENODE_LOG_SIMPLE

    irr::video::IVideoDriver* driver = SceneManager->getVideoDriver();

    assert( driver );

    driver->setTransform( irr::video::ETS_WORLD, getAbsoluteTransformation() );

    for ( size_t i = 0; i < m_MeshBuffer.size(); ++i )
    {
        AutoMeshBuffer* p = m_MeshBuffer[ i ];
        if ( p )
        {
            p->render( driver );
        }
    }

    // irr::scene::ISceneNode::render();
}

void
AutoSceneNode::clear()
{
    AUTOSCENENODE_LOG_SIMPLE
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

void
AutoSceneNode::add( AutoMeshBuffer * mb, bool dropAfterAdd )
{
    AUTOSCENENODE_LOG_SIMPLE

    //AutoMeshBuffer* child = find( mb );

    if ( !mb )
    {
        return;
    }

    mb->grab();

    m_MeshBuffer.emplace_back( mb );

    m_BoundingBox.addInternalBox( mb->MeshBuffer.BoundingBox );

    if ( dropAfterAdd )
    {
        mb->drop(); // remove old owner from ref count
    }
}

//void
//AutoSceneNode::addMeshBuffer(
//        irr::scene::SMeshBuffer && mb,
//        irr::scene::E_PRIMITIVE_TYPE primType,
//        irr::video::E_VERTEX_TYPE vertexType,
//        irr::video::E_INDEX_TYPE indexType )
//{
//    AUTOSCENENODE_LOG_SIMPLE

//    m_MeshBuffer.emplace_back( new AutoMeshBuffer( std::move( mb ), primType, vertexType, indexType ) );
//}

irr::u32
AutoSceneNode::getMeshBufferCount() const
{
    return static_cast< irr::u32 >( m_MeshBuffer.size() );
}

AutoMeshBuffer*
AutoSceneNode::getAutoMeshBuffer( irr::u32 i )
{
    assert( getMeshBufferCount() > i );
    return m_MeshBuffer[ i ];
}

irr::scene::SMeshBuffer*
AutoSceneNode::getMeshBuffer( irr::u32 i )
{
    assert( getMeshBufferCount() > i );
    assert( m_MeshBuffer[ i ] );
    return &(m_MeshBuffer[ i ]->MeshBuffer);
}

irr::u32
AutoSceneNode::getMaterialCount() const
{
    return static_cast< irr::u32 >( m_MeshBuffer.size() );
}

irr::video::SMaterial&
AutoSceneNode::getMaterial( irr::u32 i )
{
    assert( getMaterialCount() > i );
    assert( m_MeshBuffer[ i ] );
    return m_MeshBuffer[ i ]->MeshBuffer.Material;
}

irr::core::aabbox3d<irr::f32> const &
AutoSceneNode::getBoundingBox() const
{
    return m_BoundingBox;
}
