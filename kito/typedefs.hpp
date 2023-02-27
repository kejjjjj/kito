#pragma once

#ifndef tpdef
#define tpdef

#include "pch.h"



template <class T>
struct vec2
{
	T x, y;

	constexpr vec2() { x = 0; y = 0; }
	constexpr vec2(const T& v) { x = v; y = v; }
	constexpr vec2(const T& a, const T& b) { x = a; y = b; }

	constexpr vec2(const vec3_t a) { x = a[0]; y = a[1];  }

#ifdef IMGUI_API
	constexpr vec2(const ImVec2 b) { x = b.x; y = b.y; };
#endif

	vec2 operator+(const vec2& v) const { return { x + v.x, y + v.y }; }
	vec2 operator-(const vec2& v) const { return { x - v.x, y - v.y }; }
	vec2 operator*(const vec2& v) const { return { x * v.x, y * v.y }; }
	vec2 operator/(const vec2& v) const { return { x / v.x, y / v.y }; }
	void operator=(const vec2& v) { x = v.x; y = v.y; }

	vec2 operator+(const T& v) const { return { x + v, y + v }; }
	vec2 operator-(const T& v) const { return { x - v, y - v }; }
	vec2 operator*(const T& v) const { return { x * v, y * v }; }
	vec2 operator/(const T& v) const { return { x / v, y / v }; }

	vec2 operator+=(const vec2& v) { return { x += v.x, y += v.y }; }
	vec2 operator-=(const vec2& v) { return { x -= v.x, y -= v.y }; }
	vec2 operator*=(const vec2& v) { return { x *= v.x, y *= v.y }; }
	vec2 operator/=(const vec2& v) { return { x /= v.x, y /= v.y }; }
	bool operator==(const vec2& v) const { return  x == v.x && y == v.y; }
	bool operator!=(const vec2& v) const { return  x != v.x || y != v.y; }

	vec2 operator+=(const T& v) { return { x += v, y += v }; }
	vec2 operator-=(const T& v) { return { x -= v, y -= v }; }
	vec2 operator*=(const T& v) { return { x *= v, y *= v }; }
	vec2 operator/=(const T& v) { return { x /= v, y /= v }; }

#ifdef IMGUI_API
	operator ImVec2() { return ImVec2((float)x, (float)y); };
#endif

	operator vec2<int>() { return { (int)x, (int)y }; }
	operator vec2<float>() { return { (float)x, (float)y }; }


	float mag() const {
		return sqrtf(x * x + y * y);
	}
	float dot(const vec2& vec) const
	{
		return x * vec.x + y * vec.y;
	}
	float normalize() {
		const float length = this->mag();
		float ilength;

		if (length) {
			ilength = 1 / length;
			this->x *= ilength;
			this->y *= ilength;
		}

		return length;
	}
	float dist(const vec2& vec) const
	{
		const vec2 sub = *this - vec;
		return sub.mag();
	}
	vec2 inverse() const
	{
		return { -x, -y };
	}
	float MagSq() const { //magnitude squared
		return (x * x + y * y);
	}
	void clamp(const T min, const T max) {
		if (x < min)		x = min;
		else if (x > max)	x = max;

		if (y < min)		y = min;
		else if (y > max)	y = max;
	}
	//expects radians
	vec2 fromAngle(float angle) {
		return { cos(angle), sin(angle) };
	}

};

using ivec2 = vec2<int>;
using fvec2 = vec2<float>;

template <class T>
struct vec3
{

	T x, y, z;

	constexpr vec3() { x = 0; y = 0, z = 0; }
	constexpr vec3(const T& v) { x = v; y = v, z = v; }
	constexpr vec3(const T& a, const T& b, const T& c) { x = a; y = b, z = c; }
	constexpr vec3(const vec3_t a) { x = a[0]; y = a[1], z = a[2]; }

	//constexpr explicit vec3(const vec3<int>& v) { x = (int)v.x, y = (int)v.y; }

	vec3 operator+(const vec3& v) const { return { x + v.x, y + v.y, z + v.z }; }
	vec3 operator-(const vec3& v) const { return { x - v.x, y - v.y, z - v.z }; }
	vec3 operator*(const vec3& v) const { return { x * v.x, y * v.y, z * v.z }; }
	vec3 operator/(const vec3& v) const { return { x / v.x, y / v.y, z / v.z }; }
	void operator=(const vec3& v) { x = v.x; y = v.y, z = v.z; }
	void operator=(const vec3_t v) { x = v[0]; y = v[1], z = v[2]; }
	std::basic_ostream<char, std::char_traits<char>> operator<< (const vec3& v) {};

	vec3 operator+(const T& v) const { return { x + v, y + v, z + v }; }
	vec3 operator-(const T& v) const { return { x - v, y - v, z - v }; }
	vec3 operator*(const T& v) const { return { x * v, y * v, z * v }; }
	vec3 operator/(const T& v) const { return { x / v, y / v, z / v }; }

	vec3 operator+=(const vec3& v) { return { x += v.x, y += v.y, z += v.z }; }
	vec3 operator-=(const vec3& v) { return { x -= v.x, y -= v.y, z -= v.z }; }
	vec3 operator*=(const vec3& v) { return { x *= v.x, y *= v.y, z *= v.z }; }
	vec3 operator/=(const vec3& v) { return { x /= v.x, y /= v.y, z /= v.z }; }
	bool operator==(const vec3& v) const { return  x == v.x && y == v.y && z == v.z; }
	bool operator!=(const vec3& v) const { return  x != v.x || y != v.y || z != v.z; }

	vec3 operator+=(const T& v) { return { x += v, y += v, z += v.z }; }
	vec3 operator-=(const T& v) { return { x -= v, y -= v, z -= v.z }; }
	vec3 operator*=(const T& v) { return { x *= v, y *= v, z *= v.z }; }
	vec3 operator/=(const T& v) { return { x /= v, y /= v, z /= v.z }; }

#ifdef IMGUI_API

#endif
	operator vec3<int>() { return { (int)x, (int)y, (int)z }; }
	operator vec3<float>() { return { (float)x, (float)y, (float)z}; }

	float mag() const {
		return sqrtf(x * x + y * y + z * z);
	}
	float dot(const vec3& vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}
	float normalize() {
		const float length = this->mag();
		float ilength;

		if (length) {
			ilength = 1 / length;
			this->x *= ilength;
			this->y *= ilength;
			this->z *= ilength;
		}

		return length;
	}
	float dist(const vec3& vec) const
	{
		const vec3 sub = *this - vec;
		return sub.mag();
	}
	vec3 inverse() const
	{
		return { -x, -y, -z };
	}
	float MagSq() const { //magnitude squared
		return (x * x + y * y + z * z);
	}
	void clamp(const T min, const T max) {
		if (x < min)		x = min;
		else if (x > max)	x = max;

		if (y < min)		y = min;
		else if (y > max)	y = max;

		if (z < min)		z = min;
		else if (z > max)	z = max;
	}
	vec3 toangles() const
	{
		float forward;
		float yaw, pitch;

		if (y == 0 && x == 0) {
			yaw = 0;
			if (z > 0) {
				pitch = 90;
			}
			else {
				pitch = 270;
			}
		}
		else {
			if (x) {
				yaw = (atan2(y, x) * 180 / M_PI);
			}
			else if (y > 0) {
				yaw = 90;
			}
			else {
				yaw = 270;
			}
			if (yaw < 0) {
				yaw += 360;
			}

			forward = sqrt(x * x + y * y);
			pitch = (atan2(z, forward) * 180 / M_PI);
			if (pitch < 0) {
				pitch += 360;
			}
		}

		return vec3(-pitch, yaw, 0);
	}

};

using ivec3 = vec3<int>;
using fvec3 = vec3<float>;

struct Pixel
{
	uint8_t r, g, b, a;

	constexpr Pixel() { r = 0, g = 0, b = 0, a = 255; }
	constexpr Pixel(const uint8_t val) { r = val, g = val, b = val, a = val; };
	constexpr Pixel(const uint8_t _r, const uint8_t _g, const uint8_t _b, const uint8_t _a) { r = _r, g = _g, b = _b, a = _a; }
	constexpr Pixel(const Pixel& p) { r = p.r, g = p.g, b = p.b, a = p.a; }

	Pixel operator=(const Pixel& px) {
		return { px.r, px.g, px.b, px.a };
	}

#ifdef IMGUI_API
	operator ImColor() { return ImColor(r,g,b,a); };
	operator ImU32() { return IM_COL32(r, g, b, a); };

#endif


};

namespace COL
{
	constexpr Pixel BLACK = Pixel(0, 0, 0, 255);
	constexpr Pixel WHITE = Pixel(255, 255, 255, 255);
	constexpr Pixel RED = Pixel(255, 0, 0, 255);
	constexpr Pixel GREEN = Pixel(0, 255, 0, 255);
	constexpr Pixel BLUE = Pixel(0, 0, 255, 255);
	constexpr Pixel YELLOW = Pixel(255, 255, 0, 255);
	constexpr Pixel PURPLE = Pixel(255, 0, 255, 255);
	constexpr Pixel LIGHTBLUE = Pixel(0, 255, 255, 255);
	constexpr Pixel GREY = Pixel(100, 100, 100, 255);

}

#endif