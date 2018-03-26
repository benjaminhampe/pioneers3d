#ifndef LINEAR_COLOR_GRADIENT_HPP
#define LINEAR_COLOR_GRADIENT_HPP

#include <stdint.h>
#include <sstream>
#include <vector>
#include <glm/glm.hpp>

namespace irr {
namespace video {

class LinearColorGradient
{
public:
	struct Stop_t
	{
		glm::vec4 Colorf;
		float32_t Pos;	// in range 0..1
	};
	
	LinearColorGradient() {}
	~LinearColorGradient() {}

	std::string 
	toString( ) const
	{
		std::stringstream s;
		s << "LinearColorGradient[" << getName() << "].TableSize = " << getColorCount() << ":\n";
		s << std::fixed;
		for ( uint32_t i = 0; i < getColorCount(); ++i )
		{
			Stop_t const & stop = m_Stops[ i ];
			s << "GradientStop[" << i << "] = { "
			<< "t:" << stop.Pos << "; "
			<< "r:" << stop.Color.r << "; "
			<< "g:" << stop.Color.g << "; "
			<< "b:" << stop.Color.b << "; "
			<< "a:" << stop.Color.a << "; }\n";
		}
		return s.str();
	}

	void 
	clear()
	{
		m_Stops.clear();
	}
	
	uint32_t 
	getColorCount() const
	{
		return static_cast< uint32_t >( m_Stops.size() );
	}

	glm::vec4 
	getColorf( float32_t t ) const
	{
		///
		if ( m_Stops.size() < 2 )
		{
			if ( m_Stops.size() < 1 )
			{
				return glm::vec4(0,0,0,0);	// The color-table is empty, return transparent color.
			}
			else
			{
				return m_Stops[ 0 ].Color;	// The color-table is a single color, not a gradient.
			}
		}
		
		// find maximum and minimum neighbors
		bool found_greater_t_index = false;
		uint32_t   greater_t_index = 0;

		for ( uint32_t i = 0; i < getColorCount(); i++)
		{
			Stop_t const & stop = m_Stops[i];
			
			if ( std::abs( t - stop.Pos ) < 0.00001f )
			{
				return stop.Color;
			}
			else if ( t < stop.Pos )
			{
				found_greater_t_index = true;
				greater_t_index = i;
				break;
			}
		}

		if (!found_greater_t_index)
		{
			return m_Stops[ getColorCount() - 1 ].Color;
		}

		// interpolate between prev and next neighbor color
		Stop_t const & stopA = m_Stops[greater_t_index-1];
		Stop_t const & stopB = m_Stops[greater_t_index];
		glm::vec4 const & A = stopA.Color;
		glm::vec4 const & B = stopB.Color;
		float32_t const k = std::abs( (t - stopA.Pos) / (stopB.Pos - stopA.Pos) );
		float32_t const fa = A.a + k*( B.a - A.a );
		float32_t const fr = A.r + k*( B.r - A.r );
		float32_t const fg = A.g + k*( B.g - A.g );
		float32_t const fb = A.b + k*( B.b - A.b );
		return glm::vec4( fr,fg,fb,fa );
	}

	void 
	addColor( glm::vec4 const & stopColor, float32_t t = 0.5f )
	{
		Stop_t stop;
		stop.Color = stopColor;
		stop.Pos = glm::clamp( t, 0.0f, 1.0f );

		uint32_t const c = getColorCount();

		if (getColorCount()==0)
		{
			m_Stops.emplace_back( std::move( stop ) );
		}
		else // if (getColorCount()>0)
		{
			bool found_greater_t_index = false;
			uint32_t   greater_t_index = 0;

			for ( uint32_t i = 0; i < getColorCount(); ++i )
			{
				if ( std::abs( t - m_Stops[i].Pos ) < 0.00001f )
				{
					return *this;	// dont insert if any t does equal one of array-elements
				}
				else if ( m_Stops[i].Pos > t )
				{
					found_greater_t_index = true;
					      greater_t_index = i;
					break;
				}
			}

			if ( found_greater_t_index )
			{
				m_Stops.insert( stop, greater_t_index );
			}
			else
			{
				m_Stops.emplace_back( std::move( stop ) );
			}
		}
		return *this;
	}

	void 
	setColor( uint32_t index, glm::vec4 const & stopColor, float32_t t = 0.5f )
	{
		if (index >= getColorCount())
		{
			return;
		}
		
		m_Stops[index].Color = stopColor;
		m_Stops[index].Pos = glm::clamp( t, 0.0f, 1.0f );
	}

	bool 
	isTransparent( ) const
	{
		for ( uint32_t i = 0; i < getColorCount(); ++i )
		{
			if (m_Stops[i].Color.a < 0.999f)
			{
				return true;
			}
		}

		return false;
	}
	
	std::string 
	getName() const
	{
		return m_Name;
	}

	void 
	setName( std::string const & name )
	{
		m_Name = name;
	}

private:
	std::vector< Stop_t > m_Stops;
	std::string m_Name;
};

} // end namespace video
} // end namespace irr

#endif // LINEAR_COLOR_GRADIENT_HPP

#if 0
	
uint32_t 
getColor( float32_t t ) const
{
	return getColorf(t).toSColor();
}

void 
addColor( uint32_t const & stopColor, float32_t t = 0.5f )
{
	return addColor( glm::vec4(stopColor), t);
}

void 
setColor( uint32_t index, const uint32_t& stopColor, float32_t t = 0.5f )
{
	const uint32_t size0 = getColorCount();
	if (index >= size0)
		return *this;

	m_Stops[index].Color = glm::vec4( stopColor);
	m_Stops[index].Pos = glm::clamp( t, 0.0f, 1.0f );
	return *this;
}

E_MATERIAL_TYPE getMaterialType( ) const
{
	if (isTransparent())
		return EMT_TRANSPARENT_ALPHA_CHANNEL;
	else
		return EMT_SOLID;
}

ECOLOR_FORMAT getColorFormat( ) const
{
	if (isTransparent())
		return ECF_A8R8G8B8;
	else
		return ECF_R8G8B8;
}


// new
IImage*	LinearColorGradient::createImage( uint32_t w, uint32_t h, bool bVertical ) const
{
	#if _DEBUG
	os::Printer::log( "LinearColorGradient::createImage()", ELL_INFORMATION );
	#endif // _DEBUG

	if (w==0 || h==0)
	{
		os::Printer::log( "Can't create Image of size zero.", ELL_ERROR );
		return 0;
	}

	// old
	//IImage* tmp = driver->createImage( this->getColorFormat(), core::dimension2du(w,h) );

	// new
	IImage* tmp = (IImage*)new CImage( this->getColorFormat(), core::dimension2du(w,h) );
	if (!tmp)
	{
		os::Printer::log( "Could not create CImage", ELL_ERROR );
		return 0;
	}

	const core::dimension2du& ImageSize = tmp->getDimension();

//	#if _DEBUG
//		// os::Printer::log( core::sprintf("Created new CImage(%d,%d,%d)", ImageSize.Width, ImageSize.Height, tmp->getBitsPerPixel()).c_str(), ELL_INFORMATION );
//		// os::Printer::log( "start filling", ELL_INFORMATION );
//	#endif // _DEBUG

	// vertical filling
	if ( bVertical )
	{
		const float32_t fy = 1.0f / (float32_t)h;

		for (uint32_t y=0; y<ImageSize.Height; y++)
		{
			uint32_t color = getColor( fy*y );

			for (uint32_t x=0; x<ImageSize.Width; x++)
			{
				tmp->setPixel( x,y,color );
			}
		}

	}
	// horizontal filling
	else
	{
		const float32_t fx = 1.0f / (float32_t)w ;

		for (uint32_t x=0; x<ImageSize.Width; x++)
		{
			uint32_t color = getColor( fx*x );

			for (uint32_t y=0; y<ImageSize.Height; y++)
			{
				tmp->setPixel( x,y,color );
			}
		}
	}

//	#if _DEBUG
//		os::Printer::log( "finish image filling with LinearColorGradient", ELL_INFORMATION );
//	#endif // _DEBUG

	return tmp;
}

#endif