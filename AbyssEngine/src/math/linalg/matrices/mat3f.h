#pragma once
#include <iostream>
#include "../../mathUtils.h"
#include "../vectors/vec2f.h"
#include "../vectors/vec3f.h"

namespace abyssengine {
	namespace math {
		struct mat3f
		{
			union {
				float elements[3 * 3];
				vec3f columns[3];
			};

			mat3f() : columns{ vec3f{}, vec3f{}, vec3f{} } {}
			mat3f(const vec3f& column0, const vec3f& column1, const vec3f& column2) : columns{ column0, column1, column2 } {}
			mat3f(const mat3f& other) : mat3f(other.columns[0], other.columns[1], other.columns[2]) {}

			mat3f& multiply(const mat3f& other)
			{
				for (int y = 0; y < 3; y++)
					for (int x = 0; x < 3; x++)
					{
						float sum = 0.0f;
						for (int e = 0; e < 3; e++)
						{
							sum += elements[x + e * 3] * other.elements[e + y * 3];
						}
						elements[x + y * 3] = sum;
					}
				return *this;
			}

			vec3f multiply(const vec3f& vec)
			{
				vec3f returnVector;

				returnVector.x = vec.x * elements[0] + vec.y * elements[4] + vec.z * elements[8];
				returnVector.y = vec.x * elements[1] + vec.y * elements[5] + vec.z * elements[9];
				returnVector.z = vec.x * elements[2] + vec.y * elements[6] + vec.z * elements[10];

				return returnVector;
			}

			vec3f operator*(const vec3f& vec) { return multiply(vec); }

			mat3f operator*(const mat3f& other) { return mat3f(*this).multiply(other); }
			mat3f& operator*=(const mat3f& other) { return multiply(other); }

			static mat3f identity(const float& scalar = 1.0f)
			{
				mat3f returnMatrix;

				for (size_t i = 0; i < 3; i++)
					returnMatrix.columns[i].elements[i] = scalar;

				return returnMatrix;
			}

			static mat3f translate(const vec2f& translation)
			{
				mat3f returnMatrix = identity();

				returnMatrix.columns[2].x = translation.x;
				returnMatrix.columns[2].y = translation.y;

				return returnMatrix;
			}

			static mat3f rotate(const float& angle, const vec3f& axis)
			{
				mat3f returnMatrix = identity();

				float r = math::toRadians(angle);
				float c = cos(r);
				float s = sin(r);
				float omc = 1.0f - c;

				float x = axis.x;
				float y = axis.y;
				float z = axis.z;

				returnMatrix.elements[0 + 0 * 3] = c + x * x * omc;
				returnMatrix.elements[0 + 1 * 3] = x * y * omc - z * s;
				returnMatrix.elements[0 + 2 * 3] = x * z * omc + y * s;

				returnMatrix.elements[1 + 0 * 3] = y * x * omc + z * s;
				returnMatrix.elements[1 + 1 * 3] = c + y * y * omc;
				returnMatrix.elements[1 + 2 * 3] = y * z * omc - x * s;

				returnMatrix.elements[2 + 0 * 3] = z * x * omc - y * s;
				returnMatrix.elements[2 + 1 * 3] = z * y * omc + x * s;
				returnMatrix.elements[2 + 2 * 3] = c + z * z * omc;

				return returnMatrix;
			}

			static mat3f scale(const vec2f& factor)
			{
				mat3f returnMatrix = identity();

				returnMatrix.columns[0].x = factor.x;
				returnMatrix.columns[1].y = factor.y;

				return returnMatrix;
			}
		};
	} 
}