#include "pch.h"


DWORD Sys_Milliseconds()
{
	return timeGetTime() - (* (DWORD*)0x13E39A4);
}