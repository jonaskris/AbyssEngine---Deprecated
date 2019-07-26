#pragma once

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

	/*
		Counter used to give every Unit a unique identifier.
	*/
	class UnitTypeIdentifierCounter
	{
		template <typename UnitType>
		friend struct UnitTypeIdentifier;

		static inline size_t counter = 1;
	};

	/*
		Identifies a UnitType with a unique identifier.
	*/
	template <typename UnitType>
	struct UnitTypeIdentifier
	{
	private:
		static inline size_t identifier = 0;
	public:
		static size_t getIdentifier() {

			if (identifier == 0)
				identifier = UnitTypeIdentifierCounter::counter++;
			return identifier;
		};
	};
}