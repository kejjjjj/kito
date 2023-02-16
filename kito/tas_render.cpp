#include "pch.h"

void TAS_Render::R_Render()
{
	R_ShowSegmentPath(tas->movement.request_current_segment());

}
void TAS_Render::R_ShowSegmentPath(const segment_s* seg)
{
	if (!seg)
		return;


	ivec2 xy;

	auto points = tas->ui.SegmentToScreen(*seg);
	auto begin = points.begin();
	auto end = points.end();

	for (auto& it = begin; it != end; it++) {
		ivec2 a = *it;


		ivec2 b = *++it;

		if (it == points.end())
			break;

		ImGui::GetBackgroundDrawList()->AddLine(a, b, IM_COL32(255, 255, 0, 255), 3.f);

		--it;

	}


	
}