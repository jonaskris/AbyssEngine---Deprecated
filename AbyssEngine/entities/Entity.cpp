#include <iostream>
#include "Entity.h"
#include "components/Component.h"
#include "components/gComponent/GComponent.h"
#include "components/gComponent/GSSComponent.h"
#include "components/gComponent/GTComponent.h"
#include "components/CComponent.h"
#include "components/PComponent.h"
#include "components/SComponent.h"

Entity::Entity(std::vector<Component*>& components) 
{
	for (size_t i = 0; i < components.size(); i++) {
		switch (components.at(i)->getType()) {
		case Component::componentType::GComponentType:
			this->gComponents.push_back((GComponent*)components.at(i));
			break;
		case Component::componentType::CComponentType:
			this->cComponents.push_back((CComponent*)components.at(i));
			break;
		case Component::componentType::PComponentType:
			if (!pComponent) {
				this->pComponent = (PComponent*)components.at(i);
				break;
			}
			std::cout << "Tried creating an entity with multiple position components! \n\tThe extra component was discarded." << std::endl;
			break;
		case Component::componentType::SComponentType:
			if (!sComponent) {
				this->sComponent = (SComponent*)components.at(i);
				break;
			}
			std::cout << "Tried creating an entity with multiple state components! \n\tThe extra component was discarded." << std::endl;
			break;
		default:
			break;
		}
	}

	if (!pComponent) {
		pComponent = new PComponent(vec3(0.0f, 0.0f, 0.0f));
	}

	bindPComponent();
}

Entity::~Entity()
{

}

void Entity::bindPComponent()
{
	for (size_t i = 0; i < cComponents.size(); i++) {
		bindPComponentToCComponent(cComponents.at(i));
	}

	for (size_t i = 0; i < gComponents.size(); i++) {
		bindPComponentToGComponent(gComponents.at(i));
	}
}

void Entity::setPComponent(PComponent* pComponent)
{
	this->pComponent = pComponent;
	bindPComponent();
}

void Entity::setSComponent(SComponent* sComponent)
{
	this->sComponent = sComponent;
}

void Entity::addGComponent(GComponent* gComponent)
{
	gComponents.push_back(gComponent);
	bindPComponentToGComponent(gComponent);
}

void Entity::addCComponent(CComponent* cComponent)
{
	cComponents.push_back(cComponent);
	bindPComponentToCComponent(cComponent);
}

void Entity::bindPComponentToGComponent(GComponent* gComponent) 
{
	gComponent->bindPComponent(pComponent);
}

void Entity::bindPComponentToCComponent(CComponent* cComponent)
{
	cComponent->bindPComponent(pComponent);
}

std::vector<GComponent*> Entity::getGComponents()
{
	return gComponents;
}

std::vector<CComponent*> Entity::getCComponents()
{
	return cComponents;
}

PComponent* Entity::getPComponent()
{
	return pComponent;
}

SComponent* Entity::getSComponent()
{
	return sComponent;
}