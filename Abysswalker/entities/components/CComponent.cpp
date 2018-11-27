#include "CComponent.h"

CComponent::CComponent(const float vertices[], const unsigned int& verticesLength, const unsigned short indices[], const unsigned int& indicesLength) : Component(Component::componentType::CComponentType)
{
	this->verticesLength = verticesLength;
	this->vertices = new float[verticesLength];
	for (size_t i = 0; i < verticesLength; i++) {
		this->vertices[i] = vertices[i];
	}

	this->indicesLength = indicesLength;
	this->indices = new float[indicesLength];
	for (size_t i = 0; i < indicesLength; i++) {
		this->indices[i] = indices[i];
	}
}

CComponent::~CComponent()
{
	delete[] vertices;
	delete[] indices;
}

void CComponent::bindPComponent(PComponent* pComponent)
{
	this->pComponent = pComponent;
}