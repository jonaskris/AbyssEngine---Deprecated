#include <vector>
#include "ResourceManager.h"

#include "../utils/UtilsSemanticTypes.h"
#include "../utils/FileUtils.h"

namespace abyssengine {
	ResourceManager* ResourceManager::instance = NULL;
	std::unordered_map<std::string, TextureAtlas*> ResourceManager::textureAtlases;

	ResourceManager::ResourceManager()
	{
		// Get paths for all atlases in TEXTURE_ATLAS_PATH, and sort names by alphabetical order.
		std::vector<Path> paths = FileUtils::getFilenamesInDir(RESOURCE_LOCATION + TEXTURE_ATLAS_LOCATION);
		//std::sort(paths.begin(), paths.end());
	
		// Initialize each textureatlas, their id is their position in atlases vector.
		for (size_t i = 0; i < paths.size(); i++)
			textureAtlases[paths.at(i).name] = new TextureAtlas(paths.at(i));

	};
	
	ResourceManager* ResourceManager::getInstance()
	{
		if (!instance)
			instance = new ResourceManager();
		return instance;
	}
}