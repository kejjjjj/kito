#include "pch.h"


TAS_FileSystem_In::TAS_FileSystem_In(const std::string& file) : f(std::unique_ptr<std::fstream>(new std::fstream)), name(file)
{
	if (!fs::F_FileExists(file)) {
		Com_Printf(CON_CHANNEL_SUBTITLE, "!fs::F_FileExists(%s)\n", file.c_str());

		return;
	}

	if (!fs::F_OpenFile(*f, file, fs::fileopen::FILE_IN)) {
		Com_Printf(CON_CHANNEL_SUBTITLE, "!fs::F_OpenFile(*f, %s, fs::fileopen::FILE_IN)\n", file.c_str());
		return;

	}

	fs::F_Reset();

	ok = true;
}
std::optional<std::shared_ptr<TAS_Movement>> TAS_FileSystem_In::read()
{
	if (!ok)
		return std::nullopt;
	
	fs::F_Reset();

	std::shared_ptr<TAS_Movement> movement = std::shared_ptr<TAS_Movement>(new TAS_Movement);

	Com_Printf(CON_CHANNEL_SUBTITLE, "TAS_FileSystem_In::read(%s)\n", name.c_str());

	const auto ps = In_ReadBlock<playerState_s>();	
	if (!ps) return std::nullopt;

	const auto pm = In_ReadBlock<pmove_t>();
	if (!pm) return std::nullopt;

	const auto pml = In_ReadBlock<pml_t>();
	if (!pml) return std::nullopt;

	movement->entry.ps = ps.value();
	movement->entry.pm = pm.value();
	movement->entry.pml = pml.value();
	
	while (true) {
		if (!(read_seg = In_ReadSegment()))
			break;

		movement->segments.push_back(read_seg.value());
	}

	std::cout << "segments loaded: " << movement->segments.size() << '\n';

	return movement;


}
using namespace fs;
template<typename T>
std::optional<T> TAS_FileSystem_In::In_ReadBlock()
{
	T data{};

	char ch = F_Get(*f);
	if (ch != '[') {
		F_SyntaxError("std::optional<T> TAS_FileSystem_In::In_ReadBlock(): expected %c instead of %c", '[', ch);
		return std::nullopt;
	}
	size_t bytes_read = 0;
	DWORD base = (DWORD)(&data);
	do {
		std::string hex = "0x";

		for (int i = 0; i < 2; i++) {

			if (f->eof() || !f->good()) {
				F_SyntaxError("std::optional<T> TAS_FileSystem_In::In_ReadBlock(): unexpected end of file");
				return std::nullopt;
			}

			ch = F_Get(*f);

			if (bytes_read == sizeof(T) && ch != ']') {
				F_SyntaxError("bytes_read (%u) == sizeof(T) (%u) && ch != ']' (%c)", bytes_read, sizeof(T), ch);
				return std::nullopt;
			}

			else if (bytes_read == sizeof(T) && ch == ']') {
				F_Get(*f); //skip the newline
				return data;
			}

			if (!IsHex(ch)) {
				F_SyntaxError("std::optional<T> TAS_FileSystem_In::In_ReadBlock(): expected a hex character instead of %c", ch);
				return std::nullopt;
			}
			hex.push_back(ch);


		}
		//here it HAS to be from 0 to 255
		auto hex_byte = std::strtol(hex.c_str(), NULL, 0);
		*(BYTE*)base = (BYTE)hex_byte;

		base += 1;
		bytes_read++;

	} while (true);


	return data;
}
std::optional<segment_s> TAS_FileSystem_In::In_ReadSegment()
{
	segment_s data{};

	char ch = F_Get(*f);
	if (ch != '{') {

		if (std::isspace(ch) || f->eof() || !f->good())
			return std::nullopt;

		F_SyntaxError("std::optional<segment_s> TAS_FileSystem_In::In_ReadSegment(): expected %c instead of %c", '{', ch);
		return std::nullopt;
	}F_Get(*f); //skip newline

	auto options = In_ReadBlock<segment_options>();

	if (!options)
		return std::nullopt;

	data.options = options.value();

	auto framecount = In_ReadBlock<int>();

	if (!framecount)
		return std::nullopt;

	data.frame_count = framecount.value();

	std::cout << "framecount: " << data.frame_count << '\n';

	ch = F_Get(*f);
	if (ch != '}') {
		F_SyntaxError("std::optional<segment_s> TAS_FileSystem_In::In_ReadSegment(): expected %c instead of %c", '}', ch);
		return std::nullopt;
	}F_Get(*f); //skip newline

	ch = F_Get(*f);
	if (ch != '{') {
		F_SyntaxError("std::optional<segment_s> TAS_FileSystem_In::In_ReadSegment(): expected %c instead of %c", '{', ch);
		return std::nullopt;
	}F_Get(*f); //skip newline

	
	for (int i = 0; i < data.frame_count; i++) {

		auto cmd = In_ReadBlock<recorder_cmd>();
		if (!cmd) {
			return std::nullopt;
		}
		data.content.push_back(cmd.value());
	}

	ch = F_Get(*f);
	if (ch != '}') {
		F_SyntaxError("std::optional<segment_s> TAS_FileSystem_In::In_ReadSegment(): expected %c instead of %c", '}', ch);
		return std::nullopt;
	}F_Get(*f); //skip newline

	return data;
}