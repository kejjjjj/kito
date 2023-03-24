#ifndef _rendned
#define _rendned

#include "pch.h"

void R_Init();

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

struct R
{
	R() { ok = R::Init(); };

	bool Init();

	R* GetContext() { return this; }
	bool R_ImGui(IDirect3DDevice9* d);
	static HRESULT __stdcall draw_func(IDirect3DDevice9* d);

	struct DrawList* dl;

	IDirect3DDevice9* device = 0;
	//HRESULT(__stdcall* endscene)(IDirect3DDevice9*);
	hook::hookobj<HRESULT(IDirect3DDevice9*)> endscene;

	//HRESULT(__stdcall* oWndProc)(HWND, UINT, WPARAM, LPARAM);

	hook::hookobj<HRESULT __stdcall(HWND, UINT, WPARAM, LPARAM)> oWndProc;
	static LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	hook::hookobj<void()> R_RecoverLostDevice_f;

	bool device_needs_reset = false;

	inline static hook::hookobj<void()> CL_ShutdownRenderer_f;
	static void CL_ShutdownRenderer();
	static void R_RecoverLostDevice();


	static void CG_DrawActive();
	hook::hookobj<void()> CG_DrawActive_f;

	bool R_BeginFrame();
	void R_EndFrame();
	bool ok = 0;
}; 

void CG_CalcViewValues(int a1, void* a2);
inline hook::hookobj<void(int, void*)> CG_CalcViewValues_f;
void CG_UpdateViewWeaponAnim();
inline hook::hookobj<void()> CG_UpdateViewWeaponAnim_f;

inline R* r_glob = 0;

#endif