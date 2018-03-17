#ifndef PIONEERS3DAPPLICATION_HPP
#define PIONEERS3DAPPLICATION_HPP

#include <pioneers3d/common/Utils.hpp>
#include <pioneers3d/scene/Camera.hpp>

namespace pioneers3d {

class Pioneers3DApplication : public irr::IEventReceiver
{
public:
    Pioneers3DApplication();

    virtual ~Pioneers3DApplication();

    bool
    run();

    bool
    OnEvent( irr::SEvent const & event ) override;

private:
    irr::IrrlichtDevice* m_Device = nullptr;

    irr::SIrrlichtCreationParameters m_DeviceConfig;

    irr::video::SColor m_ClearColor;

    //Camera m_Camera;
};

} // namespace pioneers3d

#endif // PIONEERS3DAPPLICATION_HPP
