#pragma once
#include "../../InputEnums.h"
#include "../../../math/linalg.h"

namespace abyssengine {
	namespace input {
		class MouseObserver
		{
		public:
			MouseObserver();
			virtual ~MouseObserver();

			virtual void notifyMousePositionEvent(const math::vec2f& position, const math::vec2f& lastPosition) const {};
			virtual void notifyMouseEnterEvent(Mouse::Action action, const math::vec2f& position) const {};
			virtual void notifyMouseButtonEvent(Mouse::Button button, Mouse::Action action, Mouse::Modifier modifier, const math::vec2f& position) const {};
			virtual void notifyMouseScrollEvent(const math::vec2f& offset) const {};
			virtual void notifyMouseDragEvent(Mouse::Button button, Mouse::Action action, Mouse::Modifier modifier, const math::vec2f& from, const math::vec2f& to) const {};
		};
	}
}