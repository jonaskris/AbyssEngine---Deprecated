#pragma once
#include "../components/Component.h"
#include "../units/Unit.h"
#include "../units/UnitTags.h"

class EntityManager;

/*
	Events have limited lifetime.

	Untargeted events entityId is only used to identify individual events and do not signify ownership. 
	Systems that request these events will be handed every event of that type regardless
	of entityId.

	Events can be set to be erased which takes effect at end of current update,
	an erased event will still be active and considered by systems until actually erased.

	Events can also set to be ignored. Ignored events will not remain active and
	will not be considered by systems. Ignored events will also be erased at end of current update.
*/
template <typename EventType>
struct Event : public LimitedLifetimeUnit, UnitTag_Untargeted, UnitTypeIdentifier<EventType>
{
protected:
	Event() { }
	explicit Event(const float& lifetime) : LimitedLifetimeUnit(lifetime) { }
};

/*
	Events have limited lifetime.

	Targeted events do have ownership, 
	and are only considered by systems in context with components with same entityId.

	Events can be set to be erased which takes effect at end of current update,
	an erased event will still be active and considered by systems until actually erased.

	Events can also set to be ignored. Ignored events will not remain active and
	will not be considered by systems. Ignored events will also be erased at end of current update.
*/
template <typename EventType>
struct TargetedEvent : public LimitedLifetimeUnit, UnitTypeIdentifier<EventType>
{
protected:
	TargetedEvent() {}
	explicit TargetedEvent(const float& lifetime) : LimitedLifetimeUnit(lifetime) { }

	explicit TargetedEvent(const size_t& entityId) : LimitedLifetimeUnit(entityId) { }
	TargetedEvent(const size_t& entityId, const float& lifetime) : LimitedLifetimeUnit(entityId, lifetime) { }
};