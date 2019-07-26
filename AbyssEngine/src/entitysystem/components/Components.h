#pragma once
#include "Component.h"
#include "../units/UnitTypeIdentifier.h"
#include "../../math/linalg.h"

namespace entitysystem
{

	using namespace abyssengine;

	/*
		Component used for testing purposes.

		UnitStorageSpecifier is used here to set an initial storage capacity. This is done to avoid
		excessive reallocation in the vector the components are stored in.
	*/
	struct ComponentA : public Component<ComponentA>, UnitStorageSpecifier<ComponentA>
	{
		float x, y, z;
		ComponentA(float x, float y, float z) : x(x), y(y), z(z) {};
	};
	size_t UnitStorageSpecifier<ComponentA>::initialStorageCapacity = 1024;

	struct ComponentB : public Component<ComponentB>
	{
		bool b;
		ComponentB(bool b) : b(b) {};
	};
}