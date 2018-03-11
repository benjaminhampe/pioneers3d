#include "Pioneers3DApplication.hpp"

#include <assert.h>

namespace pioneers3d {

Pioneers3DApplication::Pioneers3DApplication()
    : m_Device( nullptr )
{
    m_Device = irr::createDevice( irr::video::EDT_OPENGL, irr::core::dimension2du(800,600), 32, false, true, false, nullptr );

    assert( m_Device );

    irr::scene::ISceneManager* smgr = m_Device->getSceneManager();

    irr::scene::ISceneNode* rootNode = smgr->getRootSceneNode();

    createCameraSceneNodeFPS( smgr, rootNode );

    m_Device->setEventReceiver( this );
}

Pioneers3DApplication::~Pioneers3DApplication()
{
    if ( m_Device )
    {
        m_Device->closeDevice();
        m_Device->drop();
    }
}

bool
Pioneers3DApplication::run()
{
    if (m_Device && m_Device->run())
    {
        irr::video::IVideoDriver* driver = m_Device->getVideoDriver();
        if (driver)
        {
            driver->beginScene( true, true, irr::video::SColor(255,255,235,215) );

            irr::scene::ISceneManager* smgr = m_Device->getSceneManager();
            if ( smgr )
            {
                smgr->drawAll();
            }

            driver->endScene();
        }

//        irr::core::stringw s = L"FPS(";
//        s += m_VideoDriver->getFPS();
//        s += L")";
//        m_Device->setWindowCaption( s.c_str() );

        return true;
    }
    else
    {
        return false;
    }
}

bool
Pioneers3DApplication::OnEvent( const irr::SEvent& event )
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        const irr::SEvent::SKeyInput& key = event.KeyInput;

        if (key.Key == irr::KEY_ESCAPE)
        {
            if ( m_Device )
            {
                m_Device->closeDevice();
                m_Device = nullptr;
            }
            return true;
        }
    }
    return false;
}

} // namespace pioneers3d
