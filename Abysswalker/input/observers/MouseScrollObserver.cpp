#include "MouseScrollObserver.h"
#include "../listeners/MouseListener.h"

MouseScrollObserver::MouseScrollObserver()
{
	MouseListener::addObserver(*this, MouseListener::SCROLL);
}

MouseScrollObserver::~MouseScrollObserver()
{
	MouseListener::removeObserver(*this, MouseListener::SCROLL);
}
