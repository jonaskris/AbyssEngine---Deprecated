#pragma once
#include "MouseObserver.h"
#include "../listeners/MouseListener.h"
#include "../../../math/linalg.h"

namespace abyssengine {
	class MousePositionObserver : public MouseObserver
	{
	public:
		MousePositionObserver()
		{
			MouseListener::addObserver(*this, MouseListener::POSITION);
		}

		virtual ~MousePositionObserver()
		{
			MouseListener::removeObserver(*this, MouseListener::POSITION);
		}
		virtual void notifyMousePositionEvent(const math::vec2f& position) = 0;
	};
}