///////////////////////////////////////////////////////////////////////////////
/// @file   Color.hpp
/// @brief  Definition of class Color
/// @author Benjamin Hampe <benjaminhampe@gmx.de>
/// @date   2018
///
/// Copyright (c) 2018 Benjamin Hampe
///////////////////////////////////////////////////////////////////////////////

#ifndef DE_HAMPE_IMAGE_IMAGE_HPP
#define DE_HAMPE_IMAGE_IMAGE_HPP

#include <de/hampe/common/image/Types.hpp>

BEGIN_NAMESPACE_DE_HAMPE_COMMON_IMAGE

class Image
{
public:
   Image();

   std::vector< uint8_t > m_Data;
};

END_NAMESPACE_DE_HAMPE_COMMON_IMAGE

#endif // DE_HAMPE_IMAGE_COLOR_HPP
