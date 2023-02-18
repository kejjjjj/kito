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

struct movement_data
{
	//these have to be copies
	pmove_t pm;
	pml_t pml;
	playerState_s ps;
};
struct segment_options
{
	bool strafebot = false;
	bool bhop = false;
};
struct segment_s
{
	int32_t segment_index = 0;
	int32_t start_index = 0;
	int32_t end_index = 0;
	int32_t frame_count = 0;
	char forwardmove = 0;
	char rightmove = 0;
	movement_data end;
	segment_options options;
	segment_list content;
};

class TAS_Movement
{
public:

	//void walk_to_beginning();
	//void create_movement_for_segment();

	segment_s* request_current_segment() { return current_segment;}
	size_t get_segment_count() { return segments.size(); }
	size_t get_frame_count() { return segments.back().end_index-1; }
	void set_current_segment(size_t i) {  if(i < segments.size()) current_segment = &segments[i]; }
	segment_s* get_segment_by_index(const size_t i) { if (i < segments.size()) return &segments[i]; }
	void update_movement_for_segment(segment_s& seg);
	void update_movement_for_each_segment();
	void update_all_segment_indices();
	void pmovesingle(pmove_t* pm, pml_t* pml, segment_s& seg);
	movement_data* initialize_player_data_for_segment(segment_s& seg);

	void create_first_segment(pmove_t* pm, pml_t* pml);

	void add_segment();
	void add_frames_to_current_segment(int32_t& amount);
	void remove_frames_from_current_segment(int32_t& amount);

	int32_t segment_index = 0;
	int32_t frame_index = 0;
	entry_point entry;

	movement_data first_segment, this_segment;

	bool waiting_for_creation = false;
	
private:
	segment_s* current_segment = 0;
	std::vector<segment_s> segments;
	
	

};

#endif