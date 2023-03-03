#include "pch.h"


TAS_FileSystem_Out::TAS_FileSystem_Out(const TAS_Movement& src) : 
	data(std::make_unique<TAS_Movement>(src)), 
	f(std::unique_ptr<std::fstream>(new std::fstream))
{

	
	const dvar_s* mapname = Dvar_FindMalleableVar("mapname");

	if (!mapname) {
		Com_Printf(CON_CHANNEL_SUBTITLE, "unable to create the file because the mapname dvar does not exist!\n");
		return;
	}

	const size_t pos = tas->cfile->full_path.find_last_of('\\');
	const std::string directory = tas->cfile->full_path.substr(0, pos);
	//const std::string file_name = full_path.substr(pos + 1);

	fs::F_CreateDirectory(directory);


	if (!fs::F_CreateFile(tas->cfile->full_path)) {
		Com_Printf(CON_CHANNEL_SUBTITLE, "!fs::F_CreateFile(%s)\n", tas->cfile->full_path.c_str());
		return;
	}

	if (!fs::F_OpenFile(*f, tas->cfile->full_path, fs::fileopen::FILE_OUT)) {
		Com_Printf(CON_CHANNEL_SUBTITLE, "!fs::F_OpenFile(f, %s, fs::fileopen::FILE_OUT)\n", tas->cfile->full_path.c_str());
		return;
	}

	ok = true;

}
bool TAS_FileSystem_Out::write()
{
	if (!ok)
		return false;

	Out_WriteVersion();

	Out_DataBlock<playerState_s>(data->entry.ps);
	Out_DataBlock<pmove_t>(data->entry.pm);
	Out_DataBlock<pml_t>(data->entry.pml);


	for (auto& i : tas->movement.segments) {
		*f << "{\n";
		Out_DataBlock<segment_options>(i.options);
		Out_DataBlock<int>(i.frame_count);

		*f << "}\n";
		*f << "{\n";

		Out_Segment((i));

		*f << "}\n";
	}
	auto ext = fs::GetFileExtension(tas->cfile->full_path);
	auto copy = fs::removeFileExtension(tas->cfile->full_path, ext.size());
	fs::F_CloseFile(*f);
	//Sleep(5);

	try {
		if(fs::F_FileExists(copy + "_backup.kej"))
			std::filesystem::remove(copy + "_backup.kej");

		std::filesystem::copy(tas->cfile->full_path, copy + "_backup.kej");
	}
	catch (std::filesystem::filesystem_error& err) {
		Com_Printf(CON_CHANNEL_SUBTITLE, "^1backup failed: %s\n", err.what());
	}
	return 1;
}
void TAS_FileSystem_Out::Out_WriteVersion()
{
	*f << TAS_FS_FILEVERSION << '\n';
}
template<typename T>
void TAS_FileSystem_Out::Out_DataBlock(const T& data)
{
	DWORD base = (DWORD)&data;
	*f << '[';
	for (int i = 0; i < sizeof(T); i += 1) {
		std::stringstream ss;
		std::string s;
		ss << std::hex << (int)(*(BYTE*)(base + i));

		if ((s = ss.str()).size() == 1)
			s.insert(s.begin(), '0');

		*f << s;

	}
	*f << "]\n";

}
void TAS_FileSystem_Out::Out_Segment(const segment_s& segment)
{
	for(const auto& i : segment.content)
		Out_DataBlock(i);

}