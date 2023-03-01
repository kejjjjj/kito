#ifndef _rendned
#define _rendned

#include "pch.h"

void R_Init();

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

struct R
{
	R() { R::Init(); };

	bool Init();

	R* GetContext() { return this; }
	bool R_ImGui(IDirect3DDevice9* d);
	static HRESULT __stdcall draw_func(IDirect3DDevice9* d);
	static LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	struct DrawList* dl;

	IDirect3DDevice9* device = 0;
	HRESULT(__stdcall* endscene)(IDirect3DDevice9*);
	HRESULT(__stdcall* oWndProc)(HWND, UINT, WPARAM, LPARAM);

	void(*R_RecoverLostDevice_f)();
	bool device_needs_reset = false;

	void (*CL_ShutdownRenderer_f)();
	static void CL_ShutdownRenderer();
	static void R_RecoverLostDevice();

	static void CG_DrawActive();
	void(*CG_DrawActive_f)();



	bool R_BeginFrame();
	void R_EndFrame();
};

void CG_CalcViewValues(int a1, void* a2);
inline void (*CG_CalcViewValues_f)(int, void*);

inline R* r_glob = 0;

#endif