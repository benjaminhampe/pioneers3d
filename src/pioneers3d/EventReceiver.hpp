#ifndef PIONEERS3D_BASE_EVENT_RECEIVER_HPP
#define PIONEERS3D_BASE_EVENT_RECEIVER_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

class BaseEventReceiver : public irr::IEventReceiver
{
public:
    explicit BaseEventReceiver( irr::IrrlichtDevice* device = nullptr )
        : m_Device( device )
    {
        std::cout << __FUNCTION__ << "("<< (void*)m_Device << ")\n";

        assert( m_Device );

        m_Device->setEventReceiver( this );
    }
    virtual ~BaseEventReceiver()
    {
        std::cout << __FUNCTION__ << "()\n";
    }

    bool
    OnEvent( const irr::SEvent& event ) override
    {
        if ( event.EventType == irr::EET_KEY_INPUT_EVENT )
        {
            irr::SEvent::SKeyInput const & keyEvent = event.KeyInput;

            if ( keyEvent.Key == irr::KEY_ESCAPE )
            {
                if ( m_Device )
                {
                    m_Device->closeDevice();
                }
                return true;
            }

            if ( keyEvent.Key == irr::KEY_SPACE && keyEvent.PressedDown == false )
            {
                if ( m_Device )
                {
                    irr::scene::ICameraSceneNode* camera = m_Device->getSceneManager()->getActiveCamera();
                    if ( camera )
                    {
                        camera->setInputReceiverEnabled( !camera->isInputReceiverEnabled() );
                    }
                }
                return true;
            }
        }

        return false;
    }

    void
    OnResize( irr::core::dimension2du const & winSize )
    {
        if ( m_Device )
        {
            m_Device->getVideoDriver()->OnResize( winSize );
        }
    }

    void setDevice( irr::IrrlichtDevice* device )
    {
        if ( device == nullptr )
        {
            m_Device = device;
        }


    }
public:
    irr::IrrlichtDevice* m_Device = nullptr;

    irr::core::dimension2du m_WindowSize;
};


} // end namespace pioneers3d

#endif // PIONEERS3D_COMMON_BOARD_DATA_HPP
