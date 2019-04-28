#pragma once
#include <vector>
#include <typeinfo>
#include "Component.h"
#include "ComponentManagerIterator.h"
#include "../Entity.h"

#define COMPONENTMANAGER_DEFAULT_INITIAL_CAPACITY 1024

/* 
	ComponentManager is a sorted collection of a specified type of component.
*/
class ComponentManagerBase
{
	/* 
		A virtual helper method to insert component into derived classes vector.
	*/
	virtual void insertComponentVirtual(const Entity& entity, ComponentStoreType const* component) = 0;

	/*
		A virtual helper method that checks if the derived class stores a components assigned id.
		Components are assigned id from ComponentIdentifier.
	*/
	virtual bool storesTypeId(const size_t& id) const = 0;
public:
	/*
		Insures proper destruction of derived class.
	*/
	virtual ~ComponentManagerBase() { };

	/*
		Gets pointer to component at specified index.
	*/
	virtual ComponentStoreType* componentAt(const size_t& index) = 0;

	/*
		Gets pointer to component belonging to specified entity.
	*/
	virtual ComponentStoreType* getComponentFromEntity(const Entity& e) = 0;

	/* 
		Inserts a component into the collection after checking that it stores the component type. 
	*/
	template <typename ComponentType>
	bool insertComponent(const Entity& entity, const ComponentType& component) {
		static_assert(std::is_base_of<ComponentStoreType, ComponentType>::value, "ComponentType must be derived from ComponentStoreType!");

		if (storesComponentType<ComponentType>())
		{
			insertComponentVirtual(entity, &component);
			return true;
		}
		else {
			return false;
		}
	};

	/* 
		Erases components belonging to specified entity.
		Returns true if it found any components to erase. 
	*/
	virtual bool eraseComponentOf(const Entity& entity) = 0;

	/* 
		Returns a ComponentManagerIterator to the beginning of the ComponentManager.
	*/
	ComponentManagerIterator begin() { return ComponentManagerIterator(0, this); };

	template <typename ComponentType>
	bool storesComponentType() {
		static_assert(std::is_base_of<ComponentStoreType, ComponentType>::value, "ComponentType must be derived from ComponentStoreType!");

		return storesTypeId(Component<ComponentType>::getIdentifierStatic());
	};

	virtual Entity entityAt(const size_t& index) const = 0;

	virtual size_t getIdentifier() const = 0;

	virtual size_t size() const = 0;
};

/* 
	Wraps component to assign it an entity.
*/
template <typename ComponentType>
struct ComponentWrapper
{
	static_assert(std::is_base_of<ComponentStoreType, ComponentType>::value, "ComponentType must be derived from ComponentStoreType!");

	Entity entity;
	ComponentType component;
	ComponentWrapper(const Entity& entity, const ComponentType& component) : entity(entity), component(component) {};
};

template <typename ComponentType>
class ComponentManager : public ComponentManagerBase
{
	static_assert(std::is_base_of<ComponentStoreType, ComponentType>::value, "ComponentType must be derived from ComponentStoreType!");

	friend class ComponentManagerIterator;

	static size_t componentTypeIdentifier;

	std::vector<ComponentWrapper<ComponentType>> componentVector;

	/* 
		Inserts sorted, beginning from the back of the array.
	*/
	void insertComponentVirtual(const Entity& entity, ComponentStoreType const* component) override
	{
		for (auto it = componentVector.rbegin(); it != componentVector.rend(); it++)
		{
			if (entity > (*it).entity)
			{
				ComponentWrapper wrapped = ComponentWrapper{ Entity{ entity.id }, *((ComponentType*)component) };
				componentVector.insert(it.base(), wrapped);
				return;
			}
		}
		componentVector.push_back(ComponentWrapper{ entity, *((ComponentType*)component) });
	}

	/*
		Checks that the component manager stores component with specified identifier.
		Components are assigned id from ComponentIdentifier.
	*/
	bool storesTypeId(const size_t& id) const override { return Component<ComponentType>::getIdentifierStatic() == id; };
public:

	ComponentManager()
	{
		componentVector.reserve(COMPONENTMANAGER_DEFAULT_INITIAL_CAPACITY);
	};

	~ComponentManager() { };


	/*
		Gets pointer to component at specified index.
	*/
	ComponentStoreType* componentAt(const size_t& index) override
	{
		if(index < componentVector.size())
			return &(componentVector.at(index).component);
		return static_cast<ComponentStoreType*>(nullptr);
	}

	/*
		Gets pointer to component belonging to specified entity using binary search.
		Returns null pointer if not found.
	*/
	ComponentStoreType* getComponentFromEntity(const Entity& e) override
	{
		size_t l = 0;
		size_t r = componentVector.size() - 1;

		while (l <= r)
		{
			size_t m = (l + r) / 2;

			if (componentVector.at(m).entity < e)
			{
				l = m + 1;
			} else if (componentVector.at(m).entity > e)
			{
				if (r == 0 || m == 0)			// To avoid underflow
					return static_cast<ComponentStoreType*>(nullptr);
				r = m - 1;
			} else
			{
				return static_cast<ComponentStoreType*>(&(*(componentVector.begin() + m)).component);
			}
		}
		return static_cast<ComponentStoreType*>(nullptr);
	}

	/*
		Retrieves vector to componentVector.
	*/
	std::vector<ComponentWrapper<ComponentType>>* getComponentVector()
	{
		return &componentVector;
	}

	/*
		Erases components belonging to specified entity using binary search.
		Returns true if it found any components to erase.
	*/
	bool eraseComponentOf(const Entity& e) override
	{
		size_t l = 0;
		size_t r = componentVector.size() - 1;

		while (l <= r)
		{
			size_t m = (l + r) / 2;

			if (componentVector.at(m).entity < e)
			{
				l = m + 1;
			} else if (componentVector.at(m).entity > e)
			{
				if (r == 0 || m == 0)			// To avoid underflow
					return false;
				r = m - 1;
			} else
			{
				componentVector.erase(componentVector.begin() + m);
				return true;
			}
		}
		return false;	
	}

	Entity entityAt(const size_t& index) const override
	{
		return componentVector[index].entity;
	}

	size_t getIdentifier() const override { return componentTypeIdentifier; };
	static size_t getIdentifierStatic() { return componentTypeIdentifier; };

	size_t size() const override { return componentVector.size(); };
};
template <typename ComponentType>
size_t ComponentManager<ComponentType>::componentTypeIdentifier = Component<ComponentType>::getIdentifierStatic();