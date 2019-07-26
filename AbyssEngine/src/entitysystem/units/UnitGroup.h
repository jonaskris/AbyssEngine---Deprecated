#pragma once
#include <map>
#include <utility>
#include "Unit.h"
#include "../utils/Algorithm.h"

namespace entitysystem
{
	class EntityManager;

	/*
		UnitGroups are used to pass around groups of Units regardless of UnitType.
	*/
	class UnitGroup
	{
		friend class EntityManager;

		struct Group
		{
			size_t unitIdentifier;

			UnitBase* first;
			size_t count;

			Group(const size_t& unitIdentifier, UnitBase* const first, const size_t& count) : unitIdentifier(unitIdentifier), first(first), count(count) {};

			operator size_t() const { return unitIdentifier; }
		};
	private:
		std::vector<Group> groups;

		// How many Groups starting from back that can be replaced by another.
		// Used to change value of existing groups, instead of allocating a whole new group.
		size_t replaceable = 0;
	public:
		/*
			Sets all current groups to be able to be replaced with new values.
		*/
		void setReplaceable()
		{
			replaceable = groups.size();
		}

		void insert(const size_t& unitIdentifier, const std::pair<UnitBase*, size_t>& group)
		{
			insert(unitIdentifier, group.first, group.second);
		}

		void insert(const size_t& unitIdentifier, UnitBase* const first, const size_t& count)
		{
			if (replaceable > 0)
			{
				Group& replaceableGroup = groups.at(groups.size() - replaceable);

				replaceableGroup.unitIdentifier = unitIdentifier;
				replaceableGroup.first = first;
				replaceableGroup.count = count;
				replaceable--;
				return;
			}

			groups.insert(groups.begin() + (groups.size() - replaceable), Group{ unitIdentifier, first, count });
		}

		template <typename UnitType>
		std::pair<UnitType*, size_t> get()
		{
			static_assert(std::is_base_of<UnitBase, UnitType>::value, "UnitType must be derived from Unit!");

			int index = -1;
			for (size_t i = 0; i < groups.size(); i++)
			{
				if (groups.at(i).unitIdentifier == UnitType::getIdentifier())
				{
					if (i >= groups.size() - replaceable)
						break;

					index = i;
					break;
				}
			}

			if (index < 0)
				return std::pair(static_cast<UnitType*>(nullptr), 0);

			return std::pair(static_cast<UnitType*>(groups.at(index).first), groups.at(index).count);
		}
	};
}