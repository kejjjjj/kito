#pragma once

#ifndef tasfs
#define tasfs

#include "pch.h"

#define RECORDING_DIRECTORY_MAP(mapname, x) (std::string(fs::GetExePath() + "\\SP_TAS\\recordings\\" + mapname + "\\" + x + ".kej"))
#define RECORDING_DIRECTORY() (std::string(fs::GetExePath() + "\\SP_TAS"))

enum class filemode_e
{
	FILE_IMPORT,
	FILE_EXPORT
};

class TAS_FileSystem
{
public:
	TAS_FileSystem() = delete;
	explicit TAS_FileSystem(const std::string& dname);
	~TAS_FileSystem() { /*delete f;*/ };

	bool valid = false;
	std::string display_name;
	std::string full_path;
	//bool save(const std::vector<segment_s>& data);

	TAS_FileSystem_Out* save;

	std::optional<int32_t> IO_ReadInt(std::fstream& f);
	std::optional<float> IO_ReadFloat(std::fstream& f);
	std::optional<fvec2> IO_ReadVector2(std::fstream& f);
	std::optional<fvec3> IO_ReadVector3(std::fstream& f);

private:
	filemode_e fm = filemode_e::FILE_EXPORT;	
	//std::fstream* f;

};

#endif