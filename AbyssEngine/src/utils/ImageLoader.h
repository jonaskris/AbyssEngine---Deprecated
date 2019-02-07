#pragma once
#include <string>
#include <iostream>
#include <GL/glew.h>
#include "lodepng/lodepng.h"

namespace abyssengine {
	inline void load_image(std::string& filename, unsigned int& width, unsigned int& height, size_t& in_size, std::vector<unsigned char>& pixels)
	{
		unsigned int error = lodepng::decode(pixels, width, height, filename);

		if (error) {
			std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
		}

		//free(image);
	}
}