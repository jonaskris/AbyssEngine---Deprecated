#pragma once
#include <GL/glew.h>
#include <vector>
#include <string>
#include "Resource.h"
#include "../utils/ImageUtils.h"
#include "../math/vec2.h"
#include "../utils/UtilsSemanticTypes.h"

namespace abyssengine {
	class Texture : public Resource
	{
	protected:
		size_t width = 0, height = 0;
		GLuint textureId = 0;
	public:
		Texture(const Path& path) : Resource(path)
		{
			std::vector<unsigned char> pixels;
			ImageUtils::load_image(path, width, height, pixels);

			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);
			//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
			
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		size_t getWidth() const
		{
			return width;
		}
	
		size_t getHeight() const
		{
			return height;
		}

		GLuint getTextureId() const
		{
			return textureId;
		}

		bool operator<(const Texture& other) const
		{
			return textureId < other.textureId;
		}

	//public:
	//	static void loadAtlases();
	//	static Texture* getAtlas(unsigned short atlasId);
	//	static std::vector<Texture*> atlases;
	//private:
	//	std::string path;
	//	std::string name;
	//	GLuint textureID;
	//	GLsizei width, height;
	//	unsigned int spriteSize;
	//private:
	//	float hpcX; // Half pixel correction to avoid bleeding between individual textures
	//	float hpcY;
	//public:
	//	Texture(const std::string& path, unsigned int spriteSize);
	//
	//	GLuint load(std::vector<unsigned char>& pixels);
	//
	//	std::vector<math::vec2> getTextureCoordinates(unsigned int textureIndex);
	//	GLuint getTextureID();
	//
	//	void bind() const;
	//	void unbind() const;
	//
	//	inline unsigned int getWidth() const;
	//	inline unsigned int getHeight() const;
	//private:
	//	static bool initialized;
	};
}