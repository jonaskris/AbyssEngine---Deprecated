#pragma once
#include <string>
#include <iostream>
#include <GL/glew.h>
#include "UtilsSemanticTypes.h"
#include "lodepng/lodepng.h"

namespace abyssengine {
	class ImageUtils {
	public:
		static void load_image(const Path& path, unsigned int& width, unsigned int& height, std::vector<unsigned char>& pixels)
		{
			unsigned int error = lodepng::decode(pixels, width, height, path.getFullPath());

			if (error)
			{
				std::cout << "Failed to load image, lodepng error " << error << ": " << lodepng_error_text(error) << std::endl;
				return;
			}

			// Flip image vertically
			unsigned short bytesPerPixel = (unsigned short)(pixels.size() / (width * height));
			unsigned int rowWidth = width * bytesPerPixel;
			
			// For every row
			size_t counter = 0;
			for (size_t i = 0; i < height / 2; i++)
			{
				// For every byte in row
				for (size_t j = 0; j < rowWidth; j++)
				{
					size_t index1 = i * rowWidth + j;
					size_t index2 = (height - i - 1) * rowWidth + j;
			
					unsigned char temp = pixels[index1];
					pixels[index1] = pixels[index2];
					pixels[index2] = temp;
					counter++;
				}
			}


		}
	};
}