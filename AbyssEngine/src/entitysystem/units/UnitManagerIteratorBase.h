#pragma once
#include <utility>

struct Unit;

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
		Finds the next group of units with common entityId.

		Returns false if incrementing leads to out of bounds.
	*/
	virtual bool increment() = 0;

	/*
		Gets current group.
		Returns all units in unit vector if it stores type with UnitTag_Untargeted.
	*/
	virtual std::pair<Unit*, size_t> getGroup() const = 0;

	/*
		Gets the unit type identifier of the units being iterated on.
	*/
	virtual size_t getUnitTypeIdentifier() const = 0;

	/*
		Returns whether UnitType is base of UnitTag_Untargeted.
	*/
	virtual bool getStoresUntargeted() const = 0;

	/*
		Resets iterator to beginning of the unit vector.
	*/
	virtual UnitManagerIteratorBase* begin() = 0;

	/*
		Returns size of unit vector of UnitManager (Not queue).
	*/
	virtual size_t size() const = 0;

	/*
		For sorting iterators by size of unit vector of UnitManager (Not queue).
	*/
	bool operator < (const UnitManagerIteratorBase& other) const { return size() < other.size(); }
};