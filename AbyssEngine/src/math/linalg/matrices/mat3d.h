#pragma once
#include <iostream>
#include "../../mathUtils.h"
#include "../vectors/vec2f.h"
#include "../vectors/vec3f.h"

namespace abyssengine {
	namespace math {
		struct mat3d
		{
			union {
				double elements[3 * 3];
				vec3d columns[3];
			};

			mat3d() : columns{ vec3d{}, vec3d{}, vec3d{} } {}
			mat3d(const vec3d& column0, const vec3d& column1, const vec3d& column2) : columns{ column0, column1, column2 } {}
			mat3d(const mat3d& other) : mat3d(other.columns[0], other.columns[1], other.columns[2]) {}

			mat3d& multiply(const mat3d& other)
			{
				mat3d temp;

				for (size_t row = 0; row < 3; row++)
				{
					for (size_t column = 0; column < 3; column++)
					{
						double sum = 0.0;
						for (size_t e = 0; e < 3; e++)
						{
							sum += elements[row + e * 3] * other.elements[e + column * 3];
						}
						temp.elements[row + column * 3] = sum;
					}
				}

				memcpy(elements, temp.elements, 3 * 3 * sizeof(double));
				return *this;
			}

			vec3d multiply(const vec3d& vec)
			{
				vec3d returnVector;

				returnVector.x = vec.x * elements[0] + vec.y * elements[4] + vec.z * elements[8];
				returnVector.y = vec.x * elements[1] + vec.y * elements[5] + vec.z * elements[9];
				returnVector.z = vec.x * elements[2] + vec.y * elements[6] + vec.z * elements[10];

				return returnVector;
			}

			vec3d operator*(const vec3d& vec) { return multiply(vec); }

			mat3d operator*(const mat3d& other) { return mat3d(*this).multiply(other); }
			mat3d& operator*=(const mat3d& other) { return multiply(other); }

			static mat3d identity(const double& scalar = 1.0)
			{
				mat3d returnMatrix;

				for (size_t i = 0; i < 3; i++)
					returnMatrix.columns[i].elements[i] = scalar;

				return returnMatrix;
			}

			static mat3d translate(const vec2d& translation)
			{
				mat3d returnMatrix = identity();

				returnMatrix.columns[2].x = translation.x;
				returnMatrix.columns[2].y = translation.y;

				return returnMatrix;
			}

			static mat3d rotate(const double& angle, const vec3d& axis)
			{
				mat3d returnMatrix = identity();

				double r = math::toRadians(angle);
				double c = cos(r);
				double s = sin(r);
				double omc = 1.0 - c;

				double x = axis.x;
				double y = axis.y;
				double z = axis.z;

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

			static mat3d scale(const vec2d& factor)
			{
				mat3d returnMatrix = identity();

				returnMatrix.columns[0].x = factor.x;
				returnMatrix.columns[1].y = factor.y;

				return returnMatrix;
			}
		};
	}
}