#pragma once
#include <iostream>
#include "systems/System.h"
#include "../math/vec3.h"
#include "EntityManager.h"
#include "DefaultComponents.h"
#include "DefaultGComponents.h"

namespace abyssengine {
	class Test_Movement : public System<Velocity_Component, Point_Component>
	{
	private:
		friend class EntityManager;

		const float boundary = 3.0f;

		void update(const double& dt) override
		{
			updateEntities(dt);
		}

		void updateEntity(const double& dt, UnitGroup& units)
		{
			Velocity_Component* v = units.get<Velocity_Component>().first;
			Point_Component* p = units.get<Point_Component>().first;

			if (p->vertex.vertex.x < -boundary)
			{
					v->velocity.x *= -1.0f;
					p->vertex.vertex.x += -boundary - p->vertex.vertex.x;
			} else if (p->vertex.vertex.x > boundary) {
					v->velocity.x *= -1.0f;
					p->vertex.vertex.x -= p->vertex.vertex.x - boundary;
			}

			if (p->vertex.vertex.y < -boundary)
			{
					v->velocity.y *= -1.0f;
					p->vertex.vertex.y += -boundary - p->vertex.vertex.y;
			} else if (p->vertex.vertex.y > boundary) {
					v->velocity.y *= -1.0f;
					p->vertex.vertex.y -= p->vertex.vertex.y - boundary;
			}

			p->vertex.vertex += v->velocity * (float)dt;
		}

	public:
		Test_Movement() { };
	};

	class Camera_Movement : public System<Camera_Component>
	{
	private:
		friend class EntityManager;

		void update(const double& dt) override
		{
			updateEntities(dt);
		}

		void updateEntity(const double& dt, UnitGroup& units)
		{
			Camera_Component* c = units.get<Camera_Component>().first;

			c->viewMatrix = math::mat4::viewMatrix(c->lookFrom, c->lookAt, math::vec3{ 0.0f, 1.0f, 0.0f });
		}
	public:
		Camera_Movement() { };
	};
}