#pragma once
#include "../systems/System.h"
#include "../defaultcomponents/Graphics.h"
#include "../defaultcomponents/Spatial.h"
#include "../defaultevents/Input.h"
#include "../../math/semantics/Time.h"
#include "../../Defines.h"

namespace abyssengine {
	namespace entitysystem {
		class Camera_Rotation_Control : public System<Camera_Component, Mouse_Position_Event>
		{
		private:
			void update(const math::Time& time) override
			{
				updateEntities(time);
			}

			void updateEntity(const math::Time& time, UnitGroup& units) override
			{
				Camera_Component& c = units.get<Camera_Component>().first[0];
				Mouse_Position_Event& pe = units.get<Mouse_Position_Event>().first[0];

				math::vec2f mousePosition = pe.getPosition();
				math::vec2f mouseLastPosition = pe.getLastPosition();

				c.yaw += (mouseLastPosition.x - mousePosition.x) * (float)MOUSE_SENSITIVITY;
				c.pitch += (mouseLastPosition.y - mousePosition.y) * (float)MOUSE_SENSITIVITY;

				if (c.pitch > 89.99f)
					c.pitch = 89.99f;
				if (c.pitch < -89.99f)
					c.pitch = -89.99f;

				c.yaw = std::fmodf(c.yaw, 360.0f);

				c.update();
			}
		};

		class Camera_Position_Control : public System<Camera_Component, Transform_Component, Keyboard_Key_Event>
		{
		private:
			void update(const math::Time& time) override
			{
				updateEntities(time);
			}

			void updateEntity(const math::Time& time, UnitGroup& units) override
			{
				static const float movementSpeed = 0.03f;
				
				Camera_Component& c = units.get<Camera_Component>().first[0];
				Transform_Component& t = units.get<Transform_Component>().first[0];
				std::pair<Keyboard_Key_Event*, size_t> ks = units.get<Keyboard_Key_Event>();

				math::vec3f dp;

				for (size_t i = 0; i < ks.second; i++) {
					Keyboard_Key_Event& k = ks.first[i];

					if (k.getKey() == input::Keyboard::Key::W && k.getAction() == input::Keyboard::Action::HOLD)
						dp += c.front.normalize() * movementSpeed;
					if (k.getKey() == input::Keyboard::Key::S && k.getAction() == input::Keyboard::Action::HOLD)
						dp -= c.front.normalize() * movementSpeed;
					if (k.getKey() == input::Keyboard::Key::D && k.getAction() == input::Keyboard::Action::HOLD)
						dp += c.front.cross(math::vec3f(0.0f, 0.0f, 1.0f)).normalize() * movementSpeed;
					if (k.getKey() == input::Keyboard::Key::A && k.getAction() == input::Keyboard::Action::HOLD)
						dp -= c.front.normalize().cross(math::vec3f(0.0f, 0.0f, 1.0f)).normalize() * movementSpeed;
					if (k.getKey() == input::Keyboard::Key::SPACE && k.getAction() == input::Keyboard::Action::HOLD)
						dp.z += movementSpeed;
					if (k.getKey() == input::Keyboard::Key::LEFT_SHIFT && k.getAction() == input::Keyboard::Action::HOLD)
						dp.z -= movementSpeed;
				}

				t.transforms[0] = math::mat4f::translate(dp) * t.transforms[0];
				c.position = math::toVec3f(t.toMatrix().decomposeToTranslation() * (math::vec4f(0.0f, 0.0f, 0.0f, 1.0f)));

				c.view = math::mat4f::viewMatrix(c.position, c.position + c.front, c.up);
			}
		};

		//class Transform_Updater : public System<Transform_Component, Position_Component::optional, Scale_Component::optional>
		//{
		//private:
		//	void update(const math::Time& time) override
		//	{
		//		updateEntities(time);
		//	}
		//
		//	void updateEntity(const math::Time& time, UnitGroup& units) override
		//	{
		//		Transform_Component& t = units.get<Transform_Component>().first[0];
		//		Position_Component* p = units.get<Position_Component>().first;
		//		Scale_Component* s = units.get<Scale_Component>().first;
		//
		//		t.transform = math::mat4f::identity();
		//		if (s)
		//			t.transform = math::mat4f::scale(s->scale.vec);
		//		if (p)
		//			t.transform = math::mat4f::translate(p->position.vec);
		//	}
		//};
		//
	}
}