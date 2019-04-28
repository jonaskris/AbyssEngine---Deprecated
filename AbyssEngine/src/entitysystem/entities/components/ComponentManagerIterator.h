#pragma once
#include "../Entity.h"

class ComponentManagerBase;
struct ComponentStoreType;

/*
	A generic iterator for use with ComponentManager.
*/
class ComponentManagerIterator
{
private:
	friend class ComponentManagerBase;

	size_t index = 0;
	ComponentManagerBase* componentManager;

	ComponentManagerIterator(const size_t& index, ComponentManagerBase* componentManager) : componentManager(componentManager), index(index) { };
public:

	/* 
		Returns false if incrementing leads to out of bounds. 
	*/
	bool increment();

	/* 
		Returns false if decrementing leads to out of bounds. 
	*/
	bool decrement();

	/*
		Gets the entity associated with component at current index.
	*/
	Entity getCurrentEntity() const;

	/* 
		Gets the component at current index.
	*/
	ComponentStoreType* getCurrentComponent() const;

	/* 
		For sorting iterators by size of the componentmanager.
	*/
	bool operator < (const ComponentManagerIterator& other) const;
};