#include "pch.h"


TAS_FileSystem_Out::TAS_FileSystem_Out(const TAS_Movement& src) : 
	data(std::make_unique<TAS_Movement>(src)), 
	f(new std::fstream)
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
	assert(ok != true);

	Out_PlayerState(std::make_unique<playerState_s>(data->entry.ps));
	
	return 1;
}

void TAS_FileSystem_Out::Out_PlayerState(const std::unique_ptr<playerState_s>& ps)
{
	DWORD base = (DWORD)ps.get();
	*f << "[\n";

	for (int i = 0; i < sizeof(playerState_s); i++) {
		*f << *(BYTE*)(base + i);
	}


	*f << ']';
}