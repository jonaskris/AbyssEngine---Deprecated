#pragma once
#include <string>
#include <vector>
#include <filesystem>

namespace abyssengine {
	std::vector<std::string> getFilenamesInDir(std::string path, bool withExtension, bool withPath)
	{
		namespace fs = std::filesystem;
		std::vector<std::string> returnVector;

		for (const auto & entry : fs::directory_iterator(path))
		{
			if (withExtension) {
				returnVector.push_back(entry.path().filename().generic_string());
			}
			else {
				returnVector.push_back(entry.path().stem().generic_string());
			}
			returnVector.back() = path + returnVector.back();
		}

		//std::cout << entry.path() << std::endl;

		return returnVector;
	}
}