#include "pch.h"


void Recorder::StartRecording()
{
	Recorder::recorder_sequence.clear();
	Recorder::recorder_sequence.resize(0);
	Recorder::playback = false;
	Recorder::recording = true;
	Com_Printf(CON_CHANNEL_SUBTITLE, "Recording..\n");
}
void Recorder::StopRecording()
{
	Com_Printf(CON_CHANNEL_SUBTITLE, "Stop recording..\n");
	Recorder::recording = false;
}
void Recorder::StartPlayback()
{
	Recorder::recording = false;
	if (Recorder::recorder_sequence.empty())
		return;
	Com_Printf(CON_CHANNEL_SUBTITLE, "Begin playback..\n");

	Recorder::playback = true;
	Recorder::it = Recorder::recorder_sequence.begin();
	
}
void Recorder::Record(usercmd_s* cmd)
{
	recorder_cmd _cmd;
	_cmd.serverTime = cmd->serverTime;
	_cmd.angles[0] = cmd->angles[0];
	_cmd.angles[1] = cmd->angles[1];
	_cmd.angles[2] = cmd->angles[2];

	_cmd.buttons = cmd->buttons;
	_cmd.forwardmove = cmd->forwardmove;
	_cmd.rightmove = cmd->rightmove;

	Recorder::recorder_sequence.push_back(_cmd);
}
void Recorder::Playback(usercmd_s* cmd)
{

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
	*(int*)(0x85BD98 + 11454) = cmd->serverTime; //clients->serverTime
	cmd->buttons |= it->buttons;
	cmd->forwardmove = it->forwardmove;
	cmd->rightmove = it->rightmove;
	++Recorder::it;
	
	
}
