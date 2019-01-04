#include "SComponent.h"

SComponent::SComponent(float maxHealth) : Component(Component::componentType::SComponentType)
{
	this->maxHealth = maxHealth;
}

SComponent::~SComponent()
{
}