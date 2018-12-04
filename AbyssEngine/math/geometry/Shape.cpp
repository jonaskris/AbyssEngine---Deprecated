#include "Shape.h"

std::vector<vec3> Shape::getVertices(Shape::shape shape)
{
	std::vector<vec3> returnVector;

	switch (shape) {
	case Shape::BOX:
		returnVector.push_back(vec3(-0.5f, -0.5f, -0.5f));
		returnVector.push_back(vec3(-0.5f, 0.5f, -0.5f));
		returnVector.push_back(vec3(0.5f, 0.5f, -0.5f));
		returnVector.push_back(vec3(0.5f, -0.5f, -0.5f));
		returnVector.push_back(vec3(-0.5f, -0.5f, 0.5f));
		returnVector.push_back(vec3(-0.5f, 0.5f, 0.5f));
		returnVector.push_back(vec3(0.5f, 0.5f, 0.5f));
		returnVector.push_back(vec3(0.5f, -0.5f, 0.5f));
			break;
	}
	
	return returnVector;
}

std::vector<unsigned int> Shape::getIndices(Shape::shape shape)
{
	std::vector<unsigned int> returnVector;

	switch (shape) {
	case Shape::BOX:
		// Far rectangle
			returnVector.push_back(0); returnVector.push_back(1); returnVector.push_back(1); returnVector.push_back(2); returnVector.push_back(2); returnVector.push_back(3); returnVector.push_back(3); returnVector.push_back(0);
		// Connections between rectangles
			returnVector.push_back(0); returnVector.push_back(4); returnVector.push_back(1); returnVector.push_back(5); returnVector.push_back(2); returnVector.push_back(6); returnVector.push_back(3); returnVector.push_back(7);
		// Near rectangle
			returnVector.push_back(4); returnVector.push_back(5); returnVector.push_back(5); returnVector.push_back(6); returnVector.push_back(6); returnVector.push_back(7); returnVector.push_back(7); returnVector.push_back(4);
		break;
	}

	return returnVector;
}