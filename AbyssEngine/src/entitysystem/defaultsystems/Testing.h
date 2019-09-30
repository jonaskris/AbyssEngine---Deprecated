#pragma once
#include <iostream>
#include "../systems/System.h"
#include "../../math/linalg.h"
#include "../entitymanager/EntityManager.h"
#include "../../input/InputEnums.h"
#include "../defaultevents/Input.h"
#include "../defaultcomponents/Spatial.h"
#include "../../math/semantics/Time.h"

namespace abyssengine {
	namespace entitysystem {
		//class Test_Movement : public System<Velocity_Component, Position_Component>
		//{
		//private:
		//	const float boundary = 3.0f;
		//
		//	void update(const math::Time& time) override
		//	{
		//		updateEntities(time);
		//	}
		//
		//	void updateEntity(const math::Time& time, UnitGroup& units) override
		//	{
		//		math::Velocity& v = units.get<Velocity_Component>().first[0].velocity;
		//		math::Position& p = units.get<Position_Component>().first[0].position;
		//
		//		if (p.x < -boundary)
		//		{
		//			v.x *= -1.0f;
		//			p.x += -boundary - p.x;
		//		}
		//		else if (p.x > boundary) {
		//			v.x *= -1.0f;
		//			p.x -= p.x - boundary;
		//		}
		//
		//		if (p.y < -boundary)
		//		{
		//			v.y *= -1.0f;
		//			p.y += -boundary - p.y;
		//		}
		//		else if (p.y > boundary) {
		//			v.y *= -1.0f;
		//			p.y -= p.y - boundary;
		//		}
		//
		//		p += v * time;
		//	}
		//};
		//
		//class Test_Changepos : public System<Mouse_Button_Event, Position_Component, Point_Component>
		//{
		//private:
		//	void update(const math::Time& time) override
		//	{
		//		updateEntities(time);
		//	}
		//
		//	void updateEntity(const math::Time& time, UnitGroup& units) override
		//	{
		//		Mouse_Button_Event& m = units.get<Mouse_Button_Event>().first[0];
		//		Position_Component& p = units.get<Position_Component>().first[0];
		//
		//		if (m.getButton() == input::Mouse::Button::LEFT_CLICK && m.getAction() == input::Mouse::Action::PRESS)
		//			(math::vec3f&)p = math::vec3f{ 0.0f, 0.0f, 0.0f };
		//	}
		//};
	}
}