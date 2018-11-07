#include "CComponent.h"
#include <iostream>

CComponent::CComponent(const float vertices[], const unsigned int& verticesLength, const unsigned short indices[], const unsigned int& indicesLength)
{
	this->verticesLength = verticesLength;
	this->vertices = new float[verticesLength];
	for (int i = 0; i < verticesLength; i++) {
		this->vertices[i] = vertices[i];
	}

	this->indicesLength = indicesLength;
	this->indices = new float[indicesLength];
	for (int i = 0; i < indicesLength; i++) {
		this->indices[i] = indices[i];
	}
}

CComponent::~CComponent()
{
	delete[] vertices;
	delete[] indices;
}