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
	
	std::shared_ptr<TAS_Movement> movement = std::unique_ptr<TAS_Movement>(new TAS_Movement);

	Com_Printf(CON_CHANNEL_SUBTITLE, "TAS_FileSystem_In::read(%s)\n", name.c_str());

	auto ps = In_PlayerState();
	if (!ps) return std::nullopt;

	movement->entry.ps = ps.value();


	return movement;


}
using namespace fs;
std::optional<playerState_s> TAS_FileSystem_In::In_PlayerState()
{
	playerState_s ps{};

	char ch = F_Get(*f);
	bool stoploop = false;
	if (ch != '[') {
		Com_Error(ERR_DROP, "TAS_FileSystem_In::In_PlayerState(): expected %c instead of %c", '[', ch);
		return std::nullopt;
	}

	DWORD base = (DWORD)( & ps);
	do {
		std::string hex = "0x";

		for (int i = 0; i < 2; i++) {
			
			if (f->eof() || !f->good()) {
				Com_Error(ERR_DROP, "TAS_FileSystem_In::In_PlayerState(): unexpected end of file");
				return std::nullopt;
			}

			ch = F_Get(*f);

			if (ch == ']') {
				//std::cout << "{ " << ps.origin[0] <<  ", " << ps.origin[1] << ", " << ps.origin[2] << " }\n";
				return ps;
			}

			if (!IsHex(ch)) {
				Com_Error(ERR_DROP, "TAS_FileSystem_In::In_PlayerState(): expected a hex character instead of %c", ch);
				return std::nullopt;
			}
			hex.push_back(ch);
		}
		//here it HAS to be from 0 to 255
		auto hex_byte = std::strtol(hex.c_str(), NULL, 0);
		*(BYTE*)base = (BYTE)hex_byte;

		base += 1;


	} while (true);
}