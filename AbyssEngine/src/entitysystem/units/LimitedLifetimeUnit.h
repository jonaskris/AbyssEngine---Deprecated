#pragma once

namespace abyssengine {
	namespace entitysystem {

		template <typename UnitType>
		class UnitContainer;

		class LimitedLifetimeUnitBase 
		{
		public:
			virtual float getLifetime() const = 0;
		};

		template <typename UnitType>
		class LimitedLifetimeUnit : public LimitedLifetimeUnitBase
		{
			friend class UnitContainer<UnitType>;
		private:
			float lifetime;

		protected:
			LimitedLifetimeUnit(const float& lifetime) : lifetime(lifetime) {};
			
		public:
			float getLifetime() const { return lifetime; }
		};
	}
}