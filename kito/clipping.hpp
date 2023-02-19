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
	fvec3 viewangles;
	fvec3 origin;
	fvec3 velocity;
};

struct Recorder
{
	explicit Recorder(std::list<recorder_cmd> input) : recorder_sequence(input) { 
		Recorder::StartPlayback();
	}
	~Recorder() = default;


	std::list<recorder_cmd> recorder_sequence;
	bool IsPlayback() { return playback; }

	void StartPlayback();
	void Playback(usercmd_s* cmd);
	recorder_cmd* CurrentCmd() { 
		if (!playback) 
			return 0; 

		return &*(it); 
	}

private:
	bool playback = 0;
	std::list<recorder_cmd>::iterator it;
	int refTime = 0;
};
#endif