#pragma once
#include <GL/glew.h>
#include <vector>
#include "../resource/Resource.h"
#include "../resource/ResourceException.h"
#include "../resourcemanager/ResourceManager.h"
#include "Texture.h"
#include "../filetypes/Json.h"
#include "../../math/Linalg.h"

namespace abyssengine {
	namespace resources {
		/*
			A texture atlas is a spesialization of texture.

			The Json should be in the format of an image and the width(i) and height(i) of tiles. i is optional.
			If width or height is not specified, defaulted to 1.
			If texture is not specified, defaulted to json file name.
			The Json should have .texa extension.
			Example:
			{
				"texture": "image.png",
				"widthi" : 3
				"height" : 4
			}
		*/
		class TextureAtlas : public Resource<TextureAtlas>
		{
			friend class ResourceBase;
		private:
			GLuint textureID = 0;
			size_t widthi = 1, heighti = 1;
			size_t spriteSize;

			std::vector<std::vector<math::vec2f>> uvs;

			TextureAtlas(const Json& json) : Resource(json.getPath())
			{
				const nlohmann::json jsonObj = json.getJsonObject();

				nlohmann::json jsonTexture = jsonObj["texture"];

				Texture* texture = nullptr;

				if (jsonTexture.is_string()) {
					texture = ResourceManager::getInstance()->getResource<Texture>(jsonTexture.get<std::string>());
					if (!texture)
						throw ResourceCreationException(std::string("Couldent find texture: ") + jsonTexture.get<std::string>() + std::string(" for texture atlas!"));
				} else {
					Path path = json.getPath();
					texture = ResourceManager::getInstance()->getResource<Texture>(path.name + path.extension);
					if (!texture)
						throw ResourceCreationException(std::string("Couldent find texture: ") + path.name + path.extension + std::string(" for texture atlas!"));
				}

				textureID = texture->getTextureID();

				if (jsonObj["widthi"].is_number_unsigned())
					widthi = jsonObj["widthi"].get<size_t>();
				else if (jsonObj["width"].is_number_unsigned())
					widthi = jsonObj["width"].get<size_t>();

				if (jsonObj["heighti"].is_number_unsigned())
					heighti = jsonObj["heighti"].get<size_t>();
				else if (jsonObj["height"].is_number_unsigned())
					heighti = jsonObj["height"].get<size_t>();

				spriteSize = texture->getHeight() / heighti;

				float hpcX = (1.0f / widthi) / 2.0f;
				float hpcY = (1.0f / heighti) / 2.0f;

				uvs.reserve(widthi * heighti);

				for (size_t i = 0; i < widthi * heighti; i++)
				{
					int column = (i % widthi);
					int row = (i - column) / widthi;

					// Finds the coordinates of the texture in pixelspace
					int x = column * spriteSize;
					int y = (heighti - row) * spriteSize - spriteSize;

					// Finds the x and y components and adds the size of the sprite, which is used to contruct the squares 4 corners
					int xs = x + spriteSize;
					int ys = y + spriteSize;

					// Normalises the coordinates and adds half pixel correction
					float xn = (x + hpcX) / (float)texture->getWidth();
					float yn = (y + hpcY) / (float)texture->getHeight();
					float xsn = (xs - hpcX) / (float)texture->getWidth();
					float ysn = (ys - hpcY) / (float)texture->getHeight();

					// Texture coordinates are rotated by 90 degrees, as lodepng loads images in a different orientation than opengl.
					uvs.push_back(std::vector<math::vec2f>{ math::vec2f(xn, yn), math::vec2f(xsn, yn), math::vec2f(xsn, ysn), math::vec2f(xn, ysn) });
				}


			}
		public:
			GLuint getTextureID() const { return textureID; }
			size_t getWidthi() const { return widthi; }
			size_t getHeighti() const { return heighti; }
			std::vector<math::vec2f> getUV(const size_t & index) const { return uvs.at(index % (widthi * heighti)); };
		};
	}
}