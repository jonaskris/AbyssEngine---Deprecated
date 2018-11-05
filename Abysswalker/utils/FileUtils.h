#pragma once
#include <iostream>
#include <fstream>
#include <string>

namespace FileUtils {
	inline std::string read_file(const char* filepath)
	{
		std::ifstream file;
		file.open(filepath);
		
		std::string file_contents;
		std::string string;
		while (std::getline(file, string))
		{
			file_contents += string + "\n";
		}

		file.close();
		return file_contents;
	}
}
