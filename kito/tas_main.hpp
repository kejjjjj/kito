#pragma once

#ifndef _tasdata
#define _tasdata

#include "pch.h"


class TAS
{
public:
	TAS() = default;
	~TAS() = default;

	void Init();

	TAS_Movement movement;
	TAS_FileSystem filesystem;
	TAS_UI ui;

};

inline TAS* tas = 0;

#endif