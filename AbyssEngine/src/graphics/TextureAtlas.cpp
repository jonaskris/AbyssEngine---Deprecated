#include <iostream>
#include <algorithm>
#include "TextureAtlas.h"
#include "../utils/DirUtils.h"
#include "../utils/ImageLoader.h"

namespace abyssengine {
	std::vector<TextureAtlas*> TextureAtlas::atlases;
	//TextureAtlas* TextureAtlas::atlases[Atlas::MAX] = {};
	bool TextureAtlas::initialized = false;

	//const std::string TextureAtlas::atlasPaths[] =
	//{
	//	"testSheet1.png",
	//	"testSheet2.png"
	//};

	TextureAtlas::TextureAtlas(const std::string& path, unsigned int spriteSize) : path(path), spriteSize(spriteSize)
	{
		std::vector<unsigned char> pixels;

		unsigned int width, height;
		load_image(path, width, height, pixels);

		this->width = width;
		this->height = height;

		this->textureID = load(pixels);

		this->hpcX = (1.0f / width) / 2.0f;
		this->hpcY = (1.0f / height) / 2.0f;
	}

	GLuint TextureAtlas::load(std::vector<unsigned char>& pixels)
	{
		//unsigned int width, height;
		//
		//load_image(path, width, height, pixels);
		//
		//this->width = width;
		//this->height = height;
		GLuint newTextureID;

		glGenTextures(1, &newTextureID);
		glBindTexture(GL_TEXTURE_2D, newTextureID);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);

		glBindTexture(GL_TEXTURE_2D, 0);

		return newTextureID;
	}

	void TextureAtlas::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	void TextureAtlas::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	unsigned int TextureAtlas::getWidth() const
	{
		return width;
	}

	unsigned int TextureAtlas::getHeight() const
	{
		return height;
	}

	std::vector<math::vec2> TextureAtlas::getTextureCoordinates(unsigned int index) // Returns in order: Top right, bottom right, bottom left, top left.
	{
		int columns = (width / spriteSize - width % spriteSize);
		int rows = (height / spriteSize - height % spriteSize);

		int column = (index % columns);
		int row = (index - column) / columns;

		//Finds the coordinates of the texture in pixelspace
		int x = column * spriteSize;
		int y = row * spriteSize;

		//Finds the x and y components and adds the size of the sprite, which is used to contruct the squares 4 corners
		int xs = x + spriteSize;
		int ys = y + spriteSize;

		//Normalises the coordinates and adds half pixel correction
		float xn = x / (float)width + hpcX;
		float yn = y / (float)height + hpcY;
		float xsn = xs / (float)width - hpcX;
		float ysn = ys / (float)height - hpcY;

		std::vector<math::vec2> textureCoordinates;

		// Texture coordinates are rotated by 90 degrees, as lodepng loads images in a different orientation than opengl.
		textureCoordinates.push_back(math::vec2(xn, yn));
		textureCoordinates.push_back(math::vec2(xsn, yn));
		textureCoordinates.push_back(math::vec2(xsn, ysn));
		textureCoordinates.push_back(math::vec2(xn, ysn));

		return textureCoordinates;
	}

	void TextureAtlas::loadAtlases()
	{
		// Get paths for all atlases in TEXTURE_ATLAS_PATH, and sort names by alphabetical order.
		std::vector<std::string> paths = getFilenamesInDir(TEXTURE_ATLAS_PATH, true, true);
		std::sort(paths.begin(), paths.end());
		//for (size_t i = 0; i < paths.size(); i++)
		//{
		//	std::cout << paths.at(i) << std::endl;
		//}

		// Initialize each textureatlas, their id is their position in atlases vector.
		for (size_t i = 0; i < paths.size(); i++)
		{
			atlases.push_back(new TextureAtlas(paths.at(i), SPRITE_SIZE));
		}

		//for (int i = 0; i < Atlas::MAX; i++) {
		//	atlases[i] = new TextureAtlas((TEXTURE_ATLAS_PATH + atlasPaths[i]).c_str(), SPRITE_SIZE);
		//}
	}

	//std::vector<math::vec2>* TextureAtlas::getTextureCoordinates(unsigned short atlasId, unsigned short textureIndex)
	//{
	//	//if (type == MAX) {
	//	//	std::cout << "MAX is not a textureAtlas you can load!" << std::endl;
	//	//	return;
	//	//}
	//	atlases[type]->getTextureCoordinates(index, textureCoordinates);
	//}

	TextureAtlas* TextureAtlas::getAtlas(unsigned short atlasId)
	{
		if (atlasId < 0 || atlasId >= atlases.size())
			std::cout << "Attempted to get atlas by invalid atlasId!" << std::endl;
		return atlases.at(atlasId);
		return nullptr;
	}

	GLuint TextureAtlas::getTextureID() {
		return textureID;
	}
}