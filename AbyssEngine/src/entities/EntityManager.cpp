#include "EntityManager.h"

namespace abyssengine {

	EntityManager::EntityManager()
	{
	}

	EntityManager::~EntityManager()
	{
	}

	//unsigned int EntityManager::newEntity(std::vector<Component::types> components, BehaviourMap behaviourMap)
	//{
	//	Entity newEntity = Entity(behaviourMap);
	//	entities.push_back(newEntity);
	//
	//	for (size_t i = 0; i < components.size(); i++) 
	//	{
	//		switch (components.at(i)) 
	//		{
	//		case Component::types::Collision:
	//
	//			break;
	//		case Component::types::Graphics:
	//			break;
	//		case Component::types::Position:
	//			break;
	//		}
	//	}
	//}

	void EntityManager::newTestEntity()
	{
		BehaviourMap b;
		Entity newEntity = Entity(b);

		Position_Component p = Position_Component(newEntity.getId());
		p.position = math::vec3((rand() / (float)RAND_MAX) * 10, (rand() / (float)RAND_MAX) * 10, 0.0f);

		entities.push_back(newEntity);
		graphics_Point_Components.push_back(Graphics_Point_Component(newEntity.getId()));
		position_Components.push_back(p);
	}

	std::vector<Graphics_Sprite_Component>& EntityManager::getGraphicsSpriteComponents()
	{
		return graphics_Sprite_Components;
	}

	std::vector<Graphics_Line_Component>& EntityManager::getGraphicsLineComponents()
	{
		return graphics_Line_Components;
	}

	std::vector<Graphics_Point_Component>& EntityManager::getGraphicsPointComponents()
	{
		return graphics_Point_Components;
	}

	std::vector<Graphics_Text_Component>& EntityManager::getGraphicsTextComponents()
	{
		return graphics_Text_Components;
	}


	void EntityManager::update(const double &dt)
	{
		// Iterate through events to create behaviors
			// Behaviour must be sorted by entityId
			// If vector capacity of events or behaviours is twice(Or something else) as big as it's size, shrink to fit to reduce memory usage.
			// Erase everything in event vector

		// Iterate through behaviours to create actions
			// Actions must be sorted by entityId
			// Erase behaviours that are finished
		
		// Iterate through components to execute actions and create events
			// Events must be 
			// Erase everything in action vector
	}
}
