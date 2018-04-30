#ifndef PIONEERS3D_GAME_HPP
#define PIONEERS3D_GAME_HPP

#include <pioneers3d/Types.hpp>
#include <pioneers3d/Game_Camera.hpp>

namespace pioneers3d {

void        Game_destroy( Game_t* game );
void        Game_clear( Game_t* game );
void        Game_createStandard( Game_t* game );
void        Game_start( Game_t * game );
int         Game_exec( Game_t * game );
void        Game_load( std::string const & fileName );
void        Game_save( std::string const & fileName );

std::string Game_toXML( Game_t* game );

class EventReceiver : public BaseEventReceiver
{
public:
    explicit EventReceiver( Game_t* game = nullptr );
    virtual ~EventReceiver();
    virtual bool OnEvent( irr::SEvent const & event ) override;
public:
    Game_t* m_Game = nullptr;
    CylinderCamera m_Camera;
};

} // end namespace pioneers3d

#endif // PIONEERS3D_GAME_HPP
