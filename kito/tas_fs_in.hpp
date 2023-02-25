#pragma once

#ifndef tas_fn_in
#define tas_fn_in

#include "pch.h"

struct TAS_FileSystem_In
{
	TAS_FileSystem_In(const std::string& file);
	~TAS_FileSystem_In() = default;

	bool ok = false;

	bool read();

private:
	
	std::optional<playerState_s> In_PlayerState();

	std::unique_ptr<std::fstream> f;

};

#endif