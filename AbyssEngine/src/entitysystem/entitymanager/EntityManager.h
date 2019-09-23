#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include "../systems/System.h"
#include "../units/Unit.h"
#include "../units/OwnedUnit.h"
#include "../units/UnitContainer.h"
#include "../units/OwnedUnitIterator.h"
#include "../units/UnitGroup.h"
#include "EachCallable.h"
#include "../../math/semantics/Time.h"

namespace abyssengine {
	namespace entitysystem {
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
			std::vector<UnitContainerBase*> unitContainers;
			size_t entityIdCounter = 1; // For assigning entityId.

			/*
				Unpacks parameter pack of units when creating an entity, base case.
			*/
			template <typename UnitType>
			void unpackAndStoreUnitsInContainers(const size_t& entityId, const UnitType& unit)
			{
				static_assert(std::is_base_of<UnitBase, UnitType>::value, "UnitType must be derived from UnitBase!");

				newUnit(entityId, unit);
			}

			/*
				Unpacks parameter pack of units when creating an entity, recursive case.
			*/
			template <typename UnitType, typename... Rest>
			void unpackAndStoreUnitsInContainers(const size_t& entityId, const UnitType& unit, const Rest& ... rest)
			{
				static_assert(std::is_base_of<UnitBase, UnitType>::value, "UnitType must be derived from UnitBase!");

				newUnit(entityId, unit);
				unpackAndStoreUnitsInContainers(entityId, rest...);
			}

			/*
				Unpacks parameter pack of unit types, base case.
			*/
			template <typename UnitType>
			static void unpackUnitTypesHelper(std::vector<size_t>& unitIdentifiersUnpacking)
			{
				static_assert(std::is_base_of<UnitBase, UnitType>::value, "UnitType must be derived from UnitBase!");

				unitIdentifiersUnpacking.push_back(UnitType::getIdentifier());
			}

			/*
				Unpacks parameter pack of unit types, recursive case.
			*/
			template <typename UnitType, typename F, typename... Rest>
			static void unpackUnitTypesHelper(std::vector<size_t>& unitIdentifiersUnpacking)
			{
				static_assert(std::is_base_of<UnitBase, UnitType>::value, "UnitType must be derived from UnitBase!");

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
				for (size_t i = 0; i < unitContainers.size(); i++)
					delete unitContainers[i];
				for (size_t i = 0; i < systems.size(); i++)
					delete systems[i];
			};

			/*
				Executes EachCallable.eachCall on every entity that has specified set of unit types.
			*/
			void each(EachCallableBase * eachCallable)
			{
				std::vector<std::pair<size_t, bool>> unitIdentifiers = eachCallable->getUnitIdentifiers();

				if (unitIdentifiers.size() == 0)
					return;

				// Get an iterator to every relevant unitManager.
				std::vector<OwnedUnitIteratorBase*> unitContainerIterators;
				for (size_t i = 0; i < unitIdentifiers.size(); i++)
				{
					bool found = false;
					for (size_t j = 0; j < this->unitContainers.size(); j++)
						if (unitIdentifiers.at(i).first == this->unitContainers.at(j)->getIdentifier())
						{
							unitContainerIterators.push_back(this->unitContainers.at(j)->begin());
							found = true;
							break;
						}

					if (!found || unitContainerIterators.back()->size() == 0)
					{
						if (!(unitIdentifiers.at(i).second))
							return;

						unitIdentifiers.erase(unitIdentifiers.begin() + i);
						i--;
					}
				}

				// To make sure an each on only untargeted units is only done once (since an iterator on untargeted units is not incremented and wont end the loop that way).
				bool allUntargeted = true;
				for (size_t i = 0; i < unitContainerIterators.size(); i++)
					if (unitContainerIterators.at(i)->getStoresOwnedUnits())
					{
						allUntargeted = false;
						break;
					}

				// Preallocate UnitGroup.
				UnitGroup unitGroup;
				unitGroup.groups.reserve(unitContainerIterators.size());

				size_t targetEntityId = 0;
				do
				{
					for (size_t i = 0; i < unitContainerIterators.size(); i++)
					{
						if (!unitContainerIterators.at(i)->getStoresOwnedUnits())
							continue;

						if (unitContainerIterators.at(i)->getEntityId() < targetEntityId)
							if (!unitContainerIterators.at(i)->incrementWhileSmallerThan(targetEntityId))
								if (!(unitIdentifiers.at(i).second))
								{
									goto end;
								} else {
									unitContainerIterators.erase(unitContainerIterators.begin() + i);
									i--;
									goto continueInner;
								}
						if (unitContainerIterators.at(i)->getEntityId() > targetEntityId && !unitIdentifiers.at(i).second)
						{
							targetEntityId = unitContainerIterators.at(i)->getEntityId();

							if (i != 0)
								goto continueOuter;
						}
					continueInner:;
					}

					// Call eachCallable with units from iterators.	
					unitGroup.setReplaceable();
					for (size_t i = 0; i < unitContainerIterators.size(); i++)
					{
						if (!unitContainerIterators.at(i)->getStoresOwnedUnits()
							|| (unitContainerIterators.at(i)->getEntityId() == targetEntityId))
							unitGroup.insert(unitContainerIterators.at(i)->getUnitTypeIdentifier(), unitContainerIterators.at(i)->getGroup());
					}

					eachCallable->eachCall(unitGroup);
					targetEntityId++;

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
			size_t newEntity(const UnitTypes & ... units)
			{
				size_t newEntity = entityIdCounter++;

				unpackAndStoreUnitsInContainers(newEntity, units...);

				return newEntity;
			}

			/*
				Stores a unit in a UnitManager and assigns it to the specified entity.
			*/
			template <typename UnitType>
			size_t newUnit(const size_t & entityId, UnitType unit)
			{
				static_assert(std::is_base_of<UnitBase, UnitType>::value, "UnitType must be derived from Unit!");

				if constexpr (std::is_base_of<OwnedUnitBase, UnitType>::value)
					if (unit.getEntityId() == 0)
						unit.setEntityId(entityId);

				// Try storing unit in an existing manager.
				for (size_t i = 0; i < unitContainers.size(); i++)
					if (unitContainers.at(i)->storesUnitType<UnitType>())
					{
						unitContainers.at(i)->insert(unit);

						if constexpr (std::is_base_of<OwnedUnitBase, UnitType>::value)
							return unit.getEntityId();
						else
							return 0;
					}

				// If unsuccessful in storing unit above, there were no UnitManager that stores given unit type.
				// Create a new unit manager that stores the unit type, and insert the unit into the new manager. 
				unitContainers.push_back(new UnitContainer<UnitType>());
				unitContainers.back()->insert(unit);

				if constexpr (std::is_base_of<OwnedUnitBase, UnitType>::value)
					return unit.getEntityId();
				else
					return 0;
			}

			/*
				Stores a unit in a UnitManager and assigns it to a new entity.

				Returns entityId
			*/
			template <typename UnitType>
			size_t newUnit(UnitType unit)
			{
				static_assert(std::is_base_of<UnitBase, UnitType>::value, "UnitType must be derived from Unit!");
				
				if constexpr (std::is_base_of<OwnedUnitBase, UnitType>::value)
					if (unit.getEntityId() == 0)
						unit.setEntityId(newEntity());

				// Try storing unit in an existing manager.
				for (size_t i = 0; i < unitContainers.size(); i++)
					if (unitContainers.at(i)->storesUnitType<UnitType>())
					{
						unitContainers.at(i)->insert(unit);

						if constexpr (std::is_base_of<OwnedUnitBase, UnitType>::value)
							return unit.getEntityId();
						else
							return 0;
					}

				// If unsuccessful in storing unit above, there were no UnitManager that stores given unit type.
				// Create a new UnitManager that stores the unit type, and insert the unit into the new manager. 
				unitContainers.push_back(new UnitContainer<UnitType>());
				unitContainers.back()->insert(unit);

				if constexpr (std::is_base_of<OwnedUnitBase, UnitType>::value)
					return unit.getEntityId();
				else
					return 0;
			}

			/*
				Set units of entity to be erased after current update, the component will still be considered by systems.
				If no UnitTypes are specified, all units of the entity are set to be erased.
			*/
			template <typename... UnitTypes>
			void setErase(const size_t & entityId)
			{
				if constexpr (sizeof...(UnitTypes) == 0)
				{
					for (size_t i = 0; i < unitContainers.size(); i++)
						unitContainers[i]->setErase(entityId);
				}
				else {
					std::vector<size_t> unitIdentifiers = unpackUnitTypes<UnitTypes...>();

					for (size_t i = 0; i < unitContainers.size(); i++)
						if (std::find(unitIdentifiers.begin(), unitIdentifiers.end(), unitContainers[i]->getIdentifier()) != unitIdentifiers.end())
							unitContainers[i]->setErase(entityId);
				}
			}

			/*
				Set units of entity to be ignored by systems and erased on end of update.
				If no UnitTypes are specified, all units of the entity are set to be ignored.
			*/
			template <typename... UnitTypes>
			void setIgnore(const size_t & entityId)
			{
				if constexpr (sizeof...(UnitTypes) == 0)
				{
					for (size_t i = 0; i < unitContainers.size(); i++)
						unitContainers[i]->setIgnore(entityId);
				}
				else {
					std::vector<size_t> unitIdentifiers = unpackUnitTypes<UnitTypes...>();

					for (size_t i = 0; i < unitContainers.size(); i++)
						if (std::find(unitIdentifiers.begin(), unitIdentifiers.end(), unitContainers[i]->getIdentifier()) != unitIdentifiers.end())
							unitContainers[i]->setIgnore(entityId);
				}
			}

			/*
				Registers a system that will be used to update Units on update.
			*/
			template <typename SystemType>
			void registerSystem(SystemType * system)
			{
				systems.push_back(system);
				systems.back()->setEntityManager(this);
			}

			/*
				Updates every System and UnitManager.
			*/
			void update(const math::Time & time)
			{
				// PreUpdate every UnitContainer. Inserts into unit vector from insertionQueue.
				for (size_t i = 0; i < unitContainers.size(); i++)
					unitContainers.at(i)->preUpdate();

				// Update every system.
				for (size_t i = 0; i < systems.size(); i++)
					systems.at(i)->update(time);

				// PostUpdate every UnitManager. Updates lifetimes and erases units set to be erased.
				for (size_t i = 0; i < unitContainers.size(); i++)
					unitContainers.at(i)->postUpdate(time.value);
			}

			/*
				Inserts Units from UnitManager queues.
				Used for testing purposes.
			*/
			void insertFromQueues()
			{
				for (size_t i = 0; i < unitContainers.size(); i++)
					unitContainers.at(i)->preUpdate();
			}

			/*
				Retrieves vector to all units by type.
			*/
			template <typename UnitType>
			std::vector<UnitType>* getUnitVector()
			{
				static_assert(std::is_base_of<UnitBase, UnitType>::value, "UnitType must be derived from Unit!");

				for (size_t i = 0; i < unitContainers.size(); i++)
					if (unitContainers.at(i)->storesUnitType<UnitType>())
						return static_cast<UnitContainer<UnitType>*>(unitContainers.at(i))->getUnits();

				return nullptr;
			}

			/*
				Retrieves summed size of every UnitContainer.
			*/
			size_t sizeUnits() const
			{
				size_t sum = 0;
				for (size_t i = 0; i < unitContainers.size(); i++)
					sum += unitContainers.at(i)->size();

				return sum;
			};

			/*
				Retrieves size of UnitManager that stores specified type.
			*/
			template <typename UnitType>
			size_t sizeUnitsType() const
			{
				static_assert(std::is_base_of<UnitBase, UnitType>::value, "UnitType must be derived from Unit!");

				for (size_t i = 0; i < unitContainers.size(); i++)
					if (UnitType::getIdentifier() == unitContainers.at(i)->getIdentifier())
						return unitContainers.at(i)->size();
				return 0;
			};

			size_t sizeUnitManagers() const { return unitContainers.size(); };
			size_t sizeSystems() const { return systems.size(); };
		};
	}
}