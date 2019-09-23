#pragma once
#include <utility>
#include "../../utils/TypeIdentifier.h"

namespace abyssengine {
	namespace entitysystem {
		template <typename UnitType>
		class UnitContainer;

		class OwnedUnitIteratorBase
		{
		public:
			virtual bool incrementWhileSmallerThan(const size_t& entityId) = 0;
			virtual std::pair<UnitBase*, size_t> getGroup() const = 0;
			virtual size_t size() const = 0;
			virtual bool getStoresOwnedUnits() const = 0;
			virtual size_t getUnitTypeIdentifier() const = 0;
			virtual size_t getEntityId() const = 0;
		};

		template <typename UnitType>
		class OwnedUnitIterator : public OwnedUnitIteratorBase
		{
			friend class UnitContainer<UnitType>;

		private:
			UnitContainer<UnitType>* unitContainer;

			// Index of first element and count of units in group.
			std::pair<size_t, size_t> currentGroup = std::pair<size_t, size_t>(0, 0);


			explicit OwnedUnitIterator(UnitContainer<UnitType>* unitContainer) : unitContainer(unitContainer), currentGroup(std::pair(0, 0)) {};
		public:
			/*
				Finds the next group of Units with common entityId.
				Returns false if incrementing leads to out of bounds.
			*/
			bool incrementWhileSmallerThan(const size_t& entityId) override
			{
				if constexpr (std::is_base_of<OwnedUnitBase, UnitType>::value)
				{

					size_t newIndex = currentGroup.first + currentGroup.second;

					while (newIndex < unitContainer->units.size() && (unitContainer->units.at(newIndex).getEntityId() < entityId/* || unitContainer->units.at(newIndex).getIgnore()*/))
						newIndex++;

					if (newIndex == unitContainer->units.size())
						return false;

					size_t newCount = 1;
					size_t firstEntityId = unitContainer->units.at(newIndex).getEntityId();
					while (newIndex + newCount < unitContainer->units.size() && unitContainer->units.at(newIndex + newCount).getEntityId() == firstEntityId)
						newCount++;

					currentGroup = std::pair<size_t, size_t>(newIndex, newCount);
				}
				return true;
			}

			/*
				Gets current group.
				Gets all Units in Unit vector if it doesent store OwnedUnit.
			*/
			std::pair<UnitBase*, size_t> getGroup() const override
			{
				if constexpr (!std::is_base_of<OwnedUnitBase, UnitType>::value)
					return std::pair<UnitBase*, size_t>(static_cast<UnitBase*>(&unitContainer->units.at(0)), unitContainer->size());
				else
					return std::pair<UnitBase*, size_t>(static_cast<UnitBase*>(&unitContainer->units.at(currentGroup.first)), currentGroup.second);
			}
			
			size_t size() const override
			{
				return unitContainer->size();
			}

			bool getStoresOwnedUnits() const override
			{
				return std::is_base_of<OwnedUnitBase, UnitType>::value;
			}

			size_t getUnitTypeIdentifier() const override
			{
				return utils::TypeIdentifier<UnitType>::getIdentifier();
			}

			size_t getEntityId() const override
			{
				if constexpr (std::is_base_of<OwnedUnitBase, UnitType>::value)
					return unitContainer->units.at(currentGroup.first).getEntityId();
				else
					return 0;
			}
		};
	}
}