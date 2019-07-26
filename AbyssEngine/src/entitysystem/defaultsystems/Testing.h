#pragma once
#include <iostream>
#include "../systems/System.h"
#include "../../math/linalg.h"
#include "../entitymanager/EntityManager.h"
#include "../../input/InputEnums.h"
#include "../defaultevents/Input.h"
#include "../defaultcomponents/Spatial.h"

namespace abyssengine {
	using UnitGroup = entitysystem::UnitGroup;

	template <typename... UnitTypes>
	using System = entitysystem::System<UnitTypes...>;

	class Test_Movement : public System<Velocity_Component, Position_Component>
	{
	private:
		const float boundary = 3.0f;

		void update(const double& dt) override
		{

			updateEntities(dt);
		}

		void updateEntity(const double& dt, UnitGroup& units) override
		{
			Velocity_Component& v = units.get<Velocity_Component>().first[0];
			Position_Component& p = units.get<Position_Component>().first[0];

			if (p.x < -boundary)
			{
				v.x *= -1.0f;
				p.x += -boundary - p.x;
			}
			else if (p.x > boundary) {
				v.x *= -1.0f;
				p.x -= p.x - boundary;
			}

			if (p.y < -boundary)
			{
				v.y *= -1.0f;
				p.y += -boundary - p.y;
			}
			else if (p.y > boundary) {
				v.y *= -1.0f;
				p.y -= p.y - boundary;
			}

			p += v * (float)dt;
		}
	};

	class Test_Changepos : public System<MouseButton_Event, Position_Component>
	{
	private:
		void update(const double& dt) override
		{
			updateEntities(dt);
		}

		void updateEntity(const double& dt, UnitGroup& units) override
		{
			MouseButton_Event& m = units.get<MouseButton_Event>().first[0];
			Position_Component& p = units.get<Position_Component>().first[0];

			if (m.getButton() == Mouse::Button::LEFT_CLICK && m.getAction() == Mouse::Action::PRESS)
				(math::vec3f&)p = math::vec3f{0.0f, 0.0f, 0.0f};
		}
	};
}