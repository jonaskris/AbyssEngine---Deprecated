#pragma once
#include <type_traits>
#include <functional>
#include <vector>
#include <algorithm>
#include "Entity.h"
#include "../systems/System.h"
#include "components/ComponentManager.h"
#include "components/ComponentManagerIterator.h"


struct ComponentBase;
class EntityManagerSystemInterface;

/*
	Stores entities, systems and component managers,
	and defines their relationship.
*/
class EntityManager
{
	friend class EntityManagerSystemInterface;
private:
	/*
		Systems.
	*/
	std::vector<SystemBase*> systems;

	/*
		Entities.
	*/
	std::vector<ComponentManagerBase*> componentManagers;
	unsigned int entityCounter = 1; // For assigning entity id, 0 is null value

	/*
		Unpacks parameter pack of components when creating an entity, base case.
	*/
	template <typename ComponentType>
	void unpackAndStoreComponentsInManagers(const Entity& entity, const ComponentType& component)
	{
		static_assert(std::is_base_of<ComponentBase, ComponentType>::value, "ComponentType must be derived from ComponentBase!");

		newComponent(entity, component);
	}

	/*
		Unpacks parameter pack of components when creating an entity, recursive case.
	*/
	template <typename ComponentType, typename... Rest>
	void unpackAndStoreComponentsInManagers(const Entity& entity, const ComponentType& component, const Rest& ... rest)
	{
		static_assert(std::is_base_of<ComponentBase, ComponentType>::value, "ComponentType must be derived from ComponentBase!");

		newComponent(entity, component);
		unpackAndStoreComponentsInManagers(entity, rest...);
	}

	/*
		Unpacks parameter pack of ComponentTypes to get a vector of component manager iterators of their respective component managers, base case.
	*/
	template <typename ComponentType>
	std::vector<ComponentManagerIterator>& unpackAndGetComponentManagersIteratorsHelper(std::vector<ComponentManagerIterator>& vec)
	{
		static_assert(std::is_base_of<ComponentBase, ComponentType>::value, "ComponentType must be derived from ComponentBase!");

		for (size_t i = 0; i < this->componentManagers.size(); i++)
			if (this->componentManagers.at(i)->storesComponentType<ComponentType>())
			{
				vec.push_back(this->componentManagers.at(i)->begin());
				return vec;
			}

		return vec;
	}

	/*
		Unpacks parameter pack of ComponentTypes to get a vector of component manager iterators of their respective component managers, recursive case.
	*/
	template <typename F, typename ComponentType, typename... Rest>
	std::vector<ComponentManagerIterator>& unpackAndGetComponentManagersIteratorsHelper(std::vector<ComponentManagerIterator>& vec)
	{
		static_assert(std::is_base_of<ComponentBase, ComponentType>::value, "ComponentType must be derived from ComponentBase!");

		for (size_t i = 0; i < this->componentManagers.size(); i++)
			if (this->componentManagers.at(i)->storesComponentType<ComponentType>())
			{
				vec.push_back(this->componentManagers.at(i)->begin());
				return unpackAndGetComponentManagersIteratorsHelper<F, Rest...>(vec);
			}

		return unpackAndGetComponentManagersIteratorsHelper<F, Rest...>(vec);
	}

	/*
		Unpacks parameter pack of ComponentTypes to get a vector of component manager iterators of their respective component managers.
	*/
	template <typename... Rest>
	std::vector<ComponentManagerIterator> unpackAndGetComponentManagersIterators()
	{
		std::vector<ComponentManagerIterator> vec;
		return unpackAndGetComponentManagersIteratorsHelper<Rest...>(vec);
	}

public:
	EntityManager() {};
	~EntityManager()
	{
		for (size_t i = 0; i < componentManagers.size(); i++)
			delete componentManagers[i];
		for (size_t i = 0; i < systems.size(); i++)
			delete systems[i];
	};

	/*
		Executes a System.updateEntity on every entity that has specified set of component types.
	*/
	void each(const double& dt, SystemBase * system, std::vector<size_t>& componentIdentifiers)
	{

		if (componentIdentifiers.size() == 0)
			return;

		// Get each relevant ComponentManager and create an iterator for it.
		std::vector<ComponentManagerIterator> componentManagerIterators;
		for (size_t i = 0; i < componentIdentifiers.size(); i++) 
		{
			for (size_t j = 0; j < this->componentManagers.size(); j++)
			{
				size_t ci1 = componentIdentifiers.at(i);

				size_t ci2 = this->componentManagers.at(j)->getIdentifier();
				if (ci1 == ci2)
				{
					componentManagerIterators.push_back(this->componentManagers.at(j)->begin());
				}
			}
		}

		// Check that the ComponentManagers the ComponentManagerIterators point to are not empty
		for (size_t i = 0; i < componentManagerIterators.size(); i++)
			if (componentManagerIterators[i].getComponentManagerSize() == 0)
				return;

		// Check if iterator/manager was found for each of ComponentTypes, if not, return.
		if (componentIdentifiers.size() != componentManagerIterators.size())
			return;

		// Since unpacking iterators results in reversed order, it must be reversed again to get original order.
		std::reverse(componentManagerIterators.begin(), componentManagerIterators.end());

		// Create vector of which iterators indices would be where if sorted, from smallest to biggest. To reduce redundant iterating.
		std::vector<size_t> indicesSorted;
		indicesSorted.reserve(componentManagerIterators.size());
		for (size_t i = 0; i < componentManagerIterators.size(); i++)
			indicesSorted.push_back(i);
		std::sort(indicesSorted.begin(), indicesSorted.end(), [&componentManagerIterators](const size_t & l, const size_t & r) { return componentManagerIterators[l].getComponentManagerSize() < componentManagerIterators[r].getComponentManagerSize(); });


		// While first iterator is not at end.
		do
		{
			if (componentManagerIterators.at(indicesSorted[0]).getCurrentComponent()->getDisabled())
				goto incrementFirst;
			//For every other iterator.
			for (size_t i = 1; i < componentManagerIterators.size(); i++)
			{
				// While entity of component at current iterator is smaller than first iterators entity.
				while (componentManagerIterators.at(indicesSorted[i]).getCurrentComponent()->entity < componentManagerIterators.at(indicesSorted[0]).getCurrentComponent()->entity)
					if (!componentManagerIterators.at(i).increment())
						return;

				// If entity of component at first iterator is not the same as entity of component at current iterator or disabled, 
				// increment first iterator and search for next set of components.
				if (!(componentManagerIterators.at(indicesSorted[i]).getCurrentComponent()->entity == componentManagerIterators.at(indicesSorted[0]).getCurrentComponent()->entity) || componentManagerIterators.at(indicesSorted[i]).getCurrentComponent()->getDisabled())
					goto incrementFirst;
			}

			// If reached this point, lambda can be executed with the components that iterators point to.
			// Get component of each iterator and execute lambda with vector of these components 
			{
				std::vector<ComponentBase*> components;
				for (size_t i = 0; i < componentManagerIterators.size(); i++)
					components.push_back(componentManagerIterators.at(i).getCurrentComponent());
				system->updateEntity(dt, components);
			}

		incrementFirst:;
		} while (componentManagerIterators.at(indicesSorted[0]).increment());
	}

	/*
		Creates an entity.
		Returns the entity.
	*/
	Entity newEntity()
	{
		Entity newEntity{ entityCounter };
		entityCounter++;

		return newEntity;
	}

	/*
		Creates an entity and stores components assigned to the new entity.
		Returns the entity.
	*/
	template <typename... ComponentTypes>
	Entity newEntity(const ComponentTypes & ... components)
	{
		Entity newEntity{ entityCounter };
		entityCounter++;

		unpackAndStoreComponentsInManagers(newEntity, components...);

		return newEntity;
	}

	/*
		Stores a component in componentmanagers and assigns it to the specified entity.
	*/
	template <typename ComponentType>
	void newComponent(const Entity & entity, ComponentType component)
	{
		static_assert(std::is_base_of<ComponentBase, ComponentType>::value, "ComponentType must be derived from ComponentBase!");

		component.setEntity(entity);

		// Try storing component in an existing manager.
		for (size_t i = 0; i < componentManagers.size(); i++)
			if (componentManagers.at(i)->storesComponentType<ComponentType>())
			{
				componentManagers.at(i)->insertComponent(component);
				return;
			}

		// If unsuccessful in storing component above, there were no component manager that stores given ComponentType.
		// Create a new componentManager that stores the component type, and insert the component into the new manager. 
		componentManagers.push_back(new ComponentManager<ComponentType>());
		componentManagers.back()->insertComponent(component);
	}

	/*
		Disables all components of specified entity to erase them after current update.
		Disabled components are not considered by systems.
	*/
	void disableComponentsOf(const Entity & entity)
	{
		for (size_t i = 0; i < componentManagers.size(); i++)
			componentManagers[i]->disableComponentOf(entity);
	}

	/*
		Disables component of specified ComponentType and Entity to erase them after current update.
		Disabled components are not considered by systems.
	*/
	template <typename ComponentType>
	void disableComponentOf(const Entity & entity)
	{
		for (size_t i = 0; i < componentManagers.size(); i++)
			if (componentManagers[i]->storesComponentType<ComponentType>())
			{
				componentManagers[i]->disableComponentOf(entity);
				return;
			}
	}

	/*
		Registers a system that will be used to update components on update.
		ConstructorArgs are optional.
		Returns whether the system was registered successfully.
	*/
	template <typename SystemType>
	bool registerSystem(SystemType * system)
	{
		static_assert(std::is_base_of<SystemBase, SystemType>::value, "SystemType must be derived from SystemBase!");

		systems.push_back(system);
		systems.back()->setEntityManager(this);
		return true;
	}

	/*
		Updates every registered system,
		updates lifetimes of LifetimeComponents,
		and erases disabled components.
	*/
	void update(const double& dt)
	{
		// Update every system.
		for (size_t i = 0; i < systems.size(); i++)
			systems.at(i)->update(dt);

		// Decrease lifetime of every LimitedLifetimeComponent.
		for (size_t i = 0; i < componentManagers.size(); i++)
			componentManagers[i]->updateComponentLifetimes(dt);

		// Erase every BasicComponent with disabled = true, or LimitedLifetimeComponent with 0 or less lifetime
		for (size_t i = 0; i < componentManagers.size(); i++)
			componentManagers[i]->eraseDisabledComponents();
	}

	/*
		Retrieves vector to all components by type.
	*/
	template <typename ComponentType>
	std::vector<ComponentType> * getComponentVectorByType()
	{
		for (size_t i = 0; i < componentManagers.size(); i++)
			if (componentManagers.at(i)->storesComponentType<ComponentType>())
				return static_cast<ComponentManager<ComponentType>*>(componentManagers.at(i))->getComponentVector();

		return nullptr;
	}

	/*
		Retrieves size of ComponentManager that stores specified type.
	*/
	template <typename ComponentType>
	size_t sizeComponentManager() const
	{
		for (size_t i = 0; i < componentManagers.size(); i++)
			if (ComponentTypeIdentifier<ComponentType>::getIdentifierStatic() == componentManagers.at(i)->getIdentifier())
				return componentManagers.at(i)->size();
		return 0;
	};

	size_t sizeComponentManagers() const { return componentManagers.size(); };
	size_t sizeSystems() const { return systems.size(); };
};