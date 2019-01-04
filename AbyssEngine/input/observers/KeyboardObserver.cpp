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

SimpleKeyboardObserver::SimpleKeyboardObserver()
{
	KeyboardListener::addObserver(*this);
}

SimpleKeyboardObserver::~SimpleKeyboardObserver()
{
	KeyboardListener::removeObserver(*this);
}