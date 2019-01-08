#pragma once
#include "../Component.h"
#include "../../Entity.h"
#include "../../../math/vec3.h"

class GSSComponent;
class GTComponent;
class GLComponent;
class PComponent;
class CComponent;

class GComponent: public Component
{
public:
	struct FrustumInfo
	{
		float biggestEnclosingRadius;
		vec3 center;
	};
	virtual FrustumInfo getFrustumInfo() = 0;


	const enum gComponentType { GSSComponentType, GLComponentType, GTComponentType, MAX };
protected:
	PComponent* pComponent;

	GComponent(gComponentType type) : Component(Component::componentType::GComponentType)
	{
		this->type = type;
	}
public:
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


	friend void Entity::bindPComponentToGComponent(GComponent* gComponent);
	void bindPComponent(PComponent* pComponent)
	{
		this->pComponent = pComponent;
	}
};