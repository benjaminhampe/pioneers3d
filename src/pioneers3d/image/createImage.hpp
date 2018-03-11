#ifndef CREATE_IMAGE_HPP
#define CREATE_IMAGE_HPP

namespace irr {
namespace video {

    class IVideoDriver;
    class IImage;

} // end namespace video
} // end namespace irr

namespace pioneers3d {

    irr::video::IImage*
    createImage( irr::video::IVideoDriver* driver, int w, int h );

} // end namespace pioneers3d

#endif // CREATE_IMAGE_HPP
