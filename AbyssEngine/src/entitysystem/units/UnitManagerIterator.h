#pragma once
#include <utility>
#include "Unit.h"
#include "UnitTags.h"
#include "UnitManager.h"
#include "UnitManagerIteratorBase.h"

namespace entitysystem
{
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
		std::pair<size_t, size_t> currentGroup = std::pair<size_t, size_t>(0, 0);

		explicit UnitManagerIterator(UnitManager<UnitType>* unitManager) : unitManager(unitManager), currentGroup(std::pair(0, 0)) { };
	public:

		/*
			Finds the next group of Units with common entityId.
			Returns false if incrementing leads to out of bounds.
		*/
		bool incrementWhileSmallerThan(const size_t& entityId) override
		{
			size_t newIndex = currentGroup.first + currentGroup.second;

			while (newIndex < unitManager->units.size() && (unitManager->units.at(newIndex).getEntityId() < entityId || unitManager->units.at(newIndex).getIgnore()))
				newIndex++;

			if (newIndex == unitManager->units.size())
				return false;

			size_t newCount = 1;
			size_t firstEntityId = unitManager->units.at(newIndex).getEntityId();
			while (newIndex + newCount < unitManager->units.size() && unitManager->units.at(newIndex + newCount).getEntityId() == firstEntityId)
				newCount++;

			currentGroup = std::pair<size_t, size_t>(newIndex, newCount);
			return true;
		}

		/*
			Gets current group.
			Gets all Units in Unit vector if it stores type with UnitTag_Untargeted.
		*/
		std::pair<UnitBase*, size_t> getGroup() const override
		{
			if constexpr (std::is_base_of<UnitTag_Untargeted, UnitType>::value)
				return std::pair<UnitBase*, size_t>(static_cast<UnitBase*>(&unitManager->units.at(0)), unitManager->units.size());
			else
				return std::pair<UnitBase*, size_t>(static_cast<UnitBase*>(&unitManager->units.at(currentGroup.first)), currentGroup.second);
		}

		/*
			Gets the UnitTypeIdentifier of the Units being iterated on.
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
			static bool storesUntargeted = std::is_base_of<UnitTag_Untargeted, UnitType>::value;
			return storesUntargeted;
		}

		/*
			Resets iterator to beginning of the Unit vector.
		*/
		UnitManagerIteratorBase* begin() override
		{
			if (getStoresUntargeted())
				return this;

			size_t newIndex = 0;
			size_t newCount = 1;
			size_t firstEntityId = unitManager->units.at(newIndex).getEntityId();
			while (newIndex + newCount < unitManager->units.size() && unitManager->units.at(newIndex + newCount).getEntityId() == firstEntityId)
				newCount++;

			currentGroup = std::pair<size_t, size_t>(newIndex, newCount);

			return this;
		}

		/*
			Returns size of Unit vector of UnitManager (Not queue).
		*/
		size_t size() const override
		{
			return unitManager->units.size();
		}
	};
}