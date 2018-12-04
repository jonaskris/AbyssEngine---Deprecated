#pragma once
#include "MouseObserver.h"

class MouseButtonObserver: public MouseObserver
{
public:
	MouseButtonObserver();
	virtual ~MouseButtonObserver();
	virtual void notifyMouseButtonEvent(const int& button, const int& action, const int& mods) = 0;
};

