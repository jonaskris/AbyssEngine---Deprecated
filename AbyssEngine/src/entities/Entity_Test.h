#pragma once
#include "Entity.h"
#include "../math/vec3.h"

namespace abyssengine {
	class GComponent;

	class Entity_Test : public Entity
	{
	private:
		math::vec3 speed;
		math::vec3 direction;
		math::vec3 boundaries;
	public:
		Entity_Test(std::vector<Component*>& components, math::vec3 speed, math::vec3 direction, math::vec3 boundaries);
		~Entity_Test();

		void update();
	};
}