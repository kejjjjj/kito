#include "pch.h"

void TAS_UI::UI_Render()
{
	TAS_UI::UI_SegmentEditor();
	TAS_UI::UI_FrameEditor();
}

void TAS_UI::UI_SegmentEditor()
{

	ImGui::SliderInt_2("Segment", &tas->movement.segment_index, 0, tas->movement.get_segment_count() + 5);
	ImGui::Button("add"); ImGui::SameLine(); ImGui::Button("insert"); ImGui::SameLine(); ImGui::Button("delete"); ImGui::SameLine();


}
void TAS_UI::UI_FrameEditor()
{

}