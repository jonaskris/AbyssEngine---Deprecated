#pragma once
#include <vector>
#include "../entitymanager/EntityManager.h"
#include "../entitymanager/EachCallable.h"
#include "../units/UnitGroup.h"
#include "../../math/semantics/Time.h"

namespace abyssengine {
	namespace entitysystem {
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
			virtual void update(const math::Time& time) { };
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
			math::Time time = 0;

			virtual void updateEntity(const math::Time& time, UnitGroup& unitGroup) { };
			void eachCall(UnitGroup& unitGroup) override { updateEntity(time, unitGroup); }
		protected:
			void updateEntities(const math::Time& time)
			{
				this->time = time;
				this->entityManager->each(this);
			}
		};
	}
}