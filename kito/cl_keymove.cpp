#include "pch.h"


void cg::CL_MouseMove(usercmd_s* cmd)
{
	__asm
	{
		mov cmd, edi;
	}

	CL_MouseMove_f(cmd);

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

//	cmd->angles[1] = ANGLE2SHORT(90);
	//static int roll = 0;

	//if (GetAsyncKeyState(VK_NUMPAD7)&1 || roll && roll < 360) {
	//	CG_SetPlayerAngles(vAngle->angles, vec3_t{ float(roll), float(roll), float(roll) });
	//	++roll;
	//}
	//else
	//	roll = 0;
	

	return;
}