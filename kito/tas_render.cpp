#include "pch.h"

void TAS_Render::R_Render()
{

	for (size_t i = 0; i < tas->movement.get_segment_count(); i++) 
		R_ShowSegmentPath(tas->movement.get_segment_by_index(i), i == tas->movement.segment_index ?  IM_COL32(0, 255, 0, 255) : IM_COL32(255, 255, 0, 255));
	


}
void TAS_Render::R_ShowSegmentPath(const segment_s* seg, unsigned int color)
{
	if (!seg)
		return;

	auto points = tas->ui.SegmentToScreen(*seg);
	auto begin = points.begin();
	auto end = points.end();

	for (auto& it = begin; it != end; it++) {
		ivec2 a = *it;
		ivec2 b = *++it;

		if (it == points.end())
			break;

		ImGui::GetBackgroundDrawList()->AddLine(a, b, color, 3.f);

		--it;

	}


	
}