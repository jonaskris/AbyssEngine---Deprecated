#pragma once
#include <vector>
#include <functional>
#include <algorithm>
#include <utility>
#include <type_traits>
#include "../../utils/Algorithm.h"
#include "../../utils/TypeIdentifier.h"
#include "../../utils/Void.h"
#include "OwnedUnit.h"
#include "BatchInsertableUnit.h"
#include "BatchInsertableUnitContainer.h"
#include "BatchErasableUnit.h"
#include "LimitedLifetimeUnit.h"
#include "OwnedUnitIterator.h"

#define UC_DEFAULT_INITIAL_CAPACITY 256

namespace abyssengine {
	namespace entitysystem {
		/*
			UnitContainer is a collection of a specified UnitType.
		*/
		class UnitContainerBase
		{
		protected:
			virtual void insertUnitVirtual(void const* unit) = 0;

		public:
			virtual ~UnitContainerBase() {};

			virtual void* at(const size_t& index) = 0;

			virtual OwnedUnitIteratorBase* begin() = 0;

			template <typename UnitType>
			bool insert(const UnitType& unit)
			{
				if (!storesUnitType<UnitType>())
					return false;
				
				insertUnitVirtual((void* const)&unit);
				return true;
			};

			template <typename UnitType>
			bool storesUnitType()
			{
				return getIdentifier() == utils::TypeIdentifier<UnitType>::getIdentifier();
			};

			virtual void preUpdate() = 0;
			virtual void postUpdate(const float& dt) = 0;

			/*
				Returns the identifier of the UnitType the UnitContainer stores.
			*/
			virtual size_t getIdentifier() const = 0;

			virtual size_t size() const = 0;
		};

		template <typename UnitType>
		class UnitContainer : public UnitContainerBase,
			public std::conditional< std::is_base_of<BatchInsertableUnit, UnitType>::value, BatchInsertableUnitContainer<UnitType>, Void>::type
		{
			static_assert(std::is_base_of<UnitBase, UnitType>::value, "UnitType must be derived from Unit!");
			friend class OwnedUnitIterator<UnitType>;

		protected:
			std::vector<UnitType> units;

			virtual void insertUnitVirtual(void const* unit) override
			{ 	
				if constexpr (std::is_base_of<OwnedUnitBase, UnitType>::value)
					utils::insertSortedReverse(units, *((UnitType * const)unit), [](const UnitType & lhs) { return lhs.getEntityId(); });
				else
					units.push_back(*((UnitType * const)unit));
			}
		public:
			UnitContainer() {};

			virtual ~UnitContainer() {};

			void* at(const size_t& index) override
			{
				return &(units.at(index));
			}

			virtual OwnedUnitIteratorBase* begin() override
			{
				return new OwnedUnitIterator<UnitType>(this);
			}

			virtual void preUpdate() override
			{
				if constexpr (std::is_base_of<BatchInsertableUnit, UnitType>::value)
				{
					// Insert into units vector from insertion queue.
					if constexpr (std::is_base_of<OwnedUnitBase, UnitType>::value)
						for (size_t i = 0; i < BatchInsertableUnitContainer<UnitType>::queue.size(); i++)
								utils::insertSortedReverse(units, BatchInsertableUnitContainer<UnitType>::queue[i], [](const UnitType & unit) { return unit.getEntityId(); });
					else
						units.insert(units.begin(), BatchInsertableUnitContainer<UnitType>::queue.begin(), BatchInsertableUnitContainer<UnitType>::queue.end());

					// Empty insertion queue.
					BatchInsertableUnitContainer<UnitType>::queue.clear();
				}
			}

			virtual void postUpdate(const float& dt) override 
			{
				// Update lifetimes if stores LimitedLifetimeUnit.
				if constexpr (std::is_base_of<LimitedLifetimeUnitBase, UnitType>::value)
					for (size_t i = 0; i < units.size(); i++)
						units[i].lifetime -= dt;

				//// Erase every BatchErasableUnit if erase == true or LimitedLifetimeUnit if lifetime <= 0.
				units.erase(std::remove_if(units.begin(), units.end(), 
					[](const UnitType& unit) 
					{ 
						if constexpr(std::is_base_of<LimitedLifetimeUnitBase, UnitType>::value)
							if(unit.getLifetime() <= 0.0f) return true; 
						if constexpr (std::is_base_of<BatchErasableUnit, UnitType>::value)
							if (unit.getErase()) return true;
						return false;
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