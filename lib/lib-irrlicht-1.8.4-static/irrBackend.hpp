#ifndef IRRLICHBACKEND_HPP
#define IRRLICHBACKEND_HPP

#include <irrlicht.h>
#include <stdint.h>
#include <sstream>
#include <glm/glm.hpp>

#include <iostream>

typedef float float32_t;
typedef double float64_t;

//std::string toString( irr::core::dimension2du const & u );
std::string toString( irr::core::vector2df const & v );
std::string toString( irr::core::vector3df const & v );
std::string toString( irr::video::SColor const & color );
std::string toString( irr::video::S3DVertex const & v );
std::string toString( glm::ivec2 const & v );
std::string toString( glm::ivec3 const & v );
std::string toString( glm::vec2 const & v );
std::string toString( glm::vec3 const & v );

template <class T>
std::string
toString( irr::core::dimension2d<T> const & u )
{
    std::stringstream s;
    s << u.Width << "," << u.Height;
    return s.str();
}

bool equals( glm::vec2 a, glm::vec2 b, float32_t eps = 0.0001f );
bool equals( glm::vec3 a, glm::vec3 b, float32_t eps = 0.0001f );

glm::ivec3 getDesktopSize();

float32_t convertToNormalized( int16_t value );

inline irr::core::recti
mkRect( int32_t x, int32_t y, uint32_t w, uint32_t h )
{
    return irr::core::recti( irr::core::position2di( x, y ), irr::core::dimension2du( w, h ) );
}

class irrBackend
{
public:
    irrBackend();

    static void
    closeDevice( irr::IrrlichtDevice* & device )
    {
        if (device)
        {
            device->closeDevice();
            device->drop();
            device = nullptr;
        }
    }

    static irr::IrrlichtDevice*
    createNullDevice()
    {
        irr::IrrlichtDevice * device = irr::createDevice( irr::video::EDT_NULL );
        return device;
    }

    static irr::video::IImage*
    createImage( irr::video::IVideoDriver* driver, int32_t w, int32_t h, irr::video::SColor color = irr::video::SColor(255,0,200,0) )
    {
        irr::video::IImage* img = driver->createImage( irr::video::ECF_A8R8G8B8, irr::core::dimension2du(w,h) );
        img->fill( color );
        return img;
    }

    static irr::video::IImage*
    loadImage( irr::video::IVideoDriver* driver, std::string fileName )
    {
        irr::video::IImage* img = driver->createImageFromFile( fileName.c_str() );
        return img;
    }

    static bool
    saveImage( irr::video::IVideoDriver* driver, irr::video::IImage * img, std::string fileName )
    {
        return driver->writeImageToFile( img, fileName.c_str(), 0 );
    }

    static irr::IrrlichtDevice*
    createOpenGLDevice( int32_t w, int32_t h, bool fullscreen = false )
    {
        irr::SIrrlichtCreationParameters params;
        params.WindowSize = irr::core::dimension2du(
            static_cast< int32_t >( w ),
            static_cast< int32_t >( h ) );
        params.Bits = 32;
        params.AntiAlias = irr::video::EAAM_QUALITY;
        params.Doublebuffer = true;
        params.Vsync = false;
        params.DriverType = irr::video::EDT_OPENGL;
        params.HighPrecisionFPU = true;
        params.Fullscreen = fullscreen;
        params.Stencilbuffer = true;
        params.ZBufferBits = 24;
        irr::IrrlichtDevice* device = irr::createDeviceEx( params );
        if (!device)
        {
            std::cout << "ERROR: Cannot create device\n";
        }
        return device;
    }

    static void
    runDevice( irr::IrrlichtDevice * device )
    {
        if ( !device )
        {
            return;
        }

        irr::video::IVideoDriver* driver = device->getVideoDriver();
        irr::video::SColor clearColor( 255, 200, 200, 220 );
        irr::scene::ISceneManager* smgr = device->getSceneManager();
        irr::scene::ISceneNode* root = smgr->getRootSceneNode();
        irr::scene::IMesh* mesh = smgr->getGeometryCreator()->createSphereMesh( 50.f, 33, 33 );
        irr::scene::IMeshSceneNode* sphere = smgr->addMeshSceneNode( mesh, root, -1 );
        mesh->drop();
        sphere->setMaterialFlag( irr::video::EMF_LIGHTING, false );
        sphere->setMaterialFlag( irr::video::EMF_WIREFRAME, true );

        irr::scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS( root, 100.0f, 0.5f, -1 );
        camera->setPosition( irr::core::vector3df( 0,0,-1000) );
        camera->setTarget( irr::core::vector3df(0,0,0) );
        camera->setNearValue( 1.0f );
        camera->setFarValue( 10000.0f );

        while (device->run())
        {
//            if (device->isWindowActive())
//            {
                driver->beginScene( true, true, clearColor );
                smgr->drawAll();
                driver->endScene();
//            }
//            else
//            {
//                device->yield();
//            }
        }
    }

    static irr::scene::IMeshSceneNode *
    createEarthSceneNode( irr::IrrlichtDevice* device )
    {
        irr::video::IVideoDriver* driver = device->getVideoDriver();
        irr::scene::ISceneManager* smgr = device->getSceneManager();
        irr::scene::ISceneNode* root = smgr->getRootSceneNode();
        irr::scene::IMesh* sphere = smgr->getGeometryCreator()->createSphereMesh( 50.f, 33, 33 );
        irr::scene::IMeshSceneNode* node = smgr->addMeshSceneNode( sphere, root, -1 );
        sphere->drop();
        node->setMaterialFlag( irr::video::EMF_FOG_ENABLE, false );
        node->setMaterialFlag( irr::video::EMF_NORMALIZE_NORMALS, true );
        node->setMaterialFlag( irr::video::EMF_LIGHTING, false );
        //node->setMaterialFlag( irr::video::EMF_WIREFRAME, true );
        irr::video::ITexture * dayTex = driver->getTexture( "../../media/earth_day_8k.jpg" );
        node->setMaterialTexture( 0, dayTex );
        return node;
    }
};

#endif // IRRLICHBACKEND_HPP
