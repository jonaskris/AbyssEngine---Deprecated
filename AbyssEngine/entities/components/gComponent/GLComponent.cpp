#include "GLComponent.h"

GLComponent::GLComponent() : GComponent(GComponent::gComponentType::GLComponentType)
{
}

GLComponent::GLComponent(const vec3& vertex1, const vec3& vertex2) : GLComponent()
{
	vertices[0] = vertex1;
	vertices[1] = vertex2;
}

GLComponent::GLComponent(const vec3& vertex1, const vec3& vertex2, const vec4& color) : GLComponent(vertex1, vertex2)
{
	this->colors[0] = color;
	this->colors[1] = color;
}

GLComponent::GLComponent(const vec3& vertex1, const vec3& vertex2, const vec4& color1, const vec4& color2) : GLComponent(vertex1, vertex2)
{
	this->colors[0] = color1;
	this->colors[1] = color2;
}