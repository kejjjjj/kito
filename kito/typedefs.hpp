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
	//constexpr explicit vec2(const vec2<int>& v) { x = (int)v.x, y = (int)v.y; }

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
	operator ImVec2() { return ImVec2(x, y); };
#endif

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


struct Pixel
{
	uint8_t r, g, b, a;

	constexpr Pixel() { r = 0, g = 0, b = 0, a = 255; }
	constexpr Pixel(const uint8_t val) { r = val, g = val, b = val, a = val; };
	constexpr Pixel(const uint8_t _r, const uint8_t _g, const uint8_t _b, const uint8_t _a) { r = _r, g = _g, b = _b, a = _a; }

	Pixel operator=(const Pixel& px) {
		return { px.r, px.g, px.b, px.a };
	}

#ifdef IMGUI_API
	operator ImColor() { return ImColor(r,g,b,a); };
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