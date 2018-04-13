#ifndef PIONEERS3D_BASE_EVENT_RECEIVER_HPP
#define PIONEERS3D_BASE_EVENT_RECEIVER_HPP

#include <pioneers3d/Types.hpp>
#include <pioneers3d/Game_Camera.hpp>

namespace pioneers3d {

class EventReceiver : public BaseEventReceiver
{
public:
    explicit EventReceiver( Game_t* game = nullptr );
    virtual ~EventReceiver();

    bool OnEvent( irr::SEvent const & event ) override;

public:
    Game_t* m_Game = nullptr;

    CylinderCamera m_Camera;
};


} // end namespace pioneers3d

#endif // PIONEERS3D_COMMON_BOARD_DATA_HPP
