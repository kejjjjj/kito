#pragma once

#ifndef clipping__
#define clipping__

#include "pch.h"

struct recorder_cmd
{
	int serverTime;
	int angles[3];
	int32_t buttons;
	char forwardmove;
	char rightmove;
	int FPS;
};

struct Recorder
{
	Recorder() = default;
	~Recorder() = default;

	void StartRecording();
	void StopRecording();
	bool IsRecording() { return recording; }
	bool IsPlayback() { return playback; }

	void StartPlayback();
	void Record(usercmd_s* cmd);
	void Playback(usercmd_s* cmd);

	std::list<recorder_cmd> recorder_sequence;

private:
	bool recording = 0;
	bool playback = 0;
	std::list<recorder_cmd>::iterator it;
	int refTime = 0;
};

inline Recorder recorder;
#endif