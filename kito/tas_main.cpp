#include "pch.h"

void TAS::Init()
{
	TAS::TAS_SetupHardcodedFont();



}

void TAS::TAS_SetupHardcodedFont()
{
	const std::string name = "conduit_itc_light1.ttf";
	const std::string full_path = fs::GetExePath() + "\\SP_TAS\\resources\\fonts";

	auto c_str = std::string(full_path + "\\" + name);

	if (!fs::F_FileExists(full_path, name)) {
		std::cout << "filename: " << c_str.c_str() << '\n';
		Com_Error(ERR_DISCONNECT, "unable to find font: '%s'\n", c_str.c_str());
		return;
	}

	ImGui::GetIO().Fonts->AddFontFromFileTTF(c_str.c_str(), 24);

}