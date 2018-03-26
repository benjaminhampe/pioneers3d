#include "CFontFactory.h"

#include "CImageFactory.h"

#include <irrlicht.h>
#include <fstream>
#include <ft2build.h>
#include FT_FREETYPE_H

// SFontContext gFC;

////////////////////////////////////////////////////////////////////////////////////////
//void dbDrawGlyph( irr::video::IImage* image, FT_Bitmap* bitmap, const irr::video::SColor& color, FT_Int x, FT_Int y)
////////////////////////////////////////////////////////////////////////////////////////
//{
//	FT_Int i, j, p=0, q=0;
//	FT_Int x2 = x + bitmap->width;
//	FT_Int y2 = y + bitmap->rows;
//	irr::s32 W = image->getDimension().Width;
//	irr::s32 H = image->getDimension().Height;
//	for ( j=y; j<y2; j++)
//	{
//		p=-1;
//		for ( i=x; i<x2; i++)
//		{
//			p++;
//			if ( i < 0 || j < 0 || i >= W || j >= H )
//				continue;
//			irr::u8 value = bitmap->buffer[p + q * bitmap->width];
//			if (value>0)
//			{
//				irr::video::SColor c0(image->getPixel(i,j));
//				irr::video::SColor c1 = color; c1.setAlpha(value);
//				image->setPixel(i,j,dbBlendColor32(c0,c1),false);
//			}
//		}
//		q++;
//	}
//}
//

/////////////////////////////////////////////////
// class: CFont
/////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//dbFont::dbFont(const irr::io::path& font, irr::u32 size)
////////////////////////////////////////////////////////////////////////////////////////
//: m_facename(""), m_face(NULL), m_size(0,0)
//{
//	create(font, irr::core::dimension2du(0,size));
//}
//
////! @brief destructor
////!
////! @param FontFile
////! @param y-Size
////!
////////////////////////////////////////////////////////////////////////////////////////
//dbFont::~dbFont()
////////////////////////////////////////////////////////////////////////////////////////
//{
//	destroy();
//}
//
////! @brief creates a new m_logfilename like Arial_
////! @brief invokes FT_New_Face
////////////////////////////////////////////////////////////////////////////////////////
//bool
//dbFont::create(const irr::io::path& font, const irr::core::dimension2du& size)
////////////////////////////////////////////////////////////////////////////////////////
//{
//	#ifdef FONT_LIBRARY_DEBUG
//	// ... create m_logfile name ... [file.ext without path]
//	m_logfile="Font";
//
//	// search for chars '/' && '\\'
//	bool hasPath = false;
//	irr::s32 pos=font.findLast('/');
//	if (pos==-1)
//	{
//		pos=font.findLast('\\');
//		if (pos!=-1) hasPath=true;
//	}
//	else
//		hasPath=true;
//
//	// split pathpart from filename
//	if (hasPath==true)
//		m_logfile+=font.subString(pos+1, font.size()-1-pos);
//	else
//		m_logfile+=font;
//
//	m_logfile+="_";
//	m_logfile+=m_size.Width;
//	m_logfile+="_";
//	m_logfile+=m_size.Height;
//	m_logfile+=".log";
//
//	std::wofstream f(m_logfile.c_str(), std::ios::out);
//	f<<"Font::Font()\n";
//	f<<"\tfile: "<<m_facename.c_str()<<"\n";
//	f<<"\tsize: "<<m_size.Width<<" x "<<m_size.Height<<"\n";
//	#endif
//
//	// Abbruchbedingung
//	if (!ft_context.library)
//	{
//		#ifdef FONT_LIBRARY_DEBUG
//		f<<"\t\terror, no library\n";
//		f.close();
//		#endif
//		return false;
//	}
//
//	// load font from file
//	FT_Error error = FT_New_Face( ft_context.library, font.c_str(), 0, &m_face);
//
//	#ifdef FONT_LIBRARY_DEBUG
//	f<<"\tFT_New_Face()\n";
//	#endif
//
//	// Abbruchbedingung
//	if (error)
//	{
//		#ifdef FONT_LIBRARY_DEBUG
//		f<<"\t\terror "<<error;
//		if (error==FT_Err_Unknown_File_Format)
//			f<<", font not supported";
//		f<<"\n";
//		f.close();
//		#endif
//		return false;
//	}
//	#ifdef FONT_LIBRARY_DEBUG
//	f<<"\t\tsuccess\n";
//	#endif
//
//	return setSize(size);
//}
//
////////////////////////////////////////////////////////////////////////////////////////
//bool
//dbFont::destroy()
////////////////////////////////////////////////////////////////////////////////////////
//{
//	#ifdef FONT_LIBRARY_DEBUG
//	// ... log function parameters ...
//	std::wofstream f(m_logfile.c_str(), std::ios::out | std::ios::app);
//	f<<"Font::~Font()\n";
//	#endif
//	// abort
//	if (!ft_context.library)
//	{
//		#ifdef FONT_LIBRARY_DEBUG
//		f<<"\terror, no library\n";
//		f.close();
//		#endif
//		return false;
//	}
//
//	FT_Error error = FT_Done_Face(m_face);
//	if (error)
//	{
//		#ifdef FONT_LIBRARY_DEBUG
//		f<<"\terror, no face\n";
//		f.close();
//		#endif
//		return false;
//	}
//	else
//	{
//		#ifdef FONT_LIBRARY_DEBUG
//		f<<"\tsuccess, face deleted\n";
//		f.close();
//		#endif
//		return true;
//	}
//}
//
////////////////////////////////////////////////////////////////////////////////////////
//bool
//dbFont::setSize(const irr::core::dimension2du& size)
////////////////////////////////////////////////////////////////////////////////////////
//{
//	if (!m_face) return false;
//
//	//! ... set character size ...
//	// use 50pt at 100dpi
//	// error = FT_Set_Char_Size( face, 50 * 64, 0, 100, 0 );
//	#ifdef FONT_LIBRARY_DEBUG
//	std::wofstream f(m_logfile.c_str(), std::ios::out | std::ios::app);
//	f<<"Font::setSize()\n";
//	f<<"\tFT_Set_Pixel_Sizes()\n";
//	#endif
//	m_size = size;
//	FT_Error error = 0;
//
//	error = FT_Set_Pixel_Sizes(
//			m_face,   // handle to face object
//			m_size.Width,      // pixel_width
//			m_size.Height );   // pixel_height
//
//	if ( error )
//	{
//	#ifdef FONT_LIBRARY_DEBUG
//		f<<"\t\terror "<<error<<"\n";
//		f.close();
//	#endif
//		return false;
//	}
//	else
//	{
//	#ifdef FONT_LIBRARY_DEBUG
//		f<<"\t\tnew size = "<<m_size.Width<<" x "<<m_size.Height<<"\n";
//		f<<"\t\tsuccess\n";
//		f.close();
//	#endif
//		return true;
//	}
//}
//
////////////////////////////////////////////////////////////////////////////////////////
//bool
//dbFont::setSize(const irr::u32& width, const irr::u32& height)
////////////////////////////////////////////////////////////////////////////////////////
//{
//	return setSize(irr::core::dimension2du(width,height));
//}
//
////! Berechnet die Dimension eines Glyphen in Pixeln
////////////////////////////////////////////////////////////////////////////////////////
//irr::core::dimension2du
//dbFont::getGlyphSize(wchar_t c, bool AntiAliased)
////////////////////////////////////////////////////////////////////////////////////////
//{
//	irr::core::dimension2du size(0,0);
//	return size;
//}
//
////! Berechnet die Dimension eines Glyphen in Pixeln
////////////////////////////////////////////////////////////////////////////////////////
//irr::u32
//dbFont::getGlyphWidth(wchar_t c, bool AntiAliased)
////////////////////////////////////////////////////////////////////////////////////////
//{
//	irr::u32 width(0);
//	return width;
//}
//
////! Berechnet die Dimension eines Glyphen in Pixeln
////////////////////////////////////////////////////////////////////////////////////////
//irr::u32
//dbFont::getGlyphHeight(wchar_t c, bool AntiAliased)
////////////////////////////////////////////////////////////////////////////////////////
//{
//	irr::u32 height(0);
//	return height;
//}
//
////! Berechnet die Dimension eines Textes in Pixeln
////////////////////////////////////////////////////////////////////////////////////////
//irr::u32
//dbFont::getTextWidth(const irr::core::stringw& txt, bool AntiAliased)
////////////////////////////////////////////////////////////////////////////////////////
//{
//	irr::u32 width(0);
//	return width;
//}
//
////! Berechnet die Dimension eines Textes in Pixeln
////////////////////////////////////////////////////////////////////////////////////////
//irr::u32 dbFont::getTextHeight(const irr::core::stringw& txt, bool AntiAliased)
////////////////////////////////////////////////////////////////////////////////////////
//{
//	irr::u32 height(0);
//	return height;
//}
//
//
////////////////////////////////////////////////////////////////////////////////////////
////! @brief createImageFromText
////! @param IrrlichtVideoDriver
////! @param texture-width, if 0 then optimal width will be calculated
////! @param texture-width, if 0 then optimal width will be calculated
////! @param text as unicode u16 chars (wchar_t)
////! @param argb color ( alpha value can be any, is set by freetype if antialiased or not)
////! @param AntiAlised (false == 1 bit monochrome text, true == 8 bit greyscale outlines)
////! @param Horizontal-Align (LEFT, CENTER, RIGHT)
////! @param Vertical-Align (TOP, MIDDLE, BOTTOM)
////! @return new Irrlicht-Image with transparent background (ARGB 0x00000000)
////////////////////////////////////////////////////////////////////////////////////////
//irr::video::IImage*
//dbFont::getImage( irr::video::IVideoDriver* driver, const irr::core::stringw& txt, const irr::video::SColor& color, bool AntiAliased)
////////////////////////////////////////////////////////////////////////////////////////
//{
//	#ifdef FONT_LIBRARY_DEBUG
//	std::wofstream f(m_logfile.c_str(), std::ios::out | std::ios::app);
//	f<<"Font::createImageFromText()\n";
//	f<<"\n\tText == "<<txt.c_str()<<"\n\n";
//	#endif
//	irr::video::IImage* img=0;
//	if (!driver) return img;
//	if (!ft_context.library) return img;
//	if (!m_face) return img;
//	if (!txt.size()) return img;
//
//	FT_Error 	  error(0);
//	FT_GlyphSlot  glyph = m_face->glyph;  // a small shortcut
//	FT_UInt       glyph_index;
//
//	irr::u32 n;
//	irr::u32 s = txt.size();
//	irr::s32 pen_x = 0;
//	irr::s32 pen_y = 0;
//
//	FT_Render_Mode mode;
//	if (AntiAliased)
//		mode = FT_RENDER_MODE_NORMAL; // 8bit no cleartype
//	else
//		mode = FT_RENDER_MODE_MONO; // 1bit no cleartype
//
//	for ( n = 0; n < s; n++ )
//	{
//	#ifdef FONT_LIBRARY_DEBUG
//		f<<"\tIndex ["<<n<<"], \tChar ["<<txt[n]<<"], \t";
//	#endif
//
//		glyph_index = FT_Get_Char_Index( m_face, txt[n] );
//
//		error = FT_Load_Glyph( m_face, glyph_index, FT_LOAD_DEFAULT );
//		if ( error )
//		{
//			continue;  /// ignore errors
//		}
//		error = FT_Render_Glyph( m_face->glyph, mode );
//		if ( error )
//		{
//			continue;  /// ignore errors
//		}
//
//	#ifdef FONT_LIBRARY_DEBUG
//		f<<"GlyphIndex ["
//		<<glyph_index
//		<<"], \t"
//		<<"PenPos ("
//		<<pen_x
//		<<", "
//		<<pen_y
//		<<"), \t"
//		<<"BitmapPos ("
//		<<glyph->bitmap_left
//		<<", "
//		<<glyph->bitmap_top
//		<<"), \t";
//
//		FT_Bitmap* bmp = & glyph->bitmap;
//		f<<"BitmapSize ("
//		<<bmp->width
//		<<", "
//		<<bmp->rows
//		<<"), \t"
//		<<"Advance ("
//		<<(glyph->advance.x>>6)
//		<<", "
//		<<(glyph->advance.y>>6)<<")\n";
//	#endif
//
//		irr::core::dimension2du fullSize(1024,128);
//		irr::video::IImage* image = driver->createImage(irr::video::ECF_A8R8G8B8, fullSize);
//		// now, draw to our target surface
//		dbDrawGlyph(image, &glyph->bitmap, color, pen_x + glyph->bitmap_left, pen_y - glyph->bitmap_top );
//
//		// increment pen position
//		pen_x += glyph->advance.x >> 6;
//		pen_y += glyph->advance.y >> 6;
//	}
//
//	#ifdef FONT_LIBRARY_DEBUG
//	f.close();
//	#endif
//
//
//	return 0;
//}
//
////////////////////////////////////////////////////////////////////////////////////////
////! @brief createTextureFromText
////! @param IrrlichtVideoDriver
////! @param texture-width, if 0 then optimal width will be calculated
////! @param texture-width, if 0 then optimal width will be calculated
////! @param text as unicode u16 chars (wchar_t)
////! @param argb color ( alpha value can be any, is set by freetype if antialiased or not)
////! @param AntiAlised (false == 1 bit monochrome text, true == 8 bit greyscale outlines)
////! @param Horizontal-Align (LEFT, CENTER, RIGHT)
////! @param Vertical-Align (TOP, MIDDLE, BOTTOM)
////! @return new Irrlicht-Image with transparnt background (ARGB 0x00000000)
////////////////////////////////////////////////////////////////////////////////////////
//irr::video::ITexture*
//dbFont::getTexture(
//    irr::video::IVideoDriver* driver, // IRRlicht VideoDriver
//    irr::s32 w,
//    irr::s32 h,
//    const irr::core::stringw& txt,
//    const irr::video::SColor& txtcolor,
//    bool AntiAliased,
//    HORIZONTAL_ALIGN align,
//    VERTICAL_ALIGN valign)
////////////////////////////////////////////////////////////////////////////////////////
//{
//
//return 0;
//}
//
////////////////////////////////////////////////////////////////////////////////////////
////! @fn Main Drawing Function for texts on software surfaces (images)
////! @brief drawText to Irrlicht Image or Texture
////! @param Irrlicht-Image, that must exist
////! @param Position X
////! @param Position Y
////! @param text as unicode u16 chars (wchar_t)
////! @param argb color ( alpha value can be any, is set by freetype if antialiased or not)
////! @param AntiAlised (false == 1 bit monochrome text, true == 8 bit greyscale outlines)
////! @param Horizontal-Align (LEFT, CENTER, RIGHT)
////! @param Vertical-Align (TOP, MIDDLE, BOTTOM)
////! @return new Irrlicht-Image with transparnt background (ARGB 0x00000000)
////////////////////////////////////////////////////////////////////////////////////////
//void
//dbFont::draw( irr::video::IImage* image, irr::s32 x, irr::s32 y, const irr::core::stringw& txt, const irr::video::SColor& color, bool AntiAliased,
//	HORIZONTAL_ALIGN align, VERTICAL_ALIGN valign)
////////////////////////////////////////////////////////////////////////////////////////
//{
//	#ifdef FONT_LIBRARY_DEBUG
//	std::wofstream f(m_logfile.c_str(), std::ios::out | std::ios::app);
//	f<<"Font::drawText()\n";
//	f<<"\n\tText == "<<txt.c_str()<<"\n\n";
//	#endif
//	FT_Error error(0);
//	if (!ft_context.library) error+=1;
//	if (!m_face) error+=1;
//	if (!image) error+=1;
//	if (!txt.size()) error+=1;
//
//	if (error)
//	{
//	#ifdef FONT_LIBRARY_DEBUG
//		f<<"\tparameter error count == "<<error<<"\n";
//		f.close();
//	#endif
//	//	return;
//	}
//
//	#ifdef FONT_LIBRARY_DEBUG
//	irr::u32 errorCount(0);
//	#endif
//	FT_GlyphSlot  slot = m_face->glyph;  // a small shortcut
//	FT_UInt       glyph_index;
//
//	irr::u32 n;
//	irr::u32 s = txt.size();
//	irr::s32 pen_x = x;
//	irr::s32 pen_y = y;
//
//	FT_Render_Mode mode;
//	if (AntiAliased)
//		mode = FT_RENDER_MODE_NORMAL; // 8bit no cleartype
//	else
//		mode = FT_RENDER_MODE_MONO; // 1bit no cleartype
//
//	for ( n = 0; n < s; n++ )
//	{
//	#ifdef FONT_LIBRARY_DEBUG
//		f<<"\tIndex ["<<n<<"], \tChar ["<<txt[n]<<"], \t";
//	#endif
//		// Alternative
//		// load glyph image into the slot (erase previous one)
//		// error = FT_Load_Char( face, TEST[n], FT_LOAD_RENDER );
//
//		/// retrieve glyph index from character code
//		glyph_index = FT_Get_Char_Index( m_face, txt[n] );
//
//	#ifdef FONT_LIBRARY_DEBUG
//		f<<"GlyphIndex ["<<glyph_index<<"], \t";
//	#endif
//
//		/// load glyph image into the slot (erase previous one)
//		error = FT_Load_Glyph( m_face, glyph_index, FT_LOAD_DEFAULT );
//		if ( error )
//		{
//	#ifdef FONT_LIBRARY_DEBUG
//			errorCount++;
//			f<<"error, ";
//	#endif
//			continue;  /// ignore errors
//		}
//
//
//		/// convert to an [anti-]aliased bitmap
//		error = FT_Render_Glyph( m_face->glyph, mode );
//		if ( error )
//		{
//	#ifdef FONT_LIBRARY_DEBUG
//			errorCount++;
//			f<<"error, ";
//	#endif
//		 continue;  /// ignore errors
//		}
//
//	#ifdef FONT_LIBRARY_DEBUG
//		f<<"PenPos ("<<pen_x<<", "<<pen_y<<"), \t";
//		f<<"BitmapPos ("<<slot->bitmap_left<<", "<<slot->bitmap_top<<"), \t";
//		FT_Bitmap* bmp = & slot->bitmap;
//		f<<"BitmapSize ("<<bmp->width<<", "<<bmp->rows<<"), \t";
//		f<<"Advance ("<<(slot->advance.x>>6)<<", "<<(slot->advance.y>>6)<<")\n";
//	#endif
//
//		// now, draw to our target surface
//		dbDrawGlyph(image,
//							&slot->bitmap,
//							color,
//					pen_x + slot->bitmap_left,
//					pen_y - slot->bitmap_top );
//
//		// increment pen position
//		pen_x += slot->advance.x >> 6;
//		pen_y += slot->advance.y >> 6;
//	}
//
//	#ifdef FONT_LIBRARY_DEBUG
//	f<<"\ttotal error count == "<<errorCount<<"\n";
//	f.close();
//	#endif
//} /// END FUNCTION
//
////////////////////////////////////////////////////////////////////////////////////////
//irr::scene::IBillboardSceneNode*
//dbFont::createBillboard(irr::IrrlichtDevice* device)
////////////////////////////////////////////////////////////////////////////////////////
//{
//	irr::video::IVideoDriver* driver = driver;
//	irr::scene::ISceneManager* smgr = smgr;
//	if (!driver) return NULL;
//	if (!smgr) return NULL;
//	irr::scene::IBillboardSceneNode* billboard = smgr->addBillboardSceneNode();
//	if (!billboard) return NULL;
//	billboard->setMaterialTexture(0,driver->getTexture("billboard.jpg"));
//	return billboard;
//}
