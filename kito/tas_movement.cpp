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

	first_segment.pm = entry.pm;
	first_segment.pml = entry.pml;
	first_segment.ps = entry.ps;

	add_segment();

	//Com_Printf(CON_CHANNEL_SUBTITLE, "new project \"%s\" created", tas->cfile->display_name.c_str());


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
	if (current_segment)
		frame_index = current_segment->end_index;
	else
		frame_index = 0;



	current_segment = &segments.back();
	current_segment->segment_index = segments.size() - 1;

	current_segment->content.resize(seg.frame_count);
	current_segment->options.forwardmove = 127;

	if (segments.size() > 1) {
		auto prev = &segments[current_segment->segment_index - 1];
		current_segment->options.weapon = prev->options.weapon;
		current_segment->options.iWeapon = prev->options.iWeapon;
	}
	else
	{
		auto weapons = cg::G_GetWeaponsList(&first_segment.ps);
		current_segment->options.weapon = weapons.front().second;
		current_segment->options.iWeapon = 0;
	}
	update_movement_for_each_segment();
}
void TAS_Movement::insert_segment()
{
	segment_s seg;

	seg.frame_count = 100;

	seg.start_index = current_segment->end_index + 1;
	seg.end_index = seg.start_index + seg.frame_count;
	seg.segment_index = current_segment->segment_index+1;

	segments.insert(segments.begin() + seg.segment_index, seg);

	auto prev = &segments[seg.segment_index - 1];

	current_segment = &segments[seg.segment_index];
	current_segment->content.resize(seg.frame_count);
	current_segment->options.forwardmove = 127;
	current_segment->options.weapon = prev->options.weapon;
	current_segment->options.iWeapon = prev->options.iWeapon;


	update_movement_for_each_segment();


}
void TAS_Movement::delete_segment()
{
	if (segments.size() < 2)
		return;

	segments.erase(segments.begin() + current_segment->segment_index, segments.begin() + current_segment->segment_index + 1);
	current_segment = &segments[current_segment->segment_index-1];
	frame_index = current_segment->end_index;
	update_movement_for_each_segment();
}
void TAS_Movement::add_frames_to_current_segment(int32_t& amount)
{

	if (!(amount = std::clamp(amount, 0, INT_MAX - current_segment->frame_count))) {
		return;
	}

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

	int i = -1;
	for (auto& it = begin; it != end; ++it) {
		i++;

		if (it == segments.begin()) {
			it->start_index = 0;
			it->end_index = it->start_index + it->frame_count;
			continue;
		}

		auto prev = (it - 1);

		it->start_index = prev->end_index;
		it->end_index = it->start_index + it->frame_count;
		it->segment_index = i;
	}

}
recorder_cmd* TAS_Movement::get_frame_data(const int32_t frame)
{
	if (segments.empty())
		return 0;

	const auto SegmentFromFrame = [frame](std::vector<segment_s>& seg) -> segment_s*
	{
		if (frame == 0)
			return &seg.front();

		for (auto& i : seg) {

			if((frame - i.start_index) <= i.frame_count)
				return &i;
		}
		return 0;
	};

	auto seg = SegmentFromFrame(this->segments);
	if (!seg)
		return &segments.front().content.front();

	auto it = seg->content.begin();

	std::advance(it, frame - seg->start_index);

	return &*it;

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
int weapon_change_time = 0;
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

	

	//if (seg.segment_index) {


	//}
	//ps->weapon = seg.options.weapon;
	//ps->weaponTime = 0;
	//ps->weapFlags &= 0xFFFFFBFF;
	//ps->weaponstate = WEAPON_RAISING;
	//ps->weapAnim = ~ps->weapAnim & 0x200;
	//ps->weaponDelay = 0;

	if (pm->ps->weapon != seg.options.weapon) {
		bool alive; // cc

		ps->weapFlags &= 0xFFFFFFFD;
		ps->pm_flags &= 0xFFFFFDFF;
		alive = ps->pm_type < PM_DEAD;
		ps->weaponTime = 0;
		ps->weaponDelay = 0;
		ps->weaponstate = WEAPON_READY;
		if (alive)
			ps->weapAnim = ~ps->weapAnim & 0x200;

		pm->cmd.weapon = seg.options.weapon;
	}
	int j = 0;
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

		if (j == 1) {
			if (ps->weaponstate == WEAPON_RAISING)
				ps->weaponstate = WEAPON_DROPPING_QUICK;
		}

		cmd.forwardmove = pm->cmd.forwardmove;
		cmd.rightmove = pm->cmd.rightmove;
		cmd.FPS = 1000 / pml->msec;
		cmd.buttons = pm->cmd.buttons;
		cmd.serverTime = pm->cmd.serverTime;
		cmd.angles[0] = pm->cmd.angles[0];
		cmd.angles[1] = pm->cmd.angles[1];
		cmd.angles[2] = pm->cmd.angles[2];
		cmd.mins = pm->mins;
		cmd.maxs = pm->maxs;
		cmd.weapon = ps->weapon;
		cmd.offhand = pm->cmd.offHandIndex;

		memcpy(&pm->oldcmd, &pm->cmd, sizeof(usercmd_s));
		pm->cmd.buttons = 0;

		pm->cmd.serverTime += pml->msec;
		pm->ps->commandTime += pml->msec;

		i = cmd;
		j++;

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

	pm->cmd.forwardmove = options->forwardmove;
	pm->cmd.rightmove = options->rightmove;
	//pm->cmd.weapon= seg.options.weapon;

	if ((pm->ps->pm_flags & PMF_MELEE_CHARGE) != 0)
		pm->cmd.forwardmove = 127;

	if ((ps->pm_flags & PMF_RESPAWNED) != 0)
	{
		pm->cmd.buttons &= 0x1301u;
		pm->cmd.forwardmove = 0;
		pm->cmd.rightmove = 0;
		ps->velocity[0] = 0.0;
		ps->velocity[1] = 0.0;
		ps->velocity[2] = 0.0;
	}
	if (ps->weaponstate == WEAPON_FIRING)
	{
		int weaponIdx = ps->weapon;
		if (weaponIdx)
		{
			if (BG_WeaponNames[weaponIdx]->freezeMovementWhenFiring)
			{
				pm->cmd.buttons &= 0xFFFFFB3F;
				pm->cmd.forwardmove = 0;
				pm->cmd.rightmove = 0;
				ps->velocity[0] = 0.0;
				ps->velocity[1] = 0.0;
				ps->velocity[2] = 0.0;
			}
		}
	}

	ps->pm_flags &= 0xFFFFEFFF;
	if (ps->pm_type >= PM_DEAD)
		pm->tracemask &= 0xFDFF3FFF;

	if ((ps->pm_flags & PMF_PRONE) == 0 || BG_WeaponNames[ps->weapon]->overlayReticle && ps->fWeaponPosFrac > 0.0) {
		ps->pm_flags &= 0xFFFFFDFF;
	}

	if (PM_InteruptWeaponWithProneMove_(ps))
	{
		ps->pm_flags &= 0xFFFFFDFF;
		PM_ExitAimDownSight_(ps);
	}

	if ((ps->pm_flags & PMF_SIGHT_AIMING) != 0 && ps->viewHeightTarget == 11)
	{
		if (BG_WeaponNames[ps->weapon]->overlayReticle)
		{
			if (0.0f >= ps->fWeaponPosFrac)
			{
				pm->cmd.forwardmove = 0;
				pm->cmd.rightmove = 0;
			}
		}
		else
		{
			pm->cmd.forwardmove = 0;
			pm->cmd.rightmove = 0;
		}
	}
	ps->eFlags &= 0xFFFFFFBF;

	if ((ps->pm_flags & PMF_RESPAWNED) == 0)
	{
		if ((!ps->weaponstate || ps->weaponstate == 5) && ps->ammoclip[BG_WeaponNames[ps->weapon]->iClipIndex + 4] && (pm->cmd.buttons & 1) != 0)
			ps->eFlags |= EF_FIRING;
	}
	if (ps->pm_type < PM_DEAD && (pm->cmd.buttons & 0x101) == 0)
		ps->pm_flags &= 0xFFFFFBFF;

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
	fvec3 org, vector;
	
	switch (seg.options.viewangle_type) 
	{
		case viewangle_type::STRAFEBOT:
			if (auto yaw = CG_GetOptYaw(pm, pml)) {
				deltaY = yaw.value() - pm->ps->viewangles[YAW];
			}
			deltaX = -options->strafebot.up;
			break;
		
		case viewangle_type::FIXED_TURNRATE:
			deltaX = -options->fixed_turn.up;
			deltaY = -options->fixed_turn.right;
			break;
		case viewangle_type::AIMLOCK:
			org = ps->origin; org.z += ps->viewHeightCurrent;
			vector = (seg.options.aimlock.target - org).toangles();

			deltaX = vector.x - ps->viewangles[PITCH];
			deltaY = vector.y - ps->viewangles[YAW];
			break;
		default:
			break;
	}
	pm->ps->viewangles[PITCH] += deltaX;
	pm->ps->viewangles[YAW] += deltaY;

	pm->cmd.angles[PITCH] += ANGLE2SHORT(deltaX);
	pm->cmd.angles[YAW] += ANGLE2SHORT(deltaY);

	//pm->ps->weapon = seg.options.weapon;
	//pm->cmd.weapon = pm->ps->weapon;


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

	//if (pm->ps->weapon != seg.options.weapon) {
	//	ps->weaponstate = WEAPON_OFFHAND_START;
	//}

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
			//if (seg.options.bhop)
			//	pm->cmd.buttons |= cmdEnums::jump;
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
void TAS_Movement::set_player_pov(usercmd_s* cmd)
{
	if (!player_pov || !tas->ui.editing)
		return;
	
	auto ok = get_frame_data(frame_index);

	if (!ok)
		return;

	VectorClear(ps_loc->velocity);
	cmd->angles[0] = ok->angles[0];
	cmd->angles[1] = ok->angles[1];
	cmd->angles[2] = ok->angles[2];

	ps_loc->origin[0] = ok->origin.x;
	ps_loc->origin[1] = ok->origin.y;
	ps_loc->origin[2] = ok->origin.z;

}