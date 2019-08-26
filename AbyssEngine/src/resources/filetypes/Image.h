#pragma once
#include <utility>
#include <optional>
#include "../file/File.h"
#include "../file/FileException.h"
//#include <FreeImage.h>
#include <SOIL2.h>
#include <stb_image.h>

namespace abyssengine {
	namespace resources {
		class Image : public File<Image>
		{
			friend class FileBase;
		private:
			unsigned char* pixels;
			int width, height;

			Image(const Path& path) : File(path)
			{
				std::string pathStr = path.getFullPath();
				
				stbi_set_flip_vertically_on_load(true);
				pixels = stbi_load(pathStr.c_str(), &width, &height, 0, STBI_rgb_alpha);
			}
		public:
			const unsigned char* const getPixels() const { return pixels; }

			size_t getWidth() const { return width; }
			size_t getHeight() const { return height; }

			bool suitableAsDefaultFor(const Path & originallyRequested) const override { return originallyRequested.name == "Default" || originallyRequested.name == "default"; };
		};
	}
}