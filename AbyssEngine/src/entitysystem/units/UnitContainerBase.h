#pragma once

namespace abyssengine {
	namespace entitysystem {

		class UnitIteratorBase;

		/*
			UnitContainer is a collection of a specified UnitType.
		*/
		class UnitContainerBase
		{
		protected:
			virtual void insertUnitVirtual(void const* unit) = 0;

		public:
			virtual ~UnitContainerBase() {};

			//virtual void* at(const size_t& index) = 0;

			virtual UnitIteratorBase* begin() = 0;

			template <typename UnitType>
			bool insert(const UnitType& unit)
			{
				if (!storesUnitType<UnitType>())
					return false;

				insertUnitVirtual((void* const)& unit);
				return true;
			};

			template <typename UnitType>
			bool storesUnitType()
			{
				return getIdentifier() == utils::TypeIdentifier<UnitType>::getIdentifier();
			};

			virtual void preUpdate() = 0;
			virtual void postUpdate(const float& dt) = 0;

			/*
				Returns the identifier of the UnitType the UnitContainer stores.
			*/
			virtual size_t getIdentifier() const = 0;

			virtual size_t size() const = 0;
		};
	}
}