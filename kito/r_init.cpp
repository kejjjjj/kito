#include "pch.h"

void R_Init()
{
	r_glob = new R;

	Com_Printf(CON_CHANNEL_CONSOLEONLY, "R_Init(): Creating graphics...\n");

	if (!r_glob)
		Com_Error(ERR_FATAL, "R_Init(): this will never occur\n");

	if (!r_glob->Init())
		Com_Error(ERR_FATAL, "R_Init(): cannot create graphics..\n");
	
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

	//ALLOCATE DRAWLIST -- CLEARED IN CG_CLEANUP
	dl = new DrawList;

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

	if (!r_glob->R_ImGui() || !r_glob->R_BeginFrame()) {
		Com_Error(ERR_DROP, "R::draw_func(IDirect3DDevice9* d): !r_glob->R_ImGui() || !r_glob->R_BeginFrame()");
		return r_glob->endscene(d);
	}
	
	DrawList* dl = r_glob->dl;

	r_glob->R_BeginFrame();

	dl->ui_wheel->Draw();


	r_glob->R_EndFrame();
	



	return r_glob->endscene(d);
}
LRESULT __stdcall R::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
		return 1l;
	}

	switch (uMsg) {
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	case WM_DESTROY:
		break;

	}
	return r_glob->oWndProc(hWnd, uMsg, wParam, lParam);

}
bool R::R_BeginFrame()
{
	if (!ImGui::GetCurrentContext())
		return false;

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	return true;
}
void R::R_EndFrame()
{
	ImGui::EndFrame();
	ImGui::Render();
	ImDrawData* data = ImGui::GetDrawData();
	ImGui_ImplDX9_RenderDrawData(data);
}