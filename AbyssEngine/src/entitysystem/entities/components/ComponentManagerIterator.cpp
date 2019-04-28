#include "ComponentManagerIterator.h"
#include "ComponentManager.h"
#include "../Entity.h"

struct ComponentStoreType;

Entity ComponentManagerIterator::getCurrentEntity() const 
{ 
	return componentManager->entityAt(index); 
};

ComponentStoreType* ComponentManagerIterator::getCurrentComponent() const 
{
	return componentManager->componentAt(index);
};

bool ComponentManagerIterator::increment()
{
	if (index == (componentManager->size() - 1))
		return false;
	index++;
	return true;
};

bool ComponentManagerIterator::decrement()
{
	if (index == 0)
		return false;
	index--;
	return true;
};

bool ComponentManagerIterator::operator < (const ComponentManagerIterator& other) const
{
	return (componentManager->size() < other.componentManager->size());
}