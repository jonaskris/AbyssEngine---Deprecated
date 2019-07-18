#pragma once
#include <utility>
#include "Unit.h"
#include "UnitTags.h"
#include "UnitManager.h"
#include "UnitManagerIteratorBase.h"

class UnitManagerBase;

template <typename UnitType>
struct Event;

/*
	Used to increment over UnitManagers in terms of groups.
*/
template <typename UnitType>
class UnitManagerIterator : public UnitManagerIteratorBase
{
	friend class UnitManager<UnitType>;
private:
	UnitManager<UnitType>* unitManager;

	// Index of first element and count of elements in group.
	std::pair<size_t, size_t> currentGroup;

	explicit UnitManagerIterator(UnitManager<UnitType>* unitManager) : unitManager(unitManager), currentGroup(std::pair(0, 0)) { };

public:

	/*
		Finds the next group of units with common entityId.

		Returns false if incrementing leads to out of bounds.
	*/
	bool increment() override
	{
		size_t newFirstIndex = currentGroup.first + currentGroup.second;
		size_t count = 0;
		size_t sizeUnits = unitManager->units.size();

		if (newFirstIndex >= sizeUnits)
			return false;

		size_t entityIdFirstIndex = unitManager->units.at(newFirstIndex);

		while (newFirstIndex + count < sizeUnits && unitManager->units.at(newFirstIndex + count).getEntityId() == entityIdFirstIndex)
			count++;

		currentGroup = std::pair(newFirstIndex, count);
		return true;
	}

	/*
		Gets current group.
		Returns all units in unit vector if it stores type with UnitTag_Untargeted.
	*/
	std::pair<Unit*, size_t> getGroup() const override
	{
		if constexpr (std::is_base_of<UnitTag_Untargeted, UnitType>::value)
			return std::pair<Unit*, size_t>(static_cast<Unit*>(&unitManager->units.at(0)), unitManager->units.size());
		else
			return std::pair<Unit*, size_t>(static_cast<Unit*>(&unitManager->units.at(currentGroup.first)), currentGroup.second);
	}

	/*
		Gets the UnitTypeIdentifier of the units being iterated on.
	*/
	virtual size_t getUnitTypeIdentifier() const override
	{
		return UnitType::getIdentifier();
	}

	/*
		Returns whether UnitType is base of UnitTag_Untargeted.
	*/
	virtual bool getStoresUntargeted() const override
	{
		return std::is_base_of<UnitTag_Untargeted, UnitType>::value;
	}

	/*
		Resets iterator to beginning of the unit vector.
	*/
	UnitManagerIteratorBase* begin() override
	{
		currentGroup = std::pair<size_t, size_t>(0, 0);
		return this;
	}

	/*
		Returns size of unit vector of UnitManager (Not queue).
	*/
	size_t size() const override
	{
		return unitManager->units.size();
	}
};