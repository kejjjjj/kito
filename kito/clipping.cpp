#include "pch.h"



void Recorder::StartPlayback()
{
	if (Recorder::recorder_sequence.empty())
		return;
	Com_Printf(CON_CHANNEL_SUBTITLE, "Begin playback..\n");

	Recorder::playback = true;
	Recorder::it = Recorder::recorder_sequence.begin();
	
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
		Com_Printf(CON_CHANNEL_SUBTITLE, "End playback..\n");
		return;
	}
	else if (Recorder::it == Recorder::recorder_sequence.begin())
		Recorder::refTime = cmd->serverTime;

	cmd->angles[0] = it->angles[0];
	cmd->angles[1] = it->angles[1];
	cmd->angles[2] = it->angles[2];
	cmd->serverTime = refTime + (it->serverTime - Recorder::recorder_sequence.front().serverTime);

	com_maxfps->current.integer = it->FPS;

	*(int*)(0x85BD98 + 11454) = cmd->serverTime; //clients->serverTime
	cmd->buttons = it->buttons;
	cmd->forwardmove = it->forwardmove;
	cmd->rightmove = it->rightmove;
	++Recorder::it;
	
	
}
