#pragma once
#include "../../InputEnums.h"
#include "../../../math/linalg.h"

namespace abyssengine {
	class MouseObserver
	{
	public:
		virtual void notifyMousePositionEvent(const math::vec2f& position) {};
		virtual void notifyMouseEnterEvent(Mouse::Action action, const math::vec2f& position) {};
		virtual void notifyMouseButtonEvent(Mouse::Button button, Mouse::Action action, Mouse::Modifier modifier, const math::vec2f& position) {};
		virtual void notifyMouseScrollEvent(const math::vec2f& offset) {};
		virtual void notifyMouseDragEvent(Mouse::Button button, Mouse::Action action, Mouse::Modifier modifier, const math::vec2f& from, const math::vec2f& to) {};
	};
}