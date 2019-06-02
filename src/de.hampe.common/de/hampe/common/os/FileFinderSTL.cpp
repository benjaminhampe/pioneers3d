#include "FileFinderSTL.hpp"

#include <vector>
#include <string>
#include <sstream>

#include <experimental/filesystem>
#include <thread>
#include <mutex>
#include <memory>
#include <condition_variable>

BEGIN_NAMESPACE_DE_HAMPE_COMMON_OS


template < typename FUNC >
void addDefaultFileTypes( FUNC addString )
{
   addString( "*" );
   addString( "pdf" );
   addString( "txt" );
   addString( "raw" );
}

template < typename FUNC >
void addAudioFileTypes( FUNC addString )
{
   addString( "mp3" );
   addString( "wav" );
   addString( "aac" );
   addString( "mp4" );
   addString( "m4a" );
   addString( "flac" );
   addString( "ogg" );
   addString( "wma" );
   addString( "flv" );
}

template < typename FUNC >
void addImageFileTypes( FUNC addString )
{
   addString( "jpg" );
   addString( "jpeg" );
   addString( "png" );
   addString( "bmp" );
   addString( "gif" );
   addString( "tif" );
   addString( "tga" );
   addString( "pcx" );
}

template < typename FUNC >
void addVideoFileTypes( FUNC addString )
{
   addString( "mp4" );
   addString( "m4a" );
   addString( "flac" );
   addString( "ogg" );
   addString( "wma" );
   addString( "flv" );
}

FileFinderSTL::FileFinderSTL()
{

}


END_NAMESPACE_DE_HAMPE_COMMON_OS
