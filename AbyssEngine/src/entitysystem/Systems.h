#pragma once
#include "systems/System.h"
#include "../math/vec3.h"
#include "entities/EntityManager.h"
#include "Components.h"
#include "GComponents.h"

namespace abyssengine {
	class Test_Movement_System : public System<Test_Movement_System>
	{
	private:
		friend class EntityManager;
		explicit Test_Movement_System(EntityManager* entityManager) : System(entityManager) { };

		void update(const double& dt) override
		{
			static const float boundary = 3.0f;

			static std::function updateLambda =
				[&](std::vector<ComponentStoreType*>& components)
			{
				Velocity_Component* a = static_cast<Velocity_Component*>(components.at(0));
				Point_Component* b = static_cast<Point_Component*>(components.at(1));
				
				if (b->vertex.vertex.x <= -boundary || b->vertex.vertex.x >= boundary)
					a->velocity.x *= -1;

				if (b->vertex.vertex.y <= -boundary || b->vertex.vertex.y >= boundary)
					a->velocity.y *= -1;

				b->vertex.vertex += a->velocity;
			};

			entityManager->each<Velocity_Component, Point_Component>(updateLambda);
		}
	};
}