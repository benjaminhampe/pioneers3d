#include "TileSceneNode.hpp"

namespace pioneers3d {

TileSceneNode::TileSceneNode( irr::scene::ISceneManager* smgr, irr::scene::ISceneNode* parent, int id )
    : irr::scene::ISceneNode( parent, smgr, id )
{
    std::cout << __FUNCTION__ << "()" << std::endl;
}

TileSceneNode::~TileSceneNode()
{
    std::cout << "~" << __FUNCTION__ << "()" << std::endl;
}

} // end namespace pioneers3d
