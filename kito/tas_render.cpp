#include "pch.h"

void TAS_Render::R_Render()
{

	for (size_t i = 0; i < tas->movement.get_segment_count(); i++) 
		R_ShowSegmentPath(tas->movement.get_segment_by_index(i), i == tas->movement.segment_index ?  IM_COL32(0, 255, 0, 255) : IM_COL32(255, 255, 0, 255));
	

	R_DrawHitbox();

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
void TAS_Render::R_DrawHitbox()
{
	if (tas->movement.player_pov)
		return;

	auto data = tas->movement.get_frame_data(tas->movement.frame_index);

	if (!data)
		return;

	box_s box(data->origin, data->mins, data->maxs);
	box.R_DrawConstructedBoxEdges(vec4_t{ 255, 0, 0,255 });
	box.R_DrawConstructedBox(vec4_t{ 255, 0, 0,50 });
}