#include <vector>
#include "GSSComponent.h"

GSSComponent::GSSComponent(TextureAtlas::Atlas atlas, unsigned short textureID) : GComponent(GComponent::gComponentType::GSSComponentType)
{
	this->textureID = textureID;
	this->atlas = atlas;
	updateUV();
}

GSSComponent::GSSComponent(TextureAtlas::Atlas atlas, unsigned short textureID, vec2 scale) : GSSComponent(atlas, textureID)
{
	this->scale = scale;
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