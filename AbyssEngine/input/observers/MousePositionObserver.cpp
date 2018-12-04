#include "MousePositionObserver.h"
#include "../listeners/MouseListener.h"

MousePositionObserver::MousePositionObserver()
{
	MouseListener::addObserver(*this, MouseListener::POSITION);
}

MousePositionObserver::~MousePositionObserver()
{
	MouseListener::removeObserver(*this, MouseListener::POSITION);
}
