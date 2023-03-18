#include "pch.h"



void Recorder::StartPlayback()
{
	if (Recorder::recorder_sequence.empty())
		return;
	//Com_Printf(CON_CHANNEL_SUBTITLE, "Begin playback..\n");

	Recorder::playback = true;
	Recorder::it = Recorder::recorder_sequence.begin();
	frame = 0;
}
//void Recorder::Record(usercmd_s* cmd)
//{
//	static dvar_s* com_maxfps = Dvar_FindMalleableVar("com_maxfps");
//
//	recorder_cmd _cmd;
//	_cmd.serverTime = cmd->serverTime;
//	_cmd.angles[0] = cmd->angles[0];
//	_cmd.angles[1] = cmd->angles[1];
//	_cmd.angles[2] = cmd->angles[2];
//
//	_cmd.buttons = cmd->buttons;
//	_cmd.forwardmove = cmd->forwardmove;
//	_cmd.rightmove = cmd->rightmove;
//	_cmd.FPS = int(*(float*)0x1290F78);
//
//	Recorder::recorder_sequence.push_back(_cmd);
//}
void Recorder::Playback(usercmd_s* cmd)
{
	static dvar_s* com_maxfps = Dvar_FindMalleableVar("com_maxfps");

	if (Recorder::it == Recorder::recorder_sequence.end()) {
		Recorder::playback = false;
		if(!tas->render.cinematic_mode)
			Com_Printf(CON_CHANNEL_SUBTITLE, "End playback..\n");
		return;
	}
	else if (refresh_start_time) {
		Recorder::refTime = cmd->serverTime;
		refresh_start_time = false;
	}

	CalibrateSegment(cmd);

	cmd->angles[0] = it->angles[0];
	cmd->angles[1] = it->angles[1];
	cmd->angles[2] = it->angles[2];
	cmd->serverTime = refTime + (it->serverTime - Recorder::recorder_sequence.front().serverTime);
	cmd->weapon = it->weapon;
	cmd->offHandIndex = it->offhand;
	com_maxfps->current.integer = it->FPS;

	*(int*)(0x85BD98 + 11454) = cmd->serverTime; //clients->serverTime
	cmd->buttons = it->buttons;
	cmd->forwardmove = it->forwardmove;
	cmd->rightmove = it->rightmove;
	++Recorder::it;
	++frame;
	
	
}
int Recorder::SegmentIndexFromIt()
{
	
}
void Recorder::CalibrateSegment(usercmd_s* cmd)
{
	//TODO:: CALL THIS FROM PMOVESINGLE INSTEAD OF RECORDER

	auto& movement = tas->movement;
	auto ps = cg::predictedPlayerState;
	std::optional<int> s_index_o;
	if (movement.calibration_required.empty() || !ps)
		return;

	if (!(s_index_o = movement.get_segmentindex_from_frame(frame)))
		return;

	const int s_index = s_index_o.value();
	const auto it = movement.calibration_required.find(s_index);

	if (it == movement.calibration_required.end())
		return;

	auto seg = movement.get_segment_by_index(s_index);

	recorder_cmd rcmd;

	rcmd.serverTime = cmd->serverTime;
	VectorCopy(cmd->angles, rcmd.angles);
	rcmd.buttons = cmd->buttons;
	rcmd.forwardmove = cmd->forwardmove;
	rcmd.rightmove = cmd->rightmove;
	rcmd.FPS = seg->options.FPS;
	rcmd.weapon = cmd->weapon;
	rcmd.offhand = cmd->offHandIndex;
	rcmd.viewangles = ps->viewangles;
	rcmd.origin = ps->origin;
	rcmd.velocity = ps->velocity;

}