#include "LinearColorGradient.hpp"

namespace irr {
namespace video {


LinearColorGradient& LinearColorGradient::addColor( const SColor& stopColor, float32_t t )

LinearColorGradient& LinearColorGradient::addColor( const SColorf& stopColor, float32_t t )

LinearColorGradient& LinearColorGradient::setColor( u32 index, const SColor& stopColor, float32_t t )

LinearColorGradient& LinearColorGradient::setColor( u32 index, const SColorf& stopColor, float32_t t )



SColor LinearColorGradient::getColor( float32_t t ) const


SColorf LinearColorGradient::getColorf( float32_t t ) const


u32 LinearColorGradient::getColorCount() const
{
	return Colors.size();
}

core::stringc LinearColorGradient::getName( ) const
{
	return Name;
}

LinearColorGradient& LinearColorGradient::setName( const core::stringc& name )
{
	Name = name;
	return *this;
}

bool LinearColorGradient::isTransparent( ) const


E_MATERIAL_TYPE LinearColorGradient::getMaterialType( ) const
{
	if (isTransparent())
		return EMT_TRANSPARENT_ALPHA_CHANNEL;
	else
		return EMT_SOLID;
}

ECOLOR_FORMAT LinearColorGradient::getColorFormat( ) const
{
	if (isTransparent())
		return ECF_A8R8G8B8;
	else
		return ECF_R8G8B8;
}

// old
//IImage*	LinearColorGradient::createImage( IVideoDriver* driver, u32 w, u32 h, bool bVertical ) const

//IImage* createImageFromLinearColorGradient( u32 w, u32 h, bool bVertical, LinearColorGradient* gradient, bool deleteGradient)
//{
//	if (!gradient)
//		return 0;
//
//	IImage* tmp = gradient->createImage( w,h,bVertical );
//
//	if (deleteGradient)
//	{
//		delete gradient;
//	}
//
//	return tmp;
//}

} // end namespace video

} // end namespace irr
