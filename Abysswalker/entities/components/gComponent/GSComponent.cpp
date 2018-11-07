#include "GSComponent.h"

const float GSComponent::vertices[16] =
{
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.0f, 1.0f
};

const unsigned short GSComponent::indices[6] =
{
	0, 1, 2, 0, 2, 3
};

GSComponent::GSComponent(PComponent* pComponent, unsigned short spriteID)
{
	modelMatrix = mat4::identity();
	this->spriteID = spriteID;
}

GSComponent::~GSComponent()
{
}
