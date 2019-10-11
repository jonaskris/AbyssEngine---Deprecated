#pragma once
#include <vector>
#include <functional>
#include <algorithm>
#include <utility>
#include <type_traits>
#include "UnitContainerBase.h"
#include "../../utils/Algorithm.h"
#include "../../utils/TypeIdentifier.h"
#include "LifetimeSpecifier.h"
#include "UnitIterator.h"

//#include "SpecializedUnitContainers.h"

#define UC_DEFAULT_INITIAL_CAPACITY 256

namespace abyssengine {
	namespace entitysystem {
		template <typename UnitType>
		class UnitContainer : public UnitContainerBase
		{
			static_assert(std::is_base_of<UnitBase, UnitType>::value, "UnitType must be derived from Unit!");
			friend class UnitIterator<UnitType>;

		protected:
			std::vector<UnitType> units;
			std::vector<UnitType> queue;

			virtual void insertUnitVirtual(void const* unit) override
			{ 	
				if constexpr (std::is_base_of<OwnedSpecifier, UnitType>::value)
					utils::insertSortedReverse(queue, *((UnitType* const)unit), [](const UnitType & unit) { return unit.getEntityId(); });
				else
					queue.push_back(*((UnitType* const)unit));
			}

			virtual std::pair<void*, size_t> getUnitsVirtual(const size_t& entityId) override
			{
				//static_assert(std::is_base_of<OwnedSpecifier, UnitType>::value, "UnitType must be derived from OwnedSpecifier!");

				std::pair<size_t, size_t> group = utils::binarySearchGroup(units, entityId, 0, units.size(), [](const UnitType & unit) { return unit.getEntityId(); });
				return std::pair<void*, size_t>((void*)&(units.at(group.first)), group.second);
			}

		public:
			UnitContainer() {};

			virtual ~UnitContainer() {};

			//void* at(const size_t& index) override
			//{
			//	return &(units.at(index));
			//}

			virtual UnitIteratorBase* begin() override
			{
				return new UnitIterator<UnitType>(this);
			}

			virtual void preUpdate() override
			{
				// Insert into units vector from insertion queue.
				if constexpr (std::is_base_of<OwnedSpecifier, UnitType>::value)
					for (size_t i = 0; i < queue.size(); i++)
							utils::insertSortedReverse(units, queue[i], [](const UnitType& unit) { return unit.getEntityId(); });
				else
					units.insert(units.begin(), queue.begin(), queue.end());

				// Empty insertion queue.
				queue.clear();
			}

			virtual void postUpdate(const float& dt) override 
			{
				// Update lifetimes if stores Unit with TemporalLifetime.
				if constexpr (std::is_base_of<TemporalLifetime, UnitType>::value)
					for (size_t i = 0; i < units.size(); i++)
						units[i].lifetime -= dt;

				// Erase Units where getErase() = true;
				/// Todo: Only run this if a flag is set.
				units.erase(std::remove_if(units.begin(), units.end(), 
					[](const UnitType& unit) 
					{ 
						return unit.getErase();
					}), units.end());
			}

			/*
				Retrieves pointer to Unit vector.
			*/
			std::vector<UnitType>* getUnits()
			{
				return &units;
			}

			/*
				Returns the identifier of the UnitType the UnitContainer stores.
			*/
			size_t getIdentifier() const override { return utils::TypeIdentifier<UnitType>::getIdentifier(); };

			size_t size() const override { return units.size(); };
		};
	}
}