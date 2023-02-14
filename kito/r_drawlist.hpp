#pragma once

#ifndef __a_3
#define __a_3

#include "pch.h"

struct DrawList
{
	DrawList() {
		std::cout << "allocating drawlist\n";
		ui_wheel = new SWheel;
	}
	~DrawList()
	{
		std::cout << "deallocating drawlist\n";
		delete ui_wheel;
	}

	SWheel* ui_wheel = 0;
	UI ui;

};

#endif