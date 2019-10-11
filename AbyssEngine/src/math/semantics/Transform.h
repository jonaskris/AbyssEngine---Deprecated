#pragma once
#include "../Linalg.h"
#include "Time.h"
#include "../../utils/TypeIdentifier.h"

namespace abyssengine {
	namespace math {
		struct Transform {};

		struct AbsoluteTransform : public Transform
		{ 
			virtual mat4f toMatrix() const = 0;
		};

		struct Position : public AbsoluteTransform
		{
			vec3f vec;

			Position(const vec3f& vec) : vec(vec) {};
			Position(const vec2f& vec) : vec(toVec3f(vec, 0.0f)) {};

			mat4f toMatrix() const override 
			{ 
				return mat4f::translate(vec);
			}
		};

		struct Rotation : public AbsoluteTransform
		{
			vec4f vec; // axis: xyz, angle: w

			Rotation(const vec3f& axis, const float& angle) : vec(toVec4f(axis, angle)) {};
			Rotation(const vec4f& vec) : vec(vec) {};

			mat4f toMatrix() const override { return mat4f::rotate(vec.w, math::vec3f(vec.x, vec.y, vec.z)); }
		};

		struct Scale : public AbsoluteTransform
		{
			vec3f vec;

			Scale(const vec3f& vec) : vec(vec) {};
			Scale(const vec2f& vec) : vec(toVec3f(vec, 0.0f)) {};

			mat4f toMatrix() const override { return mat4f::scale(vec); }
		};

		struct RelativeTransform : public Transform
		{
			static const enum Type {
				POSITION, ROTATION, SCALE
			};

			size_t relativeEntityId;
			RelativeTransform::Type type;

			RelativeTransform(const size_t& relativeEntityId, RelativeTransform::Type type) : relativeEntityId(relativeEntityId), type(type) {};
		};
	}
}