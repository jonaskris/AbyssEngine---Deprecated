#pragma once
#include "../../input/mouse/observers/MouseButtonObserver.h"
#include "../../input/keyboard/observers/KeyboardObserver.h"
#include "../../input/InputEnums.h"
#include "../defaultevents/Input.h"
#include "../systems/System.h"
#include "../defaultcomponents/Spatial.h"

namespace abyssengine {
	using UnitGroup = entitysystem::UnitGroup;

	template <typename... UnitTypes>
	using System = entitysystem::System<UnitTypes...>;

	class Input : public System<>, public MouseButtonObserver, public KeyboardObserver
	{
	private:
		void notifyMouseButtonEvent(Mouse::Button button, Mouse::Action action, Mouse::Modifier modifier, const math::vec2f& position) override
		{
			entityManager->newUnit( MouseButton_Event {button, action, modifier } );
		}

		void notifyKeyEvent(Keyboard::Key key, Keyboard::Action action, Keyboard::Modifier modifier)
		{
			entityManager->newUnit( Key_Event{ key, action, modifier } );
		}
	};
}