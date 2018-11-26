#pragma once
#include <vector>
#include "Component.h"

struct vec3;

class CComponent: public Component
{
private:
public:
	CComponent(const float vertices[], const unsigned int& verticesLength, const unsigned short indices[], const unsigned int& indicesLength);
	~CComponent();

	union {
		float* vertices;
		vec3* vecVertices; // Homogeneous coordinates. Meaning, one extra (z).
	};
	unsigned int verticesLength;

	float* indices;
	unsigned int indicesLength;
};