#include <iostream>
#include <string>
#include <vector>
#include "Font.h"
#include "../utils/DirUtils.h"


namespace abyssengine {
	bool Font::initialized = false;
	const wchar_t* Font::defaultGlyphs = L" !\"#$%&'()*+,-./0123456789:;<=>?"
		L"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
		L"`abcdefghijklmnopqrstuvwxyz{|}~";
	std::vector<Font*> Font::fonts;
	Font::Font(const char* path, float size)
	{
		this->path = path;
		this->size = size ? size : FONT_DEFAULT_SIZE;
		load();
	}

	Font::~Font()
	{

	}

	size_t Font::getFontID()
	{
		return fontID;
	}

	void Font::load()
	{
		atlas = ftgl::texture_atlas_new(FONT_ATLAS_SIZE, FONT_ATLAS_SIZE, FONT_BIT_DEPTH);
		font = ftgl::texture_font_new_from_file(atlas, size, path);
		size_t countMisses = ftgl::texture_font_load_glyphs(font, defaultGlyphs);
		if (countMisses != 0)
			std::cout << "Failed to pack " << countMisses << " glyphs into atlas. Too small atlas or too big/many glyphs." << std::endl;
	}

	Font* Font::getFont(unsigned short index, float size)
	{
		if (index >= fonts.size())
			std::cout << "Font " << index << " does not exist! Only fonts from 0 to " << fonts.size() << " are defined." << std::endl;

		return fonts.at(index);
	}

	void Font::initFonts()
	{
		if (initialized) {
			return;
		}

		std::vector<std::string> fontNames = getFilenamesInDir(FONT_PATH, true, true);

		for (size_t i = 0; i < fontNames.size(); i++)
		{
			fonts.push_back(new Font(fontNames.at(i).c_str(), FONT_DEFAULT_SIZE));
		}

		initialized = true;
	}
}