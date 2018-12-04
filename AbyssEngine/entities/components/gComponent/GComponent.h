#pragma once
#include "../Component.h"
#include "../../Entity.h"

class GSSComponent;
class GTComponent;
class GLComponent;
class PComponent;
class CComponent;

class GComponent: public Component
{
public:
	const enum gComponentType { GSSComponentType, GLComponentType, GTComponentType, MAX };
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

	static constexpr unsigned int getComponentTypeCount() {
		return (unsigned int)gComponentType::MAX;
	}

private:
	friend class GSSComponent;
	friend class GTComponent;
	friend class CComponent;
	gComponentType type;

	PComponent* pComponent;

	friend void Entity::bindPComponentToGComponent(GComponent* gComponent);
	void bindPComponent(PComponent* pComponent)
	{
		this->pComponent = pComponent;
	}
};