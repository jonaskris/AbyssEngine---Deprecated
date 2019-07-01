#include "ComponentManagerIterator.h"
#include "ComponentManager.h"
#include "../Entity.h"

struct ComponentBase;

ComponentBase* ComponentManagerIterator::getCurrentComponent() const
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

size_t ComponentManagerIterator::getComponentManagerSize() const { return componentManager->size(); }

bool ComponentManagerIterator::operator < (const ComponentManagerIterator & other) const
{
	return (componentManager->size() < other.componentManager->size());
}