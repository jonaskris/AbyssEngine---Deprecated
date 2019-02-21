#pragma once
#include "Component.h"
#include "../../math/vec3.h"
#include "../interaction/Action.h"

namespace abyssengine {

	//! Base of collision components, specialization of component
	struct Collision_Component : public Component
	{
		enum types { Cube, MAX };
	protected:
		types type;

		bool verticesValid; // If scale or rotation is changed, verticesValid is set to false and the vertices must be updated before a collision test
		math::vec3 scale = math::vec3(1.0f, 1.0f, 1.0f);
		math::vec3 rotation = math::vec3(0.0f, 0.0f, 0.0f);
	public:
		Collision_Component(Collision_Component::types type, unsigned int entityId) : Component(Component::types::Collision, entityId)
		{
			this->type = type; 
			validateVertices();
		};

		enum VecActionTypes
		{
			SetScale, ChangeScale,
			SetRotation, ChangeRotation
		};

		struct VecAction : ActionWrapper::DataAction<VecActionTypes, math::vec3> {};
		void applyAction(Collision_Component::VecAction& fa);

		virtual bool collided(const Collision_Component& other) = 0;
	private:
		virtual void validateVertices() = 0;
	};

	//! Cube component, specialization of collision component
	struct Collision_Cube_Component : public Collision_Component
	{
		Collision_Cube_Component(unsigned int entityId) : Collision_Component(Collision_Component::types::Cube, entityId) {};

		struct VertexData {
			math::vec3 vertex;
		} vertices[8];

		bool collided(const Collision_Component& other);
		void validateVertices();
	};
}