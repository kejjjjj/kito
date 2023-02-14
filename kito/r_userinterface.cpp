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
	}

	ImGui::GetStyle().Colors[ImGuiCol_CheckMark] = ImVec4(1.f, 0.f, 1.f, 1.f);

	if (!open)
		return;

	ImGui::Begin("[ALPHA] 1_kej_v2 - github.com/kejjjjj/", 0);
	
	static bool var = 0, var1 = 0, var2 = 0, var3 = 0;

	ImGui::Checkbox2("button1", &var);
	ImGui::SameLine();  
	ImGui::Checkbox2("button2", &var1);

	ImGui::Checkbox2("button3", &var2);
	ImGui::SameLine();
	ImGui::Checkbox2("button4", &var3);

	ImGui::End();

}
void UI::UI_ColorTheme(const float transparency)
{
}