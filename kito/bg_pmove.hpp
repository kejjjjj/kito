#pragma once
#ifndef bgpmove
#define bgpmove

#include "pch.h"

namespace cg
{
	inline void(*Pmove_f)(pmove_t*);
	inline void(*PM_FoliageSnd_f)(pmove_t*);

	void Pmove(pmove_t* pmove);
	void PM_FoliageSnd(pmove_t* pm);
	inline void (*PmoveSingle)(pmove_t* pm) = (void(__cdecl*)(pmove_t*))0x5BCBB0;
}

#endif