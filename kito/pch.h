// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define ANGLE2SHORT( x )  ( (int)( ( x ) * 65536 / 360 ) & 65535 )
#define SHORT2ANGLE( x )  ( ( x ) * ( 360.0 / 65536 ) )

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];

#define PI 3.14159265f

#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <functional>
#include <Psapi.h>
#include <TlHelp32.h>

// add headers that you want to pre-compile here
#include "framework.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//detours
#include "detours/detours.h"
#pragma comment(lib, "detours.lib")

//DIRECTX
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9core.h>

//IMGUI
#include "imGui/imgui.h"
#include "imGui/imgui_impl_dx9.h"
#include "imGui/imgui_impl_win32.h"
#include "imGui/imgui_internal.h"

#include "koukku.hpp"

#include "typedefs.hpp"

#include "cg_local.h"
#include "cg_offsets.h"
#include "cg_init.hpp"

#include "r_init.hpp"
#include "r_selectionwheel.hpp"

#include "com_channel.h"

#include "entry.hpp"

using namespace std::chrono_literals;


#endif //PCH_H
