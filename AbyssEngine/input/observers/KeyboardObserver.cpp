#include "KeyboardObserver.h"
#include "../listeners/KeyboardListener.h"

KeyboardObserver::KeyboardObserver()
{
	KeyboardListener::addObserver(*this);
}

KeyboardObserver::~KeyboardObserver()
{
	KeyboardListener::removeObserver(*this);
}
