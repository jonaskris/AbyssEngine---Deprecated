#pragma once
#include <math.h>

namespace abyssengine {
	namespace math {
		struct vec4d
		{
			union {
				double elements[4];
				struct {
					double x, y, z, w;
				};
			};

			vec4d() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {};
			vec4d(const double& scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {};

			vec4d(const vec4d& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {};
			vec4d(const vec3d& vec, const double& w) : x(vec.x), y(vec.y), z(vec.z), w(w) {};
			vec4d(const vec2d& vec, const double& z, const double& w) : x(vec.x), y(vec.y), z(z), w(w) {};
			vec4d(const double& x, const double& y, const double& z, const double& w) : x(x), y(y), z(z), w(w) {};

			vec4d& add(const vec4d& other)
			{
				this->x += other.x; this->y += other.y; this->z += other.z; this->w += other.w;
				return *this;
			}

			vec4d& subtract(const vec4d& other)
			{
				this->x -= other.x; this->y -= other.y; this->z -= other.z; this->w -= other.w;
				return *this;
			}

			vec4d& multiply(const vec4d& other)
			{
				this->x *= other.x; this->y *= other.y; this->z *= other.z; this->w *= other.w;
				return *this;
			}

			vec4d& divide(const vec4d& other)
			{
				this->x /= other.x; this->y /= other.y; this->z /= other.z; this->w /= other.w;
				return *this;
			}

			vec4d& add(const double& scalar)
			{
				this->x += scalar; this->y += scalar; this->z += scalar; this->w += scalar;
				return *this;
			}

			vec4d& subtract(const double& scalar)
			{
				this->x -= scalar; this->y -= scalar; this->z -= scalar; this->w -= scalar;
				return *this;
			}

			vec4d& multiply(const double& scalar)
			{
				this->x *= scalar; this->y *= scalar; this->z *= scalar; this->w *= scalar;
				return *this;
			}

			vec4d& divide(const double& scalar)
			{
				this->x /= scalar; this->y /= scalar; this->z /= scalar; this->w /= scalar;
				return *this;
			}


			// x ¤= y
			vec4d& operator+=(const vec4d& other) { return add(other); }
			vec4d& operator-=(const vec4d& other) { return subtract(other); }
			vec4d& operator*=(const vec4d& other) { return multiply(other); }
			vec4d& operator/=(const vec4d& other) { return divide(other); }

			vec4d& operator+=(const double& scalar) { return add(scalar); }
			vec4d& operator-=(const double& scalar) { return subtract(scalar); }
			vec4d& operator*=(const double& scalar) { return multiply(scalar); }
			vec4d& operator/=(const double& scalar) { return divide(scalar); }

			// x ¤ y
			vec4d operator+(const vec4d& other) const { return vec4d(*this).add(other); }
			vec4d operator-(const vec4d& other) const { return vec4d(*this).subtract(other); }
			vec4d operator*(const vec4d& other) const { return vec4d(*this).multiply(other); }
			vec4d operator/(const vec4d& other) const { return vec4d(*this).divide(other); }

			vec4d operator+(const double& scalar) const { return vec4d(*this).add(scalar); }
			vec4d operator-(const double& scalar) const { return vec4d(*this).subtract(scalar); }
			vec4d operator*(const double& scalar) const { return vec4d(*this).multiply(scalar); }
			vec4d operator/(const double& scalar) const { return vec4d(*this).divide(scalar); }

			double magnitude() const { return sqrt(x*x + y * y + z * z + w * w); }
			double dot(const vec4d& other) const { return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w; };
			vec4d normalize() const { return *this / magnitude(); }
		};
	}
}