
#include "pch.h"


void cg::CG_Init()
{
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "CG_Init() loading..\n");

	R_Init();
	CG_InitForeverHooks();
	

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
	r_glob->R_RecoverLostDevice_f	= (void(*)())										(0x5DA020);
	r_glob->CL_ShutdownRenderer_f	= (void(*)())										(0x4452E0);

	hook::install(&(PVOID&)r_glob->oWndProc, r_glob->WndProc);
	hook::install(&(PVOID&)CL_FinishMove_f, CL_FinishMove);
	hook::install(&(PVOID&)r_glob->R_RecoverLostDevice_f, r_glob->R_RecoverLostDevice);
	hook::install(&(PVOID&)r_glob->CL_ShutdownRenderer_f, r_glob->CL_ShutdownRenderer);

	//hook::install(&(PVOID&)Pmove_f, Pmove);

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
	hook::remove(&(PVOID&)Pmove_f, Pmove);
	hook::remove(&(PVOID&)r_glob->R_RecoverLostDevice_f, r_glob->R_RecoverLostDevice);
	hook::remove(&(PVOID&)r_glob->CL_ShutdownRenderer_f, r_glob->CL_ShutdownRenderer);


	Com_Printf(CON_CHANNEL_CONSOLEONLY, " done!\n");

	mglobs.initialized = false;

}
void cg::CG_Cleanup()
{
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "CG_Cleanup(): clearing data..\n");

	CG_RemoveHooks();


	delete r_glob->dl;
	delete r_glob;
	

}