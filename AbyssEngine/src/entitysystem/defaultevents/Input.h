#pragma once
#include "../../input/InputEnums.h"
#include "../events/Event.h"

namespace abyssengine {
	template <typename EventType>
	using Event = entitysystem::Event<EventType>;

	class MouseButton_Event : public Event<MouseButton_Event>
	{
	private:
		Mouse::Button button;
		Mouse::Action action;
		Mouse::Modifier modifier;
	public:
		MouseButton_Event(Mouse::Button button, Mouse::Action action, Mouse::Modifier modifier) : button(button), action(action), modifier(modifier) {};

		Mouse::Button getButton() { return button; }
		Mouse::Action getAction() { return action; }
		Mouse::Modifier getModifier() { return modifier; }
	};

	class Key_Event : public Event<Key_Event>
	{
	private:
		Keyboard::Key key;
		Keyboard::Action action;
		Keyboard::Modifier modifier;
	public:
		Key_Event(Keyboard::Key key, Keyboard::Action action, Keyboard::Modifier modifier) : key(key), action(action), modifier(modifier) {};

		Keyboard::Key getKey() { return key; }
		Keyboard::Action getAction() { return action; }
		Keyboard::Modifier getModifier() { return modifier; }
	};
}