#pragma once
#include <GL/glew.h>
#include "../file/File.h"
#include "../filetypes/Image.h"
#include "../resource/Resource.h"

namespace abyssengine {
	namespace resources {
		class Texture : public Resource<Texture>
		{
			friend class ResourceBase;
		private:
			GLuint textureID = 0;
			unsigned int width, height;

			Texture(const Image& image) : Resource(image.getPath()), width(image.getWidth()), height(image.getHeight())
			{
				glGenTextures(1, &textureID);
				glBindTexture(GL_TEXTURE_2D, textureID);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixels());

				glBindTexture(GL_TEXTURE_2D, 0);
			}
		public:
			GLuint getTextureID() const { return textureID; }
			size_t getWidth() const { return width; }
			size_t getHeight() const { return height; }
		};
	}
}