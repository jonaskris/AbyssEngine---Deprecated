#include <vector>
#include "CComponent.h"
#include "gComponent/GLComponent.h"
#include "../../math/geometry/Shape.h"
#include "../../math/vec3.h"


CComponent::CComponent(Shape::shape shape, vec3 scale) : Component(Component::componentType::CComponentType)
{
	std::vector<vec3> vertices = Shape::getVertices(shape);
	std::vector<unsigned int> indices = Shape::getIndices(shape);

	this->verticesLength = vertices.size();
	this->indicesLength = indices.size();

	this->vecVertices = new vec3[verticesLength];
	this->indices = new unsigned int[indicesLength];

	for (size_t i = 0; i < verticesLength; i++)
	{
		this->vecVertices[i] = vertices[i];
	}
	
	for (size_t i = 0; i < indicesLength; i++)
	{
		this->indices[i] = indices[i];
	}


}

std::vector<GLComponent*> CComponent::getGLComponents()
{
	std::vector<GLComponent*> returnVector;

	for (size_t i = 0; i < indicesLength / 2; i++) 
	{
		returnVector.push_back(new GLComponent(vecVertices[i * 2], vecVertices[i * 2 + 1]));
		returnVector.back()->bindPComponent(pComponent);
	}

	return returnVector;
}


void CComponent::bindPComponent(PComponent* pComponent)
{
	this->pComponent = pComponent;
}