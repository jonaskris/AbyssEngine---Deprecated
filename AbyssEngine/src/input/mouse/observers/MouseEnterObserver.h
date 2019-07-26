#pragma once
#include "MouseObserver.h"
#include "../listeners/MouseListener.h"
#include "../../InputEnums.h"
#include "../../../math/vec2.h"

namespace abyssengine {
	class MouseEnterObserver : public MouseObserver
	{
	public:
		MouseEnterObserver() { MouseListener::addObserver(*this, MouseListener::ENTER); }
		virtual ~MouseEnterObserver() { MouseListener::removeObserver(*this, MouseListener::ENTER); }

		virtual void notifyMouseEnterEvent(Mouse::Action action, const math::vec2f& position) = 0;
	};
}