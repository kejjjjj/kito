#include "pch.h"

void TAS_FileSystem::TAS_CreateDirectory()
{

	const std::string full_path = fs::GetExePath() + "\\SP_TAS";

	if (!fs::F_DirectoryExists(full_path)) {
		if (!fs::F_CreateDirectory(full_path)) {
			Com_Error(ERR_DISCONNECT, "unable to create the following directory: '%s'\n", full_path.c_str());
			return;
		}
	}
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