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