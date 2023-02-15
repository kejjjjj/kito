#include "pch.h"

bool UI::UI_Checkbox(bool& var)
{

}

void UI::UI_Draw()
{
	static bool open = false;

	if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
		open = !open;
		IN_ActivateMouse(!open);
		UI_SetSystemCursorPos();
		ImGui::GetIO().MouseDrawCursor = open;
		UI::UI_ColorTheme();
	}

	if (!open)
		return;

	ImGui::Begin("TAS", 0);

	tas->ui.UI_Render();

	ImGui::End();

}
void UI::UI_ColorTheme(const float transparency)
{
	const ImVec4 widget_color = ImVec4(127.f / 255, 21.f / 255, 60.f / 255, transparency);
	const ImVec4 main_color = ImVec4(30.f / 255, 30.f / 255, 41.f / 255, transparency);
	const ImVec4 window_color = ImVec4(33.f / 255, 34.f / 255, 51.f / 255, transparency);

	auto &style = ImGui::GetStyle();
	auto color = style.Colors;
	style.FrameRounding = 10.f;
	style.WindowRounding = 10.f;
	style.ChildRounding = 10.f;
	style.TabRounding = 10.f;
	style.GrabRounding = 10.f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

	color[ImGuiCol_CheckMark] = widget_color;
	color[ImGuiCol_SliderGrabActive] = widget_color;
	color[ImGuiCol_SliderGrab] = widget_color;

	color[ImGuiCol_TitleBg] = main_color;
	color[ImGuiCol_TitleBgActive] = main_color;
	color[ImGuiCol_FrameBgActive] = main_color;
	color[ImGuiCol_FrameBg] = main_color;
	color[ImGuiCol_FrameBgHovered] = main_color;

	color[ImGuiCol_WindowBg] = window_color;

	color[ImGuiCol_ResizeGrip] = main_color;
	color[ImGuiCol_ResizeGripActive] = main_color;
	color[ImGuiCol_Button] = main_color;
	color[ImGuiCol_ButtonActive] = main_color;
	color[ImGuiCol_ButtonHovered] = main_color;


}