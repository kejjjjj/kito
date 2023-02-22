#pragma once

#ifndef tasrender
#define tasrender

#include "pch.h"

class TAS_Render
{
public:
	void R_Render();
	void R_ShowSegmentPath(const segment_s* seg, unsigned int color);
	void R_DrawHitbox();

private:
};

#endif