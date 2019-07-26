#pragma once
#include "../listeners/KeyboardListener.h"
#include "../../InputEnums.h"

namespace abyssengine {
	class KeyboardObserver
	{
	public:
		KeyboardObserver() { KeyboardListener::addObserver(*this); }
		virtual ~KeyboardObserver() { KeyboardListener::removeObserver(*this); }

		virtual void notifyKeyEvent(Keyboard::Key key, Keyboard::Action action, Keyboard::Modifier modifier) = 0;
	};
}