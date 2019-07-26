#pragma once
#include "../linalg.h"

namespace abyssengine { namespace Shape {
	using namespace math;

	//! Cube
	const vec3f cubeVertices[]
	{
		vec3f(-0.5f, -0.5f, -0.5f),
		vec3f(-0.5f, 0.5f, -0.5f),
		vec3f(0.5f, 0.5f, -0.5f),
		vec3f(0.5f, -0.5f, -0.5f),
		vec3f(-0.5f, -0.5f, 0.5f),
		vec3f(-0.5f, 0.5f, 0.5f),
		vec3f(0.5f, 0.5f, 0.5f),
		vec3f(0.5f, -0.5f, 0.5f)
	};

	const unsigned short cubeIndices[]
	{
		0, 1, 1, 2, 2, 3, 3, 0,
		0, 4, 1, 5, 2, 6, 3, 7,
		4, 5, 5, 6, 6, 7, 7, 4
	};

	//! Rectangle
	const vec3f rectangleVertices[]{
		vec3f(-0.5f, -0.5f, 0.0f),
		vec3f(-0.5f, 0.5f, 0.0f),
		vec3f(0.5f, 0.5f, 0.0f),
		vec3f(0.5f, -0.5f, 0.0f)
	};

	const unsigned short rectangleIndices[]
	{
		0, 1, 1, 2, 2, 3, 3, 0
	};
}}					  