#include "pch.h"

TAS_FileSystem::TAS_FileSystem(const std::string& dname)/* : f(new std::fstream())*/
{

	if (!fs::F_isValidFileName(dname)) {
		std::cout << '"' << dname << "\" is not a valid filename!\n";
		Com_Printf(CON_CHANNEL_SUBTITLE, "\"%s\" is not a valid filename!\n", dname.c_str());
		return;
	}
	
	const dvar_s* mapname = Dvar_FindMalleableVar("mapname");

	if (!mapname) {
		Com_Printf(CON_CHANNEL_SUBTITLE, "unable to create the file because the mapname dvar does not exist!\n");
		return;
	}
	//fs::F_CreateFile(RECORDING_DIRECTORY_MAP(std::string(mapname->current.string), dname));

	display_name = dname;
	full_path =  RECORDING_DIRECTORY() + "\\recordings\\" + std::string(mapname->current.string) + "\\" + dname + ".kej";

	valid = true;

}
//bool TAS_FileSystem::save(const std::vector<segment_s>& data)
//{
//	std::fstream f;
//	const auto write_segment = [&f](const segment_s& seg) -> void
//	{
//		f << '{';
//
//	};
//
//	const dvar_s* mapname = Dvar_FindMalleableVar("mapname");
//
//	if (!mapname) {
//		Com_Printf(CON_CHANNEL_SUBTITLE, "unable to create the file because the mapname dvar does not exist!\n");
//		return false;
//	}
//
//	const size_t pos = full_path.find_last_of('\\');
//	const std::string directory = full_path.substr(0, pos);
//	//const std::string file_name = full_path.substr(pos + 1);
//
//	fs::F_CreateDirectory(directory);
//
//
//	if (!fs::F_CreateFile(full_path)) {
//		Com_Printf(CON_CHANNEL_SUBTITLE, "!fs::F_CreateFile(%s)\n", full_path.c_str());
//		return false;
//	}
//	
//
//	if (!fs::F_OpenFile(f, full_path, fs::fileopen::FILE_OUT)) {
//		Com_Printf(CON_CHANNEL_SUBTITLE, "!fs::F_OpenFile(f, %s, fs::fileopen::FILE_OUT)\n", full_path.c_str());
//		return false;
//	}
//	for (const auto& i : data) {
//
//		//f << '(' << i.serverTime << ')';
//		//f << '(' << i.angles[PITCH] << ',' << i.angles[YAW] << ',' << i.angles[ROLL] << ')';
//		//f << '(' << i.buttons << ")";
//		//f << '(' << (int)i.forwardmove << ")(" << (int)i.rightmove << ')';
//		//f << '(' << i.FPS << ")\n";
//		
//	
//	}
//
//	fs::F_CloseFile(f);
//
//	return true;
//}

//using namespace fs;
//std::optional<int32_t> TAS_FileSystem::IO_ReadInt(std::fstream& f)
//{
//	char ch = file.current_character;
//
//	while (std::isspace(ch)) {
//		ch = F_Get(f);
//	}
//
//	if (ch != '{') {
//		F_SyntaxError("IO_ReadInt: couldn't find '{', found '%c' instead", ch);
//		return std::nullopt;
//	}
//
//	const auto current_str = F_ReadUntil(f, '}');
//
//	if (!current_str) {
//		F_SyntaxError("IO_ReadInt: no value for key");
//		return std::nullopt;
//	}
//
//	if (!IsInteger(current_str.value())) {
//		F_SyntaxError("IO_ReadInt: value for key is not an integer ['%s']", current_str.value().c_str());
//		return std::nullopt;
//	}
//
//	return std::stoi(current_str.value());
//
//}
//std::optional<float> TAS_FileSystem::IO_ReadFloat(std::fstream& f)
//{
//	char ch = file.current_character;
//
//	while (std::isspace(ch)) {
//		ch = F_Get(f);
//	}
//
//	if (ch != '{') {
//		F_SyntaxError("IO_ReadFloat: couldn't find '{', found '%c' instead", ch);
//		return std::nullopt;
//	}
//
//	const auto current_str = F_ReadUntil(f, '}');
//
//	if (!current_str) {
//		F_SyntaxError("IO_ReadFloat: no value for key");
//		return std::nullopt;
//	}
//
//	if (!ValidNumber(current_str.value())) {
//		F_SyntaxError("IO_ReadFloat: value for key is not a number ['%s']", current_str.value().c_str());
//		return std::nullopt;
//	}
//
//	return std::stof(current_str.value());
//}
//std::optional<fvec2> TAS_FileSystem::IO_ReadVector2(std::fstream& f)
//{
//	char ch = file.current_character;
//	while (std::isspace(ch)) {
//		ch = F_Get(f);
//	}
//}
//std::optional<fvec3> TAS_FileSystem::IO_ReadVector3(std::fstream& f)
//{
//	fvec3 v;
//	char ch = file.current_character;
//
//	while (std::isspace(ch)) {
//		ch = F_Get(f);
//	}
//
//	////////////////////
//	//first component//
//	//////////////////
//	if (ch != '{') {
//		F_SyntaxError("IO_ReadFloat: couldn't find '{', found '%c' instead", ch);
//		return std::nullopt;
//	}
//
//	auto current_str = F_ReadUntil(f, ',');
//
//	if (!current_str) {
//		F_SyntaxError("IO_ReadFloat: no value for key[0]");
//		return std::nullopt;
//	}
//
//	if (!ValidNumber(current_str.value())) {
//		F_SyntaxError("IO_ReadFloat: value for key is not a number ['%s']", current_str.value().c_str());
//		return std::nullopt;
//	}
//	v.x = std::stof(current_str.value());
//
//	/////////////////////
//	//second component//
//	///////////////////
//	current_str = F_ReadUntil(f, ',');
//
//	if (!current_str) {
//		F_SyntaxError("IO_ReadFloat: no value for key[0]");
//		return std::nullopt;
//	}
//
//	if (!ValidNumber(current_str.value())) {
//		F_SyntaxError("IO_ReadFloat: value for key[2] is not a number ['%s']", current_str.value().c_str());
//		return std::nullopt;
//	}
//
//	v.y = std::stof(current_str.value());
//
//	////////////////////
//	//third component//
//	//////////////////
//
//	current_str = F_ReadUntil(f, ',');
//
//	if (!current_str) {
//		F_SyntaxError("IO_ReadFloat: no value for key[0]");
//		return std::nullopt;
//	}
//
//	if (!ValidNumber(current_str.value())) {
//		F_SyntaxError("IO_ReadFloat: value for key[2] is not a number ['%s']", current_str.value().c_str());
//		return std::nullopt;
//	}
//
//	v.z = std::stof(current_str.value());
//
//	return v;
//
//}