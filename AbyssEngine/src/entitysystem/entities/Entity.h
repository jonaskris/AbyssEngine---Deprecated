#pragma once

/*
	Entities are unique per EntityManager,
	and can only be assigned one component per ComponentType.
*/
struct Entity
{
	size_t id;

	Entity(const size_t& id) : id(id) {};

	bool operator==(const Entity& other) const
	{
		return id == other.id;
	}

	bool operator>(const Entity& other) const
	{
		return id > other.id;
	}

	bool operator<(const Entity& other) const
	{
		return id < other.id;
	}
};