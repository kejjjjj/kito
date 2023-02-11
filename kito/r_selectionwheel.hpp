#pragma once

#ifndef _selwheel
#define _selwheel

#include "pch.h"

struct WheelObj
{
	std::string display_text;
	std::function<void()> action;

};

struct SWheel
{
	explicit SWheel(std::list<WheelObj> _objects, float _radius);



private:
	size_t items = 0;
	float radius = 0;
	std::list<WheelObj> objects;
};

#endif