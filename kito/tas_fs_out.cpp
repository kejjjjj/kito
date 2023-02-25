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
	if (!ok)
		return false;

	Out_PlayerState(std::make_unique<playerState_s>(data->entry.ps));

	for (auto& seg : tas->movement.segments)
		Out_Segment(std::make_unique<segment_s>(seg));



	return 1;
}

void TAS_FileSystem_Out::Out_PlayerState(const std::unique_ptr<playerState_s>& ps)
{
	DWORD base = (DWORD)ps.get();
	*f << '[';
	for (int i = 0; i < sizeof(playerState_s); i+=1) {
		std::stringstream ss;
		std::string s;
		ss << std::hex << (int)(*(BYTE*)(base + i));

		if ((s = ss.str()).size() == 1)
			s.insert(s.begin(), '0');

		*f << s;

	}
	*f << "]\n";
}
void TAS_FileSystem_Out::Out_Segment(const std::unique_ptr<segment_s>& segment)
{
	
	*f << "{\n";

	indentation_depth = 1;

	std::string indent;

	for (int i = 0; i < indentation_depth; i++)
		indent.push_back('\t');

	*f << indent << segment->frame_count << '\n';
	*f << indent << (int)segment->forwardmove << '\n';
	*f << indent << (int)segment->rightmove << '\n';

	*f << indent << "{\n";
	++indentation_depth;
	indent.clear();

	for (int i = 0; i < indentation_depth; i++)
		indent.push_back('\t');

	DWORD base = (DWORD)(&segment->options);

	*f << indent;
	for (int j = 0; j < sizeof(segment_options); j++) {
		std::stringstream ss;
		std::string s;
		ss << std::hex << (int)(*(BYTE*)(base + j));

		if ((s = ss.str()).size() == 1)
			s.insert(s.begin(), '0');

		*f << s;
	}
	*f << '\n' << indent << "{\n";
	++indentation_depth;

	indent.clear();

	for (int i = 0; i < indentation_depth; i++)
		indent.push_back('\t');

	base = (DWORD)(&segment->content.front());

	for (auto& i : segment->content) {
		base = (DWORD)&i;
		*f << indent;
		for (int j = 0; j < sizeof(recorder_cmd); j++) {
			std::stringstream ss;
			std::string s;
			ss << std::hex << (int)(*(BYTE*)(base + j));

			if ((s = ss.str()).size() == 1)
				s.insert(s.begin(), '0');

			*f << s;
		}
		*f << '\n';
	}

	indent.pop_back();
	*f << indent << "}\n";

	indent.pop_back();
	*f << "\n" << indent << "}\n";



	indent.clear();


	*f << "}\n";


}