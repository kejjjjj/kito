#include "pch.h"

void TAS_UI::UI_Render()
{
	//no existing project
	if (!tas->filesystem || tas->movement.waiting_for_creation) {

		if (ImGui::ButtonCentered("Create Project") && !tas->movement.waiting_for_creation) { //the 2nd condition could cause memory bugs if it wasn't there
			tas->filesystem = new TAS_FileSystem("test");

			if (!tas->filesystem->valid) {
				delete tas->filesystem;
				tas->filesystem = 0;
			}

			tas->movement.waiting_for_creation = true;
		}

		return;
	}

	TAS_UI::UI_SegmentEditor();
	TAS_UI::UI_FrameEditor();
	TAS_UI::UI_OtherControls();
}

void TAS_UI::UI_SegmentEditor()
{
	auto cur_seg = tas->movement.request_current_segment();
	if (!cur_seg) {
		Com_Error(ERR_DROP, "tas->movement.request_current_segment() == nulltptr");
		return;
	}

	if (ImGui::SliderInt_22("Segment", &tas->movement.segment_index, 0, tas->movement.get_segment_count()-1)) {
		tas->movement.set_current_segment(tas->movement.segment_index);
		tas->movement.frame_index = cur_seg->start_index;
	}
	if (ImGui::Button("Add"))
		tas->movement.add_segment();
		
	ImGui::SameLine(); 
	ImGui::Button("Insert"); 
	
	ImGui::SameLine(); 
	ImGui::Button("Remove Selected");

	ImGui::NewLine();
	//ImGui::Separator();




}
void TAS_UI::UI_FrameEditor()
{
	static int add_or_remove_frames_count = 0;
	auto cur_seg = tas->movement.request_current_segment();

	ImGui::SliderInt_22("Frame", &tas->movement.frame_index, 0, tas->movement.get_frame_count());
	ImGui::PushItemWidth(130);
	ImGui::InputInt("Count", &add_or_remove_frames_count, 1, 100);

	ImGui::SameLine();
	if (ImGui::Button("Add##01"))
		tas->movement.add_frames_to_current_segment(add_or_remove_frames_count);

	ImGui::SameLine();
	if (ImGui::Button("Remove##01"))
		tas->movement.remove_frames_from_current_segment(add_or_remove_frames_count);

	ImGui::NewLine();
	ImGui::Separator();

}
void TAS_UI::UI_OtherControls()
{
	ImGui::BeginGroup();

	auto options = &tas->movement.request_current_segment()->options;

	if (ImGui::Checkbox2("strafebot", &options->strafebot))
		tas->movement.update_movement_for_each_segment();

	if(ImGui::Checkbox2("bunnyhop", &options->bhop))
		tas->movement.update_movement_for_each_segment();

	ImGui::EndGroup();

	UI_ControlsDPAD();


}
void TAS_UI::UI_ControlsDPAD()
{
	auto cur_seg = tas->movement.request_current_segment();

	const auto constructkey = [](char& dir, char value, const char* name) -> void {

		if (dir == value)
			ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0.f, 0.f, 0.f, 0.7f);

		if (ImGui::Button(name, ImVec2(40,40))) {

			if (dir == value)
				dir = NULL;
			else
				dir = value;

			tas->movement.update_movement_for_each_segment();
		}

		ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(30.f / 255, 30.f / 255, 41.f / 255, 1.f);
	};

	ImGui::SameLine();
	ImGui::Text("\t  ");
	ImGui::SameLine();

	ImGui::BeginGroup();
	ImGui::Text("\t   ");
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(0.2f, 0));
	ImGui::SameLine();
	constructkey(cur_seg->forwardmove, 127, "W##01");
	constructkey(cur_seg->rightmove, -127, "A##01");

	ImGui::SameLine();
	constructkey(cur_seg->forwardmove, -127, "S##01");

	ImGui::SameLine();
	constructkey(cur_seg->rightmove, 127, "D##01");

	ImGui::EndGroup();

	//ImGui::NewLine();
	//ImGui::Separator();

	//ImGui::Text("Debug:\n");

	//ImGui::Text("start: %d", cur_seg->start_index);
	//ImGui::Text("end: %d", cur_seg->end_index);
	//ImGui::Text("frames: %d", cur_seg->frame_count);

}
std::list<ivec2> TAS_UI::SegmentToScreen(const segment_s& segment)
{
	std::list<ivec2> points;
	ivec2 xy;
	for (auto& i : segment.content) {

		if (cg::WorldToScreen(i.origin, &xy)) {
			points.push_back(xy);
		}

	}
	return points;
}