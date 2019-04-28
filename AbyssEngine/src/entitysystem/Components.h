#pragma once
#include "entities/components/Component.h"
#include "../math/vec3.h"

namespace abyssengine {
	struct Position_Component : public Component<Position_Component>
	{
		math::vec3 position;

		Position_Component() : position(math::vec3{ 0.0f, 0.0f, 0.0f }) {}
		Position_Component(const math::vec3& position) : position(position) {}
	};

	struct Velocity_Component : public Component<Velocity_Component>
	{
		math::vec3 velocity;

		Velocity_Component() : velocity(math::vec3{ 1.0f, 1.0f, 0.0f }) {}
		Velocity_Component(const math::vec3& velocity) : velocity(velocity) {}
	};
}