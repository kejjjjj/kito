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
	bool R_ImGui();
	static HRESULT __stdcall draw_func(IDirect3DDevice9* d);
	static LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	struct DrawList* dl;

	IDirect3DDevice9* device = 0;
	HRESULT(__stdcall* endscene)(IDirect3DDevice9*);
	HRESULT(__stdcall* oWndProc)(HWND, UINT, WPARAM, LPARAM);

	bool R_BeginFrame();
	void R_EndFrame();
};

inline R* r_glob = 0;

#endif