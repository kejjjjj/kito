#include "pch.h"


TAS_FileSystem_In::TAS_FileSystem_In(const std::string& file) : f(new std::fstream())
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
bool TAS_FileSystem_In::read()
{
	if (!ok)
		return false;

	auto ps = In_PlayerState();



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
		std::stringstream ss;
		std::string hex;

		for (int i = 0; i < 2; i++) {
			ch = F_Get(*f);

			if (ch == ']') {
				return ps;
			}

			if (!IsHex(ch)) {
				Com_Error(ERR_DROP, "TAS_FileSystem_In::In_PlayerState(): expected a hex character instead of %c", '[', ch);
				return std::nullopt;
			}
			hex.push_back(ch);
		}
		//here it HAS to be from 0 to 255
		std::cout << hex << " -> ";
		ss << std::strtol(hex.c_str(), NULL, 0);
		std::cout << ss.str() << '\n';
		break;


	} while (true);


}