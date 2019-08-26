#pragma once
#include "../../input/InputEnums.h"
#include "../events/Event.h"

namespace abyssengine {
	namespace entitysystem {
		namespace im = input::Mouse;
		class Mouse_Position_Event : public Event<Mouse_Position_Event>
		{
		private:
			math::vec2f position;
			math::vec2f lastPosition;
		public:
			Mouse_Position_Event(const math::vec2f& position, const math::vec2f& lastPosition) : position(position), lastPosition(lastPosition) { };

			math::vec2f getPosition() const { return position; }
			math::vec2f getLastPosition() const { return lastPosition; }
		};

		class Mouse_Enter_Event : public Event<Mouse_Enter_Event>
		{
		private:
			im::Action action; // Enter or Exit
			math::vec2f position;
		public:
			Mouse_Enter_Event(const im::Action& action, const math::vec2f& position) : action(action), position(position) { };

			im::Action getAction() const { return action; }
			math::vec2f getPosition() const { return position; }
		};

		class Mouse_Button_Event : public Event<Mouse_Button_Event>
		{
		private:
			im::Button button;
			im::Action action;
			im::Modifier modifier;
		public:
			Mouse_Button_Event(const im::Button& button, const im::Action& action, const im::Modifier& modifier) : button(button), action(action), modifier(modifier) {};

			im::Button getButton() const { return button; }
			im::Action getAction() const { return action; }
			im::Modifier getModifier() const { return modifier; }
		};

		class Mouse_Scroll_Event : public Event<Mouse_Scroll_Event>
		{
		private:
			math::vec2f offset;
		public:
			Mouse_Scroll_Event(const math::vec2f& offset) : offset(offset) {};

			math::vec2f getOffset() const { return offset; }
		};

		class Mouse_Drag_Event : public Event<Mouse_Drag_Event>
		{
		private:
			im::Button button;
			im::Action action;
			im::Modifier modifier;
			math::vec2f from;
			math::vec2f to;
		public:
			Mouse_Drag_Event(const im::Button& button, const im::Action& action, const im::Modifier& modifier, const math::vec2f& from, const math::vec2f& to) : button(button), action(action), modifier(modifier), from(from), to(to) { };
			
			im::Button getButton() const { return button; }
			im::Action getAction() const { return action; }
			im::Modifier getModifier() const { return modifier; }
			math::vec2f getFrom() const { return from; }
			math::vec2f getTo() const { return to; }
		};

		namespace ik = input::Keyboard;
		class Keyboard_Key_Event : public Event<Keyboard_Key_Event>
		{
		private:
			ik::Key key;
			ik::Action action;
			ik::Modifier modifier;
		public:
			Keyboard_Key_Event(const ik::Key& key, const ik::Action& action, const ik::Modifier& modifier) : key(key), action(action), modifier(modifier) {};

			ik::Key getKey() const { return key; }
			ik::Action getAction() const { return action; }
			ik::Modifier getModifier() const { return modifier; }
		};
	}
}