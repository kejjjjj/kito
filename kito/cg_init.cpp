
#include "pch.h"


void cg::CG_Init()
{
	MH_STATUS state = MH_STATUS::MH_OK;

	if (state = MH_Initialize(), state != MH_STATUS::MH_OK) {
		return hook::hook_error((state));
	}

	Com_Printf(CON_CHANNEL_CONSOLEONLY, "CG_Init() loading..\n");

	tas = new TAS;

	R_Init();
	CG_InitForeverHooks();
	

	tas->Init();

	Cmd_AddCommand((char*)"showbrush", ShowBrush_f);

	Com_Printf(CON_CHANNEL_CONSOLEONLY, "^2project extension has been loaded!\n");

}
void cg::CG_PrepareHooks()
{

}
void cg::CG_InitForeverHooks()
{
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "preparing to load perma hooks\n");

	Mantle_Check_f					= (void(*)(pmove_t*, pml_t*))						(0x5B36C0);
	PM_Weapon_FireWeapon_f			= (void(__cdecl*)(int, playerState_s*))				(0x5C18D0);

	CL_FinishMove_f.init				(0x440040ul, CL_FinishMove);
	r_glob->oWndProc.init				(0x596810ul, r_glob->WndProc);
	
	r_glob->R_RecoverLostDevice_f.init	(0x5DA020ul, r_glob->R_RecoverLostDevice);
	r_glob->CL_ShutdownRenderer_f.init	(0x4452E0ul, r_glob->CL_ShutdownRenderer);
	r_glob->CG_DrawActive_f.init		(0x4111D0ul, r_glob->CG_DrawActive);

	CG_CalcViewValues_f.init			(0x42EA30ul, CG_CalcViewValues);
	CG_UpdateViewWeaponAnim_f.init		(0x433BB0ul, CG_UpdateViewWeaponAnim);

	PM_AirMove_f.init(0x5B8820ul, PM_AirMove);
	PM_WalkMove_f.init(0x5B8940ul, PM_WalkMove);
	PM_UFOMove_f.init(0x5B8E30ul, PM_UFOMove);
	PmoveSingle_f.init(0x5BCBB0ul, PmoveSingle);

	hook::write_addr(0x04F1305, "\xEB\x2E\x8B\x8B\x00", 5); //je -> jne (ent->client -> !ent->client)
	hook::nop(0x04F146D); // BG_GetSpreadForWeapon

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


	CL_FinishMove_f.release();;
	r_glob->oWndProc.release();;

	r_glob->R_RecoverLostDevice_f.release();
	r_glob->CL_ShutdownRenderer_f.release();
	r_glob->CG_DrawActive_f.release();

	CG_CalcViewValues_f.release();
	CG_UpdateViewWeaponAnim_f.release();

	PM_AirMove_f.release();
	PM_WalkMove_f.release();
	PM_UFOMove_f.release();
	PmoveSingle_f.release();


	Com_Printf(CON_CHANNEL_CONSOLEONLY, " done!\n");

	mglobs.initialized = false;

}
void cg::CG_Cleanup()
{
	MH_STATUS state = MH_STATUS::MH_OK;

	if (state = MH_Uninitialize(), state != MH_STATUS::MH_OK) {
		return hook::hook_error((state));
	}

	Com_Printf(CON_CHANNEL_CONSOLEONLY, "CG_Cleanup(): clearing data..\n");

	CG_RemoveHooks();


	delete r_glob->dl;
	delete r_glob;
	delete tas;
	

}