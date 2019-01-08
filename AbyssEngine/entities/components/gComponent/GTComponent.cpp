#include "GTComponent.h"

GTComponent::GTComponent() : GComponent(GComponent::gComponentType::GTComponentType)
{
}

GTComponent::~GTComponent()
{
}

GComponent::FrustumInfo GTComponent::getFrustumInfo()
{
	//return FrustumInfo{ (-scale.y - scale.x) / 2.0f, (pComponent != NULL) ? pComponent->position : vec3(0.0f, 0.0f, 0.0f) };
	return FrustumInfo{ 0.0f, vec3(0.0f, 0.0f, 0.0f)};
}