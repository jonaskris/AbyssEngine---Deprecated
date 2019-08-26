#pragma once

namespace abyssengine {
	namespace math {
		struct Time
		{
			float value;

			Time(const float& value) : value(value) {};
			Time(const Time& other) : value(other.value) {};

			operator float& () { return value; };
		};
	}
}