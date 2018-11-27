#include <vector>
#include "Entity_Test.h"
#include "../math/vec3.h"
#include "components/Component.h"
#include "components/PComponent.h"

Entity_Test::Entity_Test(std::vector<Component*>& components, vec3 speed, vec3 direction, vec3 boundaries) : Entity(components)
{
	this->speed = speed;
	this->direction = direction;
	this->boundaries = boundaries;
}

Entity_Test::~Entity_Test()
{
}

void Entity_Test::update() 
{

	bool directionChanged = false;
	if (this->pComponent->position.x < -boundaries.x || this->pComponent->position.x > boundaries.x) 
	{
		direction.x *= -1;
		directionChanged = true;
	}

	if (this->pComponent->position.y < -boundaries.y || this->pComponent->position.y > boundaries.y)
	{
		direction.y *= -1;
		directionChanged = true;
	}

	if (this->pComponent->position.z < -boundaries.z || this->pComponent->position.z > boundaries.z)
	{
		direction.z *= -1;
		directionChanged = true;
	}

	this->pComponent->velocity = speed * direction;

	this->pComponent->update();
}
