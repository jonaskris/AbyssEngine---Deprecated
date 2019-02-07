#include "MouseScrollObserver.h"
#include "../listeners/MouseListener.h"

namespace abyssengine {
	MouseScrollObserver::MouseScrollObserver()
	{
		MouseListener::addObserver(*this, MouseListener::SCROLL);
	}

	MouseScrollObserver::~MouseScrollObserver()
	{
		MouseListener::removeObserver(*this, MouseListener::SCROLL);
	}
}