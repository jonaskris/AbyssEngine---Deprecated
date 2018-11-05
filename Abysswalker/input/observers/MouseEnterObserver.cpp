#include "MouseEnterObserver.h"
#include "../listeners/MouseListener.h"

MouseEnterObserver::MouseEnterObserver()
{
	MouseListener::addObserver(*this, MouseListener::ENTER);
}

MouseEnterObserver::~MouseEnterObserver()
{
	MouseListener::removeObserver(*this, MouseListener::ENTER);
}
