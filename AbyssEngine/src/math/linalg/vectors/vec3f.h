#pragma once
#include <math.h>

namespace abyssengine {
	namespace math {
		struct vec3f
		{
			union {
				float elements[3];
				struct {
					float x, y, z;
				};
			};

			vec3f() : x(0.0f), y(0.0f), z(0.0f) {};
			vec3f(const float& scalar) : x(scalar), y(scalar), z(scalar) {};

			vec3f(const vec3f& vec) : x(vec.x), y(vec.y), z(vec.z) {};
			vec3f(const float& x, const float& y, const float& z) : x(x), y(y), z(z) {};

			vec3f& add(const vec3f& other)
			{
				this->x += other.x; this->y += other.y; this->z += other.z;
				return *this;
			}

			vec3f& subtract(const vec3f& other)
			{
				this->x -= other.x; this->y -= other.y; this->z -= other.z;
				return *this;
			}

			vec3f& multiply(const vec3f& other)
			{
				this->x *= other.x; this->y *= other.y; this->z *= other.z;
				return *this;
			}

			vec3f& divide(const vec3f& other)
			{
				this->x /= other.x; this->y /= other.y; this->z /= other.z;
				return *this;
			}

			vec3f& add(const float& scalar)
			{
				this->x += scalar; this->y += scalar; this->z += scalar;
				return *this;
			}

			vec3f& subtract(const float& scalar)
			{
				this->x -= scalar; this->y -= scalar; this->z -= scalar;
				return *this;
			}

			vec3f& multiply(const float& scalar)
			{
				this->x *= scalar; this->y *= scalar; this->z *= scalar;
				return *this;
			}

			vec3f& divide(const float& scalar)
			{
				this->x /= scalar; this->y /= scalar; this->z /= scalar;
				return *this;
			}


			// x ¤= y
			vec3f& operator+=(const vec3f& other) { return add(other); }
			vec3f& operator-=(const vec3f& other) { return subtract(other); }
			vec3f& operator*=(const vec3f& other) { return multiply(other); }
			vec3f& operator/=(const vec3f& other) { return divide(other); }

			vec3f& operator+=(const float& scalar) { return add(scalar); }
			vec3f& operator-=(const float& scalar) { return subtract(scalar); }
			vec3f& operator*=(const float& scalar) { return multiply(scalar); }
			vec3f& operator/=(const float& scalar) { return divide(scalar); }

			// x ¤ y
			vec3f operator+(const vec3f& other) const { return vec3f(*this).add(other); }
			vec3f operator-(const vec3f& other) const { return vec3f(*this).subtract(other); }
			vec3f operator*(const vec3f& other) const { return vec3f(*this).multiply(other); }
			vec3f operator/(const vec3f& other) const { return vec3f(*this).divide(other); }

			vec3f operator+(const float& scalar) const { return vec3f(*this).add(scalar); }
			vec3f operator-(const float& scalar) const { return vec3f(*this).subtract(scalar); }
			vec3f operator*(const float& scalar) const { return vec3f(*this).multiply(scalar); }
			vec3f operator/(const float& scalar) const { return vec3f(*this).divide(scalar); }

			float magnitude() const { return sqrt(x*x + y*y + z*z); }
			float dot(const vec3f& other) const { return this->x * other.x + this->y * other.y + this->z * other.z; };
			vec3f cross(const vec3f& other) const { return vec3f{ this->y * other.z - this->z * other.y, this->z * other.x - this->x * other.z, this->x * other.y - this->y * other.x }; }
			vec3f normalize() const { return *this / magnitude(); }
		};
	}
}