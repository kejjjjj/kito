#pragma once

#ifndef sysmain_
#define sysmain_

#include "pch.h"

DWORD Sys_Milliseconds();
bool ValidNumber(const std::string_view& expr);
bool IsInteger(const std::string_view& expr);
#endif