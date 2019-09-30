#include <iostream>
#include "File.h"
#include "FileException.h"
#include "../FileTypes/Bin.h"
#include "../FileTypes/Json.h"
#include "../FileTypes/Image.h"
#include "../FileTypes/Shader.h"

namespace abyssengine {
	namespace resources {
		FileBase* FileBase::newFile(const Path& path)
		{
			try {
				if (path.isFile())
					if (path.extension == "bin") {
						return new Bin{ path };
					}
					else if (path.extension == "json" || path.extension == "prog" || path.extension == "texa" || path.extension == "cm") {
						return new Json{ path };
					}
					else if (path.extension == "png") {
						return new Image{ path };
					}
					else if (path.extension == "vert" || path.extension == "frag" || path.extension == "geom" || path.extension == "tese" || path.extension == "tesc" || path.extension == "comp") {
						return new Shader{ path };
					}
			}
			catch (const FileCreationException & fileException) {
				std::cout << "Caught FileCreationException when initializing file from path!" << "\n\tException details: \n\t\t" << fileException.what() << "\n\tPath: " << path << std::endl;
			}
			catch (const std::exception & exception) {
				std::cout << "Caught exception when initializing file from path!" << "\n\tException details: \n\t\t" << exception.what() << "\n\tPath: " << path << std::endl;
			}

			return nullptr;
		}
	}
}