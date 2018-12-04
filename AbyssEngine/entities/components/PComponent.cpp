#include "PComponent.h"

PComponent::PComponent() : Component(Component::componentType::PComponentType)
{

}

PComponent::PComponent(vec3 position) : Component(Component::componentType::PComponentType)
{
	this->position = position;
}

PComponent::~PComponent()
{

}

void PComponent::update()
{
	velocity += acceleration;
	position += velocity;
}
