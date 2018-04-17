#ifndef GAME_CHAT_HPP
#define GAME_CHAT_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

void Chat_create( Game_t * game );
void Chat_destroy( Game_t * game );
void Chat_clear( Game_t * game );
void Chat_draw( Game_t * game, int32_t x, int32_t y );
void Chat_addMessage( Game_t * game, uint32_t color, std::string txt );
void Chat_addItem( Game_t * game, int32_t pl, std::string name, uint32_t color, std::string txt );

std::string Chat_toString( Game_t * game );

} // end namespace pioneers3d


#endif // GAME_CHAT_HPP
