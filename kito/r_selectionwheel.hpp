#pragma once

#ifndef _selwheel
#define _selwheel

#include "pch.h"

struct WheelObj
{
	std::string display_text;
	std::function<void()> action;
	Pixel color;
	void* icon;

};

struct SWheel
{
	explicit SWheel(){}
	SWheel(const ivec2 _reference_point, std::list<WheelObj> _objects, float _radius);
	~SWheel() = default;

	void Init(const ivec2 _reference_point, float _radius);

	void Init(const ivec2 _reference_point, std::list<WheelObj> _objects, float _radius);
	void Insert(const std::string& dtext, std::function<void()> fnc, Pixel col, void* ico) { objects.push_back({ dtext, fnc, {25, 23, 27, 255}, ico}); }

	void Draw();
	void OnKeyEvent();
	void OnBlurEvent();
	void EraseAll() { ref = 0; items = 0; radius = 0; keyduration = 0; keyheld = 0, lastSelected = 0; objects.clear(); objects.resize(0); }

	

private:

	void OnDrawWheel();
	void DrawSingularPoly(WheelObj& obj, float start_angle);
	void DrawSingularOutline(WheelObj& obj, float start_angle);

	ivec2 ref = 0, mpos = 0;
	size_t items = 0;
	float radius = 0;
	float keyduration = 0;
	float width = 0;
	float angle = 0;
	bool keyheld = false;
	std::list<WheelObj> objects;
	WheelObj* lastSelected = 0;
};

#endif