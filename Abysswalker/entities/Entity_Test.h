#pragma once
#include "Entity.h"
#include "../math/vec3.h"

class GComponent;

class Entity_Test : public Entity
{
private:
	vec3 speed;
	vec3 direction;
	vec3 boundaries;
public:
	Entity_Test(std::vector<Component*>& components, vec3 speed, vec3 direction, vec3 boundaries);
	~Entity_Test();

	void update();
};

