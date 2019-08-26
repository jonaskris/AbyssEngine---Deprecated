#pragma once
#include "../listeners/KeyboardListener.h"
#include "../../InputEnums.h"

namespace abyssengine {
	namespace input {
		class KeyboardObserver
		{
		public:
			KeyboardObserver() { KeyboardListener::addObserver(*this); }
			virtual ~KeyboardObserver() { KeyboardListener::removeObserver(*this); }

			virtual void notifyKeyEvent(Keyboard::Key key, Keyboard::Action action, Keyboard::Modifier modifier) const = 0;
		};
	}
}