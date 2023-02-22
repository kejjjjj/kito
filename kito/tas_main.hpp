#pragma once

#ifndef _tasdata
#define _tasdata

#include "pch.h"


class TAS
{
public:
	TAS() = default;
	//~TAS() = default;

	void Init();

	TAS_Movement movement;
	TAS_FileSystem* filesystem;
	TAS_UI ui;
	TAS_Render render;


private:
	void TAS_SetupHardcodedFont();

	std::string name;
};

inline TAS* tas = 0;

#endif