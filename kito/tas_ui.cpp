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


	ImGui::SliderInt_2("Segment", &tas->movement.segment_index, 0, tas->movement.get_segment_count());
	if (ImGui::Button("Add"))
		tas->movement.add_segment();
		
	ImGui::SameLine(); 
	ImGui::Button("Insert"); 
	
	ImGui::SameLine(); 
	ImGui::Button("Delete");

	ImGui::NewLine();
	ImGui::Separator();

	if (ImGui::ButtonCentered("try to move")) {
		
		fvec3 org = tas->movement.entry.pm.ps->origin;

		printf("org: { %.3f, %.3f, %.3f }\n", org.x, org.y, org.z);

		auto segment = tas->movement.request_current_segment();

		segment->forwardmove = 127;

		tas->movement.update_movement_for_segment(*segment);

		org = tas->movement.entry.pm.ps->origin;

		printf("new org: { %.3f, %.3f, %.3f }\n", org.x, org.y, org.z);

	}


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