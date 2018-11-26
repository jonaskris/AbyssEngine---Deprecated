#pragma once
#include "../Component.h"

class GSSComponent;
class GTComponent;

class GComponent: public Component
{
public:
	enum gComponentType { GSSComponentType, GTComponentType };
	GComponent(gComponentType type) : Component(Component::componentType::GComponentType)
	{
		this->type = type;
	}

	gComponentType getType()
	{
		return type;
	}
private:
	friend class GSSComponent;
	friend class GTComponent;
	gComponentType type;
};