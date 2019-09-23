#pragma once
#include "../Linalg.h"
#include "Time.h"
#include "Attribute.h"

namespace abyssengine {
	namespace math {
		struct Transform 
		{ 
			virtual mat4f toMatrix() const = 0;
		};

		struct Translation : public Transform
		{
			vec3f axis;

			Translation(const vec3f& axis) : axis(axis) {};
			Translation(const vec2f& axis) : axis(toVec3f(axis, 0.0f)) {};

			Position operator*(const Time& time) const { return Position{ axis * time.value }; }

			mat4f toMatrix() const override 
			{ 
				return mat4f::translate(axis); 
			}
		};

		struct Rotation : public Transform
		{
			vec4f axisAngle; // axis: xyz, angle: w

			Rotation(const vec3f& axis, const float& angle) : axisAngle(toVec4f(axis, angle)) {};
			Rotation(const vec4f& axisAngle) : axisAngle(axisAngle) {};

			Orientation operator*(const Time& time) const { return Orientation{ math::vec3f(axisAngle.x, axisAngle.y, axisAngle.z) * axisAngle.w * time.value }; }

			mat4f toMatrix() const override { return mat4f::rotate(axisAngle.w, math::vec3f(axisAngle.x, axisAngle.y, axisAngle.z)); }
		};

		struct Scaling : public Transform
		{
			vec3f axis;

			Scaling(const vec3f& axis) : axis(axis) {};
			Scaling(const vec2f& axis) : axis(toVec3f(axis, 0.0f)) {};

			Scale operator*(const Time& time) const { return Scale{ axis * time.value }; }

			mat4f toMatrix() const override { return mat4f::scale(axis); }
		};
	}
}