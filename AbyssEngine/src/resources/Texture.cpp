#include <iostream>
#include <algorithm>
#include "Texture.h"
#include "../utils/FileUtils.h"
#include "../utils/ImageUtils.h"

namespace abyssengine {
	//std::vector<Texture*> Texture::atlases;
	//bool Texture::initialized = false;
	//
	//Texture::Texture(const std::string& path, unsigned int spriteSize) : path(path), spriteSize(spriteSize)
	//{
	//	std::vector<unsigned char> pixels;
	//
	//	unsigned int width, height;
	//	ImageUtils::load_image(path, width, height, pixels);
	//
	//	this->width = width;
	//	this->height = height;
	//
	//	this->textureID = load(pixels);
	//
	//	this->hpcX = (1.0f / width) / 2.0f;
	//	this->hpcY = (1.0f / height) / 2.0f;
	//}
	//
	//GLuint Texture::load(std::vector<unsigned char>& pixels)
	//{
	//	//unsigned int width, height;
	//	//
	//	//load_image(path, width, height, pixels);
	//	//
	//	//this->width = width;
	//	//this->height = height;
	//	GLuint newTextureID;
	//
	//	glGenTextures(1, &newTextureID);
	//	glBindTexture(GL_TEXTURE_2D, newTextureID);
	//	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
	//
	//	glBindTexture(GL_TEXTURE_2D, 0);
	//
	//	return newTextureID;
	//}
	//
	//void Texture::bind() const
	//{
	//	glBindTexture(GL_TEXTURE_2D, textureID);
	//}
	//
	//void Texture::unbind() const
	//{
	//	glBindTexture(GL_TEXTURE_2D, 0);
	//}
	//
	//unsigned int Texture::getWidth() const
	//{
	//	return width;
	//}
	//
	//unsigned int Texture::getHeight() const
	//{
	//	return height;
	//}
	//
	//std::vector<math::vec2> Texture::getTextureCoordinates(unsigned int index) // Returns in order: Top right, bottom right, bottom left, top left.
	//{
	//	std::vector<math::vec2> textureCoordinates;
	//
	//	int columns = (width / spriteSize - width % spriteSize);
	//	int rows = (height / spriteSize - height % spriteSize);
	//
	//	int column = (index % columns);
	//	int row = (index - column) / columns;
	//
	//	// Finds the coordinates of the texture in pixelspace
	//	int x = column * spriteSize;
	//	int y = (rows - row) * spriteSize - spriteSize;
	//
	//	// Finds the x and y components and adds the size of the sprite, which is used to contruct the squares 4 corners
	//	int xs = x + spriteSize;
	//	int ys = y + spriteSize;
	//
	//	// Normalises the coordinates and adds half pixel correction
	//	float xn = (x + hpcX) / (float)width;
	//	float yn = (y + hpcY) / (float)height;
	//	float xsn = (xs - hpcX) / (float)width;
	//	float ysn = (ys - hpcY) / (float)height;
	//
	//	// Texture coordinates are rotated by 90 degrees, as lodepng loads images in a different orientation than opengl.
	//	textureCoordinates.push_back(math::vec2(xn, yn));
	//	textureCoordinates.push_back(math::vec2(xsn, yn));
	//	textureCoordinates.push_back(math::vec2(xsn, ysn));
	//	textureCoordinates.push_back(math::vec2(xn, ysn));
	//
	//	return textureCoordinates;
	//}
	//
	//void Texture::loadAtlases()
	//{
	//	// Get paths for all atlases in TEXTURE_ATLAS_PATH, and sort names by alphabetical order.
	//	std::vector<std::string> paths = FileUtils::getFilenamesInDir(TEXTURE_ATLAS_PATH, true, true);
	//	std::sort(paths.begin(), paths.end());
	//
	//	// Initialize each textureatlas, their id is their position in atlases vector.
	//	for (size_t i = 0; i < paths.size(); i++)
	//		atlases.push_back(new Texture(paths.at(i), SPRITE_SIZE));
	//}
	//
	//Texture* Texture::getAtlas(unsigned short atlasId)
	//{
	//	if (atlasId < 0 || atlasId >= atlases.size())
	//		std::cout << "Attempted to get atlas by invalid atlasId!" << std::endl;
	//	return atlases.at(atlasId);
	//	return nullptr;
	//}
	//
	//GLuint Texture::getTextureID() {
	//	return textureID;
	//}
}