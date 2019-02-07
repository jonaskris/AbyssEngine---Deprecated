#pragma once
#include "MouseObserver.h"

namespace abyssengine {
	class MouseScrollObserver : public MouseObserver
	{
	public:
		MouseScrollObserver();
		virtual ~MouseScrollObserver();
		virtual void notifyMouseScrollEvent(const double& xoffset, const double& yoffset) = 0;
	};
}