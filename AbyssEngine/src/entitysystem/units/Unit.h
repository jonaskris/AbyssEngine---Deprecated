#pragma once

class EntityManager;

template <typename UnitType>
class UnitManager;

/*
	Used to specify storage conditions for a specific UnitType.

	InitialStorageCapacity optionally defines the initial reserved capacity of vector in UnitManager that stores the UnitType.
	If UnitStorageSpecifier is not used, UM_DEFAULT_INITIAL_CAPACITY in UnitManager.h will be used.
*/
template <typename UnitType>
struct UnitStorageSpecifier
{
private:
	static size_t initialStorageCapacity;
public:
	static size_t getInitialStorageCapacity() { return initialStorageCapacity; }
};
template <typename UnitType>
size_t UnitStorageSpecifier<UnitType>::initialStorageCapacity = 0;

/*
	Counter used to give every unit a unique identifier.
*/
class UnitTypeIdentifierCounter
{
	template <typename UnitType>
	friend struct UnitTypeIdentifier;

	static inline size_t counter = 1;
};

/*
	Identifies a unit with a unique identifier.
*/
template <typename UnitType>
struct UnitTypeIdentifier
{
private:
	static inline size_t identifier = 0;
public:
	static size_t getIdentifier() {

		if (identifier == 0)
			identifier = UnitTypeIdentifierCounter::counter++;
		return identifier;
	};
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
struct Unit
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
	Unit() : entityId(0), ignore(false) {};
	explicit Unit(const size_t& entityId) : entityId(entityId), ignore(false) {};
public:
	virtual ~Unit() {};

	size_t getEntityId()
	{
		return entityId;
	}

	/*
		Allows for implicit conversion to size_t for comparison of units.
	*/
	operator size_t() const { return entityId; }

	virtual bool getErase() const { return ignore; };
	virtual bool getIgnore() const { return ignore; };
	virtual void setErase() { ignore = true; };
	virtual void setIgnore() { ignore = true; };
};

/*
	A LimitedLifetimeUnit with lifetime 0 or below (automatically decreased by deltatime every update), will be erased at the end of the current update.
	A LimitedLifetimeUnit with ignore set to true, will be ignored by systems until the end of the current update, and erased at the end of the current update.

	LimitedLifetimeUnits erase condition is if their lifetime is <= 0.
	Lifetime is automatically decreased by dt every update.
*/
struct LimitedLifetimeUnit : public Unit
{
	friend class EntityManager;

	template <typename UnitType>
	friend class UnitManager;

private:
	float lifetime;
protected:
	LimitedLifetimeUnit() : lifetime(0.0f) {};
	explicit LimitedLifetimeUnit(const float& lifetime) : lifetime(lifetime) {}

	explicit LimitedLifetimeUnit(const size_t& entityId) : Unit(entityId), lifetime(0.0f) {};
	LimitedLifetimeUnit(const size_t& entityId, const float& lifetime) : Unit(entityId), lifetime(lifetime) {}
public:
	virtual ~LimitedLifetimeUnit() {};

	float getLifetime()
	{
		return lifetime;
	}

	virtual bool getErase() const override { return lifetime <= 0.0f || getIgnore(); };
	virtual void setErase() override { lifetime = 0.0f; };
};