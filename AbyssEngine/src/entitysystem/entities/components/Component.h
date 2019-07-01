#pragma once
#include "../Entity.h"

class EntityManager;

template <typename ComponentType>
struct ComponentTypeIdentifier;

/*
	Used to specify storage conditions for specific ComponentTypes.

	InitialStorageCapacity optionally defines the initial reserved capacity of vector in ComponentManager that stores the component type,
	if not defined, CM_DEFAULT_INITIAL_CAPACITY in ComponentManager.h will be used.
*/
template <typename ComponentType>
struct ComponentStorageSpecifier
{
private:
	static size_t initialStorageCapacity;
public:
	static size_t getInitialStorageCapacity() { return initialStorageCapacity; }
};
template <typename ComponentType>
size_t ComponentStorageSpecifier<ComponentType>::initialStorageCapacity = 0;


/*
	For storing different types of components as pointers in one collection.
*/
struct ComponentBase
{
	friend class EntityManager;
private:
	Entity entity;
	void setEntity(const Entity& entity) { this->entity = entity; }
protected:
	ComponentBase() : entity(Entity{ 0 }) {}
	virtual ~ComponentBase() {};
public:
	Entity getEntity() const { return entity; }
	virtual bool getDisabled() const = 0;
};

/*
	Base of every basic component.

	BasicComponents are erased by setting disabled to true. A disabled component will not be considered by systems and will be deleted at the end of every update.
*/
template <typename ComponentType>
struct BasicComponent : public ComponentBase, ComponentTypeIdentifier<ComponentType>
{
	bool disabled = false;
protected:
	BasicComponent() {};
public:
	bool getDisabled() const override { return disabled; }
};

/*
	Lifetime is decreased by dt every update.

	LimitedLifetimeComponents are disabled by setting lifetime to 0. A disabled component will not be considered by systems and will be deleted at the end of every update.
*/
template <typename ComponentType>
struct LimitedLifetimeComponent : public ComponentBase, ComponentTypeIdentifier<ComponentType>
{
	double lifetime;
protected:
	LimitedLifetimeComponent(const double& lifetime) : lifetime(lifetime) {}
public:
	bool getDisabled() const override { return lifetime <= 0; }
};

/*
	Wraps a global variable that ensures each Component has an unique identifier for each ComponentType.
*/
class ComponentTypeIdentifierCounter
{
	template <typename ComponentType>
	friend struct ComponentTypeIdentifier;

	inline static size_t counter = 1;
};

/*
	Identifies a component with a unique identifier.
*/
template <typename ComponentType>
struct ComponentTypeIdentifier
{
private:
	static size_t identifier;
	static bool isLimitedLifetimeComponent;
public:
	static size_t getIdentifierStatic() { 
		if (identifier == 0)
			identifier = ComponentTypeIdentifierCounter::counter++;
		return identifier; 
	};
	static bool getIsLimitedLifetimeComponentStatic() { return isLimitedLifetimeComponent; };
};
template <typename ComponentType>
size_t ComponentTypeIdentifier<ComponentType>::identifier = 0;
template <typename ComponentType>
bool ComponentTypeIdentifier<ComponentType>::isLimitedLifetimeComponent = std::is_base_of<LimitedLifetimeComponent<ComponentType>, ComponentType>::value;