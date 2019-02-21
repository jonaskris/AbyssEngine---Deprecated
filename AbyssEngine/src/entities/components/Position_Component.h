#pragma once
#include "Component.h"
#include "../../math/vec3.h"
#include "../interaction/Action.h"

namespace abyssengine {

	//! Position component, specialization of component
	struct Position_Component : public Component
	{
		Position_Component(unsigned int entityId) : Component(Component::types::Position, entityId) {}

		math::vec3 acceleration = math::vec3(0.0f, 0.0f, 0.0f);
		math::vec3 velocity = math::vec3(0.0f, 0.0f, 0.0f);
		math::vec3 position = math::vec3(0.0f, 0.0f, 0.0f);

		void update(const float &dt);

		enum VecActionTypes
		{ 
			SetPosition, ChangePosition, 
			SetVelocity, ChangeVelocity,
			SetAcceleration, ChangeAcceleration
		};

		struct VecAction : ActionWrapper::DataAction<VecActionTypes, math::vec3> {};
		void applyAction(Position_Component::VecAction& va);
	};
}

