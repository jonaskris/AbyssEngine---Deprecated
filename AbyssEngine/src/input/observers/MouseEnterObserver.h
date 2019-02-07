#pragma once
#include "MouseObserver.h"

namespace abyssengine {
	class MouseEnterObserver : public MouseObserver
	{
	public:
		MouseEnterObserver();
		virtual ~MouseEnterObserver();
		virtual void notifyMouseEnterEvent(const int& entered) = 0;
	};
}