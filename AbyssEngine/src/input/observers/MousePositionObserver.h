#pragma once
#include "MouseObserver.h"

namespace abyssengine {
	class MousePositionObserver : public MouseObserver
	{
	public:
		MousePositionObserver();
		virtual ~MousePositionObserver();
		virtual void notifyMousePositionEvent(const double& xpos, const double& ypos) = 0;
	};
}