#pragma once
#include "../units/OwnedUnit.h"
#include "../units/BatchErasableUnit.h"
#include "../units/BatchInsertableUnit.h"

namespace abyssengine {
	namespace entitysystem
	{
		/*
			Entities are made up of components.

			Components can be set to be erased which takes effect at end of current update.
		*/
		template <typename UnitType>
		struct Component : public OwnedUnit<UnitType>, public BatchErasableUnit, public BatchInsertableUnit
		{

		};
	}
}