#include "pch.h"

void TAS_Movement::create_first_segment(pmove_t* pm, pml_t* pml)
{
	waiting_for_creation = false;

	memcpy_s(&entry.pm, sizeof(pmove_t), pm, sizeof(pmove_t));
	memcpy_s(&entry.pml, sizeof(pml_t), pml, sizeof(pml_t));
	memcpy_s(&entry.ps, sizeof(playerState_s), pm->ps, sizeof(playerState_s));

	entry.pm.ps = &entry.ps;

	entry.angles = pm->ps->viewangles;
	entry.origin = pm->ps->origin;
	entry.fps = pml->frametime * 1000;

	add_segment();

	Com_Printf(CON_CHANNEL_SUBTITLE, "new project \"%s\" created", tas->filesystem->display_name.c_str());


}

void TAS_Movement::add_segment()
{
	segment_s seg;

	seg.frame_count = 100;

	if (segments.empty()) { //first segment
		seg.start_index = 0;
		seg.end_index = seg.frame_count;
	}
	else {
		seg.start_index = segments.back().end_index + 1;
		seg.end_index = seg.start_index + seg.frame_count;
	}
	segments.push_back(seg);
	current_segment = &segments.back();
	current_segment->content.resize(seg.frame_count);
}

void TAS_Movement::update_movement_for_segment(segment_s& seg)
{
	auto& list = seg.content;

	if (list.empty())
		return;

	pmove_t* pm = &entry.pm;
	pml_t* pml = &entry.pml;
	playerState_s* ps = pm->ps;

	for (auto& i : list) {

		pm->cmd.forwardmove = seg.forwardmove;
		pm->cmd.rightmove = seg.rightmove;

		recorder_cmd cmd;

		if (pml->walking) {
			//sprint here!
		}

		//other stuff

		pml->msec = 1000 / 125; //simulate 125fps
		pml->frametime = (float)pml->msec / 1000.f;



		if (pml->walking) {

			cg::PM_WalkMove_f(pm, pml);
		}
		else
			cg::PM_AirMove_f(pm, pml);

		((void(__cdecl*)(pmove_t*, pml_t*))0x5B95F0)(pm, pml); //call groundtrace after 

		cg::PM_OverBounce(pm, pml);
		//Sys_SnapVector(pm->ps->velocity); //Sys_SnapVector | not called in singleplayer



		if (pm && pml) {

			cmd.viewangles = ps->viewangles;
			cmd.origin = ps->origin;
			cmd.velocity = ps->velocity;
			cmd.forwardmove = pm->cmd.forwardmove;
			cmd.rightmove = pm->cmd.rightmove;
			cmd.FPS = 1000 / pml->msec;


			memcpy(&pm->oldcmd, &pm->cmd, sizeof(pm->oldcmd));
			pm->cmd.buttons = 0;

			i = cmd;

		}

	}

}