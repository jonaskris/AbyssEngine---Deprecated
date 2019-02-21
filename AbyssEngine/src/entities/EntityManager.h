#pragma once
#include <vector>
#include <forward_list>
//#include "./components/Component.h"
#include "Entity.h"
#include "./components/Collision_Component.h"
#include "./components/Graphics_Component.h"
#include "./components/Position_Component.h"
//#include "interaction/behaviours/Behaviour.h"
#include "interaction/Action.h"
#include "interaction/Event.h"

namespace abyssengine {

	class EntityManager
	{
	private:
		std::vector<Entity> entities;
		//! Components
			//! Collision components
			std::vector<Collision_Cube_Component>	collision_Cube_Components;

			//! Graphics components
			std::vector<Graphics_Sprite_Component>	graphics_Sprite_Components;
			std::vector<Graphics_Line_Component>	graphics_Line_Components;
			std::vector<Graphics_Point_Component>	graphics_Point_Components;
			std::vector<Graphics_Text_Component>	graphics_Text_Components;
			
			//! Position components
			std::vector<Position_Component>			position_Components;

		//std::forward_list<Behaviour> behaviours;
		//std::vector<ActionWrapper::Action> actions;

		// Shared events
		std::vector<Event> sharedEvents;

		// Events
		std::vector<Event> events;

	public:
		EntityManager();
		~EntityManager();

		//unsigned int newEntity(std::vector<Component::types> components, BehaviourMap behaviourMap); // Returns new id
		void newTestEntity();
		void update(const double &dt);

		std::vector<Graphics_Sprite_Component>& getGraphicsSpriteComponents();
		std::vector<Graphics_Line_Component>& getGraphicsLineComponents();
		std::vector<Graphics_Point_Component>& getGraphicsPointComponents();
		std::vector<Graphics_Text_Component>& getGraphicsTextComponents();
	};
}