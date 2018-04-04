#include "irrBackend.hpp"

#include <assert.h>


#include <fstream>

#include <vector>
#include <array>
#include <memory>

#include <windows.h>
#include <time.h>

std::string
toString( irr::core::vector2df const & v )
{
    std::stringstream s;
    s << v.X << "," << v.Y;
    return s.str();
}

std::string
toString( irr::core::vector3df const & v )
{
    std::stringstream s;
    s << v.X << "," << v.Y << "," << v.Z;
    return s.str();
}

std::string
toString( irr::video::SColor const & color )
{
    std::stringstream s;
    s << color.getRed() << "," << color.getGreen() << "," << color.getBlue() << "," << color.getAlpha();
    return s.str();
}

std::string
toString( irr::video::S3DVertex const & v )
{
    std::stringstream s;
    s << toString( v.Pos ) << "," << toString( v.Normal ) << "," << toString( v.Color ) << "," << toString( v.TCoords );
    return s.str();
}

std::string
toString( glm::ivec2 const & v )
{
    std::stringstream s;
    s << v.x << ", " << v.y;
    return s.str();
}

std::string
toString( glm::ivec3 const & v )
{
    std::stringstream s; s << v.x << "," << v.y << "," << v.z;
    return s.str();
}

std::string
toString( glm::vec2 const & v )
{
    std::stringstream s; s << v.x << "," << v.y;
    return s.str();
}

std::string
toString( glm::vec3 const & v )
{
    std::stringstream s; s << v.x << "," << v.y << "," << v.z;
    return s.str();
}

bool
equals( glm::vec2 a, glm::vec2 b, float32_t eps )
{
    if ( irr::core::equals( a.x, b.x, eps ) &&
         irr::core::equals( a.y, b.y, eps ) ) return true;
    return false;
}

bool
equals( glm::vec3 a, glm::vec3 b, float32_t eps )
{
    if ( irr::core::equals( a.x, b.x, eps ) &&
         irr::core::equals( a.y, b.y, eps ) &&
         irr::core::equals( a.z, b.z, eps ) ) return true;
    return false;
}

//struct SDesktopInfo
//{
//    int32_t Width;
//    int32_t Height;
//    int32_t BitDepth;
//    float32_t Frequency;
//};

struct AutoNullDevice
{
    AutoNullDevice()
        : Device( irr::createDevice( irr::video::EDT_NULL ) )
    {
        Device->run();
    }

    ~AutoNullDevice()
    {
        //delete Device;
        Device->closeDevice();
        Device->drop();
    }

    irr::IrrlichtDevice* operator -> () {
        return Device;
    }

    irr::IrrlichtDevice * Device;
};

glm::ivec3 getDesktopSize()
{
    glm::ivec3 desktop( 0,0,0 );

    //AutoNullDevice device;

    irr::IrrlichtDevice * device = irr::createDevice( irr::video::EDT_NULL );
    desktop.x = device->getVideoModeList()->getDesktopResolution().Width;
    desktop.y = device->getVideoModeList()->getDesktopResolution().Height;
    desktop.z = device->getVideoModeList()->getDesktopDepth();
    device->drop();
    return desktop;
}

float32_t convertToNormalized( int16_t value )
{
    // ( make all symmetric around +0.5f )
    if ( value == 0 )
        return 0.5f;
    else if ( value > 0 )
        return 0.5f + static_cast< float32_t >(value)/65534.0f;
    else
        return 0.5f + static_cast< float32_t >(value)/65536.0f;
}


#ifdef GLM_HPP

#endif


#if 0
std::string
getLocalTimeString()
{
    SYSTEMTIME t;
    GetLocalTime( &t );
    std::stringstream s;
    s   << t.wYear << "-" << t.wMonth << "-" << t.wDay << " "
        << t.wHour << ":" << t.wMinute << ":" << t.wSecond << "." << t.wMilliseconds;
    return s.str();
}


int64_t
getPerfTimer()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter( &li );
    return static_cast< int64_t >( li.QuadPart );
}

int64_t
getPerfTimerFrequency()
{
    LARGE_INTEGER li;
    QueryPerformanceFrequency( &li );
    return static_cast< int64_t >( li.QuadPart );
}

std::string
getPerfTimerString()
{
    std::stringstream s;
    s   << getPerfTimer() << ", f=" << getPerfTimerFrequency() << " Hz\n";
    return s.str();
}

std::string
getLocalTimeString()
{
    tm * t = localtime( nullptr );
    std::stringstream s;
    s   << t->tm_year << "-" << t->tm_mon << "-" << t->tm_mday << " "
        << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec;
    return s.str();
}


std::string
getSystemTimeString()
{
    SYSTEMTIME t;
    GetSystemTime( &t );
    std::stringstream s;
    s   << t.wYear << "-" << t.wMonth << "-" << t.wDay << " "
        << t.wHour << ":" << t.wMinute << ":" << t.wSecond << "." << t.wMilliseconds;
    return s.str();
}

#endif
