#pragma once
#include <vector>
#include <functional>
#include "../entities/components/Component.h"

class EntityManager;

/*
	Base of every system.
*/
class SystemBase
{
	friend class EntityManager;
private:
	virtual void setEntityManager(EntityManager* entityManager) = 0;
protected:
	virtual ~SystemBase() { };
	virtual void update(const double& dt) = 0;
	virtual void updateEntity(const double& dt, std::vector<ComponentBase*>& components) = 0;
public:
};

/*
	Base class of systems.
	Defines operations on a set of components that has the same entity, which execute on every update of EntityManager.
*/
template <typename... ComponentTypes>
class System : public SystemBase
{
	friend class EntityManager;

	/*
		Identifiers of every type of component the system should act on. Ordered.
	*/
	static std::vector<size_t> componentIdentifiers;

	/*
		Unpacks parameter pack of component types, base case.
	*/
	template <typename ComponentType>
	static void unpackComponentTypesHelper(std::vector<size_t>& componentIdentifiersUnpacking)
	{
		static_assert(std::is_base_of<ComponentBase, ComponentType>::value, "ComponentType must be derived from ComponentBase!");

		componentIdentifiersUnpacking.push_back(ComponentTypeIdentifier<ComponentType>::getIdentifierStatic());
	}

	/*
		Unpacks parameter pack of component types, recursive case.
	*/
	template <typename F, typename ComponentType, typename... Rest>
	static void unpackComponentTypesHelper(std::vector<size_t>& componentIdentifiersUnpacking)
	{
		static_assert(std::is_base_of<ComponentBase, ComponentType>::value, "ComponentType must be derived from ComponentBase!");

		componentIdentifiersUnpacking.push_back(ComponentTypeIdentifier<ComponentType>::getIdentifierStatic());
		unpackComponentTypesHelper<F, Rest...>(componentIdentifiersUnpacking);
	}

	/*
		Unpacks parameter pack of component types.
	*/
	static std::vector<size_t> unpackComponentTypes()
	{
		std::vector<size_t> componentIdentifiersUnpacking;
		unpackComponentTypesHelper<ComponentTypes...>(componentIdentifiersUnpacking);
		return componentIdentifiersUnpacking;
	}

	EntityManager* entityManager = nullptr;
protected:
	virtual ~System() { };
	System() { };

	/*
		To be called by System.Update by each specific type of System whenever needed.
	*/
	void updateEntities(const double& dt)
	{
		entityManager->each(dt, this, componentIdentifiers);
	}

	/*
		Called on every EntityManager.update once every update before updating individual entities.
	*/
	virtual void update(const double& dt) override = 0;

	/*
		Called on every EntityManager.update for each set of entities that have the components specified in overridden update method.
	*/
	virtual void updateEntity(const double& dt, std::vector<ComponentBase*>& components) = 0;

	void setEntityManager(EntityManager* entityManager) { this->entityManager = entityManager; };
};
template <typename... ComponentTypes>
std::vector<size_t> System<ComponentTypes...>::componentIdentifiers = System<ComponentTypes...>::unpackComponentTypes();
