#include "GTComponent.h"

namespace abyssengine {
	GTComponent::GTComponent(size_t fontId, float fontSize, std::string string) : GComponent(GComponent::gComponentType::GTComponentType)
	{
		this->fontId = fontId;
		this->fontSize = fontSize;
		this->string = string;
	}

	GTComponent::~GTComponent()
	{

	}

	GComponent::FrustumInfo GTComponent::getFrustumInfo()
	{
		return FrustumInfo{ NULL, NULL };
	}

	void GTComponent::setPosition(math::vec3 position)
	{
		this->position = position;
	}

	void GTComponent::setScale(math::vec3 scale)
	{
		this->scale = scale;
	}

	void GTComponent::setColor(short i, math::vec4 color)
	{
		this->colors[i] = color;
	}

	math::vec3 GTComponent::getPosition()
	{
		this->position = position;
	}

	math::vec2 GTComponent::getScale()
	{
		return scale;
	}

	math::vec4* GTComponent::getColors()
	{
		return colors;
	}

	std::string GTComponent::getString()
	{
		return string;
	}

	char* GTComponent::getChars() 
	{
		return string.c_str[0];
	}

	size_t GTComponent::getCharCount()
	{
		size_t count = 0;
		while (string[count] != '\0')
			count++;
		return count;
	}

	size_t GTComponent::getFontId()
	{
		return fontId;
	}

	float GTComponent::getFontSize()
	{
		return fontSize;
	}
}