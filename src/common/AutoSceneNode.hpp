#ifndef DE_ALPHASONIC_AUTO_SCENE_NODE_HPP
#define DE_ALPHASONIC_AUTO_SCENE_NODE_HPP

#include <common/AutoMeshBuffer.hpp>

class AutoSceneNode : public irr::scene::ISceneNode
{
public:
    AutoSceneNode( irr::scene::ISceneManager* smgr, irr::scene::ISceneNode* parent, int id = -1 );

    virtual ~AutoSceneNode();

    void OnRegisterSceneNode() override;

    void render() override;

    irr::u32 getMaterialCount() const override;

    irr::video::SMaterial& getMaterial( irr::u32 i ) override;

    irr::core::aabbox3d<irr::f32> const & getBoundingBox() const override;

    void clear();

    void addMeshBuffer( AutoMeshBuffer * mb, bool dropAfterAdd = false );

//    void addMeshBuffer(
//            irr::scene::SMeshBuffer && mb,
//            irr::scene::E_PRIMITIVE_TYPE primType = irr::scene::EPT_TRIANGLES,
//            irr::video::E_VERTEX_TYPE vertexType = irr::video::EVT_STANDARD,
//            irr::video::E_INDEX_TYPE indexType = irr::video::EIT_16BIT );

    irr::u32 getMeshBufferCount() const;

    AutoMeshBuffer* getAutoMeshBuffer( irr::u32 i );

    irr::scene::SMeshBuffer* getMeshBuffer( irr::u32 i );

    void setPosition( glm::vec3 const & pos )
    {
        irr::scene::ISceneNode::setPosition( irr::core::vector3df( pos.x, pos.y, pos.z ) );
    }
protected:
    irr::core::aabbox3d<irr::f32> m_BoundingBox;
    std::vector< AutoMeshBuffer* > m_MeshBuffer;
};

#endif // DE_ALPHASONIC_AUTO_RENDER_SCENE_NODE_HPP
