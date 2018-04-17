#include "Game_Camera.hpp"

//#include <pioneers3d/Game_UI.hpp>
//#include <pioneers3d/Game_EventReceiver.hpp>

namespace pioneers3d {

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

void
Game_setCameraInput( Game_t * game, bool enable )
{
    irr::scene::ICameraSceneNode* camera = game->Device->getSceneManager()->getActiveCamera();
    if ( camera )
    {
        camera->setInputReceiverEnabled( enable );
    }
}


} // end namespace pioneers3d
