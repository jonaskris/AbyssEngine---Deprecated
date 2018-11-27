#pragma once
#include "../Component.h"
#include "../../Entity.h"

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

	PComponent* getPositionComponent()
	{
		return pComponent;
	}

private:
	friend class GSSComponent;
	friend class GTComponent;
	gComponentType type;

	PComponent* pComponent;

	friend void Entity::bindPComponentToGComponent(GComponent* gComponent);
	void bindPComponent(PComponent* pComponent)
	{
		this->pComponent = pComponent;
	}
};