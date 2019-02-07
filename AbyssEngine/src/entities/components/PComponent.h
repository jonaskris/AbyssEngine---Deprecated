#pragma once
#include "Component.h"
#include "../../math/vec3.h"

namespace abyssengine {
	class PComponent : public Component
	{
	public:
		PComponent();
		PComponent(math::vec3 position);
		~PComponent();
		math::vec3 position = math::vec3(0.0f, 0.0f, 0.0f);
		math::vec3 velocity = math::vec3(0.0f, 0.0f, 0.0f);
		math::vec3 acceleration = math::vec3(0.0f, 0.0f, 0.0f);

		void update();
	};
}