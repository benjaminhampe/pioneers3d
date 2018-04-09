///
/// @file 		Logger.hpp
/// @author: 	Benjamin Hampe <benjaminhampe@gmx.de>
/// @license: 	Free for all civil ( no military ) purposes.
///

#ifndef DE_ALPHASONIC_LOGGER_HPP
#define DE_ALPHASONIC_LOGGER_HPP

#include <common/Types.hpp>

namespace de {
namespace alphasonic {

/// @brief Variadic to MultiByte string ( UTF-8 ), only safe for the 128 chars ( 7-bit ),
/// using more than 7 bits to encode a char is very platform dependent ( CodePages, TTF must contain such glyphs, etc... )
/// Actually a stupid container, better use ustring.h to carry around data for multiple languages
std::string sprintf( char const* formatString, ... );

/// @brief Variadic to Unicode string ( platform dependent, Win UTF-16, Linux UTF-32 )
/// Still stupid, but Unicode
std::wstring wsprintf( wchar_t const* formatString, ... );

/// @brief The class LogLevel manages an enum.
class LogLevel
{
public:
    enum ELogLevel
    {
        None = 0,
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        Fatal,
        MaxLevel
    };

    /// @brief Default constructor
    LogLevel() : m_Level( None ) {}

    /// @brief Value constructor
    LogLevel( ELogLevel const & level ) : m_Level( level ) { }

    /// @brief Implicit cast operator
    operator ELogLevel() const { return m_Level; }

    /// @brief Copy operator
    LogLevel& operator= ( ELogLevel const & level ) { m_Level = level; return *this; }

    /// @brief Convert enum value to string.
    static std::string createString( ELogLevel const & level )
    {
        switch ( level )
        {
            case None: return "None";
            case Trace: return "Trace";
            case Debug: return "Debug";
            case Info: return "Info";
            case Warn: return "Warn";
            case Error: return "Error";
            case Fatal: return "Fatal";
            default: return "Unknown";
        }
    }

    /// @brief Convert class member enum value to string.
    std::string toString() const { return createString( m_Level );	}

private:
    ELogLevel m_Level;
};

/// @brief The class Logger prints formatted messages to the console window ( for now only )
class Logger
{
public:
    static Logger & singleton()
    {
        static Logger logger( "de.alphasonic.Logger" );
        return logger;
    }

    Logger( std::string const & name )
        : m_LoggerName( name )
    {
        std::cout << "Created Logger [" << m_LoggerName << "]\n" << std::endl;
    }

    void addListener( irr::gui::IGUIListBox* logbox )
    {
        m_Listener.push_back( logbox );
    }

    Logger& log( LogLevel const & level )
    {
        std::cout << "[" << level.toString() << "] " << m_LoggerName << " :: ";
        return *this; // chain together
    }
    Logger & raw() { return *this; }
    Logger & trace() { return this->log( LogLevel::Trace ); }
    Logger & debug() { return this->log( LogLevel::Debug ); }
    Logger & info() { return this->log( LogLevel::Info ); }
    Logger & warn() { return this->log( LogLevel::Warn ); }
    Logger & error() { return this->log( LogLevel::Error ); }
    Logger & fatal() { return this->log( LogLevel::Fatal ); }

    template <class T>
    Logger& operator<< ( T const & value )
    {
        std::cout << value;
        return *this; // chain together
    }

    // prints [<LogLevel>] <m_LoggerName> :: <followed by everything << concatted << with << stream operator>

private:
    std::string m_LoggerName;

    std::vector< irr::gui::IGUIListBox* > m_Listener;

};

} // end namespace alphasonic
} // end namespace de

//inline std::ostream &
//operator<< ( std::ostream & out, de::alphasonic::LogLevel const & level )
//{
//    out << level.toString();
//    return out;
//}

#if 0

void ALPHASONIC_LOG( de::alphasonic::LogLevel const & level, const char* formatString, ... );
void ALPHASONIC_LOG_INFO( const char* formatString, ... );
void ALPHASONIC_LOG_ERROR( const char* formatString, ... );
void ALPHASONIC_LOG_DEBUG( const char* formatString, ... );

#define $( ... ) ( de::alphasonic::sprintf( __VA_ARGS__ ).c_str() )

#ifndef ALPHASONIC_CREATE_STATIC_CLASS_LOGGER
#define ALPHASONIC_CREATE_STATIC_CLASS_LOGGER(className) \
public: \
    static Logger & \
    getLogger() \
    { \
        static Logger s_Logger( (className) ) \
        return s_Logger; \
    }
#endif

#ifndef ALPHASONIC_CREATE_LOGGER
#define ALPHASONIC_CREATE_LOGGER(className) \
    de::alphasonic::Logger logger((className)); \
    auto getLogger = [&logger] () -> de::alphasonic::Logger & \
    { \
        return logger; \
    };
#endif

#ifndef ALPHASONIC_CREATE_FUNCTION_LOGGER
#define ALPHASONIC_CREATE_FUNCTION_LOGGER ALPHASONIC_CREATE_LOGGER(__FUNCTION__)
#endif

#ifndef ALPHASONIC_LOG
#define ALPHASONIC_LOG(level,formatString,...) \
    getLogger() << (level) << __FUNCTION__ << ":" << __LINE__ << " :: " \
        << de::alphasonic::sprintf((formatString),__VA_ARGS__) << "\n";
#endif
#ifndef ALPHASONIC_LOG_TRACE
#define ALPHASONIC_LOG_TRACE(formatString,...) ALPHASONIC_LOG(de::alphasonic::LogLevel::Trace,(formatString),__VA_ARGS__)
#endif
#ifndef ALPHASONIC_LOG_DEBUG
#define ALPHASONIC_LOG_DEBUG(formatString,...) ALPHASONIC_LOG(de::alphasonic::LogLevel::Debug,(formatString),__VA_ARGS__)
#endif
#ifndef ALPHASONIC_LOG_INFO
#define ALPHASONIC_LOG_INFO(formatString,...) ALPHASONIC_LOG(de::alphasonic::LogLevel::Info,(formatString),__VA_ARGS__)
#endif
#ifndef ALPHASONIC_LOG_WARN
#define ALPHASONIC_LOG_WARN(formatString,...) ALPHASONIC_LOG(de::alphasonic::LogLevel::Warn,(formatString),__VA_ARGS__)
#endif
#ifndef ALPHASONIC_LOG_ERROR
#define ALPHASONIC_LOG_ERROR(formatString,...) ALPHASONIC_LOG(de::alphasonic::LogLevel::Error,(formatString),__VA_ARGS__)
#endif
#ifndef ALPHASONIC_LOG_FATAL
#define ALPHASONIC_LOG_FATAL(formatString,...) ALPHASONIC_LOG(de::alphasonic::LogLevel::Fatal,(formatString),__VA_ARGS__)
#endif
#endif

#endif // DE_ALPHASONIC_LOGGER_HPP
