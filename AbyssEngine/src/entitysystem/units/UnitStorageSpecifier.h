#pragma once

namespace abyssengine {
	namespace entitysystem
	{
		/*
			Used to specify storage conditions for a specific UnitType.

			InitialStorageCapacity optionally defines the initial reserved capacity of vector in UnitManager that stores the UnitType.
			If UnitStorageSpecifier is not used, UM_DEFAULT_INITIAL_CAPACITY in UnitManager.h will be used.
		*/
		template <typename UnitType>
		struct UnitStorageSpecifier
		{
		private:
			static size_t initialStorageCapacity;
		public:
			static size_t getInitialStorageCapacity() { return initialStorageCapacity; }
		};
		template <typename UnitType>
		size_t UnitStorageSpecifier<UnitType>::initialStorageCapacity = 0;
	}
}