 #pragma once
#include <math.h>

namespace abyssengine {
	namespace math {
		struct vec3d
		{
			union {
				double elements[3];
				struct {
					double x, y, z;
				};
			};

			vec3d() : x(0.0), y(0.0), z(0.0) {};
			vec3d(const double& scalar) : x(scalar), y(scalar), z(scalar) {};

			vec3d(const vec3d& vec) : x(vec.x), y(vec.y), z(vec.z) {};
			vec3d(const double& x, const double& y, const double& z) : x(x), y(y), z(z) {};

			vec3d& add(const vec3d& other)
			{
				this->x += other.x; this->y += other.y; this->z += other.z;
				return *this;
			}

			vec3d& subtract(const vec3d& other)
			{
				this->x -= other.x; this->y -= other.y; this->z -= other.z;
				return *this;
			}

			vec3d& multiply(const vec3d& other)
			{
				this->x *= other.x; this->y *= other.y; this->z *= other.z;
				return *this;
			}

			vec3d& divide(const vec3d& other)
			{
				this->x /= other.x; this->y /= other.y; this->z /= other.z;
				return *this;
			}

			vec3d& add(const double& scalar)
			{
				this->x += scalar; this->y += scalar; this->z += scalar;
				return *this;
			}

			vec3d& subtract(const double& scalar)
			{
				this->x -= scalar; this->y -= scalar; this->z -= scalar;
				return *this;
			}

			vec3d& multiply(const double& scalar)
			{
				this->x *= scalar; this->y *= scalar; this->z *= scalar;
				return *this;
			}

			vec3d& divide(const double& scalar)
			{
				this->x /= scalar; this->y /= scalar; this->z /= scalar;
				return *this;
			}

			// x ¤= y
			vec3d& operator+=(const vec3d& other) { return add(other); }
			vec3d& operator-=(const vec3d& other) { return subtract(other); }
			vec3d& operator*=(const vec3d& other) { return multiply(other); }
			vec3d& operator/=(const vec3d& other) { return divide(other); }

			vec3d& operator+=(const double& scalar) { return add(scalar); }
			vec3d& operator-=(const double& scalar) { return subtract(scalar); }
			vec3d& operator*=(const double& scalar) { return multiply(scalar); }
			vec3d& operator/=(const double& scalar) { return divide(scalar); }

			// x ¤ y
			vec3d operator+(const vec3d& other) const { return vec3d(*this).add(other); }
			vec3d operator-(const vec3d& other) const { return vec3d(*this).subtract(other); }
			vec3d operator*(const vec3d& other) const { return vec3d(*this).multiply(other); }
			vec3d operator/(const vec3d& other) const { return vec3d(*this).divide(other); }

			vec3d operator+(const double& scalar) const { return vec3d(*this).add(scalar); }
			vec3d operator-(const double& scalar) const { return vec3d(*this).subtract(scalar); }
			vec3d operator*(const double& scalar) const { return vec3d(*this).multiply(scalar); }
			vec3d operator/(const double& scalar) const { return vec3d(*this).divide(scalar); }

			double magnitude() const { return sqrt(x*x + y * y + z * z); }
			double dot(const vec3d& other) const { return this->x * other.x + this->y * other.y + this->z * other.z; };
			vec3d cross(const vec3d& other) const { return vec3d{ this->y * other.z - this->z * other.y, this->z * other.x - this->x * other.z, this->x * other.y - this->y * other.x }; }
			vec3d normalize() const { return *this / magnitude(); }
		};
	}
}