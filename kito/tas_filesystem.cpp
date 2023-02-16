#include "pch.h"

TAS_FileSystem::TAS_FileSystem(const std::string& dname)
{
	if (!fs::F_isValidFileName(dname)) {
		std::cout << '"' << dname << "\" is not a valid filename!\n";
		Com_PrintError(CON_CHANNEL_SUBTITLE, "\"%s\" is not a valid filename!\n", dname.c_str());
		return;
	}

	display_name = dname;
	valid = true;

	TAS_CreateEssentialDirectories();

}

void TAS_FileSystem::TAS_CreateEssentialDirectories()
{

	const std::string full_path = fs::GetExePath() + "\\SP_TAS";

	TAS_FileSystem::TAS_CreateSubDirectory("");
	TAS_FileSystem::TAS_CreateSubDirectory("recordings");
	TAS_FileSystem::TAS_CreateSubDirectory("resources");
	TAS_FileSystem::TAS_CreateSubDirectory("resources\\fonts");

}
void TAS_FileSystem::TAS_CreateSubDirectory(const std::string& name)
{

	const std::string full_path = fs::GetExePath() + "\\SP_TAS\\" + name;

	if (!fs::F_DirectoryExists(full_path)) {
		if (!fs::F_CreateDirectory(full_path)) {
			Com_Error(ERR_DISCONNECT, "unable to create the following directory: '%s'\n", full_path.c_str());
			return;
		}
	}
}