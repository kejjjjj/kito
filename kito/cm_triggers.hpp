#pragma once

#ifndef cmtrig_
#define cmtrig_

#include "pch.h"


namespace cg
{
	void ShowBrush_f();

	void CM_GetBrushOriginFromBounds(const cbrush_t* brush, vec3_t out);
	void CM_DrawBrush(const cbrush_t* b);

	inline bool show_all_triggers = false;
	inline std::vector<cbrush_t*> brushes;
}


#endif