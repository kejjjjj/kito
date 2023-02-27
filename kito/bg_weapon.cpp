#include "pch.h"


std::vector<std::pair<WeaponDef*, int>>  cg::G_GetWeaponsList(playerState_s* ps)
{
	std::vector<std::pair<WeaponDef*, int>>  weapons;

	for (int i = 1; i < *bg_lastParsedWeaponIndex + 1; i++) {

		if (((1 << (i & 0x1F)) & ps->weapons[i >> 5]) != 0) {
			if(BG_WeaponNames[i])
				if(strlen(BG_WeaponNames[i]->szDisplayName) > 1)
					weapons.push_back(std::make_pair(BG_WeaponNames[i], i));
		}

	}
	return weapons;
}