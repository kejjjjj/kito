// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define ANGLE2SHORT( x )  ( (int)( ( x ) * 65536 / 360 ) & 65535 )
#define SHORT2ANGLE( x )  ( ( x ) * ( 360.0f / 65536 ) )

#define NOMINMAX

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];

#define PI 3.14159265f
#ifndef M_PI
#define M_PI        3.14159265358979323846f // matches value in gcc v2 math.h
#endif
#define DotProduct(x,y)			((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])
#define VectorSubtract(a,b,c)	((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])
#define VectorAdd(a,b,c)		((c)[0]=(a)[0]+(b)[0],(c)[1]=(a)[1]+(b)[1],(c)[2]=(a)[2]+(b)[2])
#define VectorAddAll(a,b,c)		((c)[0]=(a)[0]+(b),(c)[1]=(a)[1]+(b),(c)[2]=(a)[2]+(b))
#define VectorCopy(a,b)			((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])
#define	VectorScale(v, s, o)	((o)[0]=(v)[0]*(s),(o)[1]=(v)[1]*(s),(o)[2]=(v)[2]*(s))
#define VectorScaleAll(a,b,c)	((c)[0]=(a)[0]*(b),(c)[1]=(a)[1]*(b),(c)[2]=(a)[2]*(b))
#define	VectorMA(v, s, b, o)	((o)[0]=(v)[0]+(b)[0]*(s),(o)[1]=(v)[1]+(b)[1]*(s),(o)[2]=(v)[2]+(b)[2]*(s))
#define VectorClear( a )              ( ( a )[0] = ( a )[1] = ( a )[2] = 0 )

#define DEG2RAD(a) (((a) * M_PI) / 180.0F)
#define RAD2DEG(a) (((a) * 180.0f) / M_PI)
#define RAD2SHORT(a) ((a) * (32768.f / (float)M_PI))
#define SHORT2RAD(a) ((a) * ((float)M_PI / 32768.f))
#define SHORT2DEG(a) (((a) / 32768.f) * 180.0f)
#define	VALUE2COLOR(x,y)	((x/y)*32)


#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <functional>
#include <Psapi.h>
#include <TlHelp32.h>
#include <fstream>
#include <filesystem>
#include <direct.h>
#include <optional>
#include <map>
#include <unordered_map>
#include <set>
#include <any>

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
#include "imGui/imgui_stdlib.h"

#include "mh/MinHook.h"


#include "koukku.hpp"

#include "typedefs.hpp"
#include "vectors.hpp"
#include "filetools.hpp"

#include "in_main.hpp"

#include "q_math.hpp"

#include "cg_local.h"
#include "cg_offsets.h"
#include "cg_init.hpp"
#include "cg_angles.hpp"
#include "cg_dvar.h"

#include "bg_pmove.hpp"
#include "bg_weapon.hpp"

#include "game_funcs.hpp"
#include "sys_main.hpp"

#include "r_selectionwheel.hpp"
#include "r_userinterface.hpp"
#include "r_world.hpp"
#include "r_drawtools.hpp"

#include "r_drawlist.hpp"
#include "r_init.hpp"

#include "cl_keymove.hpp"

#include "cm_triggers.hpp"

#include "com_channel.h"

#include "clipping.hpp"


#include "tas_movement.hpp"
#include "tas_fs_out.hpp"
#include "tas_fs_in.hpp"
#include "tas_filesystem.hpp"
#include "tas_ui.hpp"
#include "tas_render.hpp"
#include "tas_main.hpp"

#include "entry.hpp"

using namespace std::chrono_literals;


#endif //PCH_H
