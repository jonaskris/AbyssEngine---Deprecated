//#pragma once
//#include "../units/Unit.h"
//
//namespace abyssengine {
//	namespace entitysystem {
//
//		/*
//			Events have limited lifetime.
//
//			Untargeted events entityId is only used to identify individual events and do not signify ownership.
//			Systems that request these events will be handed every event of that type regardless
//			of entityId.
//
//			Events can be set to be erased which takes effect at end of current update,
//			an erased event will still be active and considered by systems until actually erased.
//
//			Events can also set to be ignored. Ignored events will not remain active and
//			will not be considered by systems. Ignored events will also be erased at end of current update.
//		*/
//		template <typename EventType>
//		struct Event : public LimitedLifetimeUnit<EventType>
//		{
//		protected:
//			Event() { };
//			explicit Event(const float& lifetime) : LimitedLifetimeUnit<EventType>(lifetime) { };
//		};
//
//		/*
//			Events have limited lifetime.
//
//			Targeted events do have ownership,
//			and are only considered by Systems in context with Components with same entityId.
//
//			Events can be set to be erased which takes effect at end of current update,
//			an erased Event will still be active and considered by systems until actually erased.
//
//			Events can also set to be ignored. Ignored Events will not remain active and
//			will not be considered by Systems. Ignored Events will also be erased at end of current update.
//		*/
//		template <typename EventType>
//		struct TargetedEvent : public LimitedLifetimeUnit<EventType>
//		{
//		protected:
//			TargetedEvent() {};
//			explicit TargetedEvent(const float& lifetime) : LimitedLifetimeUnit<EventType>(lifetime) { };
//			explicit TargetedEvent(const size_t& entityId) : LimitedLifetimeUnit<EventType>(entityId) { };
//			TargetedEvent(const size_t& entityId, const float& lifetime) : LimitedLifetimeUnit<EventType>(entityId, lifetime) { };
//		};
//	}
//}

#include "../units/BatchErasableUnit.h"
#include "../units/BatchInsertableUnit.h"
#include "../units/LimitedLifetimeUnit.h"
#include "../units/OwnedUnit.h"

namespace abyssengine {
	namespace entitysystem {
		template <typename UnitType>
		struct Event : public Unit<UnitType>, public LimitedLifetimeUnit<UnitType>, public BatchInsertableUnit
		{
			Event(const float& lifetime) : LimitedLifetimeUnit<UnitType>(lifetime) {};
			Event() : LimitedLifetimeUnit<UnitType>(0.0f) {};
		};

		template <typename UnitType>
		struct TargetedEvent : public OwnedUnit<UnitType>, public LimitedLifetimeUnit<UnitType>, public BatchInsertableUnit
		{
			TargetedEvent(const float& lifetime) : LimitedLifetimeUnit<UnitType>(lifetime) {};
			TargetedEvent() : LimitedLifetimeUnit<UnitType>(0.0f) {};
		};
	}
}