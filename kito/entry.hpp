#pragma once

#ifndef __EMNTRy
#define __EMNTRy

constexpr const char* GAME_MODULE = "iw3sp.exe";

#include "pch.h"

inline std::thread thread;

DWORD WINAPI parent_thread(HMODULE hModule);


#endif