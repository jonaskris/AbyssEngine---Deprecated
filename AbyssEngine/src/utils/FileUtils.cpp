#include "FileUtils.h"

namespace abyssengine {
	std::string FileUtils::read_file(const char* filepath)
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

	std::vector<std::string> FileUtils::read_file_lines(const char* filepath)
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

	std::vector<Path> FileUtils::getFilenamesInDir(std::string path)
	{

		namespace fs = std::filesystem;
		std::vector<Path> returnVector;

		for (const auto& entry : fs::directory_iterator(path))
		{

			//if (withExtension) 
			//	returnVector.push_back(entry.path().filename().generic_string());
			//else
			//	returnVector.push_back(entry.path().stem().generic_string());
			//
			//if(withPath)
			//	returnVector.back() = path + std::string("/") + returnVector.back();

			std::string name = entry.path().stem().generic_string();
			std::string extension = entry.path().filename().extension().generic_string();

			//std::string extension = nameWithExtension.substr(nameWithExtension.find('.') + 1, std::string::npos);
			returnVector.push_back(Path(path, name, extension));

		}

		//std::cout << entry.path() << std::endl;
		return returnVector;
	}

}