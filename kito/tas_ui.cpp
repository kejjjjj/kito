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
}

void TAS_UI::UI_SegmentEditor()
{
	static int add_or_remove_frames_count = 0;

	if (ImGui::SliderInt_22("Segment", &tas->movement.segment_index, 0, tas->movement.get_segment_count()-1)) {
		tas->movement.set_current_segment(tas->movement.segment_index);
	}
	if (ImGui::Button("Add"))
		tas->movement.add_segment();
		
	ImGui::SameLine(); 
	ImGui::Button("Insert"); 
	
	ImGui::SameLine(); 
	ImGui::Button("Remove Selected");

	ImGui::NewLine();
	ImGui::Separator();

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
void TAS_UI::UI_FrameEditor()
{

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