#pragma once

#ifndef keymvoe1
#define keymvoe1

#include "pch.h"

namespace cg
{
	inline void(*CL_FinishMove_f)(usercmd_s* cmd);
	void CL_FinishMove(usercmd_s* cmd);

}

#endif