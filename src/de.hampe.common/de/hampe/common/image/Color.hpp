///////////////////////////////////////////////////////////////////////////////
/// @file   Color.hpp
/// @brief  Definition of class Color
/// @author Benjamin Hampe <benjaminhampe@gmx.de>
/// @date   2018
///
/// Copyright (c) 2018 Benjamin Hampe
///////////////////////////////////////////////////////////////////////////////

#ifndef DE_HAMPE_COMMON_IMAGE_COLOR_HPP
#define DE_HAMPE_COMMON_IMAGE_COLOR_HPP

#include <de/hampe/common/image/Types.hpp>

BEGIN_NAMESPACE_DE_HAMPE_COMMON_IMAGE

   inline uint8_t
   ARGB_A( uint32_t const color )
   {
      return uint8_t( ( color >> 24 ) & 0xff );
   }

   inline uint8_t
   ARGB_R( uint32_t const color )
   {
      return uint8_t( ( color >> 16 ) & 0xff );
   }

   inline uint8_t
   ARGB_G( uint32_t const color )
   {
      return uint8_t( ( color >> 8 ) & 0xff );
   }

   inline uint8_t
   ARGB_B( uint32_t const color )
   {
      return uint8_t( ( color ) & 0xff );
   }

   inline uint32_t
   ARGB( uint8_t r, uint8_t g, uint8_t b, uint8_t a )
   {
       return ( uint32_t( a ) << 24 ) | ( uint32_t( r ) << 16 ) | ( uint32_t( g ) << 8 ) | uint32_t( b );
   }

   inline uint8_t
   randomByte()
   {
       return uint8_t( rand() % 255 );
   }

   inline float32_t
   randomFloat()
   {
       return glm::clamp( float32_t( rand() % 65536 ) * ( 1.0f / 65535.0f ), 0.0f, 1.0f );
   }

   inline uint32_t
   randomRGB()
   {
       return ARGB( randomByte(), randomByte(), randomByte(), 255 );
   }

   inline glm::vec4
   randomRGBf()
   {
       return glm::vec4( randomFloat(), randomFloat(), randomFloat(), 1.0f ) ;
   }

END_NAMESPACE_DE_HAMPE_COMMON_IMAGE

#endif // DE_HAMPE_COMMON_IMAGE_COLOR_HPP
