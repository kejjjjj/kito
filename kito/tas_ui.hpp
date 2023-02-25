#pragma once

#ifndef _tasui
#define _tasui

#include "pch.h"

inline std::vector<std::pair<std::string, int>> cmd_buttons
{
	std::make_pair("+attack", cmdEnums::fire),
	std::make_pair("+melee", cmdEnums::melee),
	std::make_pair("+use", cmdEnums::activate),
	std::make_pair("+reload", cmdEnums::reload),
	std::make_pair("+leanleft", cmdEnums::lean_left),
	std::make_pair("+lean_right", cmdEnums::lean_right),
	std::make_pair("+prone", cmdEnums::prone),
	std::make_pair("+crouch", cmdEnums::crouch),
	std::make_pair("+jump", cmdEnums::jump),
	std::make_pair("+sprint", cmdEnums::sprint),
	std::make_pair("+frag", cmdEnums::frag),
	std::make_pair("+special", cmdEnums::special_grenade),
	std::make_pair("+ads_hold", cmdEnums::ads_hold)
};

class TAS_UI
{
public:
	TAS_UI() = default;
	~TAS_UI() = default;

	void UI_Render();
	void UI_SaveList();
	void UI_SegmentEditor();
	void UI_FrameEditor();
	void UI_OtherControls();
	void UI_ControlsDPAD();

	void UI_AngleControls_Fixed(segment_options* options);
	void UI_AngleControls_Strafebot(segment_options* options);
	void UI_AngleControls_Aimlock(segment_options* options);

	int32_t UI_HoldButtons();
	int32_t UI_SpamButtons();

	std::list<ivec2> SegmentToScreen(const segment_s& segment);

	void UI_FileSystem();

	bool editing = false;
	bool draw_save_list = false;
private:

};

#endif