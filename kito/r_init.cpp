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
	hook::install(&(PVOID&)endscene, draw_func);

	//ALLOCATE DRAWLIST -- CLEARED IN CG_CLEANUP
	dl = new DrawList;

	return R::R_ImGui(device);

}
bool R::R_ImGui(IDirect3DDevice9* d)
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

	if (!ImGui_ImplDX9_Init(d)) {
		Com_Error(ERR_FATAL, "!ImGui_ImplDX9_Init(device)");
		return false;
	}


	return true;
}
HRESULT __stdcall R::draw_func(IDirect3DDevice9* d)
{

	if (!r_glob->R_ImGui(d)) {
		Com_Error(ERR_DROP, "R::draw_func(IDirect3DDevice9* d): !r_glob->R_ImGui() || !r_glob->R_BeginFrame()");
		return r_glob->endscene(d);
	}
	
	DrawList* dl = r_glob->dl;

	r_glob->R_BeginFrame();

	if (cg::show_all_triggers) {
		for (auto& i : cg::brushes) {
			cg::CM_DrawBrush(i);
		}
	}

	//dl->ui_wheel->Draw();

	dl->ui.UI_Draw();
	tas->render.R_Render();

	if (tas->movement.recorder) {
		if (tas->movement.recorder->IsPlayback()) {

			auto current = tas->movement.recorder->CurrentCmd();
			
			if (current && cg::predictedPlayerState) {
				float dist = current->origin.dist(cg::predictedPlayerState->origin);
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(1600, 800), 0xFFFFFFFF, std::format("sync: {:.6f}\n{:.6f}", dist, current->camera_yaw).c_str());
			}
		}
	}


	r_glob->R_EndFrame();
	

	tas->movement.set_player_pov();


	return r_glob->endscene(d);
}
using namespace r;
using namespace cg;
void R::CG_DrawActive()
{
	//R_DrawTextWithEffects("hello", "fonts/objectivefont", 500, 500, 2, 2, 180, vec4_t{ 1,1,1,1 }, 3, vec4_t{ 1,0,0,1 });
	
	tas->render.R_FrameData();
	cg::CG_DrawCoordinates();
	cg::CG_DrawVelocity();

	if (tas->TAS_CheckAutoSave())
		tas->TAS_AutoSave();



	return r_glob->CG_DrawActive_f();
}
void CG_CalcViewValues(int a1, void*a2)
{
	//cg::predictedPlayerState->viewangles[YAW] = 90;

	CG_CalcViewValues_f(a1, a2);

	if (tas->movement.recorder) {

		if (tas->movement.recorder->IsPlayback()) {

			auto current = tas->movement.recorder->CurrentCmd();

			if (current && cg::predictedPlayerState) {

				if (current->camera_yaw != -400) {
					vec3_t viewangles{ (*(float*)0x724110), *(float*)(0x724110 + 4), *(float*)(0x724110 + 8) };
					viewangles[1] = current->camera_yaw;
					AnglesToAxis(viewangles, cg::refdef->viewaxis);
				}
			}
		}
	}

	return;
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
void R::R_RecoverLostDevice()
{
	
	if (!r_glob->device_needs_reset && ImGui::GetCurrentContext()) {

		Com_Printf(CON_CHANNEL_CONSOLEONLY, "R_RecoverLostDevice(): restoring input\n");
		IN_ActivateMouse(true);
		ImGui_ImplDX9_InvalidateDeviceObjects();
		std::cout << "R_RecoverLostDevice(): restoring input\n";
		r_glob->device_needs_reset = true;
	}

	return r_glob->R_RecoverLostDevice_f();
}
void R::CL_ShutdownRenderer()
{

	std::cout << "shutdown renderer!\n";
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "shutting down renderer\n");

	if (ImGui::GetCurrentContext()) {


		Com_Printf(CON_CHANNEL_CONSOLEONLY, "also removing imgui context\n");
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	return r_glob->CL_ShutdownRenderer_f();
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
	device_needs_reset = false;
}