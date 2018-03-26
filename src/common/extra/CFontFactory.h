#ifndef __IRR_C_FONT_FACTORY_H_INCLUDED__
#define __IRR_C_FONT_FACTORY_H_INCLUDED__

//#include <irrlicht.h>
//
//#include <fstream>
//#include <ft2build.h>
//#include FT_FREETYPE_H
//#include FT_IMAGE_H
//#include FT_OUTLINE_H
//#include FT_RENDER_H
//
////#include <freetype/freetype.h>
////#include <freetype/fterrors.h>
////#include <freetype/ftmoderr.h>
////#include <freetype/ftsystem.h>
////#include <freetype/ftimage.h>
////#include <freetype/fttypes.h>
////#include <freetype/ftlist.h>
////#include <freetype/ftoutln.h>
////#include <freetype/ftsizes.h>
////#include <freetype/ftmodapi.h>
////#include <freetype/ftrender.h>
////#include <freetype/t1tables.h>
////#include <freetype/ttnameid.h>
////#include <freetype/tttables.h>
////#include <freetype/tttags.h>
////#include <freetype/ftbdf.h>
////#include <freetype/ftcid.h>
////#include <freetype/ftgzip.h>
////#include <freetype/ftlzw.h>
////#include <freetype/ftbzip2.h>
////#include <freetype/ftwinfnt.h>
////#include <freetype/ftglyph.h>
////#include <freetype/ftbitmap.h>
////#include <freetype/ftbbox.h>
////#include <freetype/ftcache.h>
////#include <freetype/ftmm.h>
////#include <freetype/ftsnames.h>
////#include <freetype/ftpfr.h>
////#include <freetype/ftstroke.h>
////#include <freetype/ftsynth.h>
////#include <freetype/ftxf86.h>
////#include <freetype/fttrigon.h>
////#include <freetype/ftlcdfil.h>
////#include <freetype/ttunpat.h>
////#include <freetype/ttunpat.h>
////#include <freetype/ftgasp.h>
////#include <freetype/ftadvanc.h>
////#include <freetype/fterrdef.h>
//
//irr::video::SColor  dbBlendColor32( const irr::video::SColor& src1, const irr::video::SColor& src2);
//void                dbDrawGlyph( irr::video::IImage* image, FT_Bitmap* bitmap, const irr::video::SColor& color, FT_Int x, FT_Int y);
//
//class CFont;
//class CGlyph;
//
//struct SFontContext
//{
//	SFontContext(IrrlichtDevice* device)
//	: Device(device)
//	{
//		if (Device)
//			Logger = Device->getLogger();
//
//		if (Logger)
//			Logger->log("CFontFactory::CFontFactor()", ELL_INFORMATION);
//
//		FT_Error error = FT_Init_FreeType(Library);
//		if (Logger)
//			Logger->log(Print("FT_Init_FreeType(%d) = %d", Library, error).c_str(), ELL_INFORMATION);
//
//		FT_Int major, minor, patch;
//		FT_Library_Version( *Library, &major, &minor, &patch);
//		if (Logger)
//			Logger->log(Print("FT_Library_Version(%d, %d, %d)", major, minor, patch).c_str(), ELL_INFORMATION);
//	}
//	~SFontContext()
//	{
//		if (Logger)
//			Logger->log(Print("CFontFactory::~CFontFactory()").c_str(), ELL_INFORMATION);
//
//		FT_Error error;
//		if (Library)
//			error = FT_Done_FreeType(*Library);
//
//		if (Logger)
//			Logger->log(Print("FT_Done_FreeType(*%d) = %d;", Library, error).c_str(), ELL_INFORMATION);
//	}
//
//	FT_Library *Library;
//    IrrlichtDevice* Device;
//    ILogger* Logger;
//};
//
//extern SFontContext* gFC;
//
//class CFont : public IGUIFont
//{
//public:
//	//! Draws some text and clips it to the specified rectangle if wanted.
//	virtual void draw(const core::stringw& text, const core::rect<s32>& position,
//		video::SColor color, bool hcenter=false, bool vcenter=false,
//		const core::rect<s32>* clip=0) = 0;
//
//	//! Calculates the width and height of a given string of text.
//	virtual core::dimension2d<u32> getDimension(const wchar_t* text) const = 0;
//
//	//! Calculates the index of the character in the text which is on a specific position.
//	virtual s32 getCharacterFromPos(const wchar_t* text, s32 pixel_x) const = 0;
//
//	//! Returns the type of this font
//	virtual EGUI_FONT_TYPE getType() const { return EGFT_CUSTOM; }
//
//	//! Sets global kerning width for the font.
//	virtual void setKerningWidth (s32 kerning) = 0;
//
//	//! Sets global kerning height for the font.
//	virtual void setKerningHeight (s32 kerning) = 0;
//
//	//! Gets kerning values (distance between letters) for the font. If no parameters are provided,
//	virtual s32 getKerningWidth(const wchar_t* thisLetter=0, const wchar_t* previousLetter=0) const = 0;
//
//	//! Returns the distance between letters
//	virtual s32 getKerningHeight() const = 0;
//
//	//! Define which characters should not be drawn by the font.
//	virtual void setInvisibleCharacters( const wchar_t *s ) = 0;
//
//	//! END OF IRRLICHT INTERFACE
//
//    CFont(const io::path& file="Arial.ttf", s32 size)
//    : Face(0)
//	{
//		// print info
//		if (gFC && gFC->Logger)
//			gFC->Logger->log(Print("CFont::CFont(%s, %d)", file.c_str(), size), ELL_INFORMATION);
//
//		// load font from file
//		FT_Error error = FT_New_Face( gFC->Library, file.c_str(), 0, Face);
//
//		// print info
//		if (gFC && gFC->Logger)
//			gFC->Logger->log(Print("FT_New_Face() = %d", error), (error) : ELL_INFORMATION);
//
//		// set pixel size
//		error = FT_Set_Pixel_Sizes(Face,0,size);   // pixel_height
//
//		// print info
//		if (gFC && gFC->Logger)
//			gFC->Logger->log(Print("FT_Set_Pixel_Sizes(%d,0,%d) = %d", Face, size, error), (error) : ELL_INFORMATION);
//
//		// select charmap
//		// As of FreeType 2.1: only a UNICODE charmap is automatically activated.
//		// If no charmap is activated automatically, just use the first one.
//		if ( Face->charmap == 0 && Face->num_charmaps > 0 )
//			FT_Select_Charmap( Face, Face->charmaps[0]->encoding );
//
//	}
//
//    CFont(const CFont& fontToCopy)
//    {
//		if (gFC && gFC->Logger)
//			gFC->Logger->log("CFont::CFont(copyctr)", ELL_INFORMATION);
//    }
//
//    ~CFont()
//    {
//    	// print info
//		if (gFC && gFC->Logger)
//			gFC->Logger->log("CFont::~CFont()", ELL_INFORMATION);
//
//		FT_Error error = FT_Done_Face(Face);
//    }
//
//	void Test()
//	{
//		FT_Set_Char_Size( face, h << 6, h << 6, 96, 96);
//	}
//
//	FT_BBox cache(wchar_t wc)
//	{
//		FT_BBox bbox;
//		FT_UInt i = FT_Get_Char_Index( Face, wc );
//		if ( i == 0 )
//		  return bbox;
//
//		FT_Error error = FT_Load_Glyph( Face, i, FT_LOAD_DEFAULT );
//		if ( error != 0 )
//		  return bbox;
//
//		FT_Glyph glyph;
//		error = FT_Get_Glyph( Face->glyph, &glyph );
//		if ( error != 0 )
//		  return bbox;
//
//		FT_BBox ft_bbox;
//		FT_Glyph_Get_CBox( glyph, ft_glyph_bbox_unscaled, &ft_bbox );
//
//		FT_Done_Glyph( glyph );
//
//		bbox = ft_bbox;
//		bbox.advance_ = Face->glyph->advance;
//
//		return bbox;
//	}
//
//	createImage(const irr::core::stringw& txt, const irr::video::SColor& color, bool AntiAliased)
//	{
//		irr::video::IImage* img=0;
//		if (!Face) return img;
//		if (!gFC) return img;
//		if (!gFC->Device) return img;
//		if (!gFC->Library) return img;
//
//		irr::video::IVideoDriver* Driver = Device->getVideoDriver();
//
//		FT_Render_Mode mode;
//		if (AntiAliased)
//			mode = FT_RENDER_MODE_NORMAL; // 8bit no cleartype
//		else
//			mode = FT_RENDER_MODE_MONO; // 1bit no cleartype
//
//		FT_Error 	error;
//		FT_UInt     index;
//		irr::s32 	x = 0;
//		irr::s32 	y = 0;
//
//		for (u32 c = 0; c < txt.size(); c++ )
//		{
//			index = FT_Get_Char_Index( Face, txt[c] );
//			error = FT_Load_Glyph( Face, index, FT_LOAD_DEFAULT );
//			if ( error )
//			{
//				continue;  /// ignore errors
//			}
//
//			error = FT_Render_Glyph( Face->glyph, mode );
//			if ( error )
//			{
//				continue;  /// ignore errors
//			}
//			// increment pen position
//			x += Face->glyph->advance.x >> 6; // mal 64
//			y += Face->glyph->advance.y >> 6; // mal 64
//		}
//
//		irr::video::IImage* image = driver->createImage(irr::video::ECF_A8R8G8B8, fullSize);
//
//		// now, draw to our target surface
//		dbDrawGlyph(image, &glyph->bitmap, color, pen_x + glyph->bitmap_left, pen_y - glyph->bitmap_top );
//		return img;
//	}
//
//private:
//	FT_Face* Face;
//};
//
//////////////////////////////////////////////////////////////////////////////////////////
//////! @fn Main Drawing Function for texts on software surfaces (images)
//////! @brief drawText to Irrlicht Image or Texture
//////! @param Irrlicht-Image, that must exist
//////! @param Position X
//////! @param Position Y
//////! @param text as unicode u16 chars (wchar_t)
//////! @param argb color ( alpha value can be any, is set by freetype if antialiased or not)
//////! @param AntiAlised (false == 1 bit monochrome text, true == 8 bit greyscale outlines)
//////! @param Horizontal-Align (LEFT, CENTER, RIGHT)
//////! @param Vertical-Align (TOP, MIDDLE, BOTTOM)
//////! @return new Irrlicht-Image with transparnt background (ARGB 0x00000000)
//////////////////////////////////////////////////////////////////////////////////////////
////void
////dbFont::draw( irr::video::IImage* image, irr::s32 x, irr::s32 y, const irr::core::stringw& txt, const irr::video::SColor& color, bool AntiAliased,
////	HORIZONTAL_ALIGN align, VERTICAL_ALIGN valign)
//////////////////////////////////////////////////////////////////////////////////////////
////{
////	#ifdef FONT_LIBRARY_DEBUG
////	std::wofstream f(m_logfile.c_str(), std::ios::out | std::ios::app);
////	f<<"Font::drawText()\n";
////	f<<"\n\tText == "<<txt.c_str()<<"\n\n";
////	#endif
////	FT_Error error(0);
////	if (!ft_context.library) error+=1;
////	if (!m_face) error+=1;
////	if (!image) error+=1;
////	if (!txt.size()) error+=1;
////
////	if (error)
////	{
////	#ifdef FONT_LIBRARY_DEBUG
////		f<<"\tparameter error count == "<<error<<"\n";
////		f.close();
////	#endif
////	//	return;
////	}
////
////	#ifdef FONT_LIBRARY_DEBUG
////	irr::u32 errorCount(0);
////	#endif
////	FT_GlyphSlot  slot = m_face->glyph;  // a small shortcut
////	FT_UInt       glyph_index;
////
////	irr::u32 n;
////	irr::u32 s = txt.size();
////	irr::s32 pen_x = x;
////	irr::s32 pen_y = y;
////
////	FT_Render_Mode mode;
////	if (AntiAliased)
////		mode = FT_RENDER_MODE_NORMAL; // 8bit no cleartype
////	else
////		mode = FT_RENDER_MODE_MONO; // 1bit no cleartype
////
////	for ( n = 0; n < s; n++ )
////	{
////	#ifdef FONT_LIBRARY_DEBUG
////		f<<"\tIndex ["<<n<<"], \tChar ["<<txt[n]<<"], \t";
////	#endif
////		// Alternative
////		// load glyph image into the slot (erase previous one)
////		// error = FT_Load_Char( face, TEST[n], FT_LOAD_RENDER );
////
////		/// retrieve glyph index from character code
////		glyph_index = FT_Get_Char_Index( m_face, txt[n] );
////
////	#ifdef FONT_LIBRARY_DEBUG
////		f<<"GlyphIndex ["<<glyph_index<<"], \t";
////	#endif
////
////		/// load glyph image into the slot (erase previous one)
////		error = FT_Load_Glyph( m_face, glyph_index, FT_LOAD_DEFAULT );
////		if ( error )
////		{
////	#ifdef FONT_LIBRARY_DEBUG
////			errorCount++;
////			f<<"error, ";
////	#endif
////			continue;  /// ignore errors
////		}
////
////
////		/// convert to an [anti-]aliased bitmap
////		error = FT_Render_Glyph( m_face->glyph, mode );
////		if ( error )
////		{
////	#ifdef FONT_LIBRARY_DEBUG
////			errorCount++;
////			f<<"error, ";
////	#endif
////		 continue;  /// ignore errors
////		}
////
////	#ifdef FONT_LIBRARY_DEBUG
////		f<<"PenPos ("<<pen_x<<", "<<pen_y<<"), \t";
////		f<<"BitmapPos ("<<slot->bitmap_left<<", "<<slot->bitmap_top<<"), \t";
////		FT_Bitmap* bmp = & slot->bitmap;
////		f<<"BitmapSize ("<<bmp->width<<", "<<bmp->rows<<"), \t";
////		f<<"Advance ("<<(slot->advance.x>>6)<<", "<<(slot->advance.y>>6)<<")\n";
////	#endif
////
////		// now, draw to our target surface
////		dbDrawGlyph(image,
////							&slot->bitmap,
////							color,
////					pen_x + slot->bitmap_left,
////					pen_y - slot->bitmap_top );
////
////		// increment pen position
////		pen_x += slot->advance.x >> 6;
////		pen_y += slot->advance.y >> 6;
////	}
////
////	#ifdef FONT_LIBRARY_DEBUG
////	f<<"\ttotal error count == "<<errorCount<<"\n";
////	f.close();
////	#endif
////} /// END FUNCTION
////
//
#endif
