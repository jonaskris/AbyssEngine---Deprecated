#include "mat4.h"

mat4::mat4()
{
	for (int i = 0; i < 4 * 4; i++) {
		elements[i] = 0.0f;
	}
}

mat4 mat4::identity() 
{
	mat4 returnMatrix;
	for (int i = 0; i < 4 * 4; i++) {
		returnMatrix.elements[i] = 0.0f;
	}

	returnMatrix.elements[0 + 0 * 4] = 1.0f;
	returnMatrix.elements[1 + 1 * 4] = 1.0f;
	returnMatrix.elements[2 + 2 * 4] = 1.0f;
	returnMatrix.elements[3 + 3 * 4] = 1.0f;

	return returnMatrix;
}

mat4& mat4::multiply(const mat4& other) {
	for (int y = 0; y < 4; y++) 
	{
		for (int x = 0; x < 4; x++) 
		{
			float sum = 0.0f;
			for (int e = 0; e < 4; e++) 
			{
				sum += elements[x + e * 4] * other.elements[e + y * 4];
			}
			elements[x + y * 4] = sum;
		}
	}
	return *this;
}

mat4 operator*(mat4 left, const mat4& right) 
{
	return left.multiply(right);
}

mat4& mat4::operator*=(const mat4& other) 
{
	return multiply(other);
}

mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
{
	mat4 returnMatrix = identity();

	returnMatrix.elements[0 + 0 * 4] = 2.0f / (right - left);
	returnMatrix.elements[1 + 1 * 4] = 2.0f / (top - bottom);
	returnMatrix.elements[2 + 2 * 4] = 2.0f / (near - far);
				
	returnMatrix.elements[0 + 3 * 4] = (left + right) / (left - right);
	returnMatrix.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
	returnMatrix.elements[2 + 3 * 4] = (far + near) / (far - near);

	return returnMatrix;
}

mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
{
	mat4 returnMatrix = identity();
	float q = 1.0f / tan(toRadians(0.5f * fov));
	float a = q / aspectRatio;

	float b = (near + far) / (near - far);
	float c = (2.0f * near * far) / (near - far);

	returnMatrix.elements[0 + 0 * 4] = a;
	returnMatrix.elements[1 + 1 * 4] = q;
	returnMatrix.elements[2 + 2 * 4] = b;
	returnMatrix.elements[2 + 3 * 4] = -1.0f;
	returnMatrix.elements[3 + 2 * 4] = c;

	return returnMatrix;
}

mat4 mat4::translation(const vec3& translation)
{
	mat4 returnMatrix = identity();

	returnMatrix.elements[0 + 3 * 4] = translation.x;
	returnMatrix.elements[1 + 3 * 4] = translation.y;
	returnMatrix.elements[2 + 3 * 4] = translation.z;

	return returnMatrix;
}

mat4 mat4::scale(const vec3& scale)
{
	mat4 returnMatrix = identity();

	returnMatrix.elements[0 + 0 * 4] = scale.x;
	returnMatrix.elements[1 + 1 * 4] = scale.y;
	returnMatrix.elements[2 + 2 * 4] = scale.z;

	return returnMatrix;
}

mat4 mat4::rotation(float angle, const vec3& axis)
{
	mat4 returnMatrix = identity();

	float r = toRadians(angle);
	float c = cos(r);
	float s = sin(r);
	float omc = 1.0f - c;

	float x = axis.x;
	float y = axis.y;
	float z = axis.z;

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