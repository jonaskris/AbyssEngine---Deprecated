#pragma once
#include <type_traits>
#include <functional>
#include <vector>
#include <set>
#include <algorithm>
#include "systems/System.h"
#include "units/UnitManager.h"
#include "units/UnitManagerIterator.h"
#include "units/UnitGroup.h"
#include "components/Component.h"

struct Unit;

/*
	Stores entities, systems and units,
	and defines their relationship.
*/
class EntityManager
{
private:
	/*
		Systems.
	*/
	std::vector<SystemBase*> systems;

	/*
		Units and entities.
	*/
	std::vector<UnitManagerBase*> unitManagers;
	unsigned int entityIdCounter = 1; // For assigning entityId.

	/*
		Unpacks parameter pack of units when creating an entity, base case.
	*/
	template <typename UnitType>
	void unpackAndStoreUnitsInManagers(const size_t& entityId, const UnitType& unit)
	{
		static_assert(std::is_base_of<Unit, UnitType>::value && std::is_base_of<UnitTypeIdentifier<UnitType>, UnitType>::value, "UnitType must be derived from Unit and UnitTypeIdentifier!");

		newUnit(entityId, unit);
	}

	/*
		Unpacks parameter pack of units when creating an entity, recursive case.
	*/
	template <typename UnitType, typename... Rest>
	void unpackAndStoreUnitsInManagers(const size_t& entityId, const UnitType& unit, const Rest&... rest)
	{
		static_assert(std::is_base_of<Unit, UnitType>::value && std::is_base_of<UnitTypeIdentifier<UnitType>, UnitType>::value, "UnitType must be derived from Unit and UnitTypeIdentifier!");

		newUnit(entityId, unit);
		unpackAndStoreUnitsInManagers(entityId, rest...); 
	}

	/*
		Unpacks parameter pack of unit types, base case.
	*/
	template <typename UnitType>
	static void unpackUnitTypesHelper(std::vector<size_t>& unitIdentifiersUnpacking)
	{
		static_assert(std::is_base_of<Unit, UnitType>::value && std::is_base_of<UnitTypeIdentifier<UnitType>, UnitType>::value, "UnitType must be derived from Unit and UnitTypeIdentifier!");

		unitIdentifiersUnpacking.push_back(UnitType::getIdentifier());
	}

	/*
		Unpacks parameter pack of unit types, recursive case.
	*/
	template <typename F, typename UnitType, typename... Rest>
	static void unpackUnitTypesHelper(std::vector<size_t>& unitIdentifiersUnpacking)
	{
		static_assert(std::is_base_of<Unit, UnitType>::value && std::is_base_of<UnitTypeIdentifier<UnitType>, UnitType>::value, "UnitType must be derived from Unit and UnitTypeIdentifier!");

		unitIdentifiersUnpacking.push_back(UnitType::getIdentifier());
		unpackUnitTypesHelper<F, Rest...>(unitIdentifiersUnpacking);
	}

	/*
		Unpacks parameter pack of unit types.
	*/
	template <typename... UnitTypes>
	static std::vector<size_t> unpackUnitTypes()
	{
		std::vector<size_t> unitIdentifiersUnpacking;
		unpackUnitTypesHelper<UnitTypes...>(unitIdentifiersUnpacking);
		return unitIdentifiersUnpacking;
	}

public:
	EntityManager() {};
	~EntityManager() 
	{
		for (size_t i = 0; i < unitManagers.size(); i++)
			delete unitManagers[i];
		for (size_t i = 0; i < systems.size(); i++)
			delete systems[i];
	};

	/*
		Executes a System.updateEntity on every entity that has specified set of unit types.
	*/
	void each(const double& dt, SystemBase* system, std::vector<size_t>& unitIdentifiers)
	{
		if (unitIdentifiers.size() == 0)
			return;

		// Get an iterator to every relevant unitManager.
		std::vector<UnitManagerIteratorBase*> unitManagerIterators;
		for (size_t i = 0; i < unitIdentifiers.size(); i++)
			for (size_t j = 0; j < this->unitManagers.size(); j++)
				if (unitIdentifiers.at(i) == this->unitManagers.at(j)->getIdentifier())
					unitManagerIterators.push_back(this->unitManagers.at(j)->begin());

		// Check that the UnitManagers the UnitManagerIterators point to are not empty (Unit vector, not queue).
		for (size_t i = 0; i < unitManagerIterators.size(); i++)
			if (unitManagerIterators.at(i)->size() == 0)
				return;

		// Check if iterator UnitManager was found for each of unitIdentifiers.
		if (unitIdentifiers.size() != unitManagerIterators.size())
			return;

		// To make sure an each on only untargeted units is only done once (since an iterator on untargeted units is not incremented and wont end the loop that way).
		bool allUntargeted = true;
		for (size_t i = 0; i < unitManagerIterators.size(); i++)
			if (!unitManagerIterators.at(i)->getStoresUntargeted())
				allUntargeted = false;

 		size_t biggestEntityId = 0;
		// For every iterator
		do 
		{
			for (size_t i = 0; i < unitManagerIterators.size(); i++)
			{
				if (unitManagerIterators.at(i)->getStoresUntargeted())
					continue;

				do 
				{
					if (!unitManagerIterators.at(i)->increment())
						goto end;
				} while (unitManagerIterators.at(i)->getGroup().first->getEntityId() < biggestEntityId);

				if (unitManagerIterators.at(i)->getGroup().first->getEntityId() > biggestEntityId)
				{
					biggestEntityId = unitManagerIterators.at(i)->getGroup().first->getEntityId();

					if(i != 0)
						goto continueOuter;
				}
				
			}

			{
				UnitGroup unitGroup;
				for (size_t i = 0; i < unitManagerIterators.size(); i++)
					unitGroup.units[unitManagerIterators.at(i)->getUnitTypeIdentifier()] = unitManagerIterators.at(i)->getGroup();
				system->updateEntity(dt, unitGroup);

				biggestEntityId++; 
			}

		continueOuter:;
		} while (!allUntargeted);
		end:;
	}

	/*
		Creates an entity.
		Returns the entity.
	*/
	size_t newEntity()
	{
		return entityIdCounter++;
	}

	/*
		Creates an entity and stores units assigned to the new entity.
		Returns the entity.
	*/
	template <typename... UnitTypes>
	size_t newEntity(const UnitTypes&... units)
	{
		size_t newEntity = entityIdCounter++;
	
		unpackAndStoreUnitsInManagers(newEntity, units...);
	
		return newEntity;
	}

	/*
		Stores a unit in a UnitManager and assigns it to the specified entity.
	*/
	template <typename UnitType>
	size_t newUnit(const size_t& entityId, UnitType unit)
	{
		static_assert(std::is_base_of<Unit, UnitType>::value && std::is_base_of<UnitTypeIdentifier<UnitType>, UnitType>::value, "UnitType must be derived from Unit and UnitTypeIdentifier!");

		if (unit.getEntityId() == 0)
			unit.setEntityId(entityId);

		// Try storing unit in an existing manager.
		for (size_t i = 0; i < unitManagers.size(); i++)
			if (unitManagers.at(i)->storesUnitType<UnitType>())
			{
				unitManagers.at(i)->insertUnit(unit);
				return unit.getEntityId();
			}
		
		// If unsuccessful in storing unit above, there were no UnitManager that stores given unit type.
		// Create a new unit manager that stores the unit type, and insert the unit into the new manager. 
		unitManagers.push_back(new UnitManager<UnitType>());
		unitManagers.back()->insertUnit(unit);

		return unit.getEntityId();
	}

	/*
		Stores a unit in a UnitManager and assigns it to a new entity.

		Returns entityId
	*/
	template <typename UnitType>
	size_t newUnit(UnitType unit)
	{
		static_assert(std::is_base_of<Unit, UnitType>::value && std::is_base_of<UnitTypeIdentifier<UnitType>, UnitType>::value, "UnitType must be derived from Unit and UnitTypeIdentifier!");

		if (unit.getEntityId() == 0)
			unit.setEntityId(newEntity());

		// Try storing unit in an existing manager.
		for (size_t i = 0; i < unitManagers.size(); i++)
			if (unitManagers.at(i)->storesUnitType<UnitType>())
			{
				unitManagers.at(i)->insertUnit(unit);
				return unit.getEntityId();
			}

		// If unsuccessful in storing unit above, there were no UnitManager that stores given unit type.
		// Create a new UnitManager that stores the unit type, and insert the unit into the new manager. 
		unitManagers.push_back(new UnitManager<UnitType>());
		unitManagers.back()->insertUnit(unit);
	
		return unit.getEntityId();
	}

	/*
		Set units of entity to be erased after current update, the component will still be considered by systems.
		If no UnitTypes are specified, all units of the entity are set to be erased.

		Note: Events are erased after every update automatically.
	*/
	template <typename... UnitTypes>
	void setErase(const size_t& entityId)
	{	
		if constexpr (sizeof...(UnitTypes) == 0)
		{
			for (size_t i = 0; i < unitManagers.size(); i++)
				unitManagers[i]->setErase(entityId);
				
		} else {
			std::vector<size_t> unitIdentifiers = unpackUnitTypes<UnitTypes...>();

			for (size_t i = 0; i < unitManagers.size(); i++)
				if (std::find(unitIdentifiers.begin(), unitIdentifiers.end(), unitManagers[i]->getIdentifier()) != unitIdentifiers.end())
					unitManagers[i]->setErase(entityId);

		}
	}

	/*
		Set units of entity to be ignored by systems and erased on end of update.
		If no UnitTypes are specified, all units of the entity are set to be ignored.
	*/
	template <typename... UnitTypes>
	void setIgnore(const size_t& entityId)
	{
		if constexpr (sizeof...(UnitTypes) == 0)
		{
			for (size_t i = 0; i < unitManagers.size(); i++)
				unitManagers[i]->setIgnore(entityId);

		} else {
			std::vector<size_t> unitIdentifiers = unpackUnitTypes<UnitTypes...>();

			for (size_t i = 0; i < unitManagers.size(); i++)
				if (std::find(unitIdentifiers.begin(), unitIdentifiers.end(), unitManagers[i]->getIdentifier()) != unitIdentifiers.end())
					unitManagers[i]->setIgnore(entityId);
		}
	}

	/*
		Registers a system that will be used to update units on update.
		ConstructorArgs are optional.
		Returns whether the system was registered successfully.
	*/
	template <typename SystemType>
	void registerSystem(SystemType* system)
	{
		static_assert(std::is_base_of<SystemBase, SystemType>::value, "SystemType must be derived from SystemBase!");
		
		systems.push_back(system);
		systems.back()->setEntityManager(this);
	}

	/*
		Updates every System and UnitManager.
	*/
	void update(const double& dt)
	{
		// PreUpdate every UnitManager. Inserts into unit vector from insertionQueue.
		for (size_t i = 0; i < unitManagers.size(); i++)
			unitManagers.at(i)->preUpdate();

		// Update every system.
		for (size_t i = 0; i < systems.size(); i++)
			systems.at(i)->update(dt);

		// PostUpdate every UnitManager. Updates lifetimes and erases units set to be erased.
		for (size_t i = 0; i < unitManagers.size(); i++)
			unitManagers.at(i)->postUpdate(dt);
	}

	/*
		Inserts units from UnitManager queues.
		Used for testing purposes.
	*/
	void insertFromQueues()
	{
		for (size_t i = 0; i < unitManagers.size(); i++)
			unitManagers.at(i)->insertFromQueue();
	}

	/*
		Retrieves vector to all units by type.
	*/
	template <typename UnitType>
	std::vector<UnitType>* getUnitVector()
	{
		static_assert(std::is_base_of<Unit, UnitType>::value && std::is_base_of<UnitTypeIdentifier<UnitType>, UnitType>::value, "UnitType must be derived from Unit and UnitTypeIdentifier!");

		for (size_t i = 0; i < unitManagers.size(); i++)
			if (unitManagers.at(i)->storesUnitType<UnitType>())
				return static_cast<UnitManager<UnitType>*>(unitManagers.at(i))->getUnits();
		
		return nullptr;
	}

	/*
		Retrieves summed size of every UnitManager.
	*/
	size_t sizeUnits() const
	{
		size_t sum = 0;
		for (size_t i = 0; i < unitManagers.size(); i++)
				sum += unitManagers.at(i)->size();

		return sum;
	};

	/*
		Retrieves size of UnitManager that stores specified type.
	*/
	template <typename UnitType>
	size_t sizeUnitsType() const
	{ 
		static_assert(std::is_base_of<Unit, UnitType>::value && std::is_base_of<UnitTypeIdentifier<UnitType>, UnitType>::value, "UnitType must be derived from Unit and UnitTypeIdentifier!");

		for (size_t i = 0; i < unitManagers.size(); i++)
			if (UnitType::getIdentifier() == unitManagers.at(i)->getIdentifier())
				return unitManagers.at(i)->size();
		return 0;
	};

	size_t sizeUnitManagers() const { return unitManagers.size(); };
	size_t sizeSystems() const { return systems.size(); };
};