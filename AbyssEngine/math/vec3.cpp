#include "vec3.h"
#include "vec2.h"
#include "vec4.h"
#include "mat4.h"

vec3::vec3(float scalar)
{
	this->x = scalar;
	this->y = scalar;
	this->z = scalar;
}

vec3::vec3(const vec3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

vec3::vec3(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

vec3::vec3(const vec2& other)
	: x(other.x), y(other.y), z(0.0f)
{
}

vec3::vec3(float x, float y)
	: x(x), y(y), z(0.0f)
{
}

vec3::vec3(const vec4& other)
	: x(other.x), y(other.y), z(other.z)
{
}

vec3 vec3::up()
{
	return vec3(0.0f, 1.0f, 0.0f);
}

vec3 vec3::down()
{
	return vec3(0.0f, -1.0f, 0.0f);
}

vec3 vec3::left()
{
	return vec3(-1.0f, 0.0f, 0.0f);
}

vec3 vec3::right()
{
	return vec3(1.0f, 0.0f, 0.0f);
}

vec3 vec3::zero()
{
	return vec3(0.0f, 0.0f, 0.0f);
}

vec3 vec3::xAxis()
{
	return vec3(1.0f, 0.0f, 0.0f);
}

vec3 vec3::yAxis()
{
	return vec3(0.0f, 1.0f, 0.0f);
}

vec3 vec3::zAxis()
{
	return vec3(0.0f, 0.0f, 1.0f);
}

vec3& vec3::add(const vec3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

vec3& vec3::subtract(const vec3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

vec3& vec3::multiply(const vec3& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;

	return *this;
}

vec3& vec3::divide(const vec3& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;

	return *this;
}

vec3& vec3::add(const vec2& other)
{
	x += other.x;
	y += other.y;

	return *this;
}

vec3& vec3::subtract(const vec2& other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}

vec3& vec3::multiply(const vec2& other)
{
	x *= other.x;
	y *= other.y;

	return *this;
}

vec3& vec3::divide(const vec2& other)
{
	x /= other.x;
	y /= other.y;

	return *this;
}

vec3& vec3::add(float other)
{
	x += other;
	y += other;
	z += other;

	return *this;
}

vec3& vec3::subtract(float other)
{
	x -= other;
	y -= other;
	z -= other;

	return *this;
}

vec3& vec3::multiply(float other)
{
	x *= other;
	y *= other;
	z *= other;

	return *this;
}

vec3& vec3::divide(float other)
{
	x /= other;
	y /= other;
	z /= other;

	return *this;
}

vec3 vec3::multiply(const mat4& transform) const
{
	return vec3(
		transform.elements[0 + 0 * 4] * x + transform.elements[1 + 0 * 4] * y + transform.elements[2 + 0 * 4] * z + transform.elements[3 + 0 * 4],
		transform.elements[0 + 1 * 4] * x + transform.elements[1 + 1 * 4] * y + transform.elements[2 + 1 * 4] * z + transform.elements[3 + 1 * 4],
		transform.elements[0 + 2 * 4] * x + transform.elements[1 + 2 * 4] * y + transform.elements[2 + 2 * 4] * z + transform.elements[1 + 2 * 4]
	);
}

vec3 operator+(const vec3& left, const vec3& right)
{
	vec3 returnVector(left);
	return returnVector.add(right);
}

vec3 operator-(const vec3& left, const vec3& right)
{
	vec3 returnVector(left);
	return returnVector.subtract(right);
}

vec3 operator*(const vec3& left, const vec3& right)
{
	vec3 returnVector(left);
	return returnVector.multiply(right);
}

vec3 operator/(const vec3& left, const vec3& right)
{
	vec3 returnVector(left);
	return returnVector.divide(right);
}

vec3 operator+(const vec3& left, const vec2& right)
{
	vec3 returnVector(left);
	return returnVector.add(right);
}

vec3 operator-(const vec3& left, const vec2& right)
{
	vec3 returnVector(left);
	return returnVector.subtract(right);
}

vec3 operator*(const vec3& left, const vec2& right)
{
	vec3 returnVector(left);
	return returnVector.multiply(right);
}

vec3 operator/(const vec3& left, const vec2& right)
{
	vec3 returnVector(left);
	return returnVector.divide(right);
}

vec3 operator+(const vec3& left, const float& right)
{
	vec3 returnVector(left);
	return returnVector.add(right);
}

vec3 operator-(const vec3& left, const float& right)
{
	vec3 returnVector(left);
	return returnVector.subtract(right);
}

vec3 operator*(const vec3& left, const float& right)
{
	vec3 returnVector(left);
	return returnVector.multiply(right);
}

vec3 operator/(const vec3& left, const float& right)
{
	vec3 returnVector(left);
	return returnVector.divide(right);
}

vec3& vec3::operator+=(const vec3& other)
{
	return add(other);
}

vec3& vec3::operator-=(const vec3& other)
{
	return subtract(other);
}

vec3& vec3::operator*=(const vec3& other)
{
	return multiply(other);
}

vec3& vec3::operator/=(const vec3& other)
{
	return divide(other);
}

vec3& vec3::operator+=(float& other)
{
	return add(other);
}

vec3& vec3::operator-=(float& other)
{
	return subtract(other);
}

vec3& vec3::operator*=(float& other)
{
	return multiply(other);
}

vec3& vec3::operator/=(float& other)
{
	return divide(other);
}

bool vec3::operator<(const vec3& other) const
{
	return x < other.x && y < other.y && z < other.z;
}

bool vec3::operator<=(const vec3& other) const
{
	return x <= other.x && y <= other.y && z <= other.z;
}

bool vec3::operator>(const vec3& other) const
{
	return x > other.x && y > other.y && z > other.z;
}

bool vec3::operator>=(const vec3& other) const
{
	return x >= other.x && y >= other.y && z >= other.z;
}

bool vec3::operator==(const vec3& other) const
{
	return x == other.x && y == other.y && z == other.z;
}

bool vec3::operator!=(const vec3& other) const
{
	return !(*this == other);
}

vec3 operator-(const vec3& vector)
{
	return vec3(-vector.x, -vector.y, -vector.z);
}

vec3 vec3::cross(const vec3& other) const
{
	return vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

float vec3::dot(const vec3& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

float& vec3::magnitude() const
{
	return *new float(sqrt(x * x + y * y + z * z));
}

vec3& vec3::normalize() const
{
	float length = magnitude();
	return *new vec3(x / length, y / length, z / length);
}

float& vec3::distance(const vec3& other) const
{
	float a = x - other.x;
	float b = y - other.y;
	float c = z - other.z;
	return *new float(sqrt(a * a + b * b + c * c));
}

std::ostream& operator<<(std::ostream& stream, const vec3& vector)
{
	stream << "[" << vector.x << ", " << vector.y << ", " << vector.z << "]";
	return stream;
}