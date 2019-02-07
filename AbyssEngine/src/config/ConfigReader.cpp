#include "ConfigReader.h"
#include <vector>
#include <string>
#include "../utils/FileUtils.h"

namespace abyssengine {
	std::map<ConfigStringToken*, ConfigToken*> ConfigReader::readConfig(const char* filepath)
	{
		// Read file
		std::vector<std::string> readFile = read_file_lines(filepath);

		std::map<ConfigStringToken*, ConfigToken*> returnMap;

		for (size_t i = 0; i < readFile.size(); i++)
		{
			std::string line = readFile.at(i);

			// Check if line actually contains an '=', if not, continue
			if (line.find("=") == std::string::npos)
				continue;

			// Change line into two strings, before the '=' and after the '='
			std::string firstToken = line.substr(0, line.find("="));
			std::string secondToken = line.substr(line.find("=") + 1, line.size());

			ConfigStringToken* firstConfigToken = new ConfigStringToken(firstToken);
			ConfigToken* secondConfigToken;

			// String parse the second string into either int, float or bool, if it cant be parsed into either then continue without adding the line into the map.
			if (secondToken == "true") {
				secondConfigToken = new ConfigBoolToken(true);
			}
			else if (secondToken == "false")
			{
				secondConfigToken = new ConfigBoolToken(false);
			}
			else
			{
				try
				{
					secondConfigToken = new ConfigfloatToken(std::stof(secondToken));
				}
				catch (std::exception e)
				{
					secondConfigToken = new ConfigStringToken(secondToken);
				}
			}


			// Add into map
			returnMap[firstConfigToken] = secondConfigToken;
		}

		return returnMap;
	}
}