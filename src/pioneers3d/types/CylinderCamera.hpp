#ifndef PIONEERS3D_TYPES_CYLINDERCAMERA_HPP
#define PIONEERS3D_TYPES_CYLINDERCAMERA_HPP

#include <pioneers3d/types/Common.hpp>

namespace pioneers3d {

   class Game_t;

//    bool Game_isCameraInput( Game_t * game );
//    void Game_toggleCameraInput( Game_t * game );
    void Game_setCameraInput( Game_t * game, bool enable );
//    void Game_resetCamera( Game_t * game );
//    void Game_setCameraTopView( Game_t * game );
//    void Game_moveCameraLeft( Game_t * game );
//    void Game_moveCameraRight( Game_t * game );
//    void Game_moveCameraUp( Game_t * game );
//    void Game_moveCameraDown( Game_t * game );
//    void Game_moveCameraForward( Game_t * game );
//    void Game_moveCameraBack( Game_t * game );

   glm::vec3 Camera_getPosition( irr::scene::ICameraSceneNode* camera );
   void Camera_setPosition( irr::scene::ICameraSceneNode* camera, glm::vec3 );

   glm::vec3 Camera_getLookAt( irr::scene::ICameraSceneNode* camera );
   void Camera_setLookAt( irr::scene::ICameraSceneNode* camera, glm::vec3 );

   irr::scene::ICameraSceneNode* Game_getCamera( Game_t * game );
   void Camera_moveToDefault( Game_t * game );
   void Camera_moveToTop( Game_t * game );
   void Camera_moveToBottom( Game_t * game );
   void Camera_moveToFront( Game_t * game );
   void Camera_moveToBack( Game_t * game );
   void Camera_moveToLeft( Game_t * game );
   void Camera_moveToRight( Game_t * game );


class CylinderCamera
{
    glm::vec3 Eye;
    float32_t Radius;
    float32_t Height;
    float32_t Angle; // y - angle, 0 degrees == -z = south, rotating clockwise (cw), 90 = west, 180 = north, 270 = east, 360 = south again

    glm::vec3 Pos; // what we calculate from Center, Radius, Height and Angle

    irr::scene::ICameraSceneNode* Camera;
public:
    CylinderCamera( irr::scene::ISceneManager* smgr, irr::scene::ISceneNode* parent, int id = -1 )
        : Eye(0,0,0), Radius( 300.0f ), Height( 300.0f ), Angle( 0.0f ), Pos(0,-300,-300), Camera(nullptr)
    {
        Camera = smgr->addCameraSceneNode( parent,
                irr::core::vector3df( Pos.x, Pos.y, Pos.z ),
                irr::core::vector3df( Eye.x, Eye.y, Eye.z ), id, true );

        Camera->setNearValue( .1f );
        Camera->setFarValue( 10000.0f );

        updatePosition();
    }
    ~CylinderCamera() {}

    void updatePosition()
    {
        float32_t w = Angle * irr::core::DEGTORAD;
        Pos = Eye + glm::vec3( Radius * sinf( w ), Height, - Radius * cosf( w ) );
        if ( Camera )
        {
            Camera->setPosition( irr::core::vector3df( Pos.x, Pos.y, Pos.z ) );
            Camera->setTarget( irr::core::vector3df( Eye.x, Eye.y, Eye.z ) );
        }
    }

    void updateFromPosition( glm::vec3 pos )
    {
        // too complicated for now
    }

    void setPosition( glm::vec3 pos )
    {
        updateFromPosition( pos );
    }

    void setRadius( float32_t r )
    {
        Radius = r;
        if ( Radius <= 1.0f ) Radius = 1.0f;
        if ( Radius >= 10000.0f ) Radius = 10000.0f;
    }

    void setHeight( float32_t h )
    {
        Height = h;
    }

    void setAngleY( float32_t angleYinDegrees )
    {
        Angle = angleYinDegrees;
        while ( Angle < 0.0f ) Angle += 360.0f;
        while ( Angle >= 360.0f ) Angle -= 360.0f;
    }

    void moveForward( float32_t speed )
    {
        setRadius( Radius - speed );
        updatePosition();
    }

    void moveBackward( float32_t speed )
    {
        setRadius( Radius + speed );
        updatePosition();
    }

    void moveUp( float32_t speed )
    {
        setHeight( Height + speed );
        updatePosition();
    }

    void moveDown( float32_t speed )
    {
        setHeight( Height - speed );
        updatePosition();
    }

    void rotateLeft( float32_t speed )
    {
        setAngleY( Angle - speed );
        updatePosition();
    }

    void rotateRight( float32_t speed )
    {
        setAngleY( Angle + speed );
        updatePosition();
    }

    bool OnEvent( irr::SEvent const & event )
    {
//        if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
//        {
//            irr::SEvent::SMouseInput const & mouse = event.MouseInput;

//            if (mouse.Wheel < 0.0f)
//            {
//                moveForward( 10.0f );
//                return true;
//            }
//            else if (mouse.Wheel > 0.0f)
//            {
//                moveBackward( 10.0f );
//                return true;
//            }
//        }
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        {
            const irr::SEvent::SKeyInput& key = event.KeyInput;

#ifdef USE_IRRLICHT
            if (key.Key == irr::KEY_KEY_W || key.Key == irr::KEY_UP)
#else
            if (key.Key == irr::IRR_KEY_W || key.Key == irr::IRR_KEY_UP)
#endif
            {
                moveForward( 3.5f );
                return true;
            }
#ifdef USE_IRRLICHT
            if (key.Key == irr::KEY_KEY_S || key.Key == irr::KEY_DOWN)
#else
            if (key.Key == irr::IRR_KEY_S || key.Key == irr::IRR_KEY_DOWN)
#endif
            {
                moveBackward( 3.5f );
                return true;
            }
#ifdef USE_IRRLICHT
            if (key.Key == irr::KEY_KEY_A || key.Key == irr::KEY_LEFT)
#else
            if (key.Key == irr::IRR_KEY_A || key.Key == irr::IRR_KEY_LEFT)
#endif
            {
                rotateLeft( 3.5f );
                return true;
            }
#ifdef USE_IRRLICHT
            if (key.Key == irr::KEY_KEY_D || key.Key == irr::KEY_RIGHT)
#else
            if (key.Key == irr::IRR_KEY_D || key.Key == irr::IRR_KEY_RIGHT)
#endif
            {
                rotateRight( 3.5f );
                return true;
            }
#ifdef USE_IRRLICHT
            if (key.Key == irr::KEY_KEY_Q || key.Key == irr::KEY_MINUS)
#else
            if (key.Key == irr::IRR_KEY_Q || key.Key == irr::IRR_KEY_MINUS)
#endif
            {
                moveDown( 3.5f );
                return true;
            }
#ifdef USE_IRRLICHT
            if (key.Key == irr::KEY_KEY_E || key.Key == irr::KEY_PLUS)
#else
            if (key.Key == irr::IRR_KEY_E || key.Key == irr::IRR_KEY_PLUS)
#endif
            {
                moveUp( 3.5f );
                return true;
            }
        }
        return false;
    }

};
//void dbSetCameraAspect( Game_t * game, int32_t width, int32_t height ) {}
//void dbSetCameraAspect( Game_t * game, float32_t aspect ) {}




} // end namespace pioneers3d

#endif // PIONEERS3D_TYPES_CAMERA_HPP
