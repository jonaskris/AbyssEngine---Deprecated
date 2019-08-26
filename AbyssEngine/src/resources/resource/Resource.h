#pragma once
#include <string>
#include "../../utils/TypeIdentifier.h"
#include "../file/File.h"
#include "../Path.h"

namespace abyssengine {
	namespace resources {


		/*
			Resources are directably usable by the engine in contrary to files which are just data containers.

			A resource is instantiated from one file defined by the type.
			An instantiating resource can request other files and resources as needed.
		*/
		class ResourceBase
		{
		private:
			const Path path;
		protected:
			ResourceBase(const Path& path) : path(path) { };
		public:
			const Path& getPath() const
			{
				return path;
			}

			virtual size_t getResourceTypeIdentifier() const = 0;
			static ResourceBase* newResource(FileBase* const file);

		};

		template <typename ResourceType>
		class Resource : public ResourceBase, public utils::TypeIdentifier<ResourceType>
		{
		protected:
			Resource(const Path& path) : ResourceBase(path) { };
		private:
			size_t getResourceTypeIdentifier() const override { return utils::TypeIdentifier<ResourceType>::getIdentifier(); }
		};
	}
}