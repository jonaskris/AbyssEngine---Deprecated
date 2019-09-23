#pragma once
#include "Unit.h"

class EntityManager;

namespace abyssengine {
	namespace entitysystem {
		class OwnedUnitBase 
		{
		private:
			virtual void setEntityId(const size_t& entityId) = 0;

		public:
			virtual size_t getEntityId() const = 0;
		};

		template <typename UnitType>
		class OwnedUnit : public Unit<UnitType>, public OwnedUnitBase
		{
			friend class EntityManager;
		private:
			size_t entityId = 0;

			void setEntityId(const size_t& entityId)
			{
				this->entityId = entityId;
			}

		public:
			size_t getEntityId() const
			{
				return entityId;
			}
		};
	}
}