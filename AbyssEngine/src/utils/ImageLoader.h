#pragma once
#include <string>
#include <iostream>
#include <GL/glew.h>
#include "lodepng/lodepng.h"

namespace abyssengine {
	inline void load_image(const std::string& filename, unsigned int& width, unsigned int& height, std::vector<unsigned char>& pixels)
	{
		unsigned int error = lodepng::decode(pixels, width, height, std::string(filename));

		if (error)
			std::cout << "Failed to load image, lodepng error " << error << ": " << lodepng_error_text(error) << std::endl;

		//free(image);
	}
}