#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "UtilsSemanticTypes.h"

namespace abyssengine {
	class FileUtils
	{
	public:
		static std::string read_file(const char* filepath);

		static std::vector<std::string> read_file_lines(const char* filepath);

		static std::vector<Path> getFilenamesInDir(std::string path);
	};
}