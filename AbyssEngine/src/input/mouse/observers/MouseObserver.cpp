#include "MouseObserver.h"
#include "../listeners/MouseListener.h"

namespace abyssengine {
	namespace input {
		
			MouseObserver::MouseObserver() { 
				MouseListener::addObserver(*this, MouseListener::POSITION); 
				MouseListener::addObserver(*this, MouseListener::ENTER); 
				MouseListener::addObserver(*this, MouseListener::BUTTON); 
				MouseListener::addObserver(*this, MouseListener::SCROLL); 
				MouseListener::addObserver(*this, MouseListener::DRAG); 
			}
			MouseObserver::~MouseObserver() { 
				MouseListener::removeObserver(*this, MouseListener::POSITION);
				MouseListener::removeObserver(*this, MouseListener::ENTER);
				MouseListener::removeObserver(*this, MouseListener::BUTTON);
				MouseListener::removeObserver(*this, MouseListener::SCROLL);
				MouseListener::removeObserver(*this, MouseListener::DRAG);
			}
	}
}