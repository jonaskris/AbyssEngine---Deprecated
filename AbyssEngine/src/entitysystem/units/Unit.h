#pragma once
#include "Optional.h"

namespace abyssengine {
	namespace entitysystem {
		class UnitBase {};

		template <typename UnitType>
		class Unit : public UnitBase
		{
		public:
			typedef Optional<UnitType> optional;
		};
	}
}