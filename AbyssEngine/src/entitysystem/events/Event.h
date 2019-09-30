#pragma once

#include "../units/Unit.h"
#include "../units/LifetimeSpecifier.h"
#include "../units/OwnageSpecifier.h"

namespace abyssengine {
	namespace entitysystem {
		template <typename UnitType, typename OwnageSpecifier = OwnerlessSpecifier>
		struct Event : public Unit<UnitType>, public BinaryLifetime, public OwnageSpecifier 
		{ 
			Event() : BinaryLifetime(true) {};
		};

		template <typename UnitType>
		struct TargetedEvent : public Event<UnitType, OwnedSpecifier> {};
	}
}