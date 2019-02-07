#include "GLComponent.h"
#include "../PComponent.h"

namespace abyssengine {
	GLComponent::GLComponent() : GComponent(GComponent::gComponentType::GLComponentType)
	{

	}

	GLComponent::GLComponent(const math::vec3& vertex1, const math::vec3& vertex2) : GLComponent()
	{
		vertices[0] = vertex1;
		vertices[1] = vertex2;
	}

	GLComponent::GLComponent(const math::vec3& vertex1, const math::vec3& vertex2, const math::vec4& color) : GLComponent(vertex1, vertex2)
	{
		this->colors[0] = color;
		this->colors[1] = color;
	}

	GLComponent::GLComponent(const math::vec3& vertex1, const math::vec3& vertex2, const math::vec4& color1, const math::vec4& color2) : GLComponent(vertex1, vertex2)
	{
		this->colors[0] = color1;
		this->colors[1] = color2;
	}

	GComponent::FrustumInfo GLComponent::getFrustumInfo()
	{
		return FrustumInfo{ (vertices[0] - vertices[1]).magnitude() / 2.0f, (pComponent != NULL) ? ((vertices[0] + 0.5f * vertices[1]) + pComponent->position) : (vertices[0] + 0.5f * vertices[1]) };
	}

	void GLComponent::setVertex(short i, math::vec3 vertex)
	{
		vertices[i] = vertex;
	}

	void GLComponent::setColor(short i, math::vec4 color)
	{
		colors[i] = color;
	}

	math::vec3 GLComponent::getVertex(short i)
	{
		return vertices[i];
	}

	math::vec4 GLComponent::getColor(short i)
	{
		return colors[i];
	}
}