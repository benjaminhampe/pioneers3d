#ifndef PIONEERS3DAPPLICATION_HPP
#define PIONEERS3DAPPLICATION_HPP

#include <irrlicht.h>
#include <pioneers3d/Types.hpp>
#include <pioneers3d/scene/Camera.hpp>

#include <windows.h>
#include <time.h>
#include <sstream>
#include <iostream>
#include <memory>

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

    //Camera m_Camera;

};

} // namespace pioneers3d

#endif // PIONEERS3DAPPLICATION_HPP
