#pragma once
#include <utility>

namespace entitysystem
{
	struct UnitBase;

	/*
		A generic iterator for use with UnitManager.
		Used to increment over UnitManagers in terms of groups.
	*/
	class UnitManagerIteratorBase
	{
	protected:
		UnitManagerIteratorBase() {};
	public:

		/*
			Finds the next group of Units with common entityId.
			Returns false if incrementing leads to out of bounds.
		*/
		virtual bool incrementWhileSmallerThan(const size_t& entityId) = 0;

		/*
			Gets current group.
			Returns all Units in Unit vector if it stores type with UnitTag_Untargeted.
		*/
		virtual std::pair<UnitBase*, size_t> getGroup() const = 0;

		/*
			Gets the unit type identifier of the units being iterated on.
		*/
		virtual size_t getUnitTypeIdentifier() const = 0;

		/*
			Returns whether UnitType is base of UnitTag_Untargeted.
		*/
		virtual bool getStoresUntargeted() const = 0;

		/*
			Resets iterator to beginning of the Unit vector.
		*/
		virtual UnitManagerIteratorBase* begin() = 0;

		/*
			Returns size of Unit vector of UnitManager (Not queue).
		*/
		virtual size_t size() const = 0;

		/*
			For sorting iterators by size of Unit vector of UnitManager (Not queue).
		*/
		bool operator < (const UnitManagerIteratorBase& other) const { return size() < other.size(); }
	};
}