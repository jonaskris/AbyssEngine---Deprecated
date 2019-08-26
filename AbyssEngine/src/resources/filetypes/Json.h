#pragma once
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../Path.h"
#include "../File/File.h"
#include "../File/FileException.h"

namespace abyssengine {
	namespace resources {
		class Json : public File<Json>
		{
			friend class FileBase;
		private:
			nlohmann::json jsonObject;

			Json(const Path& path) : File(path)
			{
				std::ifstream file(path.getFullPath());

				if (!file.is_open())
					throw FileCreationException(std::string("Couldent find file: ") + path.getFullPath());

				jsonObject = nlohmann::json::parse(file);

				file.close();
			}
		public:
			const nlohmann::json& getJsonObject() const
			{
				return jsonObject;
			}

			bool suitableAsDefaultFor(const Path & originallyRequested) const override { return false; };
		};
	}
}