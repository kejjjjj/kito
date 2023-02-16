#pragma once

#ifndef tasmovemvnet
#define tasmovemvnet

#include "pch.h"

using segment_list = std::list<recorder_cmd>;

struct entry_point
{
	fvec3 angles;
	fvec3 origin;
	int32_t fps = 0;

	//these have to be copies
	pmove_t pm;
	pml_t pml;
	playerState_s ps;
};

struct segment_s
{
	int32_t start_index = 0;
	int32_t end_index = 0;
	int32_t frame_count = 0;
	char forwardmove = 0;
	char rightmove = 0;
	playerState_s end_ps; //used for the next segment
	segment_list content;
};

class TAS_Movement
{
public:

	void walk_to_beginning();
	//void create_movement_for_segment();

	segment_s* request_current_segment() { return current_segment;}
	size_t get_segment_count() { return segments.size(); }

	void update_movement_for_segment(segment_s& seg);
	void create_first_segment(pmove_t* pm, pml_t* pml);

	void add_segment();

	int32_t segment_index = 0;
	int32_t frame_index = 0;
	entry_point entry;

	bool waiting_for_creation = false;
	
private:
	segment_s* current_segment = 0;
	std::list<segment_s> segments;
	
	

};

#endif