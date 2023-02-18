#include "pch.h"


void cg::CL_FinishMove(usercmd_s* cmd)
{
	__asm
	{
		mov cmd, edi;
	}

	//*(int*)(0x85BD98 + 11454) -= 1000 / Dvar_FindMalleableVar("com_maxfps")->current.integer;

	CL_FinishMove_f(cmd);

	if (GetAsyncKeyState(VK_NUMPAD4) & 1) {
		if (!recorder.IsRecording())
			recorder.StartRecording();
		else
			recorder.StopRecording();
	}
	else if (GetAsyncKeyState(VK_NUMPAD5) & 1) {
		if (!recorder.IsPlayback())
			recorder.StartPlayback();
	}

	if (recorder.IsRecording()) {
		recorder.Record(cmd);
	}
	else if (recorder.IsPlayback()) {
		recorder.Playback(cmd);
	}

	return;
}