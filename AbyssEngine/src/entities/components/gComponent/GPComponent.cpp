#include "GPComponent.h"
#include "../PComponent.h"

namespace abyssengine {
	GPComponent::GPComponent() : GComponent(GComponent::gComponentType::GPComponentType)
	{

	}

	GPComponent::GPComponent(const math::vec3& vertex) : GPComponent()
	{
		this->vertex = vertex;
	}

	GPComponent::GPComponent(const math::vec3& vertex, const math::vec4& color) : GPComponent(vertex)
	{
		this->color = color;
	}

	GComponent::FrustumInfo GPComponent::getFrustumInfo()
	{
		return FrustumInfo{ 0.0f, (pComponent != NULL) ? (vertex + pComponent->position) : (vertex) };
	}

	void GPComponent::setVertex(math::vec3 vertex)
	{
		this->vertex = vertex;
	}

	void GPComponent::setColor(math::vec4 color)
	{
		this->color = color;
	}

	math::vec3 GPComponent::getVertex()
	{
		return vertex;
	}

	math::vec4 GPComponent::getColor()
	{
		return color;
	}
}