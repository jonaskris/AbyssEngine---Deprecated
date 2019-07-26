#pragma once
#include "MouseObserver.h"
#include "../listeners/MouseListener.h"
#include "../../InputEnums.h"
#include "../../../math/linalg.h"

namespace abyssengine {
	class MouseButtonObserver : public MouseObserver
	{
	public:
		MouseButtonObserver() { MouseListener::addObserver(*this, MouseListener::BUTTON); }
		virtual ~MouseButtonObserver() { MouseListener::removeObserver(*this, MouseListener::BUTTON); }

		virtual void notifyMouseButtonEvent(Mouse::Button button, Mouse::Action action, Mouse::Modifier modifier, const math::vec2f& position) = 0;
	};
}