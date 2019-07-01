#pragma once
#include <string>

namespace abyssengine {
	struct Path
	{
		std::string path;
		std::string name;
		std::string extension;

		Path(const std::string& path, const std::string& name, const std::string& extension) : path(path), name(name), extension(extension) {};

		std::string getFullPath() const
		{
			return path + '/' + name + extension;
		}
	};
}