#pragma once
#include <typeinfo>

/* 
	For storing different types of components as pointers in one collection.
*/
struct ComponentStoreType
{
	virtual ~ComponentStoreType() { };
};

/*
	Wraps a global variable that ensures each Component has an unique identifier for each ComponentType.
*/
class ComponentIdentifierCounter
{
	template <typename ComponentType>
	friend struct Component;

	static size_t counter;
};

/*
	Base of every component.
*/
template <typename ComponentType>
struct Component : public ComponentStoreType
{
private:
	static size_t identifier;
public:
	static size_t getIdentifierStatic() { return identifier; };
};
template <typename ComponentType>
size_t Component<ComponentType>::identifier = ComponentIdentifierCounter::counter++;