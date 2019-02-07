#pragma once
#include <map>

namespace abyssengine { namespace KeyBindings {
	enum Key
	{
		MOVE_UP, MOVE_LEFT, MOVE_DOWN, MOVE_RIGHT, DASH
	};

	static std::map<size_t, Key> bindings = { {17, MOVE_UP}, {30, MOVE_LEFT}, {31, MOVE_DOWN}, {32, MOVE_RIGHT}, {57, DASH} };
}}