#ifndef _rendned
#define _rendned

#include "pch.h"

void R_Init();

struct R
{
	R() { R::Init(); };

	bool Init();

	R* GetContext() { return this; }
	bool R_ImGui();
	static HRESULT __stdcall draw_func(IDirect3DDevice9* d);

	

	IDirect3DDevice9* device = 0;
	HRESULT(__stdcall * endscene)(IDirect3DDevice9*);

	bool R_BeginFrame();
	void R_EndFrame();
};

inline R* r_glob = 0;

#endif