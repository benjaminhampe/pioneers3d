#include <pioneers3d/StandardGame.hpp>

using namespace pioneers3d;

int main( int argc, char** argv )
{
    Game_t game;
    Game_createStandard( &game, argc, argv );
    return Game_exec( &game );
}
