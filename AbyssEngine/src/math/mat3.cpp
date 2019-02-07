#include "mat3.h"

namespace abyssengine { namespace math {
	mat3::mat3()
	{
		for (int i = 0; i < 3 * 3; i++) {
			elements[i] = 0.0f;
		}
	}

	mat3::mat3(const mat3& other)
	{
		for (int i = 0; i < 3 * 3; i++) {
			elements[i] = other.elements[i];
		}
	}

	mat3& mat3::multiply(const mat3& other)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 3; e++)
				{
					sum += elements[x + e * 3] * other.elements[e + y * 3];
				}
				elements[x + y * 3] = sum;
			}
		}
		return *this;
	}

	vec3 mat3::multiply(const vec3& vector) const
	{
		vec3 returnVector;

		float x = vector.x;
		float y = vector.y;
		float z = vector.z;

		returnVector.x = x * elements[0] + x * elements[3] + x * elements[6];
		returnVector.y = y * elements[1] + y * elements[4] + y * elements[7];
		returnVector.z = z * elements[2] + z * elements[5] + z * elements[8];

		return returnVector;
	}

	vec3 operator*(const mat3& left, const vec3& right)
	{
		return left.multiply(right);
	}

	mat3 operator*(const mat3& left, const mat3& right)
	{
		mat3 returnMatrix(left);
		returnMatrix.multiply(right);

		return returnMatrix;
	}

	mat3& mat3::operator*=(const mat3& other)
	{
		return multiply(other);
	}

	mat3 mat3::identity()
	{
		mat3 returnMatrix;
		for (int i = 0; i < 3 * 3; i++) {
			returnMatrix.elements[i] = 0.0f;
		}

		returnMatrix.elements[0 + 0 * 3] = 1.0f;
		returnMatrix.elements[1 + 1 * 3] = 1.0f;
		returnMatrix.elements[2 + 2 * 3] = 1.0f;

		return returnMatrix;
	}

	mat3 mat3::translation(const vec2& translation)
	{
		mat3 returnMatrix = identity();

		returnMatrix.elements[0 + 0 * 3] = translation.x;
		returnMatrix.elements[1 + 1 * 3] = translation.y;

		return returnMatrix;
	}

	mat3 mat3::rotation(float angle, const vec3& axis)
	{
		mat3 returnMatrix = identity();

		float r = toRadians(angle);
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

	mat3 mat3::scale(const vec3& scale)
	{
		mat3 returnMatrix = identity();

		returnMatrix.elements[0 + 0 * 3] = scale.x;
		returnMatrix.elements[1 + 1 * 3] = scale.y;
		returnMatrix.elements[1 + 1 * 3] = scale.z;

		return returnMatrix;
	}
}}