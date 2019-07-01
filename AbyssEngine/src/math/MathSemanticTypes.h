#pragma once

namespace abyssengine {
	template <typename VecType>
	struct QuadVec
	{
		VecType vec0, vec1, vec2, vec3;

		QuadVec(const VecType& vec0, const VecType& vec1, const VecType& vec2, const VecType& vec3) : vec0(vec0), vec1(vec1), vec2(vec2), vec3(vec3) {};
	};
}