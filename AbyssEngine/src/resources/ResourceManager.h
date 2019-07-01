#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "Texture.h"
#include "TextureAtlas.h"

#define RESOURCE_LOCATION std::string("../Resources")
#define TEXTURE_LOCATION std::string("/Images/Textures")
#define TEXTURE_ATLAS_LOCATION std::string("/Images/TextureAtlases")

namespace abyssengine {
	class ResourceManager
	{
	private:
	//	//std::vector<Texture> textures;
		static std::unordered_map<std::string, TextureAtlas*> textureAtlases;
		static ResourceManager* instance;
	//
	ResourceManager();
	public:
		static ResourceManager* getInstance();
	
	
	
		/*
			Todo: Return default resource (Error sound, Debug texture etc) if resource not found.
		*/
		template <typename ResourceType>
		ResourceType* getResource(const std::string& key)
		{
			try {
				if constexpr (std::is_same<ResourceType, TextureAtlas>::value)
				{
					return textureAtlases.at(key);
				}
				else {
					return nullptr;
				}
			} catch (const std::out_of_range&) {
				return nullptr;
			}
		}
	};
}