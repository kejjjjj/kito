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

	std::function<HRESULT __stdcall(IDirect3DDevice9*)> endscene_ptr;

	IDirect3DDevice9* device = 0;
	HRESULT(__stdcall * endscene)(IDirect3DDevice9*);

private:
	
};

inline R* r_glob = 0;

#endif