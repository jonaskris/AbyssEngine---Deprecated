#include <vector>
#include "ResourceManager.h"
#include "../../Defines.h"
#include "../Path.h"
#include "../filetypes/Json.h"

namespace abyssengine {
	namespace resources {
		ResourceManager* ResourceManager::instance = NULL;

		ResourceManager::ResourceManager(const std::string& path) { };

		ResourceManager* ResourceManager::initInstance(const std::string& path)
		{
			instance = new ResourceManager(path);
			instance->init(path);
			return instance;
		}

		void ResourceManager::init(const std::string& path)
		{
			/*
				Load paths to all directories and files in specified path.
			*/
			paths = Path{ path }.getChildrenRecursive();

			/*
				Load files from paths.
			*/
			for (auto it = paths.begin(); it != paths.end(); it++)
			{
				FileBase* newFile = FileBase::newFile(*it);
				if (newFile)
					files.push_back(newFile);
			}

			/*
				Load resources from files.
			*/
			for (auto it = files.begin(); it != files.end(); it++)
			{
				ResourceBase* newResource = ResourceBase::newResource(*it);
				if (newResource)
					resources.push_back(newResource);
			}

		}


		ResourceManager* ResourceManager::getInstance()
		{
			return instance;
		}
	}
}