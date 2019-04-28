#pragma once
#include <GL/glew.h>
#include <vector>
#include <string>
#include "../math/vec2.h"


#define SPRITE_SIZE 32
#define TEXTURE_ATLAS_PATH std::string("../Resources/TextureAtlases/")

namespace abyssengine {
	class TextureAtlas
	{
	public:
		//enum Atlas { TESTSHEET, TESTSPRITE, MAX };
		static void loadAtlases();
		//static std::vector<math::vec2> getTextureCoordinates(unsigned short atlasId, unsigned short textureIndex);
		static TextureAtlas* getAtlas(unsigned short atlasId);
		static std::vector<TextureAtlas*> atlases;
	private:
		std::string path;
		GLuint textureID;
		GLsizei width, height;
		unsigned int spriteSize;
	private:
		float hpcX; // Half pixel correction to avoid bleeding between individual textures
		float hpcY;
	public:
		TextureAtlas(const std::string& path, unsigned int spriteSize);

		GLuint load(std::vector<unsigned char>& pixels);

		std::vector<math::vec2> getTextureCoordinates(unsigned int textureIndex);
		GLuint getTextureID();

		void bind() const;
		void unbind() const;

		inline unsigned int getWidth() const;
		inline unsigned int getHeight() const;
	private:
		static bool initialized;
		//static const std::string atlasPaths[Atlas::MAX];
	};
}