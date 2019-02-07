#pragma once
#include "Entity.h"

namespace abyssengine {
	class Entity_Ground : public Entity
	{
	public:
		Entity_Ground(std::vector<Component*>& components);
		~Entity_Ground();

		void preUpdate() {}
		void update(float deltaTime) {}
	};
}