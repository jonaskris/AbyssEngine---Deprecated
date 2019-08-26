#pragma once
#include <functional>
#include <fstream>
#include "../../utils/TypeIdentifier.h"
#include "../Path.h"

namespace abyssengine {
	namespace resources {
		class FileBase
		{
		protected:
			const Path path;
			FileBase(const Path& path) : path(path) { };
		public:
			const Path& getPath() const
			{
				return path;
			}

			virtual size_t getFileTypeIdentifier() const = 0;
			virtual bool suitableAsDefaultFor(const Path& originallyRequested) const = 0;

			static FileBase* newFile(const Path& path);
		};

		template <typename FileType>
		class File : public FileBase, public utils::TypeIdentifier<FileType>
		{
		protected:
			File(const Path& path) : FileBase(path) { };

			size_t getFileTypeIdentifier() const override { return utils::TypeIdentifier<FileType>::getIdentifier(); }
		};
	}
}