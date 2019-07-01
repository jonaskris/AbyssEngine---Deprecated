#pragma once
#include <string>
#include "../utils/UtilsSemanticTypes.h"

namespace abyssengine {
	class Resource
	{
	private:
		Path path; // With filename
		std::string filename; // With extension
	public:
		Resource(const Path& path) : path(path) {};

		Path getPath()
		{
			return path;
		}
	};
}