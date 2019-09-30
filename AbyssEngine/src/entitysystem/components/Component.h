#pragma once
#include "../units/Unit.h"
#include "../units/OwnageSpecifier.h"
#include "../units/LifetimeSpecifier.h"

namespace abyssengine {
	namespace entitysystem
	{
		template <typename UnitType>
		struct Component : public Unit<UnitType>, public OwnedSpecifier, public BinaryLifetime
		{
			Component(const size_t& entityId) : OwnedSpecifier(entityId) {};
			Component() : OwnedSpecifier() {};
		};
	}
}