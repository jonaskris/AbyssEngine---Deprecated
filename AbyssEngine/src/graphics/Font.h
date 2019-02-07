#pragma once
#include <vector>
#include <string>
//#include <ft2build.h>
//#include FT_FREETYPE_H
#include "../../ext/freetype-gl/freetype-gl.h"
//#include <ft2build.h>

#define FONT_ATLAS_SIZE 512
#define FONT_BIT_DEPTH 2
#define FONT_DEFAULT_SIZE 32.0f
#define FONT_PATH "../Resources/Fonts/"

namespace abyssengine {
	class Font
	{
	public:
		size_t getFontID();
		~Font();
	private:
		size_t fontID;
		const char* path;
		float size;

		ftgl::texture_font_t* font;
		ftgl::texture_atlas_t* atlas;

		Font(const char* path, float size);
		void load();
	private:
		static std::vector<Font*> fonts;
		static bool initialized;
		static const wchar_t* defaultGlyphs;
	public:
		static Font* getFont(unsigned short index, float size);
		static void initFonts();
	};
}