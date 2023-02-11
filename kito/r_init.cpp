#include "pch.h"

void R_Init()
{
	r_glob = new R;

	Com_Printf(CON_CHANNEL_CONSOLEONLY, "R_Init(): Creating graphics...\n");

	if (r_glob) {
		if (!r_glob->Init())
			Com_Error(ERR_FATAL, "R_Init(): cannot create graphics..\n");
	}
}
bool R::Init()
{
	if (!this)
		return false;
	else if (this->device)
		return true;

	PVOID* vTable = *reinterpret_cast<PVOID**>(device = cg::dx->device);
	if (!vTable) { 
		Com_Error(ERR_FATAL, "!*reinterpret_cast<PVOID**>(device = cg::dx->device)");

		return false; 
	}

	endscene = (HRESULT(__stdcall *)(IDirect3DDevice9*))vTable[42];
	hook* a = 0;
	a->install(&(PVOID&)endscene, draw_func);

	return R::R_ImGui();

}
bool R::R_ImGui()
{
	if (ImGui::GetCurrentContext())
		return true;

	std::cout << "creating new imgui context!\n";
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "creating new imgui context!\n");


	ImGui::CreateContext();

	constexpr const char* window_name = "Call Of Duty 4";

	if (!ImGui_ImplWin32_Init(FindWindowA(NULL, window_name))) {
		Com_Error(ERR_FATAL, "!ImGui_ImplWin32_Init(FindWindowA(NULL, window_name))");
		return false;
	}

	if (!ImGui_ImplDX9_Init(device)) {
		Com_Error(ERR_FATAL, "!ImGui_ImplDX9_Init(device)");
		return false;
	}

	return true;
}
HRESULT __stdcall R::draw_func(IDirect3DDevice9* d)
{

	if (GetAsyncKeyState(VK_NUMPAD5) & 1) {
		Com_Error(ERR_SERVERDISCONNECT, "HELLOOOOOOOOO");
	}


	return r_glob->endscene(d);
}
