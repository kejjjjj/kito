#include "pch.h"

void cg::Pmove(pmove_t* pm)
{


	return Pmove_f(pm);
	//if (vars::et_pmove_fixed.enabled)
	//	pm->cmd.serverTime = ((pm->cmd.serverTime + (vars::et_pmove_msec.intValue < 2 ? 2 : vars::et_pmove_msec.intValue) - 1) / vars::et_pmove_msec.intValue) * vars::et_pmove_msec.intValue;

	float frametime = 1000.f / 125;
	int _frametime = round(frametime);
	int pmove_msec = frametime;

	//if (pmove_fixed->current.enabled)
		pm->cmd.serverTime = ((pm->cmd.serverTime + (pmove_msec < 2 ? 2 : pmove_msec) - 1) / pmove_msec) * pmove_msec;
	//if (_frametime < 8)
	//	pm->cmd.serverTime += (8 - _frametime);

	//pm->cmd.serverTime += frametime;
	int finalTime = pm->cmd.serverTime;

	if (finalTime > pm->ps->commandTime + 1000) {
		pm->ps->commandTime = finalTime - 1000;
	}
	pm->numtouch = 0;

	while (pm->ps->commandTime != finalTime) {
		int msec;

		msec = finalTime - pm->ps->commandTime;

		//if (pmove_fixed->current.enabled) {
			if (msec > pmove_msec)
				msec = pmove_msec;
		//}
		//else {
		//	if (msec > 66)
		//		msec = 66;
		//}


		pm->cmd.serverTime = pm->ps->commandTime + msec;
		PmoveSingle(pm);
		VectorCopy(pm->ps->velocity, temp_velocity);
		memcpy(&pm->oldcmd, &pm->cmd, sizeof(pm->oldcmd));

	}

}
void cg::PM_AirMove(pmove_t* pm, pml_t* pml)
{

	if (tas->movement.waiting_for_creation) {
		tas->movement.create_first_segment(pm, pml);
	}
	pm_ptr = pm;
	pml_ptr = pml;

	//float yaw = CG_GetOptYaw(pm, pml);

	//if (yaw != -400) {
	//	pm->ps->viewangles[YAW] = yaw;
	//	AngleVectors(pm->ps->viewangles, pml->forward, pml->right, pml->up); //set viewangles

	//}

	PM_AirMove_f(pm, pml);
	VectorCopy(pm->ps->velocity, temp_velocity);

}
void cg::PM_WalkMove(pmove_t* pm, pml_t* pml)
{
	//pm->ps->gravity = rand() % 800;

	if (tas->movement.waiting_for_creation) {
		tas->movement.create_first_segment(pm, pml);
	}
	pm_ptr = pm;
	pml_ptr = pml;

	//float yaw = CG_GetOptYaw(pm, pml);

	//if (yaw != -400) {
	//	pm->ps->viewangles[YAW] = yaw;
	//	AngleVectors(pm->ps->viewangles, pml->forward, pml->right, pml->up); //set viewangles

	//}
	PM_WalkMove_f(pm, pml);
	VectorCopy(pm->ps->velocity, temp_velocity);

}
void cg::PM_UFOMove(pmove_t* pm, pml_t* pml)
{
	//pm->ps->gravity = rand() % 800;

	if (tas->movement.waiting_for_creation) {
		tas->movement.create_first_segment(pm, pml);
	}
	pm_ptr = pm;
	pml_ptr = pml;
	//VectorCopy(pm->ps->velocity, temp_velocity);
	return PM_UFOMove_f(pm, pml);
	

}
bool Mantle_FindMantleSurface(pmove_t* pm, trace_t* trace, float* normal, float* fwd)
{
	dvar_s* mantle_check_radius = Dvar_FindMalleableVar("mantle_check_radius");
	dvar_s* mantle_check_range = Dvar_FindMalleableVar("mantle_check_range");
	dvar_s* mantle_debug = Dvar_FindMalleableVar("mantle_debug");
	dvar_s* mantle_check_angle = Dvar_FindMalleableVar("mantle_check_angle");

	float* v4; // ecx
	playerState_s* v7; // edi
	int v8; // ecx
	char result; // al
	float angles[3]; // [esp+18h] [ebp-3Ch] BYREF
	float end[3]; // [esp+24h] [ebp-30h] BYREF
	float maxs[3]; // [esp+30h] [ebp-24h] BYREF
	float mins[3]; // [esp+3Ch] [ebp-18h] BYREF
	float start[3]; // [esp+48h] [ebp-Ch] BYREF
	float mantle_range; // [esp+58h] [ebp+4h]
	float mins_v; // [esp+5Ch] [ebp+8h]
	float prone_mins; // [esp+5Ch] [ebp+8h]
	float tracec; // [esp+5Ch] [ebp+8h]
	float traced; // [esp+5Ch] [ebp+8h]

	mins_v = -mantle_check_radius->current.value;
	mins[0] = mins_v;
	mins[1] = mins_v;
	v7 = pm->ps;
	mins[2] = 0.0;
	maxs[0] = mantle_check_radius->current.value;
	maxs[1] = mantle_check_radius->current.value;
	maxs[2] = 70.0;
	prone_mins = 15.0 - mantle_check_radius->current.value;
	mantle_range = mantle_check_range->current.value + prone_mins;
	angles[0] = *fwd;
	angles[1] = fwd[1];
	angles[2] = 0.0;
	VectorNormalize(angles);
	v8 = pm->handler;
	tracec = -prone_mins;
	start[0] = tracec * angles[0] + v7->origin[0];
	start[1] = angles[1] * tracec + v7->origin[1];
	start[2] = tracec * angles[2] + v7->origin[2];
	end[0] = angles[0] * mantle_range + v7->origin[0];
	end[1] = angles[1] * mantle_range + v7->origin[1];
	end[2] = angles[2] * mantle_range + v7->origin[2];

	pmoveHandler_t* handler = reinterpret_cast<pmoveHandler_t*>(0x06DA590);

	handler->trace(trace, start, mins, maxs, end, v7->clientNum, 0x1000000);
	
	if (trace->startsolid || trace->allsolid)
	{
		if (mantle_debug->current.enabled)
			Com_Printf(CON_CHANNEL_PLAYERWEAP, "%s\n", "Mantle Failed: Mantle brush is too thick");
		return 0;
	}
	if (1.0 == trace->fraction)
	{
		if (mantle_debug->current.enabled)
			Com_Printf(CON_CHANNEL_PLAYERWEAP, "%s\n", "Mantle Failed: No mantle surface found");
		return 0;
	}
	if ((trace->surfaceFlags & 0x6000000) != 0)
	{
		*normal = -trace->normal[0];
		normal[1] = -trace->normal[1];
		normal[2] = 0.0;
		if (VectorNormalize(normal) >= 0.00009999999747378752)
		{
			traced = normal[1] * angles[1] + *normal * angles[0] + normal[2] * angles[2];
			if (mantle_check_angle->current.value >= acos(traced) * 57.2957763671875)
			{
				//Com_Printf(CON_CHANNEL_SUBTITLE, "Mantle range!\n");
				result = 1;
			}
			else
			{
				Com_Printf(CON_CHANNEL_CONSOLEONLY, "Mantle Failed: Player is not facing mantle surface\n");
				result = 0;
			}
		}
		else
		{
			Com_Printf(CON_CHANNEL_CONSOLEONLY, "Mantle Failed: Mantle surface has vertical normal\n");
			result = 0;
		}
	}
	else
	{
		Com_Printf(CON_CHANNEL_CONSOLEONLY, "Mantle Failed: No mantle surface with MANTLE_ON or MANTLE_OVER found\n");
		result = 0;
	}

	return result;
}
bool Mantle_CheckLedge(MantleResults* r, pmove_t* pm, float height)
{
	char res{};
	__asm
	{
		//fld height;
		push height;
		mov ecx, pm;
		mov eax, r;
		mov esi, 0x5B2EB0;
		call esi;
		add esp, 0x4;
		mov res, al;
	}
	return res;

	//return res;
}
void cg::Mantle_Check(pmove_t* pm, pml_t* pml)
{
//	return Mantle_Check_f(pm, pml);

	//__asm mov pm, edi;
	//__asm mov pml, eax;
	playerState_s* ps;
	float normal[3]; // [esp+8h] [ebp-6Ch] BYREF
	trace_t trace;
	MantleResults mantle;

	pm->ps->mantleState.flags &= 0xFFFFFFEF;

	static dvar_s* mantle_enable = Dvar_FindMalleableVar("mantle_enable");

	if (mantle_enable->current.enabled) {

		ps = pm->ps;
		ps->mantleState.flags &= 0xFFFFFFF7;
		
		if (ps->pm_type < PM_DEAD)
		{
			if ((ps->pm_flags & PMF_MANTLE) != 0)
			{

			}
			else if ((ps->eFlags & 0xC) != 0) {

			}
			else
			{
				bool result = Mantle_FindMantleSurface(pm, &trace, normal, pml->forward);

				if (result)
				{
					memset(&mantle, 0, sizeof(MantleResults));
					mantle.dir[0] = normal[0];
					mantle.dir[1] = normal[1];
					mantle.dir[2] = normal[2];
					mantle.startPos[0] = ps->origin[0];
					mantle.startPos[1] = ps->origin[1];
					mantle.startPos[2] = ps->origin[2];
					if ((trace.surfaceFlags & 0x4000000) != 0)
						mantle.flags |= 1u;

					char result = Mantle_CheckLedge(&mantle, pm, 60.f);
					if (!result) {
						char result = Mantle_CheckLedge(&mantle, pm, 40.f);
						if (!result) 
							char result = Mantle_CheckLedge(&mantle, pm, 20.f);
					}
					//if (result) {
					//	Com_Printf(CON_CHANNEL_SUBTITLE, "very good!\n");
					//}
				}

			}

		}

	}

	return;
}
void cg::PM_FoliageSnd(pmove_t* pm)
{
	//playerState_s* ps = pm->ps;

	//dvar_s* bg_foliagesnd_minspeed = dvar_s::byName("bg_foliagesnd_minspeed");
	//dvar_s* bg_foliagesnd_maxspeed = dvar_s::byName("bg_foliagesnd_maxspeed");
	//dvar_s* bg_foliagesnd_fastinterval = dvar_s::byName("bg_foliagesnd_fastinterval");
	//dvar_s* bg_foliagesnd_slowinterval = dvar_s::byName("bg_foliagesnd_slowinterval");
	//dvar_s* bg_foliagesnd_resetinterval = dvar_s::byName("bg_foliagesnd_resetinterval");

	//if (pmove_mp->current.enabled) {
	//	Sys_SnapVector(ps->velocity);
	//}


	return;
}
void Sys_SnapVector(float* v) {

	int i;
	float f;

	f = *v;
	__asm fld f;
	__asm fistp i;
	*v = i;
	v++;
	f = *v;
	__asm fld f;
	__asm fistp i;
	*v = i;
	v++;
	f = *v;
	__asm fld f;
	__asm fistp i;
	*v = i;


}

//MISLEADING FUNCTION NAME!!!!!
void cg::PM_OverBounce(pmove_t* pm, pml_t* pml)
{

	vec3_t move;

	move[0] = pm->ps->origin[0] - pml->previous_origin[0];
	move[1] = pm->ps->origin[1] - pml->previous_origin[1];
	move[2] = pm->ps->origin[2] - pml->previous_origin[2];

	float dot = move[2] * move[2] + move[1] * move[1] + move[0] * move[0];
	float dot_div_frametime = dot / (pml->frametime * pml->frametime);
	float dot_speed = pm->ps->velocity[2] * pm->ps->velocity[2] + pm->ps->velocity[1] * pm->ps->velocity[1] + pm->ps->velocity[0] * pm->ps->velocity[0];

	if (dot_speed * 0.25 > dot_div_frametime)
	{
		//Com_Printf(CON_CHANNEL_OBITUARY, "possible overbounce!\n");
		float inGameFramesPerSecond = 1.0 / pml->frametime;
		pm->ps->velocity[0] = inGameFramesPerSecond * move[0];
		pm->ps->velocity[1] = inGameFramesPerSecond * move[1];
		pm->ps->velocity[2] = inGameFramesPerSecond * move[2];
	}

	float clampedFrametime = std::clamp(pml->frametime, 0.f, 1.f);

	float diffX = pm->ps->velocity[0] - pm->ps->oldVelocity[0];
	float diffY = pm->ps->velocity[1] - pm->ps->oldVelocity[1];

	float frameX = clampedFrametime * diffX;
	float frameY = clampedFrametime * diffY;

	pm->ps->oldVelocity[0] = pm->ps->oldVelocity[0] + frameX;
	pm->ps->oldVelocity[1] = pm->ps->oldVelocity[1] + frameY;


	return;

}
void cg::PM_Weapon_FireWeapon(int delay, playerState_s* ps)
{
	playerState_s* ps_copy;
	__asm mov ps_copy, eax;

	PM_Weapon_FireWeapon_f(delay, ps);

	static int firetime = 1;

	if (ps->weaponTime && firetime == 1) {
		firetime = ps->commandTime + ps->weaponTime;
	}
	if (tas->movement.called_from_prediction && ps->commandTime >= firetime && firetime != 1 /* && std::string(BG_WeaponNames[ps_copy->weapon]->szDisplayName).find("RPG") != std::string::npos */) {
		Com_Printf(CON_CHANNEL_SUBTITLE, "YEAH!\n");
		//ps_copy->velocity[2] += 1264;
		tas->movement.rpg_next_frame = true;

		firetime = 1;

	}

	//return PM_Weapon_FireWeapon_f(delay, ps);
}
void cg::PmoveSingle(pmove_t* pm)
{

	return PmoveSingle_f(pm);
}