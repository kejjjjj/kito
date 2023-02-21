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



	first_segment.pm = entry.pm;
	first_segment.pml = entry.pml;
	first_segment.ps = entry.ps;

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
	current_segment->segment_index = segments.size() - 1;
	current_segment->content.resize(seg.frame_count);
	current_segment->forwardmove = 127;
	update_movement_for_each_segment();
}
void TAS_Movement::add_frames_to_current_segment(int32_t& amount)
{


	if (!(amount = std::clamp(amount, 0, INT_MAX - current_segment->frame_count))) {
		std::cout << "NOPE\n";
		return;
	}

	std::cout << "adding: " << amount << '\n';
	current_segment->frame_count += amount;
	current_segment->end_index = current_segment->start_index + current_segment->frame_count;

	current_segment->content.resize(current_segment->frame_count);


	update_movement_for_each_segment();

}
void TAS_Movement::remove_frames_from_current_segment(int32_t& amount)
{
	if (!(amount = std::clamp(amount, 0, INT_MAX - current_segment->frame_count)))
		return;

	current_segment->frame_count -= amount;

	if (current_segment->frame_count < 1) 
		current_segment->frame_count = 1;

	current_segment->end_index = current_segment->start_index + current_segment->frame_count;
	current_segment->content.resize(current_segment->frame_count);

	update_movement_for_each_segment();


}
//fix all frame gaps/overlaps in-between segments
//called when changing the framecount of a segment
void TAS_Movement::update_all_segment_indices()
{
	if (segments.empty())
		return;

	auto begin = segments.begin();
	auto end = segments.end();

	for (auto& it = begin; it != end; ++it) {
		
		if (it == segments.begin())
			continue;

		auto prev = (it - 1);

		it->start_index = prev->end_index + 1;
		it->end_index = it->start_index + it->frame_count;

	}

}
void TAS_Movement::update_movement_for_each_segment()
{
	update_all_segment_indices();
	std::for_each(segments.begin(), segments.end(), [this](segment_s& seg) {
		TAS_Movement::update_movement_for_segment(seg); });
}
movement_data* TAS_Movement::initialize_player_data_for_segment(segment_s& seg)
{
	if (segments.empty())
		return 0;

	//fvec3 v = fvec3(entry.pm.ps->origin);

	//std::cout << std::format("entry: [{}, {}, {}]\n", v.x, v.y, v.z);

	//first element
	if (!seg.segment_index) {
		memcpy_s(&first_segment.pm, sizeof(pmove_t), &entry.pm, sizeof(pmove_t));
		memcpy_s(&first_segment.pml, sizeof(pml_t), &entry.pml, sizeof(pml_t));
		memcpy_s(&first_segment.ps, sizeof(playerState_s), &entry.ps, sizeof(playerState_s));
		first_segment.pm.ps = &first_segment.ps;

		return &first_segment;
	}

	const auto prev = &segments[seg.segment_index-1];

	memcpy_s(&this_segment.pm, sizeof(pmove_t), &prev->end.pm, sizeof(pmove_t));
	memcpy_s(&this_segment.pml, sizeof(pml_t), &prev->end.pml, sizeof(pml_t));
	memcpy_s(&this_segment.ps, sizeof(playerState_s), &prev->end.ps, sizeof(playerState_s));
	this_segment.pm.ps = &this_segment.ps;

	return &this_segment;

}
void TAS_Movement::update_movement_for_segment(segment_s& seg)
{
	auto& list = seg.content;

	if (list.empty())
		return;

	movement_data* data = initialize_player_data_for_segment(seg);

	pmove_t* pm = &data->pm;
	pml_t* pml = &data->pml;
	playerState_s* ps = pm->ps;
	recorder_cmd cmd;

	for (auto& i : list) {

		if (!pm || !pml) {
			Com_Printf(CON_CHANNEL_SUBTITLE, "yo wtf!\n");
			break;
		}
		pmovesingle(pm, pml, seg, i);




		cmd.viewangles = ps->viewangles;
		cmd.origin = ps->origin;
		cmd.velocity = ps->velocity;

		if (pm->cmd.forwardmove > 0)
			pm->cmd.forwardmove = 127;
		else if (pm->cmd.forwardmove < 0)
			pm->cmd.forwardmove = -127;

		if (pm->cmd.rightmove > 0)
			pm->cmd.rightmove = 127;
		else if (pm->cmd.rightmove < 0)
			pm->cmd.rightmove = -127;

		cmd.forwardmove = pm->cmd.forwardmove;
		cmd.rightmove = pm->cmd.rightmove;
		cmd.FPS = 1000 / pml->msec;
		cmd.buttons = pm->cmd.buttons;
		cmd.serverTime = pm->cmd.serverTime;
		cmd.angles[0] = pm->cmd.angles[0];
		cmd.angles[1] = pm->cmd.angles[1];
		cmd.angles[2] = pm->cmd.angles[2];


		memcpy(&pm->oldcmd, &pm->cmd, sizeof(usercmd_s));
		pm->cmd.buttons = 0;

		pm->cmd.serverTime += pml->msec;
		pm->ps->commandTime += pml->msec;

		i = cmd;

		

	}
	memcpy_s(&seg.end.pm, sizeof(pmove_t), pm, sizeof(pmove_t));
	memcpy_s(&seg.end.pml, sizeof(pml_t), pml, sizeof(pml_t));
	memcpy_s(&seg.end.ps, sizeof(playerState_s), pm->ps, sizeof(playerState_s));
	seg.end.pm.ps = &seg.end.ps;
}
using namespace cg;
void TAS_Movement::pmovesingle(pmove_t* pm, pml_t* pml, segment_s& seg, recorder_cmd& rcmd)
{
	playerState_s* ps = pm->ps;
	auto options = &seg.options;
	static dvar_s* mantle_enable = Dvar_FindMalleableVar("mantle_enable");

	pm->cmd.forwardmove = seg.forwardmove;
	pm->cmd.rightmove = seg.rightmove;

	if (PM_InteruptWeaponWithProneMove_(ps))
	{
		ps->pm_flags &= 0xFFFFFDFF;
		PM_ExitAimDownSight_(ps);
	}

	pml->previous_origin[0] = ps->origin[0];
	pml->previous_origin[1] = ps->origin[1];
	pml->previous_origin[2] = ps->origin[2];
	pml->previous_velocity[0] = ps->velocity[0];
	pml->previous_velocity[1] = ps->velocity[1];
	pml->previous_velocity[2] = ps->velocity[2];

	pml->msec = 1000 / 125; //simulate 125fps
	pml->frametime = (float)pml->msec / 1000.f;

	pm->cmd.buttons = options->hold_buttons;

	//if (seg.options.bhop)
	//	pm->cmd.buttons |= cmdEnums::jump;
	//else if ((pm->cmd.buttons & cmdEnums::jump) == 0)
	//	pm->cmd.buttons |= cmdEnums::sprint;


	float deltaX = 0;
	float deltaY = 0;

	if (seg.options.viewangle_type == viewangle_type::STRAFEBOT) {
		float yaw = CG_GetOptYaw(pm, pml);
		if (yaw != -400) {
			deltaY = yaw - pm->ps->viewangles[YAW];
		}
		deltaX = options->strafebot.up;

	}
	else if (seg.options.viewangle_type == viewangle_type::FIXED_TURNRATE) {
		deltaX = options->fixed_turn.up;
		deltaY = -options->fixed_turn.right;
	}

	pm->ps->viewangles[PITCH] += deltaX;
	pm->ps->viewangles[YAW] += deltaY;

	pm->cmd.angles[PITCH] += ANGLE2SHORT(deltaX);
	pm->cmd.angles[YAW] += ANGLE2SHORT(deltaY);

	PM_AdjustAimSpreadScale_(pm, pml);
	PM_UpdateViewAngles(ps, pml->msec, &pm->cmd, pm->handler);

	AngleVectors(pm->ps->viewangles, pml->forward, pml->right, pml->up); //set viewangles
	

	char fwd = pm->cmd.forwardmove;
	if (fwd >= 0)
	{
		if (fwd > 0 || pm->cmd.rightmove)
			ps->pm_flags &= 0xFFFFFFDF;
	}
	else
	{
		ps->pm_flags |= PMF_BACKWARDS_RUN;
	}


	//if (seg.options.viewangle_type == viewangle_type::STRAFEBOT) 
	//	rcmd.angles[YAW] = ANGLE2SHORT(pm->ps->viewangles[YAW]);

	if ((ps->pm_flags & PMF_MANTLE) == 0) {
		PM_UpdateAimDownSightFlag_(pm, pml);
		PM_UpdateSprint_(pm);
		PM_UpdatePlayerWalkingFlag_(pm);
		PM_CheckDuck_(pm, pml);
		PM_GroundTrace_(pm, pml);
	}

	Mantle_Check(pm, pml);

	if ((ps->pm_flags & PMF_MANTLE) != 0) {

		if ((ps->pm_flags & PMF_LADDER) != 0)
			ps->pm_flags = ps->pm_flags & 0xFFFFFFF7 | PMF_LADDER_FALL;
		ps->groundEntityNum = 2175;
		pml->groundPlane = 0;
		pml->walking = 0;

		PM_UpdateAimDownSightFlag_(pm, pml);
		PM_UpdateSprint_(pm);
		PM_UpdatePlayerWalkingFlag_(pm);
		PM_CheckDuck_(pm, pml);
		if (mantle_enable->current.enabled)
			Mantle_Move(ps, pml);

		PM_Weapon_(pm, pml);

	}
	else {


		
		PM_UpdatePronePitch_(pm, pml);
		PM_DropTimers(ps, pml);
		//if ( ps->pm_type >= PM_DEAD && pml->walking )
			//PM_DeadMove(ps);
		PM_CheckLadderMove_(pm, pml);

		if ((ps->pm_flags & PMF_LADDER) != 0)
		{
			PM_LadderMove_(pm, pml);
		}
		else if (pml->walking) {
			if (seg.options.bhop)
				pm->cmd.buttons |= cmdEnums::jump;
			PM_WalkMove_f(pm, pml);
		}
		else {
			PM_AirMove_f(pm, pml);
		}
		PM_GroundTrace_(pm, pml); //call groundtrace after 
		PM_Footsteps_(pm, pml);
		PM_Weapon_(pm, pml);
		PM_FoliageSnd_(pm);
		PM_OverBounce(pm, pml);
		//Sys_SnapVector(pm->ps->velocity); //Sys_SnapVector | not called in singleplayer
	}

	//int _yaw = pm->cmd.angles[1];
	//float __yaw = ps->viewangles[YAW];

	//if (__yaw < 0) {
	//	__yaw += 180;
	//	__yaw = (__yaw + 180 % 360);
	//}

	//_yaw -= _yaw * 2 - ANGLE2SHORT(__yaw);

	


}
std::list<recorder_cmd> TAS_Movement::create_a_list_from_segments()
{
	std::list<recorder_cmd> list;

	for (auto& i : segments) {
		for (auto& content : i.content) {
			list.push_back(content);
		}
	}

	return list;
}