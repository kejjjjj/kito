#pragma once

#ifndef r_wold
#define r_wold

#include "pch.h"

struct box_s
{
	box_s(const fvec3& origin, const fvec3& mins, const fvec3& maxs);

	void R_DrawConstructedBox(vec4_t col) const;
	void R_DrawConstructedBoxEdges(vec4_t col) const;

private:

	ivec2 lowA;
	ivec2 lowB;
	ivec2 lowC;
	ivec2 lowD;

	ivec2 highA;
	ivec2 highB;
	ivec2 highC;
	ivec2 highD;

	bool lowA_valid;
	bool lowB_valid;
	bool lowC_valid;
	bool lowD_valid;

	bool highA_valid;
	bool highB_valid;
	bool highC_valid;
	bool highD_valid;

};

namespace cg
{
	bool WorldToScreen(const fvec3& location, ivec2* out);
	std::optional<ivec2> WorldToScreen(const fvec3& location);
	void CG_DrawCoordinates();
	void CG_DrawVelocity();
	void CG_DrawPlayback();
}

#endif