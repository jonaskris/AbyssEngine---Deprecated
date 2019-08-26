#pragma once
#include "../../utils/TypeIdentifier.h"

namespace abyssengine {
	namespace entitysystem {
		/*
			Used in EachCallable for semantic reasons.
		*/
		class OptionalBase {}; // Used to check if a UnitType is optional with is_base_of in EachCallable.
		template <typename UnitType>
		class Optional : public OptionalBase, public utils::TypeIdentifier<UnitType>
		{
			static_assert(std::is_base_of<UnitBase, UnitType>::value, "UnitType must be derived from Unit!");
		};
	}
}