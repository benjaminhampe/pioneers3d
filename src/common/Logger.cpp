///
/// @file 		Logger.cpp
/// @author: 	Benjamin Hampe <benjaminhampe@gmx.de>
/// @license: 	Free for all civil ( no military ) purposes.
///
#include "Logger.hpp"

#define BUFFER_SIZE 1024

namespace de {
namespace alphasonic {

std::string
sprintf( char const * formatString, ... )
{
    va_list p;
    va_start( p, formatString );
    char tmp[ BUFFER_SIZE ];
    vsnprintf( &(tmp[0]), BUFFER_SIZE, formatString, p );
    va_end( p );
    return std::string( tmp );
}

std::wstring
wsprintf( wchar_t const * formatString, ...)
{
    va_list p;
    va_start( p, formatString );
    wchar_t tmp[ BUFFER_SIZE ];
   #if defined(_WINDOWS)
    vsnwprintf( &(tmp[0]), BUFFER_SIZE, formatString, p );
   #else
    vswprintf( &(tmp[0]), BUFFER_SIZE, formatString, p );
   #endif
    va_end( p );
    return std::wstring( tmp );
}

} // end namespace alphasonic
} // end namespace de


#if 0
void ALPHASONIC_LOG( de::alphasonic::LogLevel const & level, const char* formatString, ... )
{
    va_list p;
    va_start( p, formatString );
    char tmp[ BUFFER_SIZE ];
    vsnprintf( &(tmp[0]), BUFFER_SIZE, formatString, p );
    va_end( p );

    de::alphasonic::Logger::singleton() << (level) << __FUNCTION__ << ":" << __LINE__ << " :: " << std::string( tmp ) << "\n";
}

void ALPHASONIC_LOG_INFO( const char* formatString, ... )
{
    va_list p;
    va_start( p, formatString );
    char tmp[ BUFFER_SIZE ];
    vsnprintf( &(tmp[0]), BUFFER_SIZE, formatString, p );
    va_end( p );
    de::alphasonic::Logger::singleton() << de::alphasonic::LogLevel::Info << __FUNCTION__ << ":" << __LINE__ << " :: " << std::string( tmp ) << "\n";
}

void ALPHASONIC_LOG_ERROR( const char* formatString, ... )
{
    va_list p;
    va_start( p, formatString );
    char tmp[ BUFFER_SIZE ];
    vsnprintf( &(tmp[0]), BUFFER_SIZE, formatString, p );
    va_end( p );
    de::alphasonic::Logger::singleton() << de::alphasonic::LogLevel::Error << __FUNCTION__ << ":" << __LINE__ << " :: " << std::string( tmp ) << "\n";
}

void ALPHASONIC_LOG_DEBUG( const char* formatString, ... )
{
    va_list p;
    va_start( p, formatString );
    char tmp[ BUFFER_SIZE ];
    vsnprintf( &(tmp[0]), BUFFER_SIZE, formatString, p );
    va_end( p );
    de::alphasonic::Logger::singleton() << de::alphasonic::LogLevel::Debug << __FUNCTION__ << ":" << __LINE__ << " :: " << std::string( tmp ) << "\n";
}

#endif
