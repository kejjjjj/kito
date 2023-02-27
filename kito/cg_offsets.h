#pragma once

#ifndef cgmain
#define cgmain

#include "pch.h"

namespace cg
{

	static DxGlobals* dx = (DxGlobals*)(0x01623F84);
	static CInput* input = (CInput*)(0x00868734);
	static coordinates* coord = (coordinates*)(0x714BC4);
	static coordinates* face_coord = (coordinates*)(0x6E17B0 - 4);
	static viewangles* vAngle = (viewangles*)(0x6E17BC - 4);
	static playerState_t_origin* pOrigin = (playerState_t_origin*)(0xE0DA1C);
	static Movement* move = (Movement*)(0x815EF8);
	static playerState_s* ps_loc = (playerState_s*)(0xE0DA00);
	static playerState_s* predictedPlayerState = (playerState_s*)(0x714BA8);

	static velocity* vel = (velocity*)(0xC8143C);
	static refdef_s* refdef = (refdef_s*)(0x720080);
	inline WinMouseVars_t* s_wmv = (WinMouseVars_t*)(0x13E06F0);

	inline WeaponDef** BG_WeaponNames = reinterpret_cast<WeaponDef**>(0x14227A8);

	inline int* bg_lastParsedWeaponIndex = reinterpret_cast<int*>(0x1E20A04);
}
#endif