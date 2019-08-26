#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

namespace abyssengine { 
	namespace math {
		template <typename FloatingType>
		FloatingType toRadians(FloatingType degrees) {
			return degrees * ((FloatingType)M_PI / (FloatingType)180.0);
		}
	}
}