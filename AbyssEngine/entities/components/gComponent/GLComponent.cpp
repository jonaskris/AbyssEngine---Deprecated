#include "GLComponent.h"

GLComponent::GLComponent() : GComponent(GComponent::gComponentType::GLComponentType)
{
}

GLComponent::GLComponent(const vec3& vertex1, const vec3& vertex2) : GLComponent()
{
	vertices[0] = vertex1;
	vertices[1] = vertex2;
}