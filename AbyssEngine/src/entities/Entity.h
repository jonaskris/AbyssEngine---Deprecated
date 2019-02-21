#pragma once
#include <vector>
#include <list>
#include "../math/sets/Set.h"
#include "interaction/behaviours/BehaviourMap.h"

namespace abyssengine {
	struct Entity
	{
	private:
		static unsigned int count;
		unsigned int id;
	public:
		BehaviourMap behaviourMap;
		Entity(BehaviourMap behaviourMap)
		{
			id = count;
			count++;
			this->behaviourMap = behaviourMap;
		}

		unsigned int getId()
		{
			return id;
		}
	};
	unsigned int Entity::count = 0;
}