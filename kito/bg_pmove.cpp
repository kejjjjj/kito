#include "pch.h"

void cg::Pmove(pmove_t* pm)
{

	//if (vars::et_pmove_fixed.enabled)
	//	pm->cmd.serverTime = ((pm->cmd.serverTime + (vars::et_pmove_msec.intValue < 2 ? 2 : vars::et_pmove_msec.intValue) - 1) / vars::et_pmove_msec.intValue) * vars::et_pmove_msec.intValue;

	float frametime = 1000.f / Dvar_FindMalleableVar("com_maxfps")->current.integer;
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
		memcpy(&pm->oldcmd, &pm->cmd, sizeof(pm->oldcmd));

	}

}
void cg::PM_AirMove(pmove_t* pm, pml_t* pml)
{

	if (tas->movement.waiting_for_creation) {
		tas->movement.create_first_segment(pm, pml);
	}

	return PM_AirMove_f(pm, pml);
}
void cg::PM_WalkMove(pmove_t* pm, pml_t* pml)
{
	//pm->ps->gravity = rand() % 800;

	if (tas->movement.waiting_for_creation) {
		tas->movement.create_first_segment(pm, pml);
	}

	return PM_WalkMove_f(pm, pml);

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

	//Mod_A_Strafebot(pm);

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