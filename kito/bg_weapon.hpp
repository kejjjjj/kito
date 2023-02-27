#pragma once

#ifndef bgweapon
#define bgweapon

#include "pch.h"

namespace cg
{
	std::vector<std::pair<WeaponDef*, int>> G_GetWeaponsList(playerState_s* ps);


}

#endif