#include <vector>
#include "GSSComponent.h"
#include "../PComponent.h"

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

GComponent::FrustumInfo GSSComponent::getFrustumInfo()
{
	return FrustumInfo{ (-scale.y - scale.x) / 2.0f, (pComponent != NULL) ? pComponent->position : vec3(0.0f, 0.0f, 0.0f) };
}

void GSSComponent::setPosition(vec3 position)
{
	this->position = position;
}

void GSSComponent::setRotation(vec3 rotation)
{
	this->rotation = rotation;
}

void GSSComponent::setScale(vec3 scale)
{
	this->scale = scale;
}

void GSSComponent::setColor(short i, vec4 color)
{
	this->colors[i] = color;
}

vec3 GSSComponent::getPosition()
{
	return position;
}

vec3 GSSComponent::getRotation()
{
	return rotation;
}

vec2 GSSComponent::getScale()
{
	return scale;
}

vec4 GSSComponent::getColor(short i)
{
	return colors[i];
}

vec4* GSSComponent::getColors()
{
	return this->colors;
}
