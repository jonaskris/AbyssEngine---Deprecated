#pragma once
#include <vector>

template <typename Type>
class Set
{
	friend class Map;
public:
	std::vector<Type> members;

	Set(std::vector<Type> members)
	{
		this->members = members;
	}

	void printout()
	{
		for (size_t i = 0; i < members.size(); i++)
		{
			std::cout << members.at(i) << std::endl;
		}
	}
};