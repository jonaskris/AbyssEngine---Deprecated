#pragma once
#include "MouseObserver.h"
#include "../listeners/MouseListener.h"
#include "../../../math/vec2.h"

namespace abyssengine {
	class MouseScrollObserver : public MouseObserver
	{
	public:
		MouseScrollObserver() { MouseListener::addObserver(*this, MouseListener::SCROLL); }
		virtual ~MouseScrollObserver() { MouseListener::removeObserver(*this, MouseListener::SCROLL); }
		virtual void notifyMouseScrollEvent(const math::vec2f& offset) = 0;
	};
}