#pragma once
#include <vector>
#include "components/Component.h"
#include "components/gComponent/GComponent.h"

class Entity
{
private:
	std::vector<Component*> components;
public:
	Entity(std::vector<Component*>& components);
	~Entity();

	std::vector<GComponent*> getGComponents();
};