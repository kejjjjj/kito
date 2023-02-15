#pragma once

#ifndef tasmovemvnet
#define tasmovemvnet

#include "pch.h"

using segment_list = std::list<recorder_cmd>;



class TAS_Movement
{
public:

	struct entry_point
	{
		fvec3 angles;
		fvec3 origin;
		int32_t fps = 0;
	};
	
	void walk_to_beginning();
	void create_movement_for_segment();

	auto* request_current_segment() { return &current_segment;}
	size_t get_segment_count() { return segments.size(); }


	int32_t segment_index = 0;
	int32_t frame_index = 0;
	
private:
	std::list<recorder_cmd> current_segment;
	std::list<segment_list> segments;
	entry_point entry;
};

#endif