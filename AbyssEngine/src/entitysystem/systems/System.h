#pragma once
#include <vector>
#include <functional>

class EntityManager;

/*
	Wraps a global variable that ensures SystemIdentifier has an unique identifier for each SystemType.
*/
class SystemIdentifierCounter
{
	template <typename SystemType>
	friend class System;

	static size_t counter;
};

class SystemStoreType
{
	friend class EntityManager;
protected:
	virtual ~SystemStoreType() { };
	virtual void update(const double& dt) = 0;
public:
	virtual size_t getIdentifier() const = 0;
};

/*
	Base class of systems.
	Defines operations on a set of components that has the same entity, which execute on every update of EntityManager.
	Can only be instantiated through EntityManager's registerSystem.
*/
template <typename SystemType>
class System : public SystemStoreType
{
	friend class EntityManager;

	static size_t systemTypeIdentifier;
protected:
	virtual ~System() { };
	EntityManager* entityManager;
	explicit System(EntityManager* entityManager) : entityManager(entityManager) { };

	/*
		Called on every EntityManager.update for each set of entities that have the components specified in definition.
	*/
	virtual void update(const double& dt) override = 0;
public:
	virtual size_t getIdentifier() const override { return systemTypeIdentifier; }
	static size_t getIdentifierStatic() { return systemTypeIdentifier; }
};
template <typename SystemType>
size_t System<SystemType>::systemTypeIdentifier = SystemIdentifierCounter::counter++;