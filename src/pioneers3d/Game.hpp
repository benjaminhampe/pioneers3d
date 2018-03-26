#ifndef PIONEERS3D_GAME_DATA_HPP
#define PIONEERS3D_GAME_DATA_HPP

#include <pioneers3d/getTileTexture.hpp>
#include <pioneers3d/Board.hpp>
#include <pioneers3d/Player.hpp>

namespace pioneers3d {

class Game_t : public irr::IEventReceiver
{
public:
    std::string             BasePath;

    irr::IrrlichtDevice*    Device;
    irr::video::SColor      ClearColor;

    /// Textures
    std::vector< irr::video::ITexture* > Textures;

    /// Game
    eGameType 				Type;
    eGameState 				State;
    /// Board
    Board_t                 Board;
    /// Player
    std::vector< Player_t > Players;
    uint32_t 				CurrentPlayer;

public:
    Game_t( irr::IrrlichtDevice* device );
    virtual ~Game_t();

    bool
    OnEvent( const irr::SEvent& event ) override;

    void
    create( eGameType gameType = eGameType::STANDARD );

    /// Start main loop:
    int
    exec();

    std::string
    toXML() const;

    void
    load( std::string const & fileName );

    void
    save( std::string const & fileName );

    irr::IrrlichtDevice* getDevice() { assert( Device ); return Device; }
	
    void
    setBaseDir( std::string const & basePath )
    {
        BasePath = basePath;

        // replaceChar( BasePath, '\\', '/' );

        auto endsWidth = [] ( std::string const & txt, char endChar ) -> bool
        {
            if ( txt.empty() )
            {
                return false;
            }

            if ( txt.at( txt.size()-1 ) == endChar )
            {
                return true;
            }

            return false;
        };

        if ( !endsWidth( BasePath, '/' ) )
        {
            BasePath += '/';
        }

        std::cout << __FUNCTION__ << " :: basePath(" << basePath << ") -> BasePath(" << BasePath << ")\n";
    }
};

} // end namespace pioneers3d

#endif // PIONEERS3D_COMMON_BOARD_DATA_HPP
