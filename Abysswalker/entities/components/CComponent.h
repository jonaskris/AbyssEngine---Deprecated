#pragma once
#include <vector>
#include "../Entity.h"
#include "Component.h"

struct vec3;
class PComponent;
class GComponent;

class CComponent: public Component
{
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
private:
	PComponent* pComponent;

	friend void Entity::bindPComponentToCComponent(CComponent* cComponent);
	void bindPComponent(PComponent* pComponent);
};