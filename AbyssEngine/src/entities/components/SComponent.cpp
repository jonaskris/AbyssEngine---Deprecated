#include "SComponent.h"

namespace abyssengine {
	SComponent::SComponent(float maxHealth) : Component(Component::componentType::SComponentType)
	{
		this->maxHealth = maxHealth;
	}

	SComponent::~SComponent()
	{
	}
}