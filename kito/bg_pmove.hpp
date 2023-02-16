#pragma once
#ifndef bgpmove
#define bgpmove

#include "pch.h"

namespace cg
{
	inline void(*Pmove_f)(pmove_t*);
	inline void(*PM_FoliageSnd_f)(pmove_t*);
	inline void(*PM_AirMove_f)(pmove_t* pm, pml_t* pml);
	inline void(*PM_WalkMove_f)(pmove_t* pm, pml_t* pml);


	void Pmove(pmove_t* pmove);
	void PM_FoliageSnd(pmove_t* pm);
	void PM_AirMove(pmove_t* pm, pml_t* pml);
	void PM_WalkMove(pmove_t* pm, pml_t* pml);
	void PM_OverBounce(pmove_t* pm, pml_t* pml);


	inline void (*PmoveSingle)(pmove_t* pm) = (void(__cdecl*)(pmove_t*))0x5BCBB0;
}

#endif