#ifndef DE_HAMPE_OS_FILESYSTEM_HPP
#define DE_HAMPE_OS_FILESYSTEM_HPP

#include <de/hampe/common/os/FileMagic.hpp>
#include <iostream>

BEGIN_NAMESPACE_DE_HAMPE_COMMON_OS

class FileSystemSTL
{
   CREATE_STATIC_LOGGER( "de.hampe.os.FileSystemSTL" )
public:
   static bool
   existFile( std::string const & fileName );

   static bool
   existDirectory( std::string const & fileName );

   static std::string
   absoluteFilePath( std::string const & fileName );

   static std::string
   absoluteFileName( std::string const & fileName );

   static std::string
   filePath( std::string const & fileName );

   static std::string
   fileName( std::string const & fileName );

   static std::string
   fileExtension( std::string const & fileName );

   static uintmax_t
   fileSize( std::string const & fileName );

   static os::FileType
   fileType( std::string const & fileName );

   static os::FileType
   fileMagic( std::string const & fileName );


//   static bool
//   createDirectory( QString const & basePath );

//   static bool
//   deleteFile( QString const & fileName );

//   static QStringList
//   findFiles( QString const & directoryName );

//   static QStringList
//   findMP3Files( QString const & directoryName );

//   static QStringList
//   findAudioFiles( QString const & directoryName );
};

END_NAMESPACE_DE_HAMPE_COMMON_OS

#endif // DE_HAMPE_OS_FILESYSTEM_HPP
