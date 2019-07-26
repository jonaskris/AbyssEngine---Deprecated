#pragma once
#include <vector>
#include "../units/UnitGroup.h"

namespace entitysystem
{
	class EntityManager;

	/*
		Gives EntityManager an interface to submit UnitGroups.
	*/
	class EachCallableBase
	{
		friend class EntityManager;
	protected:
		virtual void eachCall(UnitGroup& unitgroup) = 0;
	public:
		virtual std::vector<std::pair<size_t, bool>> getUnitIdentifiers() const = 0;
	};

	template <typename... UnitTypes>
	class EachCallable : public EachCallableBase
	{
		/*
			Identifiers of every type of unit the system should act on, and whether they are optional.
		*/
		static std::vector<std::pair<size_t, bool>> unitIdentifiers;


		/*
			Unpacks parameter pack of unit types, base case.
		*/
		template <typename UnitType>
		static void unpackUnitTypesHelper(std::vector<std::pair<size_t, bool>>& unitIdentifiersUnpacking)
		{
			static_assert(std::is_base_of<UnitBase, UnitType>::value || std::is_base_of<OptionalBase, UnitType>::value, "UnitType must be derived from Unit or Optional!");

			unitIdentifiersUnpacking.push_back(std::pair(UnitType::getIdentifier(), std::is_base_of<OptionalBase, UnitType>::value));
		}

		/*
			Unpacks parameter pack of unit types, recursive case.
		*/
		template <typename UnitType, typename F, typename... Rest>
		static void unpackUnitTypesHelper(std::vector<std::pair<size_t, bool>>& unitIdentifiersUnpacking)
		{
			static_assert(std::is_base_of<UnitBase, UnitType>::value || std::is_base_of<OptionalBase, UnitType>::value, "UnitType must be derived from Unit or Optional!");

			unitIdentifiersUnpacking.push_back(std::pair(UnitType::getIdentifier(), std::is_base_of<OptionalBase, UnitType>::value));
			unpackUnitTypesHelper<F, Rest...>(unitIdentifiersUnpacking);
		}

		/*
			Unpacks parameter pack of unit types.
		*/
		static std::vector<std::pair<size_t, bool>> unpackUnitTypes()
		{
			std::vector<std::pair<size_t, bool>> unitIdentifiersUnpacking;

			if constexpr (sizeof...(UnitTypes) != 0)
				unpackUnitTypesHelper<UnitTypes...>(unitIdentifiersUnpacking);

			return unitIdentifiersUnpacking;
		}

		std::vector<std::pair<size_t, bool>> getUnitIdentifiers() const override { return unitIdentifiers; }
	};
	template <typename... UnitTypes>
	std::vector<std::pair<size_t, bool>> EachCallable<UnitTypes...>::unitIdentifiers = EachCallable<UnitTypes...>::unpackUnitTypes();
}