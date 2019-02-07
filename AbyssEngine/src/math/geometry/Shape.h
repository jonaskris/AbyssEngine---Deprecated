#pragma once
#include <vector>
#include "../vec3.h"

namespace abyssengine {
	class Shape
	{
	public:
		enum shape { BOX, RECTANGLE, MAX };

		static std::vector<math::vec3> getVertices(Shape::shape shape);
		static std::vector<unsigned int> getIndices(Shape::shape shape);
	};
}