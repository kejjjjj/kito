#include "pch.h"


void cg::CL_FinishMove(usercmd_s* cmd)
{
	__asm
	{
		mov cmd, edi;
	}

	//*(int*)(0x85BD98 + 11454) -= 1000 / Dvar_FindMalleableVar("com_maxfps")->current.integer;

	CL_FinishMove_f(cmd);

	if (GetAsyncKeyState(VK_NUMPAD4) & 1 && !tas->movement.recorder) {
		if (tas->movement.get_segment_count() > 0) {

			tas->movement.recorder = new Recorder(tas->movement.create_a_list_from_segments());

		}
	}

	if (tas->movement.recorder) {
		if (tas->movement.recorder->IsPlayback()) {
			tas->movement.recorder->Playback(cmd);
		}
		else {
			Com_Printf(CON_CHANNEL_SUBTITLE, "goodbye\n");
			delete tas->movement.recorder;
			tas->movement.recorder = 0;
		}
	}

	return;
}