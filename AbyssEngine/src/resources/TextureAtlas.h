#pragma once
#include <vector>
#include "Texture.h"
#include "../math/vec2.h"
#include "../math/MathSemanticTypes.h"
#include "../utils/UtilsSemanticTypes.h"

#define SPRITE_SIZE 32

namespace abyssengine {

	class TextureAtlas : public Texture
	{
		
	private:
		std::vector<QuadVec<math::vec2>> uvs;
	public:
		TextureAtlas(const Path& path) : Texture(path)
		{
			float hpcX = (1.0f / width) / 2.0f;
			float hpcY = (1.0f / height) / 2.0f;

			size_t columns = (width / SPRITE_SIZE - width % SPRITE_SIZE);
			size_t rows = (height / SPRITE_SIZE - height % SPRITE_SIZE);

			uvs.reserve(columns * rows);

			for (size_t i = 0; i < columns * rows; i++)
			{
				int column = (i % columns);
				int row = (i - column) / columns;
				
				// Finds the coordinates of the texture in pixelspace
				int x = column * SPRITE_SIZE;
				int y = (rows - row) * SPRITE_SIZE - SPRITE_SIZE;
				
				// Finds the x and y components and adds the size of the sprite, which is used to contruct the squares 4 corners
				int xs = x + SPRITE_SIZE;
				int ys = y + SPRITE_SIZE;
				
				// Normalises the coordinates and adds half pixel correction
				float xn = (x + hpcX) / (float)width;
				float yn = (y + hpcY) / (float)height;
				float xsn = (xs - hpcX) / (float)width;
				float ysn = (ys - hpcY) / (float)height;
				
				// Texture coordinates are rotated by 90 degrees, as lodepng loads images in a different orientation than opengl.
				uvs.push_back(QuadVec<math::vec2>{ math::vec2(xn, yn), math::vec2(xsn, yn), math::vec2(xsn, ysn), math::vec2(xn, ysn) });
			}
		}

		QuadVec<math::vec2> getUv(const size_t& index) const
		{
			return uvs.at(index);
		}
	};
}