#pragma once
#include <type_traits>
#include <functional>
#include <vector>
#include <algorithm>
#include "Entity.h"
#include "../systems/System.h"
#include "components/ComponentManager.h"
#include "components/ComponentManagerIterator.h"


struct ComponentStoreType;

/*
	Stores entities, systems and component managers,
	and defines their relationship.
*/
class EntityManager
{
private:
	/*
		Systems
	*/
	std::vector<SystemStoreType*> systems;

	/*
		Entities
	*/
	std::vector<ComponentManagerBase*> componentManagers;
	unsigned int entityCount = 0;
	unsigned int entityCounter = 1; // For assigning entity id, 0 is null value

	/*
		Unpacks parameter pack of components when creating an entity, base case.
	*/
	template <typename ComponentType>
	void unpackAndStoreComponentsInManagers(const Entity& entity, const ComponentType& component)
	{
		static_assert(std::is_base_of<ComponentStoreType, ComponentType>::value, "ComponentType must be derived from ComponentStoreType!");

		newComponent(entity, component);
	}

	/*
		Unpacks parameter pack of components when creating an entity, recursive case.
	*/
	template <typename ComponentType, typename... Rest>
	void unpackAndStoreComponentsInManagers(const Entity& entity, const ComponentType& component, const Rest&... rest)
	{
		static_assert(std::is_base_of<ComponentStoreType, ComponentType>::value, "ComponentType must be derived from ComponentStoreType!");

		newComponent(entity, component);
		unpackAndStoreComponentsInManagers(entity, rest...);
	}

	/*
		Unpacks parameter pack of ComponentTypes to get a vector of component manager iterators of their respective component managers, base case.
	*/
	template <typename ComponentType>
	std::vector<ComponentManagerIterator>& unpackAndGetComponentManagersIteratorsHelper(std::vector<ComponentManagerIterator>& vec)
	{
		static_assert(std::is_base_of<ComponentStoreType, ComponentType>::value, "ComponentType must be derived from ComponentStoreType!");

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
		static_assert(std::is_base_of<ComponentStoreType, ComponentType>::value, "ComponentType must be derived from ComponentStoreType!");

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
		Creates an entity.
		Returns the entity.
	*/
	Entity newEntity()
	{
		Entity newEntity{ entityCounter };
		entityCount++;
		entityCounter++;
	
		return newEntity;
	}

	/*
		Creates an entity and stores components assigned to the new entity.
		Returns the entity.
	*/
	template <typename... Components>
	Entity newEntity(const Components&... components)
	{
		Entity newEntity{ entityCounter };
		entityCount++;
		entityCounter++;

		unpackAndStoreComponentsInManagers(newEntity, components...);

		return newEntity;
	}

	/*
		Stores a component in componentmanagers and assigns it to the specified entity.
	*/
	template <typename ComponentType>
	void newComponent(const Entity& entity, const ComponentType& component)
	{
		static_assert(std::is_base_of<ComponentStoreType, ComponentType>::value, "ComponentType must be derived from ComponentStoreType!");

		// Try storing component in an existing manager.
		for (size_t i = 0; i < componentManagers.size(); i++)
			if (componentManagers.at(i)->storesComponentType<ComponentType>())
			{
				componentManagers.at(i)->insertComponent(entity, component);
				return;
			}
		
		// If unsuccessful in storing component above, there were no component manager that stores given ComponentType.
		// Create a new componentManager that stores the component type, and insert the component into the new manager. 
		componentManagers.push_back(new ComponentManager<ComponentType>());
		componentManagers.back()->insertComponent(entity, component);
	}

	/*
		Erases component from every ComponentManager that belongs to specified entity.
	*/
	void eraseEntity(const Entity& entity)
	{
		bool erasedComponents = false;

		for (size_t i = 0; i < componentManagers.size(); i++)
			if (componentManagers.at(i)->eraseComponentOf(entity))
				erasedComponents = true;

		if (erasedComponents)
			entityCount--;
		return;
	}

	/*
		Registers a system that will be used to update components on update call.
		ConstructorArgs are optional.
		Returns whether the system was registered successfully.
	*/
	template <typename SystemType, typename... ConstructorArgs>
	bool registerSystem(ConstructorArgs... constructorArgs)
	{
		static_assert(std::is_base_of<SystemStoreType, SystemType>::value, "SystemType must be derived from SystemStoreType!");

		// Check if a system of SystemType is already registered.
		for (size_t i = 0; i < systems.size(); i++)
			if (systems.at(i)->getIdentifier() == System<SystemType>::getIdentifierStatic())
				return false;
		
		systems.push_back(new SystemType(this, constructorArgs...));
		return true;
	}

	/* 
		Executes a lambda on every entity that has specified set of component types.
	*/
	template <typename... ComponentTypes>
	void each(std::function<void(std::vector<ComponentStoreType*>&)> lambda)
	{
		static_assert(sizeof...(ComponentTypes) > 0, "Cannot iterate over no components! Specify set of component types to iterate over in template argument.");

		// Get each relevant componentmanager and create an iterator for it.
		std::vector<ComponentManagerIterator> componentManagerIterators = unpackAndGetComponentManagersIterators<ComponentTypes...>();

		// Check if iterator/manager was found for each of ComponentTypes, if not, return.
		if (sizeof...(ComponentTypes) != componentManagerIterators.size())
			return;

		// Since unpacking iterators results in reversed order, it must be reversed again to get original order.
		std::reverse(componentManagerIterators.begin(), componentManagerIterators.end());

		// While first iterator is not at end.
		do
		{
			//For every other iterator.
			for (size_t i = 1; i < componentManagerIterators.size(); i++)
			{
				// While entity of component at current iterator is smaller than first iterators entity.
				while (componentManagerIterators.at(i).getCurrentEntity() < componentManagerIterators.at(0).getCurrentEntity())
					componentManagerIterators.at(i).increment();

				// If entity of component at first iterator is the same as entity of component at current iterator,
				// continue by finding the same entity in next iterator.
				if (!(componentManagerIterators.at(0).getCurrentEntity() == componentManagerIterators.at(i).getCurrentEntity()))
					goto continueOuter;
			}

			// If reached this point, lambda can be executed with the components that iterators point to.
			// Get component of each iterator and execute lambda with vector of these components 
			{
				std::vector<ComponentStoreType*> components;
				for (size_t i = 0; i < componentManagerIterators.size(); i++)
					components.push_back(componentManagerIterators.at(i).getCurrentComponent());
				lambda(components);
			}

			continueOuter:;
		} while (componentManagerIterators.at(0).increment());
	}

	/*
		Executes every registered systems lambda on entities that consists of their respective ComponentTypes.
	*/
	void update(const double& dt)
	{
		for (size_t i = 0; i < systems.size(); i++)
			systems.at(i)->update(dt);
	}

	size_t sizeEntities() const { return entityCount; };
	size_t sizeComponentManagers() const { return componentManagers.size(); };
	size_t sizeSystems() const { return systems.size(); };
	
	template <typename ComponentType>
	size_t sizeComponentManager()  const
	{ 
		for (size_t i = 0; i < componentManagers.size(); i++)
			if (Component<ComponentType>::getIdentifierStatic() == componentManagers.at(i)->getIdentifier())
				return componentManagers.at(i)->size();

		// If the component manager was not found.
		return 0;
	};

	/*
		Retrieves vector to all components by type.
	*/
	template <typename ComponentType>
	std::vector<ComponentWrapper<ComponentType>>* getComponentVectorByType()
	{
		for (size_t i = 0; i < componentManagers.size(); i++)
			if (componentManagers.at(i)->storesComponentType<ComponentType>())
				return static_cast<ComponentManager<ComponentType>*>(componentManagers.at(i))->getComponentVector();
		
		return nullptr;
	}

	/*
		Retrieves a pointer to a component.
	*/
	template <typename ComponentType>
	ComponentType* getComponentFromEntity(const Entity& entity)
	{
		static_assert(std::is_base_of<ComponentStoreType, ComponentType>::value, "ComponentType must be derived from ComponentStoreType!");

		for (size_t i = 0; i < componentManagers.size(); i++)
			if (componentManagers.at(i)->storesComponentType<ComponentType>())
				return static_cast<ComponentType*>(componentManagers.at(i)->getComponentFromEntity(entity));

		return static_cast<ComponentType*>(nullptr);
	}
};