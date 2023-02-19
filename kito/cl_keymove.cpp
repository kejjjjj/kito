#include "pch.h"


void cg::CL_FinishMove(usercmd_s* cmd)
{
	__asm
	{
		mov cmd, edi;
	}

	//*(int*)(0x85BD98 + 11454) -= 1000 / Dvar_FindMalleableVar("com_maxfps")->current.integer;
	CL_FinishMove_f(cmd);

	static DWORD ms = Sys_Milliseconds();


	if (GetAsyncKeyState(VK_NUMPAD4) & 1 && !tas->movement.recorder) {
		if (tas->movement.get_segment_count() > 0) {

			//VectorCopy(tas->movement.first_segment.ps.origin, ps_loc->origin);
			//VectorCopy(tas->movement.first_segment.ps.viewangles, ps_loc->viewangles);
			//VectorCopy(tas->movement.first_segment.ps.velocity, ps_loc->velocity);

			*ps_loc = tas->movement.entry.ps;
			//*pm_ptr = tas->movement.first_segment.pm;
			//*pml_ptr = tas->movement.first_segment.pml;

			segment_s* first = tas->movement.get_first_segment();


			cmd->angles[0] = first->content.front().angles[0];
			cmd->angles[1] = first->content.front().angles[1];
			cmd->angles[2] = first->content.front().angles[2];

			//CG_SetPlayerAngles(ps_loc->viewangles, tas->movement.first_segment.ps.viewangles);

			tas->movement.recorder = new Recorder(tas->movement.create_a_list_from_segments());

			ms = Sys_Milliseconds();

			return;
		}
	}

	if (tas->movement.recorder) {

		if (ms + 1000 < Sys_Milliseconds()) {

			if (tas->movement.recorder->IsPlayback()) {
				tas->movement.recorder->Playback(cmd);
			}
			else {
				Com_Printf(CON_CHANNEL_SUBTITLE, "goodbye\n");
				delete tas->movement.recorder;
				tas->movement.recorder = 0;
			}
		}
		else {
			segment_s* first = tas->movement.get_first_segment();
			cmd->angles[0] = first->content.front().angles[0];
			cmd->angles[1] = first->content.front().angles[1];
			cmd->angles[2] = first->content.front().angles[2];
		}
	}
	cg::temp_delta = cmd->angles[1];
	return;
}