#pragma once

namespace abyssengine {
	namespace entitysystem {
		struct LifetimeSpecifierBase 
		{
			virtual bool getErase() const = 0;
			virtual void setErase() = 0;
		};

		struct TemporalLifetime : public LifetimeSpecifierBase
		{
		private:
			float lifetime;

		protected:
			TemporalLifetime() : lifetime(0) {};
			TemporalLifetime(const float& lifetime) : lifetime(lifetime) {};

		public:
			bool getErase() const override { return lifetime <= 0.0f; }
			void setErase() override { lifetime = 0.0f; }

			float getLifetime() const { return lifetime; }
			void setLifetime(const float& lifetime) { this->lifetime = lifetime; }
		};

		struct BinaryLifetime : public LifetimeSpecifierBase
		{
		private:
			bool erase;

		protected:
			BinaryLifetime() : erase(false) {};
			BinaryLifetime(const bool& erase) : erase(erase) {};

		public:
			bool getErase() const override { return erase; }
			void setErase() override { erase = true; }
		};
	}
}