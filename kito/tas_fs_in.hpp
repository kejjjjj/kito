#pragma once

#ifndef tas_fn_in
#define tas_fn_in

#include "pch.h"

struct TAS_FileSystem_In
{
	TAS_FileSystem_In(const std::string& file);
	~TAS_FileSystem_In() = default;

	bool ok = false;

	std::optional<std::shared_ptr<TAS_Movement>> read();

private:
	
	TAS_Movement movement;

	void In_ReadVersion();

	template<typename T>
	std::optional<T> In_ReadBlock(size_t amount_of_bytes = 0);
	std::optional<segment_s> In_ReadSegment();

	std::unique_ptr<std::fstream> f;
	std::string name;
	std::optional<segment_s> read_seg;

	int version = 0;
};

#endif