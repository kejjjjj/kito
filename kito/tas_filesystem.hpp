#pragma once

#ifndef tasfs
#define tasfs

#include "pch.h"

enum class filemode_e
{
	FILE_IMPORT,
	FILE_EXPORT
};

class TAS_FileSystem
{
public:

	//TAS_FileSystem() = default;
	TAS_FileSystem(const std::string& dname);

	//TAS_FileSystem(const std::string_view& name, const filemode_e mode = filemode_e::FILE_EXPORT, void* data = 0);

	~TAS_FileSystem() = default;

	void TAS_CreateEssentialDirectories();
	void TAS_CreateSubDirectory(const std::string& name);

	bool valid = false;
	std::string display_name;

private:
	filemode_e fm = filemode_e::FILE_EXPORT;	

};

#endif