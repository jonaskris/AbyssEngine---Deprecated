#pragma once
#include "../components/Component.h"
#include "../../math/linalg.h"
#include "../../math/semantics/Attribute.h"
#include "../../math/semantics/Transform.h"

namespace abyssengine {
	namespace entitysystem {
		struct Position_Component : public Component<Position_Component>
		{
			math::Position position;

			Position_Component() : position(math::vec3f{ 0.0f, 0.0f, 0.0f }) {}
			Position_Component(const math::Position& position) : position(position) {}
		};

		struct Scale_Component : public Component<Scale_Component>
		{
			math::Scale scale;

			Scale_Component() : scale(math::vec3f{ 1.0f, 1.0f, 1.0f }) {}
			Scale_Component(const math::Scale& scale) : scale(scale) {}
		};

		//struct Velocity_Component : public Component<Velocity_Component>
		//{
		//	math::Velocity velocity;
		//
		//	Velocity_Component() : velocity(math::vec3f{ 0.0f, 0.0f, 0.0f }) {}
		//	Velocity_Component(const math::Velocity& velocity) : velocity(velocity) {}
		//};
	}
}