
#include "pch.h"


void cg::CG_Init()
{
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "CG_Init() loading..\n");

	R_Init();
	CG_InitForeverHooks();
	
	tas = new TAS;

	tas->Init();

	Cmd_AddCommand((char*)"showtriggers", ShowTriggers_f);

	Com_Printf(CON_CHANNEL_CONSOLEONLY, "^2project extension has been loaded!\n");

}
void cg::CG_PrepareHooks()
{

}
void cg::CG_InitForeverHooks()
{
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "preparing to load perma hooks\n");

	r_glob->oWndProc				= (HRESULT(__stdcall*)(HWND, UINT, WPARAM, LPARAM))	(0x596810);
	CL_FinishMove_f					= (void(*)(usercmd_s*))								(0x440040);
	Pmove_f							= (void(*)(pmove_t*))								(0x5BD440);
	PmoveSingle_f					= (void(*)(pmove_t*))								(0x5BCBB0);

	PM_AirMove_f					= (void(*)(pmove_t*, pml_t*))						(0x5B8820);
	PM_WalkMove_f					= (void(*)(pmove_t*, pml_t*))						(0x5B8940);
	PM_UFOMove_f					= (void(*)(pmove_t*, pml_t*))						(0x5B8E30);
	Mantle_Check_f					= (void(*)(pmove_t*, pml_t*))						(0x5B36C0);
	PM_Weapon_FireWeapon_f			= (void(__cdecl*)(int, playerState_s*))				(0x5C18D0);

	r_glob->R_RecoverLostDevice_f	= (void(*)())										(0x5DA020);
	r_glob->CL_ShutdownRenderer_f	= (void(*)())										(0x4452E0);
	r_glob->CG_DrawActive_f			= (void(*)())										(0x4111D0);

	CG_CalcViewValues_f				= (void(*)(int, void*))								(0x42EA30);
	CG_UpdateViewWeaponAnim_f		= (void(*)())										(0x433BB0);


	hook::install(&(PVOID&)r_glob->oWndProc, r_glob->WndProc);
	hook::install(&(PVOID&)CL_FinishMove_f, CL_FinishMove);
	hook::install(&(PVOID&)PM_AirMove_f, PM_AirMove);
	hook::install(&(PVOID&)PM_WalkMove_f, PM_WalkMove);
	hook::install(&(PVOID&)PM_UFOMove_f, PM_UFOMove);
	hook::install(&(PVOID&)PM_Weapon_FireWeapon_f, PM_Weapon_FireWeapon);

	hook::install(&(PVOID&)CG_CalcViewValues_f, CG_CalcViewValues);
	hook::install(&(PVOID&)CG_UpdateViewWeaponAnim_f, CG_UpdateViewWeaponAnim);

	hook::install(&(PVOID&)r_glob->R_RecoverLostDevice_f, r_glob->R_RecoverLostDevice);
	hook::install(&(PVOID&)r_glob->CL_ShutdownRenderer_f, r_glob->CL_ShutdownRenderer);
	hook::install(&(PVOID&)r_glob->CG_DrawActive_f, r_glob->CG_DrawActive);
	

	hook::install(&(PVOID&)Pmove_f, Pmove);
	hook::install(&(PVOID&)PmoveSingle_f, PmoveSingle);

}
void cg::CG_InitHooks()
{
	std::cout << "calling cg::CG_InitHooks()\n";
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "preparing to load hooks... ");
	if (mglobs.initialized)
		return;

	CG_PrepareHooks();

	Com_Printf(CON_CHANNEL_CONSOLEONLY, " done!\n");


	mglobs.initialized = true;
}
void cg::CG_RemoveHooks()
{
	std::cout << "calling cg::CG_RemoveHooks()\n";
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "preparing to remove hooks...");

	if (!mglobs.initialized)
		return;

	hook::remove(&(PVOID&)r_glob->oWndProc, r_glob->WndProc);
	hook::remove(&(PVOID&)CL_FinishMove_f, CL_FinishMove);
	hook::remove(&(PVOID&)r_glob->R_RecoverLostDevice_f, r_glob->R_RecoverLostDevice);
	hook::remove(&(PVOID&)r_glob->CL_ShutdownRenderer_f, r_glob->CL_ShutdownRenderer);
	hook::remove(&(PVOID&)PM_AirMove_f, PM_AirMove);
	hook::remove(&(PVOID&)PM_WalkMove_f, PM_WalkMove);
	hook::remove(&(PVOID&)PM_UFOMove_f, PM_UFOMove);
	hook::remove(&(PVOID&)Mantle_Check_f, Mantle_Check);
	hook::remove(&(PVOID&)r_glob->CG_DrawActive_f, r_glob->CG_DrawActive);
	hook::remove(&(PVOID&)CG_CalcViewValues_f, CG_CalcViewValues);
	hook::remove(&(PVOID&)CG_UpdateViewWeaponAnim_f, CG_UpdateViewWeaponAnim);

	hook::remove(&(PVOID&)PM_Weapon_FireWeapon_f, PM_Weapon_FireWeapon);
	hook::remove(&(PVOID&)Pmove_f, Pmove);
	hook::remove(&(PVOID&)PmoveSingle_f, PmoveSingle);

	Com_Printf(CON_CHANNEL_CONSOLEONLY, " done!\n");

	mglobs.initialized = false;

}
void cg::CG_Cleanup()
{
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "CG_Cleanup(): clearing data..\n");

	CG_RemoveHooks();


	delete r_glob->dl;
	delete r_glob;
	delete tas;
	

}