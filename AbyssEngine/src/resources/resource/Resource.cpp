#include <iostream>
#include "Resource.h"
#include "ResourceException.h"
#include "../file/File.h"
#include "../file/FileException.h"
#include "../filetypes/Json.h"
#include "../filetypes/Image.h"
#include "../resourcetypes/Program.h"
#include "../resourcetypes/Texture.h"
#include "../resourcetypes/TextureAtlas.h"
#include "../resourcetypes/Cubemap.h"

namespace abyssengine {
	namespace resources {
		ResourceBase* ResourceBase::newResource(FileBase* const file)
		{
			try {
				if (file->getFileTypeIdentifier() == utils::TypeIdentifier<Image>::getIdentifier())
				{
					const Image& image = *static_cast<Image * const>(file);

					return new Texture(image);
				} else if (file->getFileTypeIdentifier() == utils::TypeIdentifier<Json>::getIdentifier()) {
					const Json& json = *static_cast<Json * const>(file);

					if (file->getPath().extension == "prog") // GLSL program
						return new Program(json);
					else if (file->getPath().extension == "texa") // Texture atlas
						return new TextureAtlas(json);
					else if (file->getPath().extension == "cm")	// Cube map
						return new Cubemap(json);
				}
			}
			catch (const ResourceCreationException & resourceException) {
				std::cout << "Caught ResourceCreationException when initializing resource from path!" << "\n\tException details: \n\t\t" << resourceException.what() << "\n\tFile path: " << file->getPath() << std::endl;
			}
			catch (const std::exception & exception) {
				std::cout << "Caught exception when initializing resource from path!" << "\n\tException details: \n\t\t" << exception.what() << "\n\tFile path: " << file->getPath() << std::endl;
			}
			return nullptr;
		}
	}
}