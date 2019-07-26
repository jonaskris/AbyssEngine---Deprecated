#pragma once
#include <iostream>
#include "../../mathUtils.h"
#include "../vectors/vec3d.h"
#include "../vectors/vec4d.h"

namespace abyssengine {
	namespace math {
		struct mat4d
		{
			union {
				double elements[4 * 4];
				vec4d columns[4];
			};

			mat4d() : columns{ vec4d{}, vec4d{}, vec4d{}, vec4d{} } {}
			mat4d(const vec4d& column0, const vec4d& column1, const vec4d& column2, const vec4d& column3) : columns{ column0, column1, column2, column3 } {}
			mat4d(const mat4d& other) : mat4d(other.columns[0], other.columns[1], other.columns[2], other.columns[3]) {}

			mat4d& multiply(const mat4d& other)
			{
				for (int y = 0; y < 4; y++)
				{
					for (int x = 0; x < 4; x++)
					{
						double sum = 0.0;
						for (int e = 0; e < 4; e++)
						{
							sum += elements[x + e * 4] * other.elements[e + y * 4];
						}
						elements[x + y * 4] = sum;
					}
				}
				return *this;
			}

			vec4d multiply(const vec4d& vec) const
			{
				vec4d returnVector;

				double x = vec.x;
				double y = vec.y;
				double z = vec.z;
				double w = vec.w;

				returnVector.x = vec.x * elements[0] + vec.x * elements[4] + vec.x * elements[8] + vec.x * elements[12];
				returnVector.y = vec.y * elements[1] + vec.y * elements[5] + vec.y * elements[9] + vec.y * elements[13];
				returnVector.z = vec.z * elements[2] + vec.z * elements[6] + vec.z * elements[10] + vec.z * elements[14];
				returnVector.w = vec.w * elements[3] + vec.w * elements[7] + vec.w * elements[11] + vec.w * elements[15];

				return returnVector;
			}

			vec4d operator*(const vec4d& vec) const { return multiply(vec); }

			mat4d operator*(const mat4d& other) const { return mat4d(*this).multiply(other); }
			mat4d& operator*=(const mat4d& other) { return multiply(other); }

			static mat4d identity(const double& scalar = 1.0)
			{
				mat4d returnMatrix;

				for (size_t i = 0; i < 4; i++)
					returnMatrix.columns[i].elements[i] = scalar;

				return returnMatrix;
			}

			static mat4d translate(const vec3d& translation)
			{
				mat4d returnMatrix = identity();

				returnMatrix.columns[3].x = translation.x;
				returnMatrix.columns[3].y = translation.y;
				returnMatrix.columns[3].z = translation.z;

				return returnMatrix;
			}

			static mat4d rotate(const double& angle, const vec3d& axis)
			{
				mat4d returnMatrix = identity();

				double r = math::toRadians(angle);
				double c = cos(r);
				double s = sin(r);
				double omc = 1.0 - c;

				double x = axis.x;
				double y = axis.y;
				double z = axis.z;

				returnMatrix.elements[0 + 0 * 4] = x * x * omc + c;
				returnMatrix.elements[0 + 1 * 4] = y * x * omc + z * s;
				returnMatrix.elements[0 + 2 * 4] = x * z * omc - y * s;

				returnMatrix.elements[1 + 0 * 4] = x * y * omc - z * s;
				returnMatrix.elements[1 + 1 * 4] = y * y * omc + c;
				returnMatrix.elements[1 + 2 * 4] = y * z * omc + x * s;

				returnMatrix.elements[2 + 0 * 4] = x * z * omc + y * s;
				returnMatrix.elements[2 + 1 * 4] = y * z * omc - x * s;
				returnMatrix.elements[2 + 2 * 4] = z * z * omc + c;

				return returnMatrix;
			}

			static mat4d scale(const vec3d& factor)
			{
				mat4d returnMatrix = identity();

				returnMatrix.columns[0].x = factor.x;
				returnMatrix.columns[1].y = factor.y;
				returnMatrix.columns[2].y = factor.z;

				return returnMatrix;
			}

			static mat4d perspective(double fov, double aspectRatio, double near, double far)
			{
				mat4d returnMatrix = identity();
				double q = 1.0 / tan(math::toRadians(0.5f * fov));
				double a = q / aspectRatio;

				double b = (near + far) / (near - far);
				double c = (2.0 * near * far) / (near - far);

				returnMatrix.elements[0 + 0 * 4] = a;
				returnMatrix.elements[1 + 1 * 4] = q;
				returnMatrix.elements[2 + 2 * 4] = b;
				returnMatrix.elements[2 + 3 * 4] = -1.0;
				returnMatrix.elements[3 + 2 * 4] = c;

				return returnMatrix;
			}

			static mat4d orthographic(double left, double right, double bottom, double top, double near, double far)
			{
				mat4d returnMatrix = identity();

				returnMatrix.elements[0 + 0 * 4] = 2.0 / (right - left);
				returnMatrix.elements[1 + 1 * 4] = 2.0 / (top - bottom);
				returnMatrix.elements[2 + 2 * 4] = 2.0 / (near - far);

				returnMatrix.elements[0 + 3 * 4] = (left + right) / (left - right);
				returnMatrix.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
				returnMatrix.elements[2 + 3 * 4] = (far + near) / (far - near);

				return returnMatrix;
			}

			static mat4d viewMatrix(const vec3d& cameraPos, const vec3d& lookAtPos, const vec3d& up)
			{
				mat4d returnMatrix = identity();
				vec3d f = (lookAtPos - cameraPos).normalize();
				vec3d s = f.cross(up.normalize());
				vec3d u = s.cross(f);

				returnMatrix.elements[0 + 0 * 4] = s.x;
				returnMatrix.elements[0 + 1 * 4] = s.y;
				returnMatrix.elements[0 + 2 * 4] = s.z;

				returnMatrix.elements[1 + 0 * 4] = u.x;
				returnMatrix.elements[1 + 1 * 4] = u.y;
				returnMatrix.elements[1 + 2 * 4] = u.z;

				returnMatrix.elements[2 + 0 * 4] = -f.x;
				returnMatrix.elements[2 + 1 * 4] = -f.y;
				returnMatrix.elements[2 + 2 * 4] = -f.z;

				return returnMatrix * translate(vec3d(cameraPos.x, cameraPos.y, cameraPos.z) * -1);
			}
		};
	}
}