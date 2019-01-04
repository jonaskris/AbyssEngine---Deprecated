#pragma once
#include <vector>
#include "../Entity.h"
#include "Component.h"
#include "../../math/geometry/Shape.h"
#include "../../math/vec3.h"

class PComponent;
class GComponent;
class GLComponent;

class CComponent: public Component
{
public:
	/* 
	NONE: No collision, 
	COLLIDING: Any type of collision, 
	ENCLOSED: A specific case of COLLIDING, where this is completely enclosed by other object, 
	ENVELOPING: A specific case of COLLIDING, where this is completely enveloping other object.
	*/

	CComponent(Shape::shape shape, vec3 scale);

	std::vector<vec3> vertices;

	std::vector<unsigned int> indices;

	std::vector<GLComponent*> getGLComponents();
	void collided(CComponent* other);

private:
	PComponent* pComponent;

	friend void Entity::bindPComponentToCComponent(CComponent* cComponent);
	void bindPComponent(PComponent* pComponent);
};