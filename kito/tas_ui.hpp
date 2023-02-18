#pragma once

#ifndef _tasui
#define _tasui

#include "pch.h"

class TAS_UI
{
public:
	TAS_UI() = default;
	~TAS_UI() = default;

	void UI_Render();
	void UI_SegmentEditor();
	void UI_FrameEditor();
	void UI_OtherControls();
	void UI_ControlsDPAD();

	std::list<ivec2> SegmentToScreen(const segment_s& segment);

private:

};

#endif