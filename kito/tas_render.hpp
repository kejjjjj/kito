#pragma once

#ifndef tasrender
#define tasrender

#include "pch.h"

class TAS_Render
{
public:

	bool cinematic_mode = false;

	void R_Render();
	void R_ShowSegmentPath(const segment_s* seg, unsigned int color);

	void R_ShowSegmentPathColored(const segment_s* seg, Pixel& refColor);

	void R_DrawHitbox();
	void R_AngleArrow();
	void R_FrameData();

private:
};

#endif