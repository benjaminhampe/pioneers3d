#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <common/ImageUtils.hpp>

class TextureManager
{
public:
    TextureManager( irr::video::IVideoDriver * driver );

    ~TextureManager();

    uint32_t
    getTextureCount() const;

    irr::video::ITexture *
    getTexture( std::string const & key );

    bool
    addTexture( std::string const & key, irr::video::ITexture * src );

    bool
    addTexture( std::string const & key, irr::video::IImage * src, std::string const & fileName, bool removeImage = false );

    bool
    addTexture( std::string const & key, std::string const & fileName );

    void
    clear();

    bool
    loadXML( std::string const & fileName );

    bool
    saveXML( std::string const & fileName );

private:
    irr::video::IVideoDriver * m_Driver;

    std::map< std::string, irr::video::ITexture* > m_Data;

};

#endif // TEXTURE_MANAGER_HPP
