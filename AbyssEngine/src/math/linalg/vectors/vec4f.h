#pragma once
#include <math.h>
//#include "vec4d.h"

namespace abyssengine {
	namespace math {
		struct vec4f
		{
			union {
				float elements[4];
				struct {
					float x, y, z, w;
				};
			};

			vec4f() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {};
			vec4f(const float& scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {};
			vec4f(const vec4f& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {};
			vec4f(const float& x, const float& y, const float& z, const float& w) : x(x), y(y), z(z), w(w) {};

			vec4f& add(const vec4f& other)
			{
				this->x += other.x; this->y += other.y; this->z += other.z; this->w += other.w;
				return *this;
			}

			vec4f& subtract(const vec4f& other)
			{
				this->x -= other.x; this->y -= other.y; this->z -= other.z; this->w -= other.w;
				return *this;
			}

			vec4f& multiply(const vec4f& other)
			{
				this->x *= other.x; this->y *= other.y; this->z *= other.z; this->w *= other.w;
				return *this;
			}

			vec4f& divide(const vec4f& other)
			{
				this->x /= other.x; this->y /= other.y; this->z /= other.z; this->w /= other.w;
				return *this;
			}

			vec4f& add(const float& scalar)
			{
				this->x += scalar; this->y += scalar; this->z += scalar; this->w += scalar;
				return *this;
			}

			vec4f& subtract(const float& scalar)
			{
				this->x -= scalar; this->y -= scalar; this->z -= scalar; this->w -= scalar;
				return *this;
			}

			vec4f& multiply(const float& scalar)
			{
				this->x *= scalar; this->y *= scalar; this->z *= scalar; this->w *= scalar;
				return *this;
			}

			vec4f& divide(const float& scalar)
			{
				this->x /= scalar; this->y /= scalar; this->z /= scalar; this->w /= scalar;
				return *this;
			}


			// x ¤= y
			vec4f& operator+=(const vec4f& other) { return add(other); }
			vec4f& operator-=(const vec4f& other) { return subtract(other); }
			vec4f& operator*=(const vec4f& other) { return multiply(other); }
			vec4f& operator/=(const vec4f& other) { return divide(other); }

			vec4f& operator+=(const float& scalar) { return add(scalar); }
			vec4f& operator-=(const float& scalar) { return subtract(scalar); }
			vec4f& operator*=(const float& scalar) { return multiply(scalar); }
			vec4f& operator/=(const float& scalar) { return divide(scalar); }

			// x ¤ y
			vec4f operator+(const vec4f& other) const { return vec4f(*this).add(other); }
			vec4f operator-(const vec4f& other) const { return vec4f(*this).subtract(other); }
			vec4f operator*(const vec4f& other) const { return vec4f(*this).multiply(other); }
			vec4f operator/(const vec4f& other) const { return vec4f(*this).divide(other); }

			vec4f operator+(const float& scalar) const { return vec4f(*this).add(scalar); }
			vec4f operator-(const float& scalar) const { return vec4f(*this).subtract(scalar); }
			vec4f operator*(const float& scalar) const { return vec4f(*this).multiply(scalar); }
			vec4f operator/(const float& scalar) const { return vec4f(*this).divide(scalar); }

			float magnitude() const { return sqrt(x*x + y * y + z * z + w * w); }
			float dot(const vec4f& other) const { return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w; };
			vec4f normalize() const { return *this / magnitude(); }
		};
	}
}