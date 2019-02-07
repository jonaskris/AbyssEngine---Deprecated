#include <iostream>
#include "TextureAtlas.h"
#include "../utils/ImageLoader.h"

namespace abyssengine {
	TextureAtlas* TextureAtlas::atlases[Atlas::MAX] = {};
	bool TextureAtlas::initialized = false;

	const std::string TextureAtlas::atlasPaths[] =
	{
		"testSheet1.png",
		"testSheet2.png"
	};

	TextureAtlas::TextureAtlas(const std::string& path, unsigned int spriteSize)
	{
		this->path = path;
		this->spriteSize = spriteSize;
		load();
		calculateHPC();
	}

	void TextureAtlas::load()
	{
		unsigned int width, height;
		size_t in_size;
		std::vector<unsigned char> pixels;

		load_image(path, width, height, in_size, pixels);

		this->width = width;
		this->height = height;

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);


		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void TextureAtlas::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	void TextureAtlas::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	inline unsigned int TextureAtlas::getWidth() const
	{
		return width;
	}

	inline unsigned int TextureAtlas::getHeight() const
	{
		return height;
	}

	void TextureAtlas::getTextureCoordinates(int index, std::vector<math::vec2>* textureCoordinates) // Returns in order: Top right, bottom right, bottom left, top left.
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

		textureCoordinates->clear();

		// Texture coordinates are rotated by 90 degrees, as lodepng loads images in a different rotation than opengl.
		textureCoordinates->push_back(math::vec2(xn, ysn));
		textureCoordinates->push_back(math::vec2(xn, yn));
		textureCoordinates->push_back(math::vec2(xsn, yn));
		textureCoordinates->push_back(math::vec2(xsn, ysn));

	}

	void TextureAtlas::calculateHPC() {
		hpcX = (1.0f / width) / 2.0f;
		hpcY = (1.0f / height) / 2.0f;
	}

	void TextureAtlas::loadAtlases()
	{
		for (int i = 0; i < Atlas::MAX; i++) {
			atlases[i] = new TextureAtlas((TEXTURE_ATLAS_PATH + atlasPaths[i]).c_str(), SPRITE_SIZE);
		}
	}

	void TextureAtlas::getTextureCoordinates(int index, Atlas type, std::vector<math::vec2>* textureCoordinates)
	{
		if (type == MAX) {
			std::cout << "MAX is not a textureAtlas you can load!" << std::endl;
			return;
		}
		atlases[type]->getTextureCoordinates(index, textureCoordinates);
	}

	TextureAtlas* TextureAtlas::getAtlas(Atlas type)
	{
		return atlases[type];
	}

	GLuint TextureAtlas::getTextureID() {
		return textureID;
	}
}