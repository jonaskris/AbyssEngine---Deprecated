#pragma once
#include "UnitContainer.h"
#include "OwnedUnit.h"

namespace abyssengine {
	namespace entitysystem {
		template <typename UnitType>
		class BatchInsertableUnitContainer
		{
		protected:
			std::vector<UnitType> queue;
		};
	}
}