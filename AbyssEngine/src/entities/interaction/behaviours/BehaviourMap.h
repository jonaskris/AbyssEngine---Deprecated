#pragma once
#include <list>
#include <iostream>
#include "../Event.h"
#include "Behaviour.h"

namespace abyssengine {
	class BehaviourMap
	{
	public:
		BehaviourMap();
		//BehaviourMap(const std::list<Behaviour::types>& priorityList);
	private:
		//void fillPriorityList(); // Fills prioritylist with missing behaviour types if every behaviour isnt in the priority list when the object is created
		struct Connection
		{
			bool negate;
			Event::types from;
			Behaviour::types to;
		};

		std::list<Connection> connections;
		//std::list<Behaviour::types> priorityList;
	public:
		void addConnection(Event::types from, Behaviour::types to, bool negate);

		std::list<Behaviour*> map(std::list<Event*>& fromSet);
	};
}