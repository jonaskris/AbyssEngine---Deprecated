#include "MousePositionObserver.h"
#include "../listeners/MouseListener.h"

namespace abyssengine {
	MousePositionObserver::MousePositionObserver()
	{
		MouseListener::addObserver(*this, MouseListener::POSITION);
	}

	MousePositionObserver::~MousePositionObserver()
	{
		MouseListener::removeObserver(*this, MouseListener::POSITION);
	}
}