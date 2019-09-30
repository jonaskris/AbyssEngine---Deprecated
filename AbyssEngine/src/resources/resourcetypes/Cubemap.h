#pragma once
#include <GL/glew.h>
#include <vector>
#include <map>
#include "../resource/Resource.h"
#include "../resource/ResourceException.h"
#include "../resourcemanager/ResourceManager.h"
#include "../filetypes/Image.h"
#include "../filetypes/Json.h"

namespace abyssengine {
	namespace resources {
		/*
			A cubemap is a spesialization of texture.

			The Json should be in the format a list with keys { left, right, bottom, top, back, front },
			with values being their respective image. Ordering does not matter.

			The Json should have .cm extension.
			Example:
			{
				"left": "left.png",
				"right": "right.png",
				"bottom": "bottom.png",
				"top": "top.png",
				"back": "back.png",
				"front": "front.png"
			}
		*/
		class Cubemap : public Resource<Cubemap>
		{
			friend class ResourceBase;
		private:
			static const inline std::map<size_t, std::string> sides = { {0, "left"}, {1, "right"}, {2, "back"}, {3, "front"}, {4, "top"}, {5, "bottom"} };
			GLuint textureID;

			Cubemap(const Json& json) : Resource(json.getPath())
			{
				const nlohmann::json jsonObj = json.getJsonObject();

				glGenTextures(1, &textureID);
				glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

				for (const auto& side : sides)
				{
					nlohmann::json jsonImage = jsonObj[side.second];
					Image* image = nullptr;

					if (jsonImage.is_string()) {
						image = ResourceManager::getInstance()->getFile<Image>(jsonImage.get<std::string>());
						if (!image)
							throw ResourceCreationException(std::string("Couldent find image: ") + jsonImage.get<std::string>() + std::string(" for cube map!"));

						glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + side.first, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixels());
					} else {
						throw ResourceCreationException(std::string("Couldent parse json: ") + json.getPath().getFullPath() + std::string(" for cube map!"));
					}
				}
			}
		public:
			GLuint getTextureID() const { return textureID; }
		};
	}
}