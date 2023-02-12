#include "pch.h"

void IN_ActivateMouse(bool state)
{
	hook* a = nullptr;
	cg::s_wmv->mouseInitialized = state;
	cg::s_wmv->mouseActive = state;

}
void UI_SetSystemCursorPos(float x, float y)
{
	return ((void(__cdecl*)(float x, float y))0x564000)(x, y);
}