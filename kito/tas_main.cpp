#include "pch.h"

void TAS::Init()
{
	TAS::TAS_CreateEssentialDirectories();
	TAS::TAS_SetupHardcodedFont();

	fonts_loaded = true;
}
std::optional<ImFont*> TAS::FetchFont(const char* name)
{
	for (const auto& i : fonts) {
		if (!strcmp(name, i.second))
			return i.first;
	}

	return std::nullopt;
}
void TAS::TAS_LoadFont(const char* _name, const std::string& name, float scale)
{
	ImGuiIO* io = &ImGui::GetIO();

	const std::string full_path = RECORDING_DIRECTORY() + "\\resources\\fonts";
	auto c_str = std::string(full_path + "\\" + name);

	if (!fs::F_FileExists(c_str)) {
		std::cout << "filename: " << c_str.c_str() << '\n';
		Com_Error(ERR_DISCONNECT, "unable to find font: '%s'\n", c_str.c_str());
		return;
	}
	if (!io->Fonts) {
		Com_Error(ERR_DROP, "!io->Fonts!");
		return;
	}
	auto font = io->Fonts->AddFontFromFileTTF(c_str.c_str(), scale);

	if (!font) {
		std::cout << "font: " << std::quoted(c_str) << " does not exist!\n";
		Com_Error(ERR_DROP, "font '%s' does not exist!", c_str.c_str());
		return;
	}

	fonts.push_back(std::make_pair(font, _name));

	std::cout << "font: " << std::quoted(_name) << " added!\n";

}
void TAS::TAS_SetupHardcodedFont()
{
	TAS_LoadFont("conduit", "conduit_itc_light1.ttf");
	TAS_LoadFont("font90", "font_90.ttf");

	
	//if (auto font = FetchFont("conduit"))
	//	return ImGui::SetCurrentFont(font);
	
	//return Com_Error(ERR_DROP, "auto font = FetchFont(\"conduit\") == std::nullopt_t\n");

}

void TAS::TAS_CreateEssentialDirectories()
{

	const std::string full_path = fs::GetExePath() + "\\SP_TAS";

	TAS::TAS_CreateSubDirectory("");
	TAS::TAS_CreateSubDirectory("recordings");
	TAS::TAS_CreateSubDirectory("resources");
	TAS::TAS_CreateSubDirectory("resources\\fonts");

}
void TAS::TAS_CreateSubDirectory(const std::string& name)
{

	const std::string full_path = fs::GetExePath() + "\\SP_TAS\\" + name;

	if (!fs::F_DirectoryExists(full_path)) {
		if (!fs::F_CreateDirectory(full_path)) {
			Com_Error(ERR_DISCONNECT, "unable to create the following directory: '%s'\n", full_path.c_str());
			return;
		}
	}
}
bool TAS::TAS_CheckAutoSave()
{
	if (!autosave)
		return false;

	auto cmd = cg::input->GetUserCmd(cg::input->cmdNumber - 1);
	if (!cmd)
		return false;

	if ((cmd->serverTime - 10000) >= autosave) //10 seconds after each change
		return true;

	return false;

}
void TAS::TAS_AutoSave()
{
	tas->cfile->save = new TAS_FileSystem_Out(tas->movement);



	if (tas->cfile->save->ok) {
		tas->cfile->save->write();
		Com_Printf(CON_CHANNEL_SUBTITLE, "saved...\n");
	}

	autosave = 0;

	delete tas->cfile->save;
}