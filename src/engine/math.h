#pragma once
#define PI 3.1415926

namespace DxEngine
{
	template<typename T>
	struct vec2
	{
		T x = {}, y = {};
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
}