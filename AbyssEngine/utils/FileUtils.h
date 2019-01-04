#pragma once
#include <iostream>
#include <fstream>
#include <string>

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

inline std::vector<std::string> read_file_lines(const char* filepath)
{
	std::ifstream file;
	file.open(filepath);

	std::vector<std::string> file_contents;
	std::string string;
	while (std::getline(file, string))
	{
		file_contents.push_back(string);
	}

	file.close();
	return file_contents;
}