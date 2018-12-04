#pragma once

#include <iostream>
#include "Math.h"
#include "vec2.h"
#include "vec3.h"

struct mat3
{
	union {
		float elements[3 * 3];
		vec3 columns[3];
	};

	mat3();
	mat3(const mat3& other);

	static mat3 identity();

	mat3& multiply(const mat3& other);
	friend mat3 operator*(const mat3& left, const mat3& right);
	mat3& operator*=(const mat3& other);

	vec3& multiply(const vec3& vector) const;
	friend vec3 operator*(const mat3& left, const vec3& vector);

	static mat3 translation(const vec2& translation);
	static mat3 rotation(float angle, const vec3& axis);
	static mat3 scale(const vec3& scale);
};