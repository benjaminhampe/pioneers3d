#ifndef PIONEERS3D_STANDARD_GAME_HPP
#define PIONEERS3D_STANDARD_GAME_HPP

#include <pioneers3d/types/Game.hpp>

namespace pioneers3d {

void Game_destroy( Game_t* game );
void Game_clear( Game_t* game );
void Game_createStandard( Game_t* game, int argc, char** argv );
void Game_start( Game_t * game );
int  Game_exec( Game_t * game );
void Game_load( std::string const & fileName );
void Game_save( std::string const & fileName );

class EventReceiver : public irrExt::BaseEventReceiver
{
public:
    explicit EventReceiver( Game_t* game = nullptr );
    virtual ~EventReceiver();
    virtual bool OnEvent( irr::SEvent const & event ) override;
public:
    Game_t* m_Game = nullptr;
};

} // end namespace pioneers3d

#endif // PIONEERS3D_STANDARD_GAME_HPP
