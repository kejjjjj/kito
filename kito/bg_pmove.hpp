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
	inline void(*PM_UFOMove_f)(pmove_t* pm, pml_t* pml);
	inline void(*Mantle_Check_f)(pmove_t* pm, pml_t* pml);


	void Pmove(pmove_t* pmove);
	void PM_FoliageSnd(pmove_t* pm);
	void PM_AirMove(pmove_t* pm, pml_t* pml);
	void PM_WalkMove(pmove_t* pm, pml_t* pml);
	void PM_UFOMove(pmove_t* pm, pml_t* pml);

	void Mantle_Check(pmove_t* pm, pml_t* pml);

	void PM_OverBounce(pmove_t* pm, pml_t* pml);

	static void(*PM_GroundTrace_)(pmove_t* pm, pml_t* pml) = ((void(__cdecl*)(pmove_t*, pml_t*))0x5B95F0);
	static void(__cdecl*PM_CheckLadderMove_)(pmove_t* pm, pml_t* pml) = ((void(__cdecl*)(pmove_t*, pml_t*))0x5BC290);
	static void(__cdecl* PM_LadderMove_)(pmove_t* pm, pml_t* pml) = ((void(__cdecl*)(pmove_t*, pml_t*))0x5BC570);

	static void(*PM_UpdateSprint_)(pmove_t* pm) = ((void(__cdecl*)(pmove_t*))0x5B79F0);
	//static void(*PM_UpdatePlayerWalkingFlag_)(pmove_t* pm) = ((void(__cdecl*)(pmove_t*))0x5BC240);

	static void(__fastcall*PM_DropTimers)(playerState_s* ps, pml_t* pml) = ((void(__fastcall*)(playerState_s*, pml_t*))0x5BAED0);

	static void(*PM_UpdateAimDownSightFlag_)(pmove_t* pm, pml_t* pml) = ((void(__cdecl*)(pmove_t*, pml_t*))0x5BF480);
	//static void(*PM_UpdatePronePitch_)(pmove_t* pm, pml_t* pml) = ((void(__cdecl*)(pmove_t*, pml_t*))0x5BBF70);

	static void PM_UpdatePlayerWalkingFlag_(pmove_t* pm) {
		__asm
		{
			mov ecx, pm;
			mov esi, 0x5BC240;
			call esi;

		}
	}
	static void PM_Weapon_(pmove_t* pm, pml_t* pml)
	{
		__asm
		{
			lea eax, pml;
			push eax;
			mov eax, pm;
			mov esi, 0x5C29D0;
			call esi;
			add esp, 0x4;
		}
	}
	static void PM_CheckDuck_(pmove_t* pm, pml_t* pml)
	{
		__asm
		{
			lea edx, pml;
			push edx;
			mov edi, pm;
			mov esi, 0x5B9E50;
			call esi;
			add esp, 0x4;
		}
	}
	static void Mantle_Move(playerState_s* ps, pml_t* pml)
	{
		__asm
		{
			push pml;
			mov edi, ps;
			mov esi, 0x5B3860;
			call esi;
			add esp, 0x4;
		}
	}
	static void PM_UpdatePronePitch_(pmove_t* pm, pml_t* pml) {
		__asm
		{
			mov eax, pm;
			mov edi, pml;
			mov esi, 0x5BBF70;
			call esi;
		}
	}
	inline void (*PmoveSingle)(pmove_t* pm) = (void(__cdecl*)(pmove_t*))0x5BCBB0;
}

#endif