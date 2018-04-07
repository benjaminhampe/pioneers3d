#include "Game_Logger.hpp"

#define BUFFER_SIZE 1024

namespace pioneers3d {

#if 0
void GAME_PRINT( const char* fn, int line, const char* formatString, ... )
{
    va_list p;
    va_start( p, formatString );
    char tmp[ BUFFER_SIZE ];
    vsnprintf( &(tmp[0]), BUFFER_SIZE, formatString, p );
    va_end( p );
    de::alphasonic::Logger::singleton() << de::alphasonic::LogLevel::Info << fn << ":" << line << " :: " << std::string( tmp ) << "\n";
}

void GAME_ERROR( const char* fn, int line, const char* formatString, ... )
{
    va_list p;
    va_start( p, formatString );
    char tmp[ BUFFER_SIZE ];
    vsnprintf( &(tmp[0]), BUFFER_SIZE, formatString, p );
    va_end( p );
    de::alphasonic::Logger::singleton() << de::alphasonic::LogLevel::Error << fn << ":" << line << " :: " << std::string( tmp ) << "\n";
}
#endif

} // end namespace pioneers3d
