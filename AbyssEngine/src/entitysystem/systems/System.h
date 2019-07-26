#pragma once
#include <vector>
#include "../entitymanager/EntityManager.h"
#include "../entitymanager/EachCallable.h"
#include "../units/UnitGroup.h"

namespace entitysystem
{
	/*
		Base of every System.
	*/
	class SystemBase
	{
		friend class EntityManager;
	private:
		void setEntityManager(EntityManager* entityManager) { this->entityManager = entityManager; };
	protected:
		EntityManager* entityManager = nullptr;

		virtual ~SystemBase() { };

		/*
			Called on every EntityManager.update once every update.
		*/
		virtual void update(const double& dt) { };
	public:
	};

	/*
		Base class of Systems.
		Defines operations on a set of Units that has the same entity (Except event), which execute on every update of EntityManager.
	*/
	template <typename... UnitTypes>
	class System : public SystemBase, EachCallable<UnitTypes...>
	{
		friend class EntityManager;
	private:
		double deltatime = 0;

		virtual void updateEntity(const double& dt, UnitGroup& unitGroup) { };
		void eachCall(UnitGroup& unitGroup) override { updateEntity(deltatime, unitGroup); }
	protected:
		void updateEntities(const double& dt)
		{
			deltatime = dt;
			this->entityManager->each(this);
		}
	};
}