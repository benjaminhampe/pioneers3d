#ifndef BASEEVENTRECEIVER_HPP
#define BASEEVENTRECEIVER_HPP

#include <common/Types.hpp>

namespace pioneers3d {

class BaseEventReceiver : public irr::IEventReceiver
{
public:
    explicit BaseEventReceiver( irr::IrrlichtDevice* device = nullptr );
    virtual ~BaseEventReceiver();

    bool OnEvent( const irr::SEvent& event ) override;
    void OnResize( irr::core::dimension2du const & winSize );
    void setDevice( irr::IrrlichtDevice* device );

public:
    irr::IrrlichtDevice* m_Device = nullptr;
    irr::core::dimension2du m_WindowSize;
};


} // end namespace pioneers3d

#endif // BASEEVENTRECEIVER_HPP
