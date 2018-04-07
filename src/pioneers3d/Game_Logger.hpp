#ifndef GAME_LOGGER_HPP
#define GAME_LOGGER_HPP

#include <pioneers3d/Types.hpp>

namespace pioneers3d {

class GameLogger
{
    std::string m_LoggerName;

    irr::gui::IGUIListBox* m_LogBox;

    std::vector< irr::gui::IGUIListBox* > m_Listener;

    de::alphasonic::Logger m_Cout;
public:
    static GameLogger & singleton()
    {
        static GameLogger logger( "game.Logger" );
        return logger;
    }

    GameLogger( std::string name )
        : m_LoggerName(name), m_LogBox( nullptr ), m_Cout(name)
    {}

    void setLogBox( irr::gui::IGUIListBox* logbox )
    {
        m_LogBox = logbox;
    }

    void addListener( irr::gui::IGUIListBox* logbox )
    {
        m_Listener.push_back( logbox );
    }

    void error( const char* fn, int line, std::string msgText )
    {
        m_Cout.error() << fn << ":" << line << " :: " << msgText << "\n";

        if ( m_LogBox )
        {
            uint32_t index = m_LogBox->addItem( irr::core::stringw( msgText.c_str() ).c_str(), -1 );
            m_LogBox->setItemOverrideColor( index, irr::gui::EGUI_LBC_TEXT, 0xFFFF0000 );
        }
    }
};

#define GAME_LOG_ERROR(msgText) \
    { \
        GameLogger::singleton().error( __FUNCTION__, __LINE__, (msgText) ); \
    }

#if 0
#define GAME_LOG_ERROR(x) \
    { \
        de::alphasonic::Logger::singleton() << de::alphasonic::LogLevel::Error << __FUNCTION__ << ":" << __LINE__ << " :: " << (x) << '\n'; \
    }

#define GAME_LOG_INFO(x) \
    { \
        de::alphasonic::Logger::singleton() << de::alphasonic::LogLevel::Info << __FUNCTION__ << ":" << __LINE__ << " :: " << (x) << '\n'; \
    }

#define GAME_LOG_DEBUG(x) \
    { \
        de::alphasonic::Logger::singleton() << de::alphasonic::LogLevel::Debug << __FUNCTION__ << ":" << __LINE__ << " :: " << (x) << '\n'; \
    }
void GAME_PRINT( const char* fn, int line, const char* formatString, ... );

void GAME_ERROR( const char* fn, int line, const char* formatString, ... );
#endif
} // end namespace pioneers3d

#endif // GAME_LOGGER_HPP
