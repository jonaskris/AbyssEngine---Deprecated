#pragma once
#include <vector>

template <typename Type>
class Set
{
public:
	std::vector<Type> members;

	Set(std::vector<Type> members)
	{
		this->members = members;
	}

	Set(const Set<Type>& toCopy)
	{
		for (size_t i = 0; i < toCopy.members.size(); i++)
		{
			this->members.push_back(toCopy.members.at(i));
		}
	}

	void printout()
	{
		for (size_t i = 0; i < members.size(); i++)
		{
			std::cout << members.at(i) << std::endl;
		}
	}
};