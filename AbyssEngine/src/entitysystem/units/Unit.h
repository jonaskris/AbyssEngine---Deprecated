#pragma once
#include "Optional.h"

namespace abyssengine {
	namespace entitysystem {
		class UnitBase {};

		template <typename UnitType>
		class Unit : public UnitBase
		{
		public:
			/*
				Used for semantic reasons when declaring an eachcallable.
			*/
			typedef Optional<UnitType> optional;
		};
	}
}