
#include "pch.h"


void cg::CG_Init()
{
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "CG_Init() loading..\n");

	CG_InitForeverHooks();

	R_Init();

	Com_Printf(CON_CHANNEL_CONSOLEONLY, "^21_kej extension has been loaded!\n");

}
void cg::CG_PrepareHooks()
{

}
void cg::CG_InitForeverHooks()
{
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "preparing to load perma hooks\n");



}
void cg::CG_InitHooks()
{
	std::cout << "calling cg::CG_InitHooks()\n";
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "preparing to load hooks... ");
	if (mglobs.initialized)
		return;

	CG_PrepareHooks();

	hook* a = nullptr;


	Com_Printf(CON_CHANNEL_CONSOLEONLY, " done!\n");


	mglobs.initialized = true;
}
void cg::CG_RemoveHooks()
{
	std::cout << "calling cg::CG_RemoveHooks()\n";
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "preparing to remove hooks...");

	if (!mglobs.initialized)
		return;

	hook* a = nullptr;



	Com_Printf(CON_CHANNEL_CONSOLEONLY, " done!\n");

	mglobs.initialized = false;

}
void cg::CG_Cleanup()
{
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "CG_Cleanup(): clearing data..\n");

	CG_RemoveHooks();



	delete r_glob;

}