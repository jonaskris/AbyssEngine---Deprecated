#pragma once
#include "../units/Unit.h"

class EntityManager;

template <typename UnitType>
class UnitManager;

/*
	Entities are made up of components.

	Components can be set to be erased which takes effect at end of current update,
	an erased component will still be active and considered by systems until actually erased.

	Components can also set to be ignored. Ignored components will not remain active and
	will not be considered by systems. Ignored components will also be erased at end of current update.
*/
template <typename ComponentType>
struct Component : public Unit, UnitTypeIdentifier<ComponentType>
{
protected:
	bool erase;

	Component() : erase(false) {};
public:
	virtual ~Component() {};

	bool getErase() const override { return erase || getIgnore(); }
	void setErase() override { erase = true; }
};