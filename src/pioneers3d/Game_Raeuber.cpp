#include "Game_Raeuber.hpp"

#include <pioneers3d/Game_Logger.hpp>
#include <pioneers3d/Game_Textures.hpp>

namespace pioneers3d {

void Game_createRaeuber( Game_t* game )
{
    if ( !game ) { GAME_LOG_ERROR("Invalid pointer to Game") return; }
    if ( !game->Device ) { GAME_LOG_ERROR("Invalid pointer to IrrlichtDevice") return; }
    irr::scene::ISceneManager * smgr = game->Device->getSceneManager();
    if ( !smgr ) { GAME_LOG_ERROR("Invalid pointer to ISceneManager") return; }
    irr::scene::ISceneNode * root = smgr->getRootSceneNode();
    std::string const fileName = game->MediaDir + "raeuber/raeuber.x";
    irr::scene::IAnimatedMesh* mesh = game->Device->getSceneManager()->getMesh( irr::io::path( fileName.c_str() ) );

    if ( !mesh )
    {
        GAME_LOG_ERROR("Cannot get mesh from file")
        return;
    }

    irr::scene::IAnimatedMeshSceneNode* node = game->Device->getSceneManager()->addAnimatedMeshSceneNode( mesh, root, -1 );
    mesh->drop();

    node->setScale( irr::core::vector3df(0.1f,0.1f,0.1f) );

    for ( uint32_t i = 0; i < node->getMaterialCount(); ++i )
    {
        node->getMaterial( i ).Wireframe = false;
        node->getMaterial( i ).Lighting = false;
        node->getMaterial( i ).FogEnable = false;
        node->getMaterial( i ).NormalizeNormals = true;
        node->getMaterial( i ).setTexture( 0, Game_getTexture( game, eTexture::TEX_ROBBER ) );
    }
    game->Raeuber.Pos = glm::vec3(0,0,0);
    game->Raeuber.Node = node;
}

} // end namespace pioneers3d

