#ifndef GAME_CAMERA_HPP
#define GAME_CAMERA_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

bool Game_isCameraInput( Game_t * game );
void Game_toggleCameraInput( Game_t * game );
void Game_setCameraInput( Game_t * game, bool enable );

} // end namespace pioneers3d

#endif // GAME_CAMERA_HPP
