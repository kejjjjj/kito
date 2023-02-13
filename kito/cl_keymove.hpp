#pragma once

#ifndef keymvoe1
#define keymvoe1

#include "pch.h"

namespace cg
{
	inline void(*CL_MouseMove_f)(usercmd_s* cmd);
	void CL_MouseMove(usercmd_s* cmd);

}

#endif