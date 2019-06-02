#include <pioneers3d/types/CylinderCamera.hpp>
#include <pioneers3d/types/Game.hpp>

namespace pioneers3d {

void
Game_setCameraInput( Game_t * game, bool enable )
{
    irr::scene::ICameraSceneNode* camera = game->Device->getSceneManager()->getActiveCamera();
    if ( camera )
    {
        camera->setInputReceiverEnabled( enable );
    }
}

#if 0
void Game_resetCamera( Game_t * game )
{

}

void Game_setCameraTopView( Game_t * game )
{

}

void Game_moveCameraLeft( Game_t * game )
{

}

void Game_moveCameraRight( Game_t * game )
{

}

void Game_moveCameraUp( Game_t * game )
{

}

void Game_moveCameraDown( Game_t * game )
{

}

void Game_moveCameraForward( Game_t * game )
{

}

void Game_moveCameraBack( Game_t * game )
{

}

bool
Game_isCameraInput( Game_t * game )
{
    irr::IrrlichtDevice* device = game->Device;
    irr::scene::ICameraSceneNode* camera = device->getSceneManager()->getActiveCamera();
    if ( camera )
    {
        return camera->isInputReceiverEnabled();
    }
    else
    {
        return false;
    }
}

void
Game_toggleCameraInput( Game_t * game )
{
    irr::IrrlichtDevice* device = game->Device;
    irr::scene::ICameraSceneNode* camera = device->getSceneManager()->getActiveCamera();
    if ( camera )
    {
        camera->setInputReceiverEnabled( !camera->isInputReceiverEnabled() );
    }
}



#endif

} // end namespace pioneers3d
