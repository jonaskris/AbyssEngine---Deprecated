#pragma once
#include <vector>
#include <iostream>
#include "Set.h"

namespace math {
	template<typename TypeFrom, typename TypeTo>
	class Map
	{
	public:
		Map() {};
	private:
		struct Connection
		{
			TypeFrom from;
			TypeTo to;
		};

		std::vector<Connection> connections;
	public:

		void addConnection(TypeFrom from, TypeTo to)
		{
			bool alreadyContainsFrom = false;
			for (size_t i = 0; i < connections.size(); i++)
			{
				if (connections.at(i).from == from)
				{
					alreadyContainsFrom = true;
					std::cout << "Tried adding connection to set, where the from part of the connection already exists!" << std::endl;
					break;
				}
			}

			if (!alreadyContainsFrom)
			{
				connections.push_back(Connection{ from, to });
			}
		}

		Set<TypeTo> map(Set<TypeFrom> fromSet)
		{
			std::vector<TypeTo> returnVector;

			for (size_t i = 0; i < fromSet.members.size(); i++)
			{
				for (size_t j = 0; j < connections.size(); j++)
				{
					if (fromSet.members.at(i) == connections.at(j).from)
					{
						returnVector.push_back(connections.at(j).to);
						break;
					}
				}
			}
			Set<TypeTo> returnSet(returnVector);
			return returnSet;
		}
	};
}