#pragma once
#include "Component.h"
#include "../../math/vec3.h"

class PComponent: public Component
{
public:
	PComponent();
	PComponent(vec3 position);
	~PComponent();
	vec3 position = vec3(0.0f, 0.0f, 0.0f);
	vec3 velocity = vec3(0.0f, 0.0f, 0.0f);
	vec3 acceleration = vec3(0.0f, 0.0f, 0.0f);

	void update();
};

