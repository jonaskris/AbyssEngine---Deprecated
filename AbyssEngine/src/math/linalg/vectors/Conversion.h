#pragma once
#include "vec4f.h"
#include "vec4d.h"
#include "vec3f.h"
#include "vec3d.h"
#include "vec2f.h"
#include "vec2d.h"

namespace abyssengine {
	namespace math {
		inline vec4f toVec4f(const vec3f& xyz, const float& w) { return vec4f(xyz.x, xyz.y, xyz.z, w); }
		inline vec4f toVec4f(const vec2f& xy, const float& z, const float& w) { return vec4f(xy.x, xy.y, z, w); }
		inline vec4f toVec4f(const float& x, const float& y, const float& z, const float& w) { return vec4f(x, y, z, w); }

		inline vec3f toVec3f(const vec4f& xyzw) { return vec3f(xyzw.x, xyzw.y, xyzw.z); }
		inline vec3f toVec3f(const vec2f& xy, const float& z) { return vec3f(xy.x, xy.y, z); };
		inline vec3f toVec3f(const float& x, const float& y, const float& z) { return vec3f(x, y, z); };

		inline vec2f toVec2f(const vec4f& xyzw) { return vec2f(xyzw.x, xyzw.y); };
		inline vec2f toVec2f(const vec3f& xyz) { return vec2f(xyz.x, xyz.y); };
		inline vec2f toVec2f(const float& x, const float& y) { return vec2f(x, y); };
	}
}