#pragma once
#include <map>
#include <vector>
#include <utility>
#include "Unit.h"
#include "../components/Component.h"
#include "../events/Event.h"

class EntityManager;

/*
	UnitGroups are used to pass around groups of units regardless of type.
*/
class UnitGroup
{
	friend class EntityManager;
private:
	// Maps unit identifiers to respective groups of units.
	std::map<size_t, std::pair<Unit*, size_t>> units;

public:
	template <typename UnitType>
	std::pair<UnitType*, size_t> get()
	{
		static_assert(std::is_base_of<Unit, UnitType>::value && std::is_base_of<UnitTypeIdentifier<UnitType>, UnitType>::value, "UnitType must be derived from Unit and UnitTypeIdentifier!");


		auto it = units.find(UnitType::getIdentifier());

		if (it == units.end())
			return std::pair(static_cast<UnitType*>(nullptr), 0);

		return std::pair(static_cast<UnitType*>((*it).second.first), (*it).second.second);
	}
};