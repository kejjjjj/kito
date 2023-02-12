#pragma once

#ifndef gamefuncs
#define gamefuncs

#include "pch.h"

void iPrintLn(const char* text);
void iPrintLnBold(const char* text);
void SendCommand(const char* command);

inline cmd_function_s cmd_openmenu;
cmd_function_s* Cmd_FindCommand(const char* name);
cmd_function_s* Cmd_AddCommand(char* cmdname, void(__cdecl* function)());
cmd_function_s* Cmd_RemoveCommand(const char* cmdname);

void Cbuf_AddText(const char* text, int localClientNum);


void Cmd_Init();
#endif