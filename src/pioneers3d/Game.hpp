#ifndef PIONEERS3D_GAME_HPP
#define PIONEERS3D_GAME_HPP

#include <pioneers3d/Types.hpp>
#include <pioneers3d/EventReceiver.hpp>

#include <pioneers3d/gui/UI_Card.hpp>
#include <pioneers3d/gui/UI_HelpWindow.hpp>
namespace pioneers3d {

inline void Textures_print( irr::video::IVideoDriver* driver )
{
    std::cout << "TexCount = " << driver->getTextureCount() << "\n";

    for ( uint32_t i = 0; i < driver->getTextureCount(); ++i )
    {
        irr::video::ITexture* tex = driver->getTextureByIndex( i );
        if ( tex )
        {
            std::cout << "Tex[" << i << "] = " << tex->getName().getPath().c_str() << "\n";
        }
    }
}

std::string
Game_toXML( Game_t* game );

void
Game_clear( Game_t* game );

void
Game_createStandard( Game_t* game );

int
Game_exec( Game_t * game );

void
Game_load( std::string const & fileName );

void
Game_save( std::string const & fileName );

} // end namespace pioneers3d

#endif // PIONEERS3D_GAME_HPP
