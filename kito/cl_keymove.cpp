#include "pch.h"


void cg::CL_FinishMove(usercmd_s* cmd)
{
	__asm
	{
		mov cmd, edi;
	}

	//*(int*)(0x85BD98 + 11454) -= 1000 / Dvar_FindMalleableVar("com_maxfps")->current.integer;
	CL_FinishMove_f(cmd);

	if (tas->ui.editing) {
		cmd->buttons = 0;
		cmd->forwardmove = 0;
		cmd->rightmove = 0;
	}

	static DWORD ms = Sys_Milliseconds();
	static bool wait_weapon = false;

	tas->movement.set_player_pov(cmd);

	if (GetAsyncKeyState(VK_NUMPAD4) & 1 && !tas->movement.recorder) {
		if (tas->movement.get_segment_count() > 0) {

			*ps_loc = tas->movement.entry.ps;
			segment_s* first = tas->movement.get_first_segment();

			cmd->angles[0] = first->content.front().angles[0];
			cmd->angles[1] = first->content.front().angles[1];
			cmd->angles[2] = first->content.front().angles[2];

			tas->movement.recorder = new Recorder(tas->movement.create_a_list_from_segments());

			ms = Sys_Milliseconds();
			wait_weapon = true;
			return;
		}
	}

	if (tas->movement.recorder) {

		auto& io = ImGui::GetIO();

		if (io.KeysDownDuration['W'] == 0.f || io.KeysDownDuration['A'] == 0.f || io.KeysDownDuration['S'] == 0.f || io.KeysDownDuration['D'] == 0.f) {
			Com_Printf(CON_CHANNEL_SUBTITLE, "goodbye\n");
			delete tas->movement.recorder;
			tas->movement.recorder = 0;
			return;
		}

		segment_s* first = tas->movement.get_first_segment();

		if (wait_weapon)
			wait_weapon = ps_loc->weapon != first->content.front().weapon;

		else if (ms + 1000 < Sys_Milliseconds() && !wait_weapon) {

			if (tas->movement.recorder->IsPlayback()) {
				tas->movement.recorder->Playback(cmd);
			}
			else {
				Com_Printf(CON_CHANNEL_SUBTITLE, "goodbye\n");
				delete tas->movement.recorder;
				tas->movement.recorder = 0;
			}
			return;
		}
		cmd->angles[0] = first->content.front().angles[0];
		cmd->angles[1] = first->content.front().angles[1];
		cmd->angles[2] = first->content.front().angles[2];
		cmd->weapon = first->content.front().weapon;
		//cmd->serverTime = first->content.front().serverTime;

		Dvar_FindMalleableVar("com_maxfps")->current.integer = first->content.front().FPS;
		
	}
	cg::temp_delta = cmd->angles[1];


	//if (GetAsyncKeyState(VK_NUMPAD5) < 0)
	//	cmd->weapon = 16;
	return;
}