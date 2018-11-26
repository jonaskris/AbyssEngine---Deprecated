#include <vector>
#include "GSSComponent.h"

GSSComponent::GSSComponent(PComponent& pComponent, TextureAtlas::Atlas atlas, unsigned short textureID) : GComponent(GComponent::gComponentType::GSSComponentType)
{
	this->pComponent = &pComponent;
	this->textureID = textureID;
	this->atlas = atlas;
	updateUV();
}

void GSSComponent::updateUV()
{
	TextureAtlas::getTextureCoordinates(textureID, atlas, &uv);
}

void GSSComponent::setAtlas(TextureAtlas::Atlas atlas, unsigned short textureID)
{
	this->atlas = atlas;
	this->textureID = textureID;
	updateUV();
}

void GSSComponent::setTextureID(unsigned short textureID)
{
	this->textureID = textureID;
	updateUV();
}