#include "KeyboardObserver.h"
#include "../listeners/KeyboardListener.h"

namespace abyssengine {
	KeyboardObserver::KeyboardObserver()
	{
		KeyboardListener::addObserver(*this);
	}

	KeyboardObserver::~KeyboardObserver()
	{
		KeyboardListener::removeObserver(*this);
	}

	SimpleKeyboardObserver::SimpleKeyboardObserver()
	{
		KeyboardListener::addObserver(*this);
	}

	SimpleKeyboardObserver::~SimpleKeyboardObserver()
	{
		KeyboardListener::removeObserver(*this);
	}
}