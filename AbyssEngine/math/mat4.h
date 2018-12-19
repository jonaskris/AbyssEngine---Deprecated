#pragma once

#include <iostream>
#include "mathUtils.h"
#include "vec3.h"
#include "vec4.h"

struct mat4
{
	union {
		float elements[4 * 4];
		vec4 columns[4];
	};

	mat4();
	mat4(const mat4& other);
	static mat4 identity();

	mat4 multiply(const mat4& other);
	friend mat4 operator*(const mat4& left, const mat4& right);
	mat4& operator*=(const mat4& other);

	vec4 multiply(const vec4& vector) const;
	friend vec4 operator*(const mat4& left, const vec4& right);


	static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
	static mat4 perspective(float fov, float aspectRatio, float near, float far);

	static mat4 translate(const vec3& translation);
	static mat4 rotation(float angle, const vec3& axis);
	static mat4 scale(const vec3& scale);
	static mat4 LookAt(const vec3& cameraPos, const vec3& lookAtPos, const vec3& up);
};