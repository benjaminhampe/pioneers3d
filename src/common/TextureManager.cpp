#include <common/TextureManager.hpp>

typedef std::map< std::string, irr::video::ITexture* > TextureMap;

static void
removeTexture( irr::video::IVideoDriver* driver, irr::video::ITexture* &tex )
{
    assert( driver );

    if ( !tex )
    {
        return;
    }

    irr::core::stringw texName = (irr::core::stringw)tex->getName();

    std::wcout << __FUNCTION__ << "(" << texName.c_str() << ")\n";

    driver->removeTexture( tex );

    tex = nullptr;
}

TextureManager::TextureManager( irr::video::IVideoDriver * driver )
    : m_Driver( driver )
{
    std::wcout << __FUNCTION__ << "()\n";

    assert( m_Driver );
}

TextureManager::~TextureManager()
{
    std::wcout << "~" << __FUNCTION__ << "()\n";

    assert( m_Driver );

    std::wcout << __FUNCTION__ << "(" << m_Data.size() << ")\n";

    TextureMap::iterator it = m_Data.begin();
    for ( ; it != m_Data.end(); it++ )
    {
        removeTexture( m_Driver, it->second );
    }

}

uint32_t
TextureManager::getTextureCount() const
{
    return static_cast< uint32_t >( m_Data.size() );
}

irr::video::ITexture *
TextureManager::getTexture( std::string const & key )
{
    std::cout << __FUNCTION__ << "(" << key << ")\n";

    TextureMap::iterator it = m_Data.find( key );
    if ( it == m_Data.end() )
    {
        return nullptr;
    }
    else
    {
        return it->second;
    }
}

bool
TextureManager::addTexture( std::string const & key, irr::video::ITexture * src )
{
    std::cout << __FUNCTION__ << "(" << key << ")\n";

    assert( m_Driver );

    TextureMap::iterator it = m_Data.find( key );
    if ( it == m_Data.end() )
    {
        m_Data[ key ] = src;
    }
    else
    {
        // the following two lines could be combined and called exchangeTexture( driver, old, new )
        removeTexture( m_Driver, it->second );
        it->second = src;
    }
    return true;
}

bool
TextureManager::addTexture( std::string const & key, irr::video::IImage * src, std::string const & fileName, bool removeImage )
{
    std::cout << __FUNCTION__ << "(" << key << "," << fileName << ")\n";

    assert( m_Driver );

    irr::video::ITexture * tex = createTextureFromImage( m_Driver, src, fileName.empty() ? "" : fileName.c_str() );

    if (removeImage)
    {
        src->drop();
    }

    addTexture( key, tex );
}

bool
TextureManager::addTexture( std::string const & key, std::string const & fileName )
{
    std::cout << __FUNCTION__ << "(" << key << "," << fileName << ")\n";

    assert( m_Driver );

    irr::video::ITexture * tex = m_Driver->getTexture( fileName.c_str() );

    addTexture( key, tex );
}

void
TextureManager::clear()
{
    std::cout << __FUNCTION__ << "()\n";

    assert( m_Driver );
}

bool
TextureManager::loadXML( std::string const & fileName )
{
    std::cout << __FUNCTION__ << "(" << fileName << ")\n";

    assert( m_Driver );

}

bool
TextureManager::saveXML( std::string const & fileName )
{
    std::cout << __FUNCTION__ << "(" << fileName << ")\n";

    assert( m_Driver );
}
