#include "vec4.h"
#include "mat4.h"
#include "vec3.h"
#include "mat4.h"

namespace abyssengine { namespace math {
	vec4::vec4(float scalar)
		: x(scalar), y(scalar), z(scalar), w(scalar)
	{
	}

	vec4::vec4(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{
	}

	vec4::vec4(const vec3& xyz, float w)
		: x(xyz.x), y(xyz.y), z(xyz.z), w(w)
	{
	}

	vec4& vec4::add(const vec4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	vec4& vec4::subtract(const vec4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	vec4& vec4::multiply(const vec4& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;

		return *this;
	}

	vec4& vec4::divide(const vec4& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;

		return *this;
	}

	vec4& vec4::multiply(const mat4& transform) const
	{
		return *new vec4(
			transform.elements[0 + 0 * 4] * x + transform.elements[1 + 0 * 4] * y + transform.elements[2 + 0 * 4] * z + transform.elements[3 + 0 * 4] * w,
			transform.elements[0 + 1 * 4] * x + transform.elements[1 + 1 * 4] * y + transform.elements[2 + 1 * 4] * z + transform.elements[3 + 1 * 4] * w,
			transform.elements[0 + 2 * 4] * x + transform.elements[1 + 2 * 4] * y + transform.elements[2 + 2 * 4] * z + transform.elements[3 + 2 * 4] * w,
			transform.elements[0 + 3 * 4] * x + transform.elements[1 + 3 * 4] * y + transform.elements[2 + 3 * 4] * z + transform.elements[3 + 3 * 4] * w
		);
	}

	vec4 operator+(vec4 left, const vec4& right)
	{
		return left.add(right);
	}

	vec4 operator-(vec4 left, const vec4& right)
	{
		return left.subtract(right);
	}

	vec4 operator*(vec4 left, const vec4& right)
	{
		return left.multiply(right);
	}

	vec4 operator/(vec4 left, const vec4& right)
	{
		return left.divide(right);
	}

	vec4& vec4::operator+=(const vec4& other)
	{
		return add(other);
	}

	vec4& vec4::operator-=(const vec4& other)
	{
		return subtract(other);
	}

	vec4& vec4::operator*=(const vec4& other)
	{
		return multiply(other);
	}

	vec4& vec4::operator/=(const vec4& other)
	{
		return divide(other);
	}

	bool vec4::operator==(const vec4& other)
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	bool vec4::operator!=(const vec4& other)
	{
		return !(*this == other);
	}

	float vec4::dot(const vec4& other)
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}

	std::ostream& operator<<(std::ostream& stream, const vec4& vector)
	{
		stream << "[" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << "]";
		return stream;
	}
}}