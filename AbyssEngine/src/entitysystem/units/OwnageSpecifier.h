#pragma once

namespace abyssengine {
	namespace entitysystem {

		class EntityManager;

		struct OwnageSpecifierBase 
		{
		public:
			virtual size_t getEntityId() const = 0;
		};

		struct OwnedSpecifier : public OwnageSpecifierBase
		{
			friend class EntityManager;
		private:
			size_t entityId;

		protected:
			OwnedSpecifier() : entityId(0) {};
			OwnedSpecifier(const size_t& entityId) : entityId(entityId) {};

		public:
			size_t getEntityId() const override { return entityId; };
		};

		struct OwnerlessSpecifier : public OwnageSpecifierBase
		{
		public:
			size_t getEntityId() const override { return 0; };
		};
	}
}