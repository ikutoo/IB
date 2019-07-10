#pragma once
#include <cmath>

#define PI 3.1415926

namespace DxEngine
{
	template<typename T>
	struct vec2
	{
		T x = {}, y = {};

		void normalize()
		{
			T t = sqrt(x*x + y * y);
			if (t == 0) return;
			x /= t; y /= t;
		}

		vec2 operator*(T t) { return vec2{ x*t, y*t }; }
		vec2 operator/(T t) { if (t == 0) return *this; else return { x / t, y / t }; }
		void operator+=(vec2 r) { x += r.x; y += r.y; }
	};

	template<typename T>
	struct vec3
	{
		T x = {}, y = {}, z = {};

		bool operator==(const vec3& r) { return x == r.x && y == r.y && z == r.z; }
		bool operator!=(const vec3& r) { return !(*this == r); }
	};

	template<typename T>
	struct vec4
	{
		T x = {}, y = {}, z = {}, w = {};
	};

	template<typename T>
	struct rect
	{
		T x = {}, y = {}, w = {}, h = {};
	};

	using vec2i = vec2<int>;
	using vec2f = vec2<float>;
	using vec3i = vec3<int>;
	using recti = rect<int>;
	using rectf = rect<float>;

	template<typename T>
	inline bool intersects(const vec2<T>& vPoint, const rect<T>& vRect)
	{
		return vPoint.x >= vRect.x && vPoint.y >= vRect.y && vPoint.x <= vRect.x + vRect.w && vPoint.y <= vRect.y + vRect.h;
	}

	inline float randf()
	{
		return (float)rand() / RAND_MAX;
	}

	template<typename T>
	inline T clip(T value, T low, T high)
	{
		return max(min(value, high), low);
	}

	template<typename T>
	inline T distance(vec2<T> v1, vec2<T> v2)
	{
		return sqrt((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y));
	}
}