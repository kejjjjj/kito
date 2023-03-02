#pragma once
#ifndef bgpmove
#define bgpmove

#include "pch.h"

namespace cg
{
	inline pmove_t* pm_ptr;
	inline pml_t* pml_ptr;
	inline vec3_t temp_velocity;
	inline int temp_delta;
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
	static void(__cdecl* PM_AdjustAimSpreadScale_)(pmove_t* pm, pml_t* pml) = ((void(__cdecl*)(pmove_t*, pml_t*))0x5C0CF0);

	static void(*PM_UpdateSprint_)(pmove_t* pm) = ((void(__cdecl*)(pmove_t*))0x5B79F0);
	//static void(*PM_UpdatePlayerWalkingFlag_)(pmove_t* pm) = ((void(__cdecl*)(pmove_t*))0x5BC240);

	static void(__fastcall*PM_DropTimers)(playerState_s* ps, pml_t* pml) = ((void(__fastcall*)(playerState_s*, pml_t*))0x5BAED0);

	static void(*PM_UpdateAimDownSightFlag_)(pmove_t* pm, pml_t* pml) = ((void(__cdecl*)(pmove_t*, pml_t*))0x5BF480);
	static void(*PM_Footsteps_)(pmove_t* pm, pml_t* pml) = ((void(__cdecl*)(pmove_t*, pml_t*))0x5BABD0);

	//static void(*PM_UpdatePronePitch_)(pmove_t* pm, pml_t* pml) = ((void(__cdecl*)(pmove_t*, pml_t*))0x5BBF70);

	static void PM_UpdatePlayerWalkingFlag_(pmove_t* pm) {
		__asm
		{
			mov ecx, pm;
			mov esi, 0x5BC240;
			call esi;

		}
	}
	static void PM_FoliageSnd_(pmove_t* pm) {
		__asm
		{
			mov eax, pm;
			mov esi, 0x5BAD60;
			call esi;

		}
	}
	inline int PM_InteruptWeaponWithProneMove_(playerState_s* ps) {
		int rval = 0;
		__asm
		{
			mov eax, ps;
			mov esi, 0x5BF9F0;
			call esi;
			mov rval, eax;
		}
		return rval;
	}
	static void PM_ExitAimDownSight_(playerState_s* ps) {
		__asm
		{
			mov eax, ps;
			mov esi, 0x05BF560;
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
	static void PM_UpdateViewAngles(playerState_s* ps, float msec, usercmd_s* cmd, char handler) {

		__asm
		{
			movzx eax, handler;
			mov esi, cmd;
			push eax;
			push esi;
			push msec;
			mov eax, ps;
			mov esi, 0x5BBE60;
			call esi;
			add esp, 0xC;
		}

	}
	static void PM_BeginWeaponChange_(int weapon, playerState_s* ps, bool quick)
	{
		static DWORD fnc = 0x5C0190;
		__asm
		{
			push quick;
			mov esi, ps;
			mov edx, weapon;
			call fnc;
			add esp, 0x4;
		}
	}
	inline void (*PmoveSingle)(pmove_t* pm) = (void(__cdecl*)(pmove_t*))0x5BCBB0;

	inline void(__cdecl*PM_Weapon_FireWeapon_f)(int delay, playerState_s* ps);
	void PM_Weapon_FireWeapon(int delay, playerState_s* ps);

}

#endif