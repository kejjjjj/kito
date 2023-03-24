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
	TAS_UI ui;
	TAS_Render render;

	std::list<TAS_FileSystem> filesystem;
	std::unique_ptr<TAS_FileSystem> cfile;

	std::vector<std::pair<ImFont*, const char*> > fonts;
	std::optional<ImFont*> FetchFont(const char* name);

	int autosave = 0;
	bool fonts_loaded = false;
	bool TAS_CheckAutoSave();
	void TAS_AutoSave();

private:
	void TAS_SetupHardcodedFont();
	void TAS_CreateEssentialDirectories();
	void TAS_CreateSubDirectory(const std::string& name);
	void TAS_LoadFont(const char* _name, const std::string& name, float scale = 24.f);

	std::string name;
};

inline TAS* tas = 0;

#endif