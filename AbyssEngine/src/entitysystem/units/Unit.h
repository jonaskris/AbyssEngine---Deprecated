#pragma once
#include "UnitTypeIdentifier.h"
#include "Optional.h"

namespace entitysystem
{
	class EntityManager;

	template <typename UnitType>
	class UnitManager;

	struct UnitBase
	{
		friend class EntityManager;
	private:
		size_t entityId;
		bool ignore;

		void setEntityId(const size_t& entityId)
		{
			this->entityId = entityId;
		}
	protected:
		UnitBase() : entityId(0), ignore(false) {};
		explicit UnitBase(const size_t& entityId) : entityId(entityId), ignore(false) {};
	public:
		size_t getEntityId() const
		{
			return entityId;
		}

		virtual bool getErase() const { return ignore; };
		virtual bool getIgnore() const { return ignore; };
		virtual void setErase() { ignore = true; };
		virtual void setIgnore() { ignore = true; };
	};

	/*
		Units are commonality between events and components.

		Id's are set for groups of components that have unique types,
		and for individual events.

		Units can be set to be erased which takes effect at end of current update,
		an erased unit will still be active and considered by systems until actually erased.

		Units can also set to be ignored. Ignored units will not remain active and
		will not be considered by systems. Ignored units will also be erased at end of current update.
	*/
	template <typename UnitType>
	struct Unit : public UnitBase, UnitTypeIdentifier<UnitType>
	{
	protected:
		Unit() {};
		explicit Unit(const size_t& entityId) : UnitBase(entityId) {};
	public:
		// Used in EachCallable for semantic reasons.
		typedef Optional<UnitType> optional;
	};

	/*
		A LimitedLifetimeUnit with lifetime 0 or below (automatically decreased by deltatime every update), will be erased at the end of the current update.
		A LimitedLifetimeUnit with ignore set to true, will be ignored by systems until the end of the current update, and erased at the end of the current update.

		LimitedLifetimeUnits erase condition is if their lifetime is <= 0.
		Lifetime is automatically decreased by dt every update.
	*/
	struct LimitedLifetimeUnitBase {}; // Used to check if a type is a LimitedLifetimeUnit with is_base_of.
	template <typename UnitType>
	struct LimitedLifetimeUnit : public Unit<UnitType>, LimitedLifetimeUnitBase
	{
		friend class EntityManager;

		template <typename UnitType>
		friend class UnitManager;
	private:
		float lifetime;
	protected:
		LimitedLifetimeUnit() : lifetime(0.0f) {};
		explicit LimitedLifetimeUnit(const float& lifetime) : lifetime(lifetime) {}

		explicit LimitedLifetimeUnit(const size_t& entityId) : Unit<UnitType>(entityId), lifetime(0.0f) {};
		LimitedLifetimeUnit(const size_t& entityId, const float& lifetime) : Unit<UnitType>(entityId), lifetime(lifetime) {}
	public:
		float getLifetime()
		{
			return lifetime;
		}

		virtual bool getErase() const override { return lifetime <= 0.0f || this->getIgnore(); };
		virtual void setErase() override { lifetime = 0.0f; };
	};
}