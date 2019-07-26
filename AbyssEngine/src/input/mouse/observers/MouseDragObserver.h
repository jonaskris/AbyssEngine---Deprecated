#pragma once
#include "MouseObserver.h"
#include "../listeners/MouseListener.h"
#include "../../InputEnums.h"
#include "../../../math/vec2.h"

namespace abyssengine {
	class MouseDragObserver : public MouseObserver
	{
	public:
		MouseDragObserver() { MouseListener::addObserver(*this, MouseListener::DRAG); }
		virtual ~MouseDragObserver() { MouseListener::removeObserver(*this, MouseListener::DRAG); }

		virtual void notifyMouseDragEvent(Mouse::Button button, Mouse::Action action, Mouse::Modifier modifier, const math::vec2f& from, const math::vec2f& to) = 0;
	};
}