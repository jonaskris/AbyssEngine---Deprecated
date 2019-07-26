#pragma once
#include <math.h>
//#include "vec2f.h"

namespace abyssengine {
	namespace math {
		struct vec2d
		{
			union {
				double elements[2];
				struct {
					double x, y;
				};
			};

			vec2d() : x(0.0), y(0.0) {};
			vec2d(const double& scalar) : x(scalar), y(scalar) {};
			vec2d(const vec2d& vec) : x(vec.x), y(vec.y) {};
			vec2d(const double& x, const double& y) : x(x), y(y) {};

			vec2d& add(const vec2d& other)
			{
				this->x += other.x; this->y += other.y;
				return *this;
			}

			vec2d& subtract(const vec2d& other)
			{
				this->x -= other.x; this->y -= other.y;
				return *this;
			}

			vec2d& multiply(const vec2d& other)
			{
				this->x *= other.x; this->y *= other.y;
				return *this;
			}

			vec2d& divide(const vec2d& other)
			{
				this->x /= other.x; this->y /= other.y;
				return *this;
			}

			vec2d& add(const double& scalar)
			{
				this->x += scalar; this->y += scalar;
				return *this;
			}

			vec2d& subtract(const double& scalar)
			{
				this->x -= scalar; this->y -= scalar;
				return *this;
			}

			vec2d& multiply(const double& scalar)
			{
				this->x *= scalar; this->y *= scalar;
				return *this;
			}

			vec2d& divide(const double& scalar)
			{
				this->x /= scalar; this->y /= scalar;
				return *this;
			}


			// x ¤= y
			vec2d& operator+=(const vec2d& other) { return add(other); }
			vec2d& operator-=(const vec2d& other) { return subtract(other); }
			vec2d& operator*=(const vec2d& other) { return multiply(other); }
			vec2d& operator/=(const vec2d& other) { return divide(other); }

			vec2d& operator+=(const double& scalar) { return add(scalar); }
			vec2d& operator-=(const double& scalar) { return subtract(scalar); }
			vec2d& operator*=(const double& scalar) { return multiply(scalar); }
			vec2d& operator/=(const double& scalar) { return divide(scalar); }

			// x ¤ y
			vec2d operator+(const vec2d& other) const { return vec2d(*this).add(other); }
			vec2d operator-(const vec2d& other) const { return vec2d(*this).subtract(other); }
			vec2d operator*(const vec2d& other) const { return vec2d(*this).multiply(other); }
			vec2d operator/(const vec2d& other) const { return vec2d(*this).divide(other); }

			vec2d operator+(const double& scalar) const { return vec2d(*this).add(scalar); }
			vec2d operator-(const double& scalar) const { return vec2d(*this).subtract(scalar); }
			vec2d operator*(const double& scalar) const { return vec2d(*this).multiply(scalar); }
			vec2d operator/(const double& scalar) const { return vec2d(*this).divide(scalar); }

			double magnitude() const { return sqrt(x*x + y * y); }
			double dot(const vec2d& other) const { return this->x * other.x + this->y * other.y; };
			double cross(const vec2d& other) const { return this->x * other.y - this->y * other.x; }
			vec2d normalize() const { return *this / magnitude(); }
		};
	}
}