#include "MouseButtonObserver.h"
#include "../listeners/MouseListener.h"

MouseButtonObserver::MouseButtonObserver()
{
	MouseListener::addObserver(*this, MouseListener::BUTTON);
}

MouseButtonObserver::~MouseButtonObserver()
{
	MouseListener::removeObserver(*this, MouseListener::BUTTON);
}
