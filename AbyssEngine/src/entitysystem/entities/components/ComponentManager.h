#pragma once
#include <vector>
#include <typeinfo>
#include <functional>
#include <algorithm>
#include "Component.h"
#include "ComponentManagerIterator.h"
#include "../Entity.h"

#define CM_DEFAULT_INITIAL_CAPACITY 256

template <typename ComponentType>
class ComponentManager;

/*
	ComponentManager is a sorted collection of a specified type of component.
*/
class ComponentManagerBase
{
	/*
		A virtual helper method to insert component into derived classes vector.
	*/
	virtual void insertComponentVirtual(ComponentBase const* component) = 0;

	/*
		A virtual helper method that checks if the derived class stores a components assigned id.
		Components are assigned id from ComponentTypeIdentifier.
	*/
	virtual bool storesTypeId(const size_t& id) const = 0;
public:
	/*
		Insures proper destruction of derived class.
	*/
	virtual ~ComponentManagerBase() {};

	/*
		Gets pointer to component at specified index.
	*/
	virtual ComponentBase* componentAt(const size_t& index) = 0;

	/*
		Gets pointer to component belonging to specified entity.
	*/
	//virtual ComponentBase* getComponentFromEntity(const Entity& e) = 0;

	/*
		Inserts a component into the collection after checking that it stores the component type.
	*/
	template <typename ComponentType>
	bool insertComponent(const ComponentType& component) {
		static_assert(std::is_base_of<ComponentBase, ComponentType>::value, "ComponentType must be derived from ComponentBase!");

		if (!storesComponentType<ComponentType>())
			return false;
		insertComponentVirtual(&component);
		return true;
	};

	/*
		Disables a component to erase it after current update.
		Disabled components are not considered by systems.
	*/
	virtual void disableComponentOf(const Entity& entity) = 0;

	/*
		Erases every BasicComponent with disabled = true, or LimitedLifetimeComponent with lifetime <= 0.
	*/
	virtual void eraseDisabledComponents() = 0;

	/*
		Updates lifetime of every component if the ComponentManager stores LimitedLifetimeComponent.
	*/
	virtual void updateComponentLifetimes(const double& dt) = 0;

	/*
		Returns a ComponentManagerIterator to the beginning of the ComponentManager.
	*/
	ComponentManagerIterator begin() { return ComponentManagerIterator(0, this); };

	template <typename ComponentType>
	bool storesComponentType() {
		static_assert(std::is_base_of<ComponentBase, ComponentType>::value, "ComponentType must be derived from ComponentBase!");

		return storesTypeId(ComponentTypeIdentifier<ComponentType>::getIdentifierStatic());
	};

	/*
		Returns unique identifier of ComponentType it stores.
	*/
	virtual size_t getIdentifier() const = 0;

	virtual size_t size() const = 0;
};

template <typename ComponentType>
class ComponentManager : public ComponentManagerBase
{
	static_assert(std::is_base_of<ComponentBase, ComponentType>::value, "ComponentType must be derived from ComponentBase!");

	friend class ComponentManagerIterator;

	std::vector<ComponentType> componentVector;

	/*
		Inserts sorted, beginning from the back of the array.
	*/
	void insertComponentVirtual(ComponentBase const* component) override
	{
		for (auto it = componentVector.rbegin(); it != componentVector.rend(); it++)
		{
			if (component->getEntity() > (*it).getEntity())
			{
				componentVector.insert(it.base(), *((ComponentType*)component));
				return;
			}
		}
		componentVector.push_back(*((ComponentType*)component));
	}

	/*
		Checks that the component manager stores component with specified identifier.
		Components are assigned id from ComponentTypeIdentifier.
	*/
	bool storesTypeId(const size_t& id) const override { return ComponentTypeIdentifier<ComponentType>::getIdentifierStatic() == id; };
public:

	ComponentManager()
	{

		size_t initialStorageCapacity;

		if constexpr (std::is_base_of<ComponentStorageSpecifier<ComponentType>, ComponentType>::value)
			initialStorageCapacity = ComponentStorageSpecifier<ComponentType>::getInitialStorageCapacity();
		else
			initialStorageCapacity = CM_DEFAULT_INITIAL_CAPACITY;

		componentVector.reserve(initialStorageCapacity);
	};

	~ComponentManager() {};

	/*
		Gets pointer to component at specified index.
	*/
	ComponentBase* componentAt(const size_t& index) override
	{
		return &(componentVector[index]);
	}

	/*
		Gets pointer to component belonging to specified entity using binary search.
		Returns null pointer if not found.
	*/
	//ComponentBase* getComponentFromEntity(const Entity& e) override
	//{
	//	size_t l = 0;
	//	size_t r = componentVector.size() - 1;
	//
	//	while (l <= r)
	//	{
	//		size_t m = (l + r) / 2;
	//
	//		if (componentVector.at(m).getEntity() < e)
	//		{
	//			l = m + 1;
	//		} else if (componentVector.at(m).getEntity() > e) {
	//			if (r == 0 || m == 0)			// To avoid underflow
	//				return static_cast<ComponentBase*>(nullptr);
	//			r = m - 1;
	//		} else {
	//			return static_cast<ComponentBase*>(&(*(componentVector.begin() + m)));
	//		}
	//	}
	//	return static_cast<ComponentBase*>(nullptr);
	//}

	/*
		Retrieves vector to componentVector.
	*/
	std::vector<ComponentType>* getComponentVector()
	{
		return &componentVector;
	}

	/*
		Erases components belonging to specified entity using binary search.
		Returns true if it found any components to erase.
	*/
	//bool eraseComponentOf(const Entity& e) override
	//{
	//	if (componentVector.size() == 0)
	//		return;
	//	size_t l = 0;
	//	size_t r = componentVector.size() - 1;
	//
	//	while (l <= r)
	//	{
	//		size_t m = (l + r) / 2;
	//
	//		if (componentVector.at(m).getEntity() < e)
	//		{
	//			l = m + 1;
	//		} else if (componentVector.at(m).getEntity() > e) {
	//			if (r == 0 || m == 0)			// To avoid underflow
	//				return false;
	//			r = m - 1;
	//		} else {
	//			componentVector.erase(componentVector.begin() + m);
	//			return true;
	//		}
	//	}
	//	return false;	
	//}

	void disableComponentOf(const Entity& entity) override
	{
		if (componentVector.size() == 0)
			return;

		size_t l = 0;
		size_t r = componentVector.size() - 1;

		while (l <= r)
		{
			size_t m = (l + r) / 2;

			if (componentVector.at(m).getEntity() < entity)
			{
				l = m + 1;
			}
			else if (componentVector.at(m).getEntity() > entity) {
				if (r == 0 || m == 0)			// To avoid underflow
					return;
				r = m - 1;
			}
			else {
				if constexpr (std::is_base_of<BasicComponent<ComponentType>, ComponentType>::value)
					componentVector[m].disabled = true;
				else if constexpr (std::is_base_of<LimitedLifetimeComponent<ComponentType>, ComponentType>::value)
					componentVector[m].lifetime = 0.0f;
				else
					std::cout << "Tried disabling a component that was neither a BasicComponent or LimitedLifetimeComponent!" << std::endl;
				return;
			}
		}
	}


	void eraseDisabledComponents() override
	{
		componentVector.erase(std::remove_if(componentVector.begin(), componentVector.end(), [](const ComponentType & component) { return component.getDisabled(); }), componentVector.end());
	}

	void updateComponentLifetimes(const double& dt) override
	{
		if constexpr (std::is_base_of<LimitedLifetimeComponent<ComponentType>, ComponentType>::value)
			for (size_t i = 0; i < componentVector.size(); i++)
				componentVector[i].lifetime -= dt;
	}


	size_t getIdentifier() const override { return ComponentTypeIdentifier<ComponentType>::getIdentifierStatic(); };

	size_t size() const override { return componentVector.size(); };
};