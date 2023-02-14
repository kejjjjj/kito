#pragma once

#ifndef ui__
#define ui__

#include "pch.h"

class UI
{
public:
	bool UI_Checkbox(bool& var);
	
	void UI_Draw();
	void UI_ColorTheme(const float transparency = 1.f);

};

#endif