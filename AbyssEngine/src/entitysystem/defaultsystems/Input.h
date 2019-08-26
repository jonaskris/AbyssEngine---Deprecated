#pragma once
#include "../../input/mouse/observers/MouseObserver.h"
#include "../../input/keyboard/observers/KeyboardObserver.h"
#include "../../input/InputEnums.h"
#include "../defaultevents/Input.h"
#include "../systems/System.h"
#include "../defaultcomponents/Spatial.h"

namespace abyssengine {
	namespace entitysystem {

		namespace im = input::Mouse;
		class MouseInput : public System<>, public input::MouseObserver
		{
		private:
			void notifyMousePositionEvent(const math::vec2f& position, const math::vec2f& lastPosition) const override 
				{ entityManager->newUnit(Mouse_Position_Event{ position, lastPosition }); };
			void notifyMouseEnterEvent(im::Action action, const math::vec2f& position) const override
				{ entityManager->newUnit(Mouse_Enter_Event{ action, position }); };
			void notifyMouseButtonEvent(im::Button button, im::Action action, im::Modifier modifier, const math::vec2f& position) const override
				{ entityManager->newUnit(Mouse_Button_Event{ button, action, modifier }); };
			void notifyMouseScrollEvent(const math::vec2f& offset) const override
				{ entityManager->newUnit(Mouse_Scroll_Event{ offset }); };
			void notifyMouseDragEvent(im::Button button, im::Action action, im::Modifier modifier, const math::vec2f& from, const math::vec2f& to) const override
				{ entityManager->newUnit(Mouse_Drag_Event{ button, action, modifier, from, to }); };
		};

		namespace ik = input::Keyboard;
		class KeyboardInput : public System<>, public input::KeyboardObserver
		{
		private:
			void notifyKeyEvent(ik::Key key, ik::Action action, ik::Modifier modifier) const override 
				{ entityManager->newUnit(Keyboard_Key_Event{ key, action, modifier }); }
		};
	}
}