#ifndef PIONEERS3D_TYPES_OBJECTMANAGER_HPP
#define PIONEERS3D_TYPES_OBJECTMANAGER_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

// ---------------------------------------------------------------------------------------
struct Raueber_t
{
    glm::ivec2 					BoardIndex;
    glm::vec3                   Pos;
    irr::scene::ISceneNode*     Node = nullptr;
    //~Raueber_t() { if (Node) Node->drop(); }
};

void Game_createRaeuber( Game_t* game );

/*
AutoSceneNode* createSettlement( Game_t* game )
{
    irr::scene::ISceneManager* smgr = game->Device->getSceneManager();
    AutoSceneNode* node = new AutoSceneNode( smgr, smgr->getRootSceneNode(), -1 );
    node->add( createRotatedBox( glm::vec3( 0,4,0 ), glm::vec3(10,8,10), glm::vec3(0,0,0), Player_getColor( game ) ), true );
    node->add( createRotatedBox( glm::vec3( 0,9,0 ), glm::vec3(8,2,8), glm::vec3(0,0,0), Player_getColor( game ) ), true );
    return node;
}


/// @brief Create a box with one repeating texture over all 6 planes
AutoMeshBuffer* createRoad( glm::vec3 const & pos, glm::vec3 const & size, glm::vec3 const & rot, uint32_t color );
AutoMeshBuffer* createHouse( glm::vec3 const & pos, glm::vec3 const & size, glm::vec3 const & rot, uint32_t color );

void Game_createRoad( Game_t* game, glm::vec3 const & pos, glm::vec3 const & size, glm::vec3 const & rot, uint32_t color );
void Game_createHouse( Game_t* game, glm::vec3 const & pos, glm::vec3 const & size, glm::vec3 const & rot, uint32_t color );
void Game_createCity( Game_t* game );
*/

} // end namespace pioneers3d

#endif // PIONEERS3D_TYPES_OBJECTMANAGER_HPP
