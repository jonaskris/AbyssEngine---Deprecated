#pragma once
#include "../Linalg.h"
#include "Time.h"

namespace abyssengine {
	namespace math {
		struct Attribute {};

		struct Position : public Attribute
		{
			union {
				vec3f vec;
				struct {
					float x, y, z;
				};
			};

			Position(const vec3f& vec) : vec(vec) {};
			Position(const Position& other) : vec(other.vec) {};

			Position operator+(const Position& other) const { return Position{ vec + other.vec }; }
			Position& operator+=(const Position& other) { vec += other.vec; return *this; }

			Position operator-(const Position& other) const { return Position{ vec - other.vec }; }
			Position& operator-=(const Position& other) { vec -= other.vec; return *this; }
		};

		struct Velocity : public Attribute
		{
			union {
				vec3f vec;
				struct {
					float x, y, z;
				};
			};

			Velocity(const vec3f& vec) : vec(vec) {};
			Velocity(const Velocity& other) : vec(other.vec) {};

			Velocity operator+(const Velocity& other) const { return Velocity{ vec + other.vec }; }
			Velocity& operator+=(const Velocity& other) { vec += other.vec; return *this; }

			Velocity operator-(const Velocity& other) const { return Velocity{ vec - other.vec }; }
			Velocity& operator-=(const Velocity& other) { vec -= other.vec; return *this; }

			Position operator*(const Time& time) const { return Position( vec * time.value ); }
		};

		struct Acceleration : public Attribute
		{
			union {
				vec3f vec;
				struct {
					float x, y, z;
				};
			};

			Acceleration(const vec3f& vec) : vec(vec) {};
			Acceleration(const Acceleration& other) : vec(other.vec) {};

			Acceleration operator+(const Acceleration& other) const { return Acceleration{ vec + other.vec }; }
			Acceleration& operator+=(const Acceleration& other) { vec += other.vec; return *this; }

			Acceleration operator-(const Acceleration& other) const { return Acceleration{ vec - other.vec }; }
			Acceleration& operator-=(const Acceleration& other) { vec -= other.vec; return *this; }

			Velocity operator*(const Time& time) const { return Velocity{ vec * time.value }; }
		};

		/*
			Normalized vector.
		*/
		struct Orientation : public Attribute
		{
			union {
				vec3f vec;
				struct {
					float x, y, z;
				};
			};

			Orientation(const vec3f& vec) : vec(vec.normalize()) {};
			Orientation(const Orientation& other) : vec(other.vec) {};

			Orientation operator+(const Orientation& other) const { return Orientation{ vec + other.vec }; }
			Orientation& operator+=(const Orientation& other) { vec += other.vec; return *this; }
		};

		struct Scale : public Attribute
		{
			union {
				vec3f vec;
				struct {
					float x, y, z;
				};
			};

			Scale(const vec3f& scale) : vec(vec) {};
			Scale(const Scale& other) : vec(other.vec) {};

			Scale operator+(const Scale& other) const
			{
				return Scale{ vec + other.vec };
			}

			Scale& operator+=(const Scale& other)
			{
				vec += other.vec;
				return *this;
			}
		};

		struct Color : public Attribute
		{
			union
			{
				vec4f vec;
				struct {
					float x, y, z;
				};
			};

			Color(const vec4f& vec) : vec(vec) {};
			Color(const Color& other) : vec(other.vec) {};

			Color operator+(const Color& other) const
			{
				return Color{ vec + other.vec };
			}

			Color& operator+=(const Color& other)
			{
				vec += other.vec;
				return *this;
			}
		};
	}
}