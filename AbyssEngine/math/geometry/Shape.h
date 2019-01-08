#pragma once
#include <vector>
#include "../vec3.h"

class Shape
{
public:
	enum shape{ BOX, RECTANGLE, MAX };

	static std::vector<vec3> getVertices(Shape::shape shape);
	static std::vector<unsigned int> getIndices(Shape::shape shape);
};