#include "Pioneers3DApplication.hpp"
#include <vector>
#include <map>
#include <assert.h>
#include <tinyxml2.h>

namespace pioneers3d {
/*
<?xml version="1.0" encoding="utf-8"?>
<empleados>
 <cantidad>UnaCantidad</cantidad>
 <empleado>
  <idEmpleado>1</idEmpleado>
  <nombre>UnNombre1</nombre>
  <apellidos>UnosApellidos1</apellidos>
 </empleado>
 <empleado>
  <idEmpleado>2</idEmpleado>
  <nombre>UnNombre2</nombre>
  <apellidos>UnosApellidos2</apellidos>
 </empleado>
</empleados>
*/


std::string
toXML( irr::SIrrlichtCreationParameters const & cfg )
{
    std::stringstream s;
    s << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    s << "<pioneers3d>\n";
    s << "<config>\n";
    s << "\t<device>" << (int)cfg.DeviceType << "</device>\n";
    s << "\t<driver>" << (int)cfg.DriverType << "</driver>\n";
    s << "\t<loglevel>" << (int)cfg.LoggingLevel << "</loglevel>\n";
    s << "\t<width>" << (int)cfg.WindowSize.Width << "</width>\n";
    s << "\t<height>" << (int)cfg.WindowSize.Height << "</height>\n";
    s << "\t<bits>" << (int)cfg.Bits << "</bits>\n";
    s << "\t<antialias>" << (int)cfg.AntiAlias << "</antialias>\n";
    s << "\t<doublebuffer>" << (int)cfg.Doublebuffer << "</doublebuffer>\n";
    s << "\t<vsync>" << (int)cfg.Vsync << "</vsync>\n";
    s << "\t<fullscreen>" << (int)cfg.Fullscreen << "</fullscreen>\n";
    s << "\t<zbufferbits>" << (int)cfg.ZBufferBits << "</zbufferbits>\n";
    s << "\t<stencilbuffer>" << (int)cfg.Stencilbuffer << "</stencilbuffer>\n";
    s << "</config>\n";
    s << "</pioneers3d>\n";
    return s.str();
}


std::string
toXML( irr::video::IVideoModeList const & modeList )
{
    std::stringstream s;
    s << "<video-modes>\n";
    for ( uint32_t i = 0; i < modeList.getVideoModeCount(); ++i )
    {
        uint32_t w = modeList.getVideoModeResolution( i ).Width;
        uint32_t h = modeList.getVideoModeResolution( i ).Height;
        uint32_t d = modeList.getVideoModeDepth( i );
        s << "\t<mode><w>" << w << "</w><h>" << h << "</h><bpp>" << d << "</bpp></mode>\n";
    }
    s << "</video-modes>\n";
    return s.str();
}

bool
fromXML( std::string const & fileName, irr::SIrrlichtCreationParameters & params )
{
    tinyxml2::XMLDocument xml;
    tinyxml2::XMLError eResult = xml.LoadFile( fileName.c_str() );
    if (eResult != tinyxml2::XML_SUCCESS) return false;

    tinyxml2::XMLNode* pioneersNode = xml.FirstChildElement("pioneers3d");
    if (pioneersNode == nullptr) return false;

    tinyxml2::XMLNode* configRoot = pioneersNode->FirstChildElement("config");
    if (configRoot == nullptr) return false;

    int value;

    // [lambda]
    auto extractInt = [ configRoot ] ( std::string const & key, int & returnValue ) -> bool
    {
        if ( !configRoot ) return false;
        tinyxml2::XMLElement* configItem = configRoot->FirstChildElement( key.c_str() );
        if ( !configItem ) return false;
        if ( configItem->QueryIntText( &returnValue ) != tinyxml2::XML_SUCCESS ) return false;
        return true;
    };

    if ( extractInt( "device", value ) ){       params.DeviceType = static_cast< irr::E_DEVICE_TYPE >( value ); }
    if ( extractInt( "driver", value ) ){       params.DriverType = static_cast< irr::video::E_DRIVER_TYPE >( value ); }
    if ( extractInt( "width", value ) ){        params.WindowSize.Width = static_cast< unsigned int >( value ); }
    if ( extractInt( "height", value ) ){       params.WindowSize.Height = static_cast< unsigned int >( value ); }
    if ( extractInt( "loglevel", value ) ){     params.LoggingLevel = static_cast< irr::ELOG_LEVEL >( value ); }
    if ( extractInt( "bits", value ) ){         params.Bits = static_cast< unsigned char >( value ); }
    if ( extractInt( "antialias", value ) ){    params.AntiAlias = static_cast< irr::video::E_ANTI_ALIASING_MODE >( value ); }
    if ( extractInt( "doublebuffer", value ) ){ params.Doublebuffer = static_cast< bool >( value ); }
    if ( extractInt( "vsync", value ) ){        params.Vsync = static_cast< bool >( value ); }
    if ( extractInt( "fullscreen", value ) ){   params.Fullscreen = static_cast< bool >( value ); }
    if ( extractInt( "zbufferbits", value ) ){  params.ZBufferBits = static_cast< unsigned char >( value ); }
    if ( extractInt( "stencilbuffer", value ) ){params.Stencilbuffer = static_cast< bool >( value ); }
   return true;
}


std::string
trim( std::string & str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    assert( last >= first );
    return str.substr( first, (last-first+1) );
}


Pioneers3DApplication::Pioneers3DApplication()
    : m_Device( nullptr )
    , m_ClearColor( 255, 215, 235, 255 )
{
    m_DeviceConfig.DriverType = irr::video::EDT_OPENGL;
    m_DeviceConfig.WindowSize.Width = 800;
    m_DeviceConfig.WindowSize.Height = 600;
    m_DeviceConfig.AntiAlias = 0;
    m_DeviceConfig.Bits = 32;
    m_DeviceConfig.Doublebuffer = false;
    m_DeviceConfig.Vsync = false;
    m_DeviceConfig.EventReceiver = this;
    m_DeviceConfig.Fullscreen = false;
    m_DeviceConfig.Stencilbuffer = true;

    std::string xml0 = toXML( m_DeviceConfig );

    std::cout << "--------------------------------------------------\n";
    std::cout << xml0 << "\n";
    std::cout << "--------------------------------------------------\n";

//    std::vector< std::string > cfgKeys;
//    std::vector< std::string > cfgValues;

    irr::SIrrlichtCreationParameters params1;
    fromXML( xml0, params1 );
    std::string xml1 = toXML( params1 );

    std::cout << "--------------------------------------------------\n";
    std::cout << xml1 << "\n";
    std::cout << "--------------------------------------------------\n";

#if 0
    std::string cfgINI = toINI( m_DeviceConfig );

    std::vector< std::string > cfgKeys;
    std::vector< std::string > cfgValues;

    fromINI( cfgINI, cfgKeys, cfgValues );

    for ( size_t i = 0; i < cfgKeys.size(); ++i )
    {
        std::cout << __FUNCTION__ << " :: Config[" << cfgKeys[ i ] << "] = " << cfgValues[ i ] << "\n";
    }
#endif

    m_Device = irr::createDeviceEx( m_DeviceConfig );

    assert( m_Device );

    std::cout << "--------------------------------------------------\n";
    std::cout << toXML( *m_Device->getVideoModeList() ) << "\n";
    std::cout << "--------------------------------------------------\n";

    irr::scene::ISceneManager* smgr = m_Device->getSceneManager();

    irr::scene::ISceneNode* rootNode = smgr->getRootSceneNode();

    createCameraSceneNodeFPS( smgr, rootNode );

    m_Device->setEventReceiver( this );
}

Pioneers3DApplication::~Pioneers3DApplication()
{
    if ( m_Device )
    {
        m_Device->closeDevice();
        m_Device->drop();
    }
}

bool
Pioneers3DApplication::run()
{
    uint64_t startTime = m_Device->getTimer()->getRealTime();
    uint64_t currentTime = m_Device->getTimer()->getRealTime();

    if (m_Device && m_Device->run())
    {
        irr::video::IVideoDriver* driver = m_Device->getVideoDriver();
        if (driver)
        {
            driver->beginScene( true, true, m_ClearColor );

            irr::scene::ISceneManager* smgr = m_Device->getSceneManager();
            if ( smgr )
            {
                smgr->drawAll();
            }

            driver->endScene();

            std::wstringstream s; s << "Pioneers3D ";
            s << "- FPS(" << driver->getFPS() << ")";

            m_Device->setWindowCaption( s.str().c_str() );
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool
Pioneers3DApplication::OnEvent( const irr::SEvent& event )
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        const irr::SEvent::SKeyInput& key = event.KeyInput;

        if (key.Key == irr::KEY_ESCAPE)
        {
            if ( m_Device )
            {
                m_Device->closeDevice();
                m_Device = nullptr;
            }
            return true;
        }
    }
    return false;
}

} // namespace pioneers3d



#if 0
std::string
toINI( irr::SIrrlichtCreationParameters const & cfg )
{
    std::stringstream s;
    //s << "[WindowSize]\n" << cfg.WindowSize.Width << "," << cfg.WindowSize.Height << "," << cfg.Bits << "\n";
    s << "[DeviceType]\n" << cfg.DeviceType << "\n";
    s << "[DriverType]\n" << cfg.DriverType << "\n";
    s << "[LogLevel]\n" << cfg.LoggingLevel << "\n";
    s << "[WindowWidth]\n" << cfg.WindowSize.Width << "\n";
    s << "[WindowHeight]\n" << cfg.WindowSize.Height << "\n";
    s << "[BitsPerPixel]\n" << cfg.Bits << "\n";
    s << "[AntiAliasing]\n" << cfg.AntiAlias << "\n";
    s << "[Doublebuffer]\n" << cfg.Doublebuffer << "\n";
    s << "[Vsync]\n" << cfg.Vsync << "\n";
    s << "[Fullscreen]\n" << cfg.Fullscreen << "\n";
    s << "[ZBufferBits]\n" << cfg.ZBufferBits << "\n";
    s << "[Stencilbuffer]\n" << cfg.Stencilbuffer << "\n";
}

bool
fromINI( std::string const & lines, std::vector< std::string > & keys, std::vector< std::string > & values )
{
    std::cout << __FUNCTION__ << "()\n" << lines << "\n\nEXTRACT NOW...\n";

    size_t i = 0;
    size_t line = 0;
    size_t keyStart;
    size_t keyCount;
    size_t valueStart;
    size_t valueCount;
    std::string key;
    std::string value;

    while( i < lines.size() )
    {
        i = lines.find( '[', i );

        if ( i == std::string::npos )
        {
            break;
        }

        ++i;

        if ( i >= lines.size() ) { break; } // validate 'i'

        keyStart = i;

        i = lines.find( ']', i );

        if ( i == std::string::npos )
        {
            break;
        }

        if ( i <= keyStart + 1 ) { break; } // validate 'i'

        keyCount = i - 1 - keyStart; // Is there something between '[' and ']' ?

        //assert( i >= keyStart ); // Crash program if '[' and ']' are not correctly used, remove for -Wno-dev

        if ( keyCount > 0 ) // If so, extract key
        {
            key = lines.substr( keyStart, keyCount );

            std::cout << __FUNCTION__ << " :: Found key (" << key << ")\n";
        }

        // Now search for EOL after key and extract ...
        i = lines.find( '\n', i + 1 );

        if ( i == std::string::npos )
        {
            break;
        }

        ++i;

        if ( i >= lines.size() ) { break; } // validate 'i'

        valueStart = i;

        ++line;

        // ... everything between next EOL and call it value ( not trimmed, raw )
        i = lines.find( '\n', i + 1 );

        if ( i == std::string::npos )
        {
            break;
        }

        valueCount = i - valueStart;

        ++i;

        if ( i >= lines.size() ) { break; } // validate 'i'

        ++line;

        // Is there something to extract?
        if ( valueCount > 0 )
        {
            // If so, extract the raw value
            value = lines.substr( valueStart, valueCount );

            // Trim whitespaces
            trim( value );

            // trim all whitespace before and after any alpha-numeric character
            std::cout << __FUNCTION__ << " :: [OK] Found { " << key << ": " << value << "; } at line (" << line << ")\n";
            keys.push_back( key );
            values.push_back( value );
        }
        else
        {
            std::cout << __FUNCTION__ << " :: [ERROR] Invalid value for key (" << key << ")\n";
        }
    }
    return true;
}
#endif
