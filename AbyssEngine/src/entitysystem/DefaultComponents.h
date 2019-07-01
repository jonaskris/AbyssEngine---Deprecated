#pragma once
#include "entities/components/Component.h"
#include "../math/mat4.h"
#include "../math/vec3.h"

namespace abyssengine {
	struct Position_Component : public BasicComponent<Position_Component>
	{
		math::vec3 position;

		Position_Component() : position(math::vec3{ 0.0, 0.0, 0.0 }) {}
		Position_Component(const math::vec3& position) : position(position) {}
	};

	struct Velocity_Component : public BasicComponent<Velocity_Component>
	{
		math::vec3 velocity;

		Velocity_Component() : velocity(math::vec3{ 1.0, 1.0, 0.0 }) {}
		Velocity_Component(const math::vec3& velocity) : velocity(velocity) {}
	};
}