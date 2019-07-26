#pragma once
#include "../systems/System.h"
#include "../defaultcomponents/Graphics.h"

namespace abyssengine {

	using UnitGroup = entitysystem::UnitGroup;

	template <typename... UnitTypes>
	using System = entitysystem::System<UnitTypes...>;

	class Camera_Movement : public System<Camera_Component>
	{
	private:
		void update(const double& dt) override
		{
			updateEntities(dt);
		}

		void updateEntity(const double& dt, UnitGroup& units) override
		{
			Camera_Component& c = units.get<Camera_Component>().first[0];

			c.viewMatrix = math::mat4f::viewMatrix(c.lookFrom, c.lookAt, math::vec3f{ 0.0f, 1.0f, 0.0f });
		}
	};
}