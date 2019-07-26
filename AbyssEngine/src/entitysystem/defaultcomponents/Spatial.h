#pragma once
#include "../components/Component.h"
#include "../../math/linalg.h"

namespace abyssengine {

	template <typename ComponentType>
	using Component = entitysystem::Component<ComponentType>;

	struct Position_Component : public Component<Position_Component>, public math::vec3f
	{
		//math::vec3f position;
		//Position_Component() : position(math::vec3f{ 0.0, 0.0, 0.0 }) {}
		//Position_Component(const math::vec3f& position) : position(position) {}
		
		Position_Component() : math::vec3f(math::vec3f{ 0.0f, 0.0f, 0.0f }) {}
		Position_Component(const math::vec3f& position) : math::vec3f(position) {}

		//operator math::vec3f&() { return position; };
	};

	struct Velocity_Component : public Component<Velocity_Component>, public math::vec3f
	{
		//math::vec3f velocity;

		//Velocity_Component() : velocity(math::vec3f{ 0.0, 0.0, 0.0 }) {}
		//Velocity_Component(const math::vec3f& velocity) : velocity(velocity) {}

		Velocity_Component() : math::vec3f(math::vec3f{ 0.0f, 0.0f, 0.0f }) {}
		Velocity_Component(const math::vec3f& velocity) : math::vec3f(velocity) {}

		//operator math::vec3f&() { return velocity; };
	};
}