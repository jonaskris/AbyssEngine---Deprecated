#pragma once
#include <vector>
#include <functional>
#include <algorithm>
#include <utility>
#include "Unit.h"
#include "../utils/Algorithm.h"
#include "UnitManagerIterator.h"

#define UM_DEFAULT_INITIAL_CAPACITY 256

namespace entitysystem
{
	/*
		UnitManager is a sorted collection of a specified UnitType.
	*/
	class UnitManagerBase
	{
	private:
		virtual void addToInsertionQueue(UnitBase const* component) = 0;

	public:
		virtual ~UnitManagerBase() {};

		virtual UnitBase* unitAt(const size_t& index) = 0;

		/*
			Returns pointer of first Unit with entityId, and how many preceding Units has the same entityId.
		*/
		virtual std::pair<UnitBase*, size_t> unitsOf(const size_t& entityId) = 0;

		virtual void setErase(const size_t& entityId) = 0;
		virtual void setIgnore(const size_t& entityId) = 0;


		/*
			Inserts Units from queue.
		*/
		virtual void insertFromQueue() = 0;

		/*
			Inserts Units from queue.
		*/
		virtual void preUpdate() = 0;

		/*
			Updates lifetimes and erases Units.
		*/
		virtual void postUpdate(const double& dt) = 0;

		template <typename UnitType>
		void insertUnit(const UnitType& unit) {
			static_assert(std::is_base_of<UnitBase, UnitType>::value, "UnitType must be derived from Unit!");

			addToInsertionQueue(&unit);
		};

		template <typename UnitType>
		bool storesUnitType() {
			static_assert(std::is_base_of<UnitBase, UnitType>::value, "UnitType must be derived from Unit!");

			return getIdentifier() == UnitType::getIdentifier();
		};

		/*
			Returns a UnitManagerIterator to the beginning of the UnitManager.
		*/
		virtual UnitManagerIteratorBase* begin() = 0;

		/*
			Returns the identifier of the UnitType the UnitManager stores.
		*/
		virtual size_t getIdentifier() const = 0;

		virtual size_t size() const = 0;
	};

	template <typename UnitType>
	class UnitManager : public UnitManagerBase
	{
		static_assert(std::is_base_of<UnitBase, UnitType>::value, "UnitType must be derived from Unit!");

		friend class UnitManagerIterator<UnitType>;
	private:
		std::vector<UnitType> insertionQueue; // To avoid invalidating iterators during system updates.
		std::vector<UnitType> units;

		UnitManagerIterator<UnitType> iterator = UnitManagerIterator<UnitType>(this);

		void addToInsertionQueue(UnitBase const* unit) override
		{
			insertionQueue.push_back(*((UnitType*)unit));
		}

	public:
		UnitManager()
		{
			size_t initialStorageCapacity;

			if constexpr (std::is_base_of<UnitStorageSpecifier<UnitType>, UnitType>::value)
				initialStorageCapacity = UnitStorageSpecifier<UnitType>::getInitialStorageCapacity();
			else
				initialStorageCapacity = UM_DEFAULT_INITIAL_CAPACITY;

			units.reserve(initialStorageCapacity);
		};

		~UnitManager() {};

		UnitBase* unitAt(const size_t& index) override
		{
			return &(units[index]);
		}

		/*
			Returns pointer of first Unit with entityId, and how many preceding Units has the same entityId.
		*/
		std::pair<UnitBase*, size_t> unitsOf(const size_t& entityId) override
		{
			if (units.size() == 0)
				return std::pair<UnitBase*, size_t>(static_cast<UnitBase*>(nullptr), 0);

			std::pair<size_t, size_t> indicesSpan = binarySearchGroup(units, entityId, 0, units.size() - 1, [](const UnitType& lhs) { return lhs.getEntityId(); });

			return std::pair(&(units.at(indicesSpan.first)), (size_t)(indicesSpan.second - indicesSpan.first));
		}

		void setErase(const size_t& entityId) override
		{
			if (units.size() == 0)
				return;

			std::pair<size_t, size_t> indicesSpan = binarySearchGroup(units, entityId, 0, units.size() - 1, [](const UnitType& lhs) { return lhs.getEntityId(); });

			for (size_t i = (size_t)indicesSpan.first; i < indicesSpan.second; i++)
				units.at(i).setErase();
		}

		void setIgnore(const size_t& entityId) override
		{
			if (units.size() == 0)
				return;

			std::pair<size_t, size_t> indicesSpan = binarySearchGroup(units, entityId, 0, units.size() - 1, [](const UnitType& lhs) { return lhs.getEntityId(); });

			for (size_t i = (size_t)indicesSpan.first; i < indicesSpan.second; i++)
				units.at(i).setIgnore();
		}

		/*
			Retrieves pointer to Unit vector.
		*/
		std::vector<UnitType>* getUnits()
		{
			return &units;
		}

		/*
			Inserts Units from queue.
		*/
		void insertFromQueue() override
		{
			// Insert into Units vector from insertion queue.
			for (size_t i = 0; i < insertionQueue.size(); i++)
				insertSortedReverse(units, insertionQueue[i], [](const UnitType& lhs) { return lhs.getEntityId(); });

			// Empty insertion queue.
			insertionQueue.clear();
		}

		/*
			Inserts Units from queue.
		*/
		void preUpdate() override
		{
			insertFromQueue();
		}

		/*
			Updates lifetimes and erases Units.
		*/
		void postUpdate(const double& dt) override
		{
			// Update lifetimes if stores LimitedLifetimeComponent.
			if constexpr (std::is_base_of<LimitedLifetimeUnitBase, UnitType>::value)
			{
				for (size_t i = 0; i < units.size(); i++)
					units[i].lifetime -= (float)dt;
			}

			// Erase every Unit where getErase() == true.
			units.erase(std::remove_if(units.begin(), units.end(), [](const UnitType & unit) { return unit.getErase(); }), units.end());
		}

		/*
			Returns a UnitManagerIterator to the beginning of the UnitManager.
		*/
		UnitManagerIteratorBase* begin() override
		{
			return iterator.begin();
		}

		size_t getIdentifier() const override { return UnitType::getIdentifier(); };

		size_t size() const override { return units.size() + insertionQueue.size(); };
	};
}