#pragma once
#include "../systems/System.h"
#include "../defaultcomponents/Graphics.h"
#include "../defaultcomponents/Spatial.h"
#include "../defaultevents/Input.h"
#include "../../math/semantics/Time.h"
#include "../../Defines.h"

namespace abyssengine {
	namespace entitysystem {
		class Camera_Rotation_Control : public System<Camera_Component, Position_Component, Mouse_Position_Event>
		{
		private:
			void update(const math::Time& time) override
			{
				updateEntities(time);
			}

			void updateEntity(const math::Time& time, UnitGroup& units) override
			{
				Camera_Component& c = units.get<Camera_Component>().first[0];
				Position_Component& p = units.get<Position_Component>().first[0];

				Mouse_Position_Event& pe = units.get<Mouse_Position_Event>().first[0];
				math::vec2f mousePosition = pe.getPosition();
				math::vec2f mouseLastPosition = pe.getLastPosition();

				c.yaw += (mousePosition.x - mouseLastPosition.x) * MOUSE_SENSITIVITY;
				c.pitch += (mouseLastPosition.y - mousePosition.y) * MOUSE_SENSITIVITY;

				if (c.pitch > 89.0f)
					c.pitch = 89.0f;
				if (c.pitch < -89.0f)
					c.pitch = -89.0f;

				math::vec3f& front = c.front;
				front.x = cos(math::toRadians(c.yaw)) * cos(math::toRadians(c.pitch));
				front.y = sin(math::toRadians(c.pitch));
				front.z = sin(math::toRadians(c.yaw)) * cos(math::toRadians(c.pitch));

				front = front.normalize();

				c.view = math::mat4f::viewMatrix(p.position.vec, p.position.vec + c.front, c.up);
			}
		};

		class Camera_Position_Control : public System<Camera_Component, Position_Component, Keyboard_Key_Event>
		{
		private:
			void update(const math::Time& time) override
			{
				updateEntities(time);
			}

			void updateEntity(const math::Time& time, UnitGroup& units) override
			{
				static const float movementSpeed = 0.05;
				
				Camera_Component& c = units.get<Camera_Component>().first[0];
				Position_Component& p = units.get<Position_Component>().first[0];
				std::pair<Keyboard_Key_Event*, size_t> ks = units.get<Keyboard_Key_Event>();

				c.position = p.position.vec;


				for (size_t i = 0; i < ks.second; i++) {
					Keyboard_Key_Event& k = ks.first[i];

					if (k.getKey() == input::Keyboard::Key::W && k.getAction() == input::Keyboard::Action::HOLD)
						p.position.y += movementSpeed;
					if (k.getKey() == input::Keyboard::Key::S && k.getAction() == input::Keyboard::Action::HOLD)
						p.position.y -= movementSpeed;
					if (k.getKey() == input::Keyboard::Key::D && k.getAction() == input::Keyboard::Action::HOLD)
						p.position.x += movementSpeed;
					if (k.getKey() == input::Keyboard::Key::A && k.getAction() == input::Keyboard::Action::HOLD)
						p.position.x -= movementSpeed;
				}
				c.view = math::mat4f::viewMatrix(p.position.vec, p.position.vec + c.front, c.up);
			}
		};
	}
}