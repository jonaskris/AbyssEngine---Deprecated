#pragma once
#include "../systems/System.h"
#include "../defaultcomponents/Spatial.h"
#include "../../math/semantics/Time.h"
#include "../../Defines.h"

namespace abyssengine {
	namespace entitysystem {
		class Transform_Updater : public System<Transform_Component>
		{
		private:
			void update(const math::Time& time) override
			{
				updateEntities(time);
			}
		
			void updateEntity(const math::Time& time, UnitGroup& units) override
			{
				std::pair<Transform_Component*, int> transforms = units.get<Transform_Component>();

				for (size_t i = 0; i < transforms.second; i++)
					transforms.first[i].update(entityManager);
			}
		};
	}
}