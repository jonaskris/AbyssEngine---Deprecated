#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "../Path.h"
#include "../File/File.h"
#include "../Resource/Resource.h"

namespace abyssengine {
	namespace resources {
		class ResourceManager
		{
		private:
			static ResourceManager* instance;
		private:
			std::vector<Path> paths;
			std::vector<FileBase*> files;
			std::vector<ResourceBase*> resources;

			ResourceManager(const std::string& path);
			void init(const std::string& path);
		public:
			/*
				path: path to directory that contains all resources.
			*/
			static ResourceManager* initInstance(const std::string& path);

			static ResourceManager* getInstance();
		public:
			template <typename FileType>
			FileType* getFile(const std::string& path)
			{
				Path pathObj(path);

				// Attempt to find file.
				for (auto it = files.begin(); it != files.end(); it++)
					if (pathObj.isSubset((*it)->getPath()) && (*it)->getFileTypeIdentifier() == utils::TypeIdentifier<FileType>::getIdentifier())
						return static_cast<FileType*>(*it);

				// If not found, attempt to load file from the path
				FileBase * newFile = FileBase::newFile(pathObj);
				if (newFile)
				{
					files.push_back(newFile);
					paths.push_back(pathObj);
					return static_cast<FileType*>(newFile);
				}

				// If failed to load file, attempt to find a suitable default.
				for (auto it = files.begin(); it != files.end(); it++)
					if ((*it)->suitableAsDefaultFor(pathObj))
						return static_cast<FileType*>(*it);

				// If no suitable default file is found, return nullptr.
				return nullptr;
			}

			template <typename ResourceType>
			ResourceType* getResource(const std::string& path)
			{
				Path pathObj(path);

				for (auto it = resources.begin(); it != resources.end(); it++)
					if (pathObj.isSubset((*it)->getPath()) && (*it)->getResourceTypeIdentifier() == utils::TypeIdentifier<ResourceType>::getIdentifier())
						return static_cast<ResourceType*>(*it);
				return nullptr;
				// Attempt to find resource.
					// If not found, attempt to find a suitable default. Suitable default resources are marked with default.
						// If no suitable default resource is found, return nullptr.
				/// When a resource is made, an attempt should be made to mark it as default. (For example if a gltf file is named default/Default, the whole resource is marked as default.
			}

			template <typename ResourceType>
			ResourceType* submitGeneratedResource(ResourceType* resource)
			{
				resources.push_back(resource);
				return resource;
			}
		};
	}
}