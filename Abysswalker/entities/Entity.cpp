#include <iostream>
#include "Entity.h"

Entity::Entity(std::vector<Component*>& components) 
{
	bool hasPositionComponent = false;
	bool hasStateComponent = false;
	for (size_t i = 0; i < components.size(); i++) {
		switch (components.at(i)->getType()) {
		case Component::componentType::GComponentType:
			this->components.push_back(components.at(i));
			break;
		case Component::componentType::CComponentType:
			this->components.push_back(components.at(i));
			break;
		case Component::componentType::PComponentType:
			if (hasPositionComponent) {
				std::cout << "Tried creating an entity with multiple position components! \n\tThe extra component was discarded." << std::endl;
			} else {
				hasPositionComponent = true;
				this->components.push_back(components.at(i));
			}
			break;
		case Component::componentType::SComponentType:
			if (hasStateComponent) {
				std::cout << "Tried creating an entity with multiple state components! \n\tThe extra component was discarded." << std::endl;
			} else {
				hasStateComponent = true;
				this->components.push_back(components.at(i));
			}
			break;
		default:

			break;
		}
	}
}

std::vector<GComponent*> Entity::getGComponents()
{
	std::vector<GComponent*> returnComponents;
	for (size_t i = 0; i < components.size(); i++) {
		if (components.at(i)->getType() == Component::componentType::GComponentType) {
			returnComponents.push_back((GComponent*)components.at(i));
		}
	}
	return returnComponents;
}


Entity::~Entity()
{
}