#include "pch.h"

void TAS_Render::R_Render()
{
	if (cinematic_mode)
		return;

	//for (size_t i = 0; i < tas->movement.get_segment_count(); i++) 
	//	R_ShowSegmentPath(tas->movement.get_segment_by_index(i), i == tas->movement.segment_index ?  IM_COL32(0, 255, 0, 255) : IM_COL32(255, 255, 0, 255));
	//
	auto c = Pixel(130, 130, 0, 255);
	for (auto& i : tas->movement.segments) {

		R_ShowSegmentPathColored(&i, c);

	 }

	R_DrawHitbox();
	R_AngleArrow();

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
void TAS_Render::R_ShowSegmentPathColored(const segment_s* seg, Pixel& refColor)
{
	//float average{};
	
	if (!seg)
		return;
	
	auto data = ([](const segment_s& segment)-> std::list<std::pair<ivec2, float>>
	{
		std::list<std::pair<ivec2, float>> points;
		for (const auto& i : segment.content) {
			if (auto xy = cg::WorldToScreen(i.origin)) {
				points.push_back(std::make_pair(xy.value(), fvec2(i.velocity.x, i.velocity.y).mag()));
			}else
				points.push_back(std::make_pair(ivec2(-1,-1), fvec2(i.velocity.x, i.velocity.y).mag()));


		}
		return points;
	})(*seg);

	//for (auto& [x, y] : data) {
	//	average += y;
	//} average /= data.size();

	float pv = data.begin()->second;
	ivec2 pp = data.begin()->first;
	Pixel c;
	for (const auto& [p, v] : data) {
		int r = refColor.r, g = refColor.g;
		refColor.b = 0;


		if (v < pv) {
			
			r = std::clamp(r + int(pv - v), 0, 255);
			g = std::clamp(g - int(pv - v), 0, 255);
		}
		else if (v > pv) {

			r = std::clamp(r - int(v - pv), 0, 255);
			g = std::clamp(g + int(v - pv), 0, 255);

		}

		refColor.r = r;
		refColor.g = g;

		*(unsigned int*)&c = refColor.packed(); //ok

		if (seg->segment_index == tas->movement.request_current_segment()->segment_index) 
			c.r = c.g = c.b = 255;
		

		if (p != ivec2(-1, -1) && pp != ivec2(-1,-1))
			ImGui::GetBackgroundDrawList()->AddLine(pp, p, c.packed(), 3.f);

		pp = p;
		pv = v;
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
void TAS_Render::R_AngleArrow()
{
	if (tas->movement.player_pov)
		return;

	const auto data = tas->movement.get_frame_data(tas->movement.frame_index);

	if (!data)
		return;

	auto org = data->origin;
	org.z += data->maxs.z / 2;

	const auto fwd = org + (data->viewangles.toforward() * 50);
	
	if (const auto xy = cg::WorldToScreen(org)) {
		if (const auto xy2 = cg::WorldToScreen(fwd)) {
			ImGui::GetBackgroundDrawList()->AddLine(xy.value(), xy2.value(), 0xFFFFFFFF, 1);
		}
	}


}

void TAS_Render::R_FrameData()
{
	if (cinematic_mode)
		return;

	auto frame = tas->movement.get_frame_data(tas->movement.frame_index);

	if (!frame)
		return;

	char buffer[256];

	

	if (auto xy = cg::WorldToScreen(frame->origin)) {
		sprintf_s(buffer, "XY Speed: %.6f\nZ: %.6f\nweaponTime: %d\nstamina: %d\nserverTime: %i\nElapsed time: %.6f", fvec2(frame->velocity.x, frame->velocity.y).mag(), frame->velocity.z, frame->weaponTime, frame->sprintStamina, frame->serverTime,(float)(frame->serverTime - tas->movement.entry.pm.cmd.serverTime) / 1000 );
		r::R_DrawTextWithEffects(buffer, "fonts/normalfont", xy.value().x, xy.value().y, 1.25f, 1.25f, 0, vec4_t{ 1,1,1,1 }, 3, vec4_t{ 0,0,0,1 });
	}

}