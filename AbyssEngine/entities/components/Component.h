#pragma once

class Component
{
public:
	enum componentType { GComponentType, CComponentType, PComponentType, SComponentType };
	Component(componentType type)
	{
		this->type = type;
	}

	componentType getType()
	{
		return type;
	}
private:
	componentType type;
};