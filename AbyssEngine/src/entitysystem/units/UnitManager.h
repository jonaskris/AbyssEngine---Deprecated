#pragma once
#include <vector>
#include <typeinfo>
#include <functional>
#include <algorithm>
#include <utility>
#include "Unit.h"
#include "../components/Component.h"
#include "../events/Event.h"
#include "../../Algorithm.h"
#include "UnitManagerIterator.h"

#define UM_DEFAULT_INITIAL_CAPACITY 256

/*
	UnitManager is a sorted collection of a specified type of unit.
*/
class UnitManagerBase
{
private:
	virtual void addToInsertionQueue(Unit const* component) = 0;

public:
	virtual ~UnitManagerBase() {};

	virtual Unit* unitAt(const size_t& index) = 0;

	/*
		Returns pointer of first unit with entityId, and how many preceding units has the same entityId.
	*/
	virtual std::pair<Unit*, size_t> unitsOf(const size_t& entityId) = 0;

	virtual void setErase(const size_t& entityId) = 0;
	virtual void setIgnore(const size_t& entityId) = 0;


	/*
		Inserts units from queue.
	*/
	virtual void insertFromQueue() = 0;

	/*
		Inserts units from queue.
	*/
	virtual void preUpdate() = 0;

	/*
		Updates lifetimes and erases units.
	*/
	virtual void postUpdate(const double& dt) = 0;

	template <typename UnitType>
	void insertUnit(const UnitType& unit) {
		static_assert(std::is_base_of<Unit, UnitType>::value && std::is_base_of<UnitTypeIdentifier<UnitType>, UnitType>::value, "UnitType must be derived from Unit and UnitTypeIdentifier!");

		addToInsertionQueue(&unit);
	};

	template <typename UnitType>
	bool storesUnitType() {
		static_assert(std::is_base_of<UnitTypeIdentifier<UnitType>, UnitType>::value && std::is_base_of<Unit, UnitType>::value, "UnitType must be derived from Unit and UnitTypeIdentifier!");

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
	static_assert(std::is_base_of<Unit, UnitType>::value && std::is_base_of<UnitTypeIdentifier<UnitType>, UnitType>::value, "UnitType must be derived from Unit and UnitTypeIdentifier!");

	friend class UnitManagerIterator<UnitType>;
private:
	std::vector<UnitType> insertionQueue; // To avoid invalidating iterators during system updates.
	std::vector<UnitType> units;

	UnitManagerIterator<UnitType> iterator = UnitManagerIterator<UnitType>(this);

	void addToInsertionQueue(Unit const* unit) override
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

	Unit* unitAt(const size_t& index) override
	{
		return &(units[index]);
	}

	/*
		Returns pointer of first unit with entityId, and how many preceding units has the same entityId.
	*/
	std::pair<Unit*, size_t> unitsOf(const size_t& entityId) override
	{
		if (units.size() == 0)
			return std::pair(static_cast<Unit*>(nullptr), 0);

		std::pair<size_t, size_t> indicesSpan = binarySearchGroup(units, entityId, 0, units.size() - 1);

		return std::pair(&(units.at(indicesSpan.first)), (size_t)(indicesSpan.second - indicesSpan.first));
	}

	void setErase(const size_t& entityId) override
	{
		if (units.size() == 0)
			return;

		std::pair<size_t, size_t> indicesSpan = binarySearchGroup(units, entityId, 0, units.size() - 1);

		for (size_t i = (size_t)indicesSpan.first; i < indicesSpan.second; i++)
			units.at(i).setErase();
	}

	void setIgnore(const size_t& entityId) override
	{
		if (units.size() == 0)
			return;

		std::pair<size_t, size_t> indicesSpan = binarySearchGroup(units, entityId, 0, units.size() - 1);

		for (size_t i = (size_t)indicesSpan.first; i < indicesSpan.second; i++)
			units.at(i).setIgnore();
	}

	/*
		Retrieves pointer to unit vector.
	*/
	std::vector<UnitType>* getUnits()
	{
		return &units;
	}

	/*
		Inserts units from queue.
	*/
	void insertFromQueue() override
	{
		// Insert into units vector from insertion queue.
		for (size_t i = 0; i < insertionQueue.size(); i++)
		{
			insertSorted(units, insertionQueue[i]);
		}

		// Empty insertion queue.
		insertionQueue.clear();
	}

	/*
		Inserts units from queue.
	*/
	void preUpdate() override
	{
		insertFromQueue();
	}

	/*
		Updates lifetimes and erases units.
	*/
	void postUpdate(const double& dt) override
	{
		// Update lifetimes if stores LimitedLifetimeComponent.
		if constexpr (std::is_base_of<LimitedLifetimeUnit, UnitType>::value)
		{
			for (size_t i = 0; i < units.size(); i++)
				units[i].lifetime -= (float)dt;
		}

		// Erase every unit where getErase() == true.
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