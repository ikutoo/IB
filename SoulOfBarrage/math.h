#pragma once

#define PI 3.1415926

namespace DxEngine
{
	template<typename T>
	struct vec2
	{
		vec2() {}
		vec2(T _x, T _y) : x(_x), y(_y) {}

		T x = {}, y = {};
	};

	using vec2d = vec2<double>;
	using vec2f = vec2<float>;
	using vec2i = vec2<int>;
}