#pragma once
#include <vector>
#include <optional>
#include "../Path.h"
#include "../File/File.h"

namespace abyssengine {
	namespace resources {
		class Bin : public File<Bin>
		{
			friend class FileBase;
		private:
			std::vector<char> data;

			Bin(const Path& path) : File(path)
			{

				std::ifstream file(path.getFullPath());

				if (!file.is_open())
					throw FileCreationException(std::string("Couldent find file: ") + path.getFullPath());

				file.seekg(0, std::ios::end);

				size_t fileSize = (size_t)file.tellg();

				data.resize(fileSize);

				file.seekg(0, std::ios::beg);
				file.read(&data[0], fileSize);

				file.close();
			}
		public:
			const std::vector<char>& getData() const
			{
				return data;
			}

			bool suitableAsDefaultFor(const Path & originallyRequested) const override { return false; };
		};
	}
}