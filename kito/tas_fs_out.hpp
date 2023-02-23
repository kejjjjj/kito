#pragma once

#ifndef tas_fs_
#define tas_fs_

#include "pch.h"

#define WRITE_INT() (*f << *(int*)base << '\n'), base += 4
#define WRITE_UINT() (*f << *(unsigned int*)base << '\n'), base += 4
#define WRITE_FLOAT() (*f << *(float*)base << '\n'), base += 4
#define WRITE_VEC2() (*f << *(float*)base << ',' << *(float*)(base+4) << '\n'), base += 8
#define WRITE_VEC3() (*f << *(float*)base << ',' << *(float*)(base+4) <<  ',' << *(float*)(base+8) << '\n'), base += 12


struct TAS_FileSystem_Out
{
	TAS_FileSystem_Out() = delete;
	TAS_FileSystem_Out(const TAS_Movement& src);
	~TAS_FileSystem_Out() { if(f)fs::F_CloseFile(*f); };
	
	bool write();

	bool ok = true;

private:
	
	void Out_PlayerState(const std::unique_ptr<playerState_s>& ps);


	int16_t indentation_depth = 0;
	std::unique_ptr<std::fstream> f;
	const std::unique_ptr<TAS_Movement> data;
	CHAR expected_character = '\0';
};

#endif