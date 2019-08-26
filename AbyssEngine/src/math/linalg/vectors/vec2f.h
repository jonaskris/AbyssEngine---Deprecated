#pragma once
#include <math.h>

namespace abyssengine {
	namespace math {
		struct vec2f
		{
			union {
				float elements[2];
				struct {
					float x, y;
				};
			};

			vec2f() : x(0.0f), y(0.0f) {};
			vec2f(const float& scalar) : x(scalar), y(scalar) {};
			vec2f(const vec2f& vec) : x(vec.x), y(vec.y) {};
			vec2f(const float& x, const float& y) : x(x), y(y) {};

			vec2f& add(const vec2f& other)
			{
				this->x += other.x; this->y += other.y;
				return *this;
			}

			vec2f& subtract(const vec2f& other)
			{
				this->x -= other.x; this->y -= other.y;
				return *this;
			}

			vec2f& multiply(const vec2f& other)
			{
				this->x *= other.x; this->y *= other.y;
				return *this;
			}

			vec2f& divide(const vec2f& other)
			{
				this->x /= other.x; this->y /= other.y;
				return *this;
			}

			vec2f& add(const float& scalar)
			{
				this->x += scalar; this->y += scalar;
				return *this;
			}

			vec2f& subtract(const float& scalar)
			{
				this->x -= scalar; this->y -= scalar;
				return *this;
			}

			vec2f& multiply(const float& scalar)
			{
				this->x *= scalar; this->y *= scalar;
				return *this;
			}

			vec2f& divide(const float& scalar)
			{
				this->x /= scalar; this->y /= scalar;
				return *this;
			}

			// x ¤= y
			vec2f& operator+=(const vec2f& other) { return add(other); }
			vec2f& operator-=(const vec2f& other) { return subtract(other); }
			vec2f& operator*=(const vec2f& other) { return multiply(other); }
			vec2f& operator/=(const vec2f& other) { return divide(other); }

			vec2f& operator+=(const float& scalar) { return add(scalar); }
			vec2f& operator-=(const float& scalar) { return subtract(scalar); }
			vec2f& operator*=(const float& scalar) { return multiply(scalar); }
			vec2f& operator/=(const float& scalar) { return divide(scalar); }

			// x ¤ y
			vec2f operator+(const vec2f& other) const { return vec2f(*this).add(other); }
			vec2f operator-(const vec2f& other) const { return vec2f(*this).subtract(other); }
			vec2f operator*(const vec2f& other) const { return vec2f(*this).multiply(other); }
			vec2f operator/(const vec2f& other) const { return vec2f(*this).divide(other); }

			vec2f operator+(const float& scalar) const { return vec2f(*this).add(scalar); }
			vec2f operator-(const float& scalar) const { return vec2f(*this).subtract(scalar); }
			vec2f operator*(const float& scalar) const { return vec2f(*this).multiply(scalar); }
			vec2f operator/(const float& scalar) const { return vec2f(*this).divide(scalar); }

			float magnitude() const { return sqrt(x*x + y*y); }
			float dot(const vec2f& other) const { return this->x * other.x + this->y * other.y; };
			float cross(const vec2f& other) const { return this->x * other.y - this->y * other.x; }
			vec2f normalize() const { return *this / magnitude(); }
		};
	}
}